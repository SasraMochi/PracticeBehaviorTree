#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <json.hpp>
#include <fstream>
#include <map>
#include <nameof.hpp>

#include "imgui.h"


/// <summary>
/// ノードの種類
/// </summary>
enum class NodeType {
	Composite,
	Decorator,
	Branch,
	Leaf
};

/// <summary>
/// ノードの名前
/// </summary>
enum class NodeName {
	Sequence,
	Selector,
	Inverter,
	CheckFarPlayer,
	CheckNearPlayer,
	ChasePlayerLeaf,
	CircleAttackLeaf,
	DebugDrawLeef,
	AlwaysFailLeaf,
	AlwaysSuccessLeaf,
	EscapeFromPlayerLeaf,
	WaitLeaf,
	NameEnd, // 要素数取得用
};

/// <summary>
/// 各ノードの名前とタイプのマッピング
/// </summary>
static std::map<NodeName, NodeType> NODE_MAP = {
	{NodeName::Sequence, NodeType::Composite},
	{NodeName::Selector, NodeType::Composite},
	{NodeName::Inverter, NodeType::Decorator},
	{NodeName::CheckFarPlayer, NodeType::Branch},
	{NodeName::CheckNearPlayer, NodeType::Branch},
	{NodeName::ChasePlayerLeaf, NodeType::Leaf},
	{NodeName::CircleAttackLeaf, NodeType::Leaf},
	{NodeName::DebugDrawLeef, NodeType::Leaf},
	{NodeName::AlwaysFailLeaf, NodeType::Leaf},
	{NodeName::AlwaysSuccessLeaf, NodeType::Leaf},
	{NodeName::EscapeFromPlayerLeaf, NodeType::Leaf},
	{NodeName::WaitLeaf, NodeType::Leaf},
};

/// <summary>
/// ノードの構造体
/// </summary>
struct BTNode {
	int id = 0;
	NodeType type = NodeType::Leaf;
	NodeName name = NodeName::WaitLeaf;
	std::vector<int> children;
	int parent = -1;

	// Branch用の変数
	int true_child = -1;
	int false_child = -1;

	// Wait用の変数
	float wait_time = -1.f;

	// CheckFarPlayer, CheckNearPlayer用の変数
	float limit_distance = -1.f;

	std::string GetString() const {
		return std::string(NAMEOF_ENUM(name));
	}

	// エディター上での位置
	float pos_x = 0.f;
	float pos_y = 0.f;
};


/// <summary>
/// ノードで構成された木の構造体
/// </summary>
class BehaviorTreeGraph
{
	using json = nlohmann::json;

private:
	// 各種ノードタイプのタイトルバーの色
	const std::map<NodeType, ImU32> cNodeColors = {
		{ NodeType::Composite, IM_COL32(128, 32, 32, 255)},
		{ NodeType::Decorator, IM_COL32(32, 32, 128, 255) },
		{ NodeType::Branch,    IM_COL32(128, 128, 32, 255)},
		{ NodeType::Leaf,      IM_COL32(32, 128, 32, 255)}
	};

	const int cInputBit = 16;
	const int cTruePinBit = 1;
	const int cFalsePinBit = 2;

	const enum class NodeTuple {
		Node_Id,
		Child_Id,
		PinType,
	};

public:
	BehaviorTreeGraph(bool is_edit_mode);

	~BehaviorTreeGraph();

	// 初期化
	void initialize();

	// 更新
	void update();

	// 描画
	void draw();

	// モード切替
	void change_mode(bool is_edit_mode);

	// ロードするJsonファイルを選択
	void select_load_file();

	// 現在ロードしているJsonファイルパスを取得
	std::string get_loading_file() const { return mLoadFileName; }

private:
	// ノードの追加
	int add_node(NodeName name);

	// リンクの追加
	void add_link(int start_attr, int end_attr);

	// Json書き出し処理
	void export_json(const std::string& file_name);

	// Json読み込み処理
	void import_json(const std::string& file_name);

	// ノードの位置を更新
	void set_node_pos(int id, float x, float y);

	// 選択している要素を削除
	void delete_selected_items();

private:
	// ノードのリンクを取得
	const std::map<int, std::tuple<int, int, int>>& get_node_links() const { return mNodeLinks; }

	// ノード群を取得
	const std::unordered_map<int, BTNode>& get_nodes() const { return mNodes; }

	// 文字列からNodeNameを返す
	NodeName get_matching_node_name(std::string name);

	// 選択しているノードの数を取得
	const int get_selected_node_num() const { return mSelectedNodes.size(); }

	// 選択しているノードを取得
	const int get_selected_node(int index);

	// 選択しているリンクの数を取得
	const int get_selected_link_num() const { return mSelectedLinks.size(); }

private:
	// 選択している要素の更新
	void update_selected();

	// ノードのリンクを行う
	void update_links();

	// ノードの移動処理
	void update_node_pos();

	// キーの更新処理
	void update_input_key();

	// ツールバーの描画
	void draw_toolbar();

	// エディターの描画
	void draw_editor();

private:
	// ノード追加ボタンの描画
	void draw_add_button();

	// 書き出しボタンの描画
	void draw_export_button();

	// 読み込みボタンの描画
	void draw_import_button();

	// 削除ボタンの描画
	void draw_delete_button();

	// ノードを描画
	void draw_nodes();
	void draw_node(const BTNode& node, int node_id, bool is_selected);

	// タイトルを描画
	void draw_title(const BTNode& node);

	// 入力ピンを描画
	void draw_input_pin(const BTNode& node);

	// 出力ピンを描画
	void draw_output_pin(const BTNode& node, bool is_selected);

	// パラメータを描画
	void draw_parameter(const BTNode& node, int node_id, bool is_selected);

	// リンクを描画
	void draw_links();

private:
	// ノードの削除
	void remove_node(int id);

	// ノードの削除
	void remove_node(const std::vector<int>& delete_list);

	// ノードがリンクできるかどうか
	bool is_link_addable(BTNode& parent_node, BTNode& child_node, bool is_true_branch);

	// ノード同士のリンクを解除
	void remove_nodes_link(int parent_id, int child_id);

	// ノードのリンクを削除
	void delete_link(int id);

	// ノードのリンクを削除
	void delete_link(const std::vector<int>& delete_list);

	// IDからノードを検索
	BTNode& get_node(int id);

	// ノードのlimit_distanceを設定
	void set_limit_distance(int id, float limit_distance);

	// ノードのwait_timeを設定
	void set_wait_time(int id, float wait_time);

	// ノードのリンクを追加(NodeLinkだけ)
	void add_link_tuple(int parent_id, int child_id, bool is_true_branch);

	// 全ノード名をEnumからStringの配列に変換
	std::vector<std::string> get_all_node_names() const;

	// 全選択を解除
	void reset_selected();

	// 選択中のノードに関するリンクを洗い出す
	bool get_selected_nodes_related_links(std::vector<int>* links);

private:
	std::string mLoadFileName = "";

	bool mIsEditMode = true;

	std::unordered_map<int, BTNode>          mNodes;
	std::map<int, std::tuple<int, int, int>> mNodeLinks;

	int mCreatedLinkId = 0;
	int mNextId = 1;

	std::vector<int> mSelectedNodes;
	std::vector<int> mSelectedLinks;

	std::vector<std::string> mNodeNames;
	int mSelectedAddNode = 0;
};