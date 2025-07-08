#include "BehaviorTreeUtility.h"

#include "imgui.h"
#include "imnodes.h"
#include "DxLib.h"

#include <set>

BehaviorTreeGraph::BehaviorTreeGraph(bool is_edit_mode)
	: mIsEditMode{ is_edit_mode }
{
	initialize();
}

BehaviorTreeGraph::~BehaviorTreeGraph()
{
}

void BehaviorTreeGraph::initialize()
{
	mNodeNames = get_all_node_names();
}

void BehaviorTreeGraph::update()
{
	if (!mIsEditMode) return;

	// 選択している要素の更新
	update_selected();

	// リンク作成
	update_links();

	// ノードの位置を更新
	update_node_pos();

	// キー入力を更新
	update_input_key();
}

void BehaviorTreeGraph::draw()
{
	ImGui::Begin("Behavior Tree Editor");
	{
		// ツールバーの描画
		draw_toolbar();

		// ツリー描画
		draw_editor();
	}
	ImGui::End();
}

void BehaviorTreeGraph::change_mode(bool is_edit_mode)
{
	mIsEditMode = is_edit_mode;
}

void BehaviorTreeGraph::select_load_file()
{
#if defined(_WIN32)
	OPENFILENAMEA ofn = { 0 };
	char szFile[MAX_PATH] = { 0 };	// ファイルパスのサイズはWindows既定のものに
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "JSON Files\0*.json\0All Files\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST;

	if (GetOpenFileNameA(&ofn))
	{
		mLoadFileName = szFile;
		import_json(szFile);
	}
#endif
}

void BehaviorTreeGraph::draw_toolbar()
{
	if (!mIsEditMode) return;

	// ノード追加ボタン
	draw_add_button();

	// 削除ボタン
	draw_delete_button();

	ImGui::NewLine();
	// ファイル書き出し
	draw_export_button();
	ImGui::SameLine();

	// ファイル読み込み
	draw_import_button();
}

void BehaviorTreeGraph::draw_editor()
{
	ImNodes::BeginNodeEditor();
	{
		// ミニマップを描画
		ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_TopRight);
		// ノード描画
		draw_nodes();
		// リンクの描画
		draw_links();
	}
	ImNodes::EndNodeEditor();
}

void BehaviorTreeGraph::set_runnning_node_id(const int running_node_id)
{
	// 実行中のノード/リンクのリストを更新
	mRunningLinks.clear();
	mRunningNodes.clear();

	get_nodes_related_all_links(running_node_id, &mRunningLinks);
	get_nodes_related_all_nodes(running_node_id, &mRunningNodes);
}

int BehaviorTreeGraph::add_node(NodeName name)
{
	// IDの重複を避ける
	while (mNodes.find(mNextId) != mNodes.end())
	{
		mNextId++;
	}

	int id = mNextId;

	// NodeNameからノードタイプを取得
	NodeType type = NODE_MAP[name];

	mNodes[id] = BTNode{ id, type, name, {} };
	return id;
}

void BehaviorTreeGraph::remove_node(int id)
{
	auto it = mNodes.find(id);
	if (it != mNodes.end())
	{
		// 子ノードの親を解除
		for (int child_id : it->second.children)
		{
			mNodes[child_id].parent = -1;
		}

		// 親ノードの子ノードを削除
		if (it->second.parent != -1)
		{
			auto& parent_node = mNodes[it->second.parent];
			auto it_child = std::find(parent_node.children.begin(), parent_node.children.end(), id);
			if (it_child != parent_node.children.end())
			{
				parent_node.children.erase(it_child);
			}
		}
		mNodes.erase(it);
	}
}

void BehaviorTreeGraph::remove_node(const std::vector<int>& delete_list)
{
	for (int node_id : delete_list)
	{
		auto it = mNodes.find(node_id);
		if (it != mNodes.end())
		{
			remove_node(node_id);
		}
	}
}

void BehaviorTreeGraph::add_link(int start_attr, int end_attr)
{
	int parent_id = start_attr >> cInputBit;
	int child_id = end_attr >> cInputBit;
	int pin_type = start_attr & 0xFFFF; // 下位16ビット

	// 下位16ビットが1ならTrueピン、2ならFalseピン
	bool is_true_branch = (pin_type == cTruePinBit);

	if (is_link_addable(mNodes[parent_id], mNodes[child_id], is_true_branch))
	{
		if (mNodes[parent_id].type == NodeType::Branch)
		{
			if (is_true_branch)
			{
				mNodes[parent_id].true_child = child_id;
			}
			else
			{
				mNodes[parent_id].false_child = child_id;
			}
		}
		else
		{
			mNodes[parent_id].children.push_back(child_id);
		}
		mNodes[child_id].parent = parent_id;

		add_link_tuple(parent_id, child_id, is_true_branch);
	}
}

void BehaviorTreeGraph::add_link_tuple(int parent_id, int child_id, bool is_true_branch)
{
	int pin_type = is_true_branch ? cTruePinBit : cFalsePinBit;
	mNodeLinks[mCreatedLinkId] = std::make_tuple(parent_id, child_id, pin_type);
	mCreatedLinkId++;
}

std::vector<std::string> BehaviorTreeGraph::get_all_node_names() const
{
	std::vector<std::string> node_names;
	// Enumを回す
	for (int i = 0; i < static_cast<int>(NodeName::NameEnd); ++i)
	{
		NodeName node_name = static_cast<NodeName>(i);
		std::string name = std::string(NAMEOF_ENUM(node_name));
		node_names.push_back(name);
	}

	return node_names;
}

void BehaviorTreeGraph::reset_selected()
{
	mSelectedNodes.clear();
	mSelectedLinks.clear();

	ImNodes::ClearNodeSelection();
	ImNodes::ClearLinkSelection();
}

bool BehaviorTreeGraph::get_selected_nodes_related_links(std::vector<int>* links)
{
	for (int node_id : mSelectedNodes)
	{
		get_nodes_related_links(node_id, links);
	}

	return links->size() > 0;
}

bool BehaviorTreeGraph::get_nodes_related_links(const int node_id, std::vector<int>* links, bool contain_child)
{
	for (const auto& link_pair : mNodeLinks)
	{
		if (is_related_links(node_id, link_pair, contain_child))
		{
			links->push_back(link_pair.first);
		}
	}

	return links->size() > 0;
}

bool BehaviorTreeGraph::get_nodes_related_all_links(const int node_id, std::vector<int>* links)
{
	int current_id = node_id;

	// ルートノードに到達するまで続ける
	while (current_id != -1)
	{
		get_nodes_related_links(current_id, links, false);

		// 親ノードへさかのぼって再度探索
		auto it = get_node(current_id);
		current_id = it.parent;
	}
	return !links->empty();
}

bool BehaviorTreeGraph::get_nodes_related_all_nodes(const int node_id, std::vector<int>* nodes)
{
	int current_id = node_id;
	nodes->push_back(current_id);

	// ルートノードに到達するまで続ける
	while (current_id != -1)
	{
		for (const auto& node : mNodes)
		{
			if (is_related_nodes(current_id, node))
			{
				nodes->push_back(node.first);
			}
		}

		// 親ノードへさかのぼって探索
		auto it = get_node(current_id);
		current_id = it.parent;
	}

	return !nodes->empty();
}

bool BehaviorTreeGraph::is_related_links(const int node_id, const std::pair<int, std::tuple<int, int, int>>& node_link, bool contain_child)
{
	int link_id = node_link.first;
	int parent_id = std::get<0>(node_link.second);
	int child_id = std::get<1>(node_link.second);

	if (child_id == node_id) 
	{
		return true;
	}

	if (contain_child)
	{
		if (parent_id == node_id)
		{
			return true;
		}
	}

	return false;
}

bool BehaviorTreeGraph::is_related_nodes(const int node_id, const std::pair<const int, const BTNode>& node)
{

	int id = node.first;
	const auto node_type = node.second.type;

	// 葉ノードの場合は子ノードを持たないためfalse
	if (node_type == NodeType::Leaf) return false;

	// ブランチノードの場合
	if (node_type == NodeType::Branch)
	{
		// true, falseどちらもnode_idと一致しなければfalse
		if (!(node.second.true_child == node_id || node.second.false_child == node_id))
		{
			return false;
		}
	}

	// それ以外の子ノードを持つノードの場合(Composite, Decorator)
	if (node_type == NodeType::Composite || node_type == NodeType::Decorator)
	{
		const auto& children = node.second.children;
		bool found = false;

		for (const auto& child : children)
		{
			if (child == node_id)
			{
				found = true;
			}
		}

		if (!found) return false;
	}

	return true;
}

bool BehaviorTreeGraph::is_link_addable(BTNode& parent_node, BTNode& child_node, bool is_true_branch)
{
	// すでに親ノードを持っていたらfalseを返す
	if (child_node.parent != -1) return false;

	if (parent_node.type == NodeType::Decorator)
	{
		// Decoratorは持てる子ノードは一つだけ
		// もしすでに子ノードを持っていたら追加できない
		if (parent_node.children.size() > 0)
		{
			return false;
		}
	}
	else if (parent_node.type == NodeType::Branch)
	{
		// Branchは持てる子ノードはTrue,Falseでそれぞれ一つだけ
		// もし既に子ノードを持っていたら追加できない
		if (is_true_branch)
		{
			if (parent_node.true_child != -1)
			{
				return false;
			}
		}
		else
		{
			if (parent_node.false_child != -1)
			{
				return false;
			}
		}
	}

	return true;
}

void BehaviorTreeGraph::remove_nodes_link(int parent_id, int child_id)
{
	auto& parent_node = mNodes[parent_id];
	auto& child_node = mNodes[child_id];
	if (parent_node.type == NodeType::Branch)
	{
		if (parent_node.true_child == child_id)
		{
			parent_node.true_child = -1;
		}
		else if (parent_node.false_child == child_id)
		{
			parent_node.false_child = -1;
		}
	}
	else
	{
		auto it = std::find(parent_node.children.begin(), parent_node.children.end(), child_id);
		if (it != parent_node.children.end())
		{
			parent_node.children.erase(it);
		}
	}
	child_node.parent = -1;
}

void BehaviorTreeGraph::delete_link(int id)
{
	mNodeLinks.erase(id);
}

void BehaviorTreeGraph::delete_link(const std::vector<int>& delete_list)
{
	for (int link_id : delete_list)
	{
		auto it = mNodeLinks.find(link_id);
		if (it != mNodeLinks.end())
		{
			int parent_id = std::get<0>(it->second);
			int child_id = std::get<1>(it->second);
			remove_nodes_link(parent_id, child_id);
			delete_link(it->first);
		}
	}
}

void BehaviorTreeGraph::export_json(const std::string& file_name) {
	using std::swap;

	const int cJsonIndent = 4;

	json j;

	for (const auto& pair : mNodes)
	{
		const BTNode& node = pair.second;
		json node_json;
		node_json["id"] = node.id;
		node_json["type"] = static_cast<int>(node.type);
		node_json["name"] = NAMEOF_ENUM(node.name);
		node_json["parent"] = node.parent;

		if (node.type == NodeType::Branch)
		{
			node_json["true_child"] = node.true_child;
			node_json["false_child"] = node.false_child;
		}
		else
		{
			// 書き出しする前に、y座標が小さい順に並び変える
			auto children = node.children;

			std::sort(children.begin(), children.end(),
				[&](int a, int b) {
					return mNodes[a].pos_y < mNodes[b].pos_y;
				});


			node_json["children"] = children;
		}

		// ノード固有の値
		if (node.wait_time != -1.f)
		{
			node_json["wait_time"] = node.wait_time;
		}

		if (node.limit_distance != -1.f)
		{
			node_json["limit_distance"] = node.limit_distance;
		}

		node_json["pos_x"] = node.pos_x;
		node_json["pos_y"] = node.pos_y;

		j.push_back(node_json);
	}
	std::ofstream file(file_name);
	if (file.is_open()) {
		file << j.dump(cJsonIndent);
		file.close();
	}
}

void BehaviorTreeGraph::import_json(const std::string& file_name)
{
	reset_selected();

	std::ifstream file(file_name);
	if (!file.is_open()) return;

	json j;
	file >> j;
	mNodes.clear();
	mNodeLinks.clear();
	mNextId = 1;
	for (const auto& node_json : j)
	{
		int id = node_json["id"];
		NodeType type = static_cast<NodeType>(node_json["type"]);
		NodeName name = get_matching_node_name(node_json["name"].get<std::string>());
		int parent = node_json["parent"];
		BTNode node{ id, type, name, {}, parent };
		if (type == NodeType::Branch)
		{
			node.true_child = node_json["true_child"];
			node.false_child = node_json["false_child"];
		}
		else
		{
			node.children = node_json["children"].get<std::vector<int>>();
		}
		if (node_json.contains("wait_time"))
		{
			node.wait_time = node_json["wait_time"];
		}
		if (node_json.contains("limit_distance"))
		{
			node.limit_distance = node_json["limit_distance"];
		}

		node.pos_x = node_json["pos_x"];
		node.pos_y = node_json["pos_y"];

		mNodes[id] = node;

		// リンク作成
		// childrenが空でない場合はリンク
		if (node.children.size() != 0)
		{
			for (int i = 0; i < node.children.size(); ++i)
			{
				add_link_tuple(id, node.children[i], true);
			}
		}

		// true_child, false_childが空でない場合はリンク
		if (node.true_child != -1)
		{
			add_link_tuple(id, node.true_child, true);
		}

		if (node.false_child != -1)
		{
			add_link_tuple(id, node.false_child, false);
		}
	}
	mNextId = static_cast<int>(mNodes.size()) + 1;
	file.close();
}

void BehaviorTreeGraph::set_node_pos(int id, float x, float y)
{
	auto it = mNodes.find(id);
	if (it != mNodes.end())
	{
		it->second.pos_x = x;
		it->second.pos_y = y;
	}
}

BTNode& BehaviorTreeGraph::get_node(int id)
{
	auto it = mNodes.find(id);
	if (it != mNodes.end()) {
		return it->second;
	}

	throw std::runtime_error("Node not found");
}

NodeName BehaviorTreeGraph::get_matching_node_name(std::string name)
{
	for (int i = 0; i < static_cast<int>(NodeName::NameEnd); ++i)
	{
		NodeName node_name = static_cast<NodeName>(i);
		std::string node_name_string = std::string(NAMEOF_ENUM(node_name));
		if (name == node_name_string)
		{
			return node_name;
		}
	}
	return NodeName::WaitLeaf;
}

const int BehaviorTreeGraph::get_selected_node(int index)
{
	return mSelectedNodes[index];
}

void BehaviorTreeGraph::update_selected()
{
	// 選択しているノードを保持
	int selected_node_num = ImNodes::NumSelectedNodes();
	mSelectedNodes.resize(selected_node_num);
	if (selected_node_num > 0)
	{
		ImNodes::GetSelectedNodes(mSelectedNodes.data());
	}

	// 選択しているリンクを保持しておく
	int selected_link_num = ImNodes::NumSelectedLinks();
	mSelectedLinks.resize(selected_link_num);
	if (selected_link_num > 0)
	{
		ImNodes::GetSelectedLinks(mSelectedLinks.data());
	}
}

void BehaviorTreeGraph::update_links()
{
	int start_attr, end_attr;
	if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
	{
		add_link(start_attr, end_attr);
	}
}

void BehaviorTreeGraph::update_node_pos()
{
	for (int i = 0; i < mSelectedNodes.size(); ++i)
	{
		int node_id = mSelectedNodes[i];
		ImVec2 pos = ImNodes::GetNodeGridSpacePos(node_id);
		set_node_pos(node_id, pos.x, pos.y);
	}
}

void BehaviorTreeGraph::update_input_key()
{
	// もしdeleteキーが押されたら選択している要素を削除
	if (CheckHitKey(KEY_INPUT_DELETE))
	{
		delete_selected_items();
	}
}

void BehaviorTreeGraph::draw_add_button()
{
	if (!mNodeNames.empty())
	{
		const char* combo_preview_value = mNodeNames[mSelectedAddNode].c_str();
		if (ImGui::BeginCombo(u8" ", combo_preview_value))
		{
			for (int n = 0; n < mNodeNames.size(); n++)
			{
				const bool is_selected = (mSelectedAddNode == n);
				if (ImGui::Selectable(mNodeNames[n].c_str(), is_selected))
				{
					mSelectedAddNode = n;
				}

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
	}
	else
	{
		ImGui::TextDisabled(u8"追加できるノードが見つかりませんでした");
	}

	ImGui::SameLine();

	// ノードの追加ボタン
	if (ImGui::Button(u8"追加"))
	{
		NodeName node_name = get_matching_node_name(mNodeNames[mSelectedAddNode]);
		add_node(node_name);
	}
}

void BehaviorTreeGraph::draw_export_button()
{
	// ファイル保存ダイアログを使って保存先とファイル名を指定
	if (ImGui::Button(u8"Json出力"))
	{
#if defined(_WIN32)
		OPENFILENAMEA ofn = { 0 };
		char szFile[MAX_PATH] = { 0 };	// ファイルパスのサイズはWindows既定のものに
		ofn.lStructSize = sizeof(ofn);
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "JSON Files\0*.json\0All Files\0*.*\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrDefExt = "json";
		ofn.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;

		if (GetSaveFileNameA(&ofn))
		{
			export_json(szFile);
		}
#endif
	}
}

void BehaviorTreeGraph::draw_import_button()
{
	if (ImGui::Button(u8"Json読込"))
	{
		select_load_file();
	}
}

void BehaviorTreeGraph::draw_delete_button()
{
	// 何も選択していなければ削除ボタンを無効化
	const bool can_delete = (mSelectedLinks.size() > 0) || (mSelectedNodes.size() > 0);

	ImGui::BeginDisabled(!can_delete);
	if (ImGui::Button(u8"選択中の要素を削除"))
	{
		delete_selected_items();
	}
	ImGui::EndDisabled();
}

void BehaviorTreeGraph::delete_selected_items()
{
	// 削除しようとしているノードに関連するリンクを洗い出す
	std::vector<int> links_to_remove;
	bool is_get_related_links = get_selected_nodes_related_links(&links_to_remove);
	if (is_get_related_links)
	{
		// 上で洗い出したリンクを削除
		delete_link(links_to_remove);
	}

	// 選択しているノードを削除
	remove_node(mSelectedNodes);

	// 選択しているリンクを削除(まだ残っている場合)
	delete_link(mSelectedLinks);

	// 選択解除
	reset_selected();
}

void BehaviorTreeGraph::draw_nodes()
{
	// ノードの位置を更新
	for (auto& [id, node] : mNodes) {
		ImNodes::SetNodeGridSpacePos(id, ImVec2(node.pos_x, node.pos_y));
	}

	std::set<int> selected_node_set(mSelectedNodes.begin(), mSelectedNodes.end());
	for (auto& pair : mNodes)
	{
		// 各ノードを描画
		auto& node = pair.second;
		bool is_selected = selected_node_set.count(node.id) > 0;
		draw_node(node, pair.first, is_selected);
	}
}

void BehaviorTreeGraph::draw_node(const BTNode& node, int node_id, bool is_selected)
{
	if (std::find(mRunningNodes.begin(), mRunningNodes.end(), node_id) != mRunningNodes.end())
	{
		ImNodes::PushColorStyle(ImNodesCol_TitleBar, cRunningColor);
	}
	else
	{
		ImNodes::PushColorStyle(ImNodesCol_TitleBar, cNodeColors.at(node.type));
	}

	ImNodes::BeginNode(node.id);
	{
		// タイトル
		draw_title(node);

		// 入力ピン
		draw_input_pin(node);

		// 出力ピン
		draw_output_pin(node, is_selected);

		// パラメータ表示
		draw_parameter(node, node_id, is_selected);
	}
	ImNodes::EndNode();

	ImNodes::PopColorStyle();
}

void BehaviorTreeGraph::draw_title(const BTNode& node)
{
	ImNodes::BeginNodeTitleBar();
	ImGui::Text(node.GetString().c_str());
	ImNodes::EndNodeTitleBar();
}

void BehaviorTreeGraph::draw_input_pin(const BTNode& node)
{
	ImNodes::BeginInputAttribute(node.id << cInputBit);
	ImGui::Text("");
	ImNodes::EndInputAttribute();
}

void BehaviorTreeGraph::draw_output_pin(const BTNode& node, bool is_selected)
{
	if (node.type == NodeType::Branch)
	{
		ImNodes::BeginOutputAttribute(node.id << cInputBit | cTruePinBit);

		if (is_selected)
		{
			ImGui::Text("True");
		}
		else
		{
			ImGui::Text("o");
		}
		ImNodes::EndOutputAttribute();

		ImNodes::BeginOutputAttribute(node.id << cInputBit | cFalsePinBit);
		if (is_selected)
		{
			ImGui::Text("False");
		}
		else
		{
			ImGui::Text("x");
		}
		ImNodes::EndOutputAttribute();
	}
	else if (node.type != NodeType::Leaf)
	{
		ImGui::SameLine();
		ImNodes::BeginOutputAttribute(node.id << cInputBit | cTruePinBit);
		ImGui::Text("");
		ImNodes::EndOutputAttribute();
	}
}

void BehaviorTreeGraph::draw_parameter(const BTNode& node, int node_id, bool is_selected)
{
	if (node.name == NodeName::WaitLeaf)
	{
		if (is_selected && mIsEditMode)
		{
			ImGui::Text(u8"WaitTime(フレーム数)");
			ImGui::SetNextItemWidth(200);

			float wait_time = node.wait_time;
			ImGui::InputFloat("", &wait_time);
			set_wait_time(node_id, wait_time);
		}
		else
		{
			ImGui::Text("WaitTime: %.1f", node.wait_time);
		}
	}
	else if (node.name == NodeName::CheckFarPlayer ||
		node.name == NodeName::CheckNearPlayer)
	{
		if (is_selected && mIsEditMode)
		{
			ImGui::Text(u8"最大/最小範囲");
			ImGui::SetNextItemWidth(200);

			float limit_distance = node.limit_distance;
			ImGui::InputFloat("", &limit_distance);
			set_limit_distance(node_id, limit_distance);
		}
		else
		{
			ImGui::Text(u8"範囲: %.1f", node.limit_distance);
		}
	}
}

void BehaviorTreeGraph::draw_links()
{
	for (auto& pair : mNodeLinks)
	{
		int link_id = pair.first;
		if (std::find(mRunningLinks.begin(), mRunningLinks.end(), link_id) != mRunningLinks.end())
		{
			ImNodes::PushColorStyle(ImNodesCol_Link, cRunningColor);
		}
		else
		{
			ImNodes::PushColorStyle(ImNodesCol_Link, cLinkColor);
		}

		int parent_id = std::get<static_cast<int>(NodeTuple::Node_Id)>(pair.second);
		int child_id = std::get<static_cast<int>(NodeTuple::Child_Id)>(pair.second);
		int pin_type = std::get<static_cast<int>(NodeTuple::PinType)>(pair.second);
		if (pin_type == cTruePinBit)
		{
			ImNodes::Link(link_id, (parent_id << cInputBit | cTruePinBit), (child_id << cInputBit));

		}
		else if (pin_type == cFalsePinBit)
		{
			ImNodes::Link(link_id, (parent_id << cInputBit | cFalsePinBit), (child_id << cInputBit));
		}

		ImNodes::PopColorStyle();
	}
}

void BehaviorTreeGraph::set_limit_distance(int id, float limit_distance)
{
	mNodes.at(id).limit_distance = limit_distance;
}

void BehaviorTreeGraph::set_wait_time(int id, float wait_time)
{
	mNodes.at(id).wait_time = wait_time;
}