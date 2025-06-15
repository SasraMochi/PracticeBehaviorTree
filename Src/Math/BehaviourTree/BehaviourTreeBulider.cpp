#include "BehaviourTreeBulider.h"

#include "Actor/BlackBoard.h"
#include "INode.h"
#include "Math/BehaviourTree/CompositeNode/Selector.h"
#include "Math/BehaviourTree/CompositeNode/Sequence.h"
#include "Math/BehaviourTree/DecoratorNode/Inverter.h"
#include "Math/BehaviourTree/BranchNode/CheckNearPlayer.h"
#include "Math/BehaviourTree/BranchNode/CheckFarPlayer.h"
#include "Math/BehaviourTree/LeafNode/WaitLeaf.h"
#include "Math/BehaviourTree/LeafNode/ChasePlayerLeaf.h"
#include "Math/BehaviourTree/LeafNode/EscapeFromPlayerLeaf.h"
#include "Math/BehaviourTree/LeafNode/CircleAttackLeaf.h"
#include "Math/BehaviourTree/LeafNode/AlwaysSuccessLeaf.h"
#include "Math/BehaviourTree/LeafNode/AlwaysFailLeaf.h"
#include "Math/BehaviourTree/LeafNode/DebugDrawLeaf.h"

#include "json.hpp"
using json = nlohmann::json;

#include <fstream>

INode* BehaviourTreeBuilder::BuildAttackerTree(std::string file_path, BlackBoard* blackboard)
{
	// JSONファイルを読み込む
	std::ifstream file(file_path);
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open behavior_tree.json");
	}

	json j;
	file >> j;

	// IDからJSON要素へのマッピングを構築する
	std::unordered_map<int, json> nodeMap;
	for (auto& node : j)
	{
		int id = node["id"].get<int>();
		nodeMap[id] = node;
	}

	// 再帰的にノードを構築するラムダ関数
	std::function<INode* (int)> buildNode = [&](int nodeId) -> INode*
	{
		if (nodeMap.find(nodeId) == nodeMap.end())
		{
			throw std::runtime_error("Node id not found in JSON: " + std::to_string(nodeId));
		}
		auto nodeJson = nodeMap[nodeId];
		std::string name = nodeJson["name"].get<std::string>();


		// --- Compositeノード ---
		if (name == "Sequence")
		{
			Sequence* seq = new Sequence(blackboard);
			for (auto childId : nodeJson["children"])
			{
				seq->add_node(buildNode(childId.get<int>()));
			}
			return seq;
		}
		else if (name == "Selector")
		{
			Selector* selector = new Selector(blackboard);
			for (auto childId : nodeJson["children"])
			{
				selector->add_node(buildNode(childId.get<int>()));
			}
			return selector;
		}

		// --- Decoratorノード ---
		else if (name == "Inverter")
		{
			int childId = nodeJson["children"][0].get<int>();
			return new Inverter(blackboard, buildNode(childId));
		}

		// --- Branchノード ---
		else if (name == "CheckNearPlayer")
		{
			int trueChildId = nodeJson["true_child"].get<int>();
			int falseChildId = nodeJson["false_child"].get<int>();
			float limitDistance = nodeJson["limit_distance"].get<float>();
			return new CheckNearPlayer(blackboard, buildNode(trueChildId), buildNode(falseChildId), limitDistance);
		}
		else if (name == "CheckFarPlayer")
		{
			int trueChildId = nodeJson["true_child"].get<int>();
			int falseChildId = nodeJson["false_child"].get<int>();
			float limitDistance = nodeJson["limit_distance"].get<float>();
			return new CheckFarPlayer(blackboard, buildNode(trueChildId), buildNode(falseChildId), limitDistance);
		}

		// --- Leafノード ---
		else if (name == "WaitLeaf")
		{
			float waitTime = nodeJson["wait_time"].get<float>();
			return new WaitLeaf(blackboard, waitTime);
		}
		else if (name == "ChasePlayerLeaf")
		{
			return new ChasePlayerLeaf(blackboard);
		}
		else if (name == "EscapeFromPlayerLeaf")
		{
			return new EscapeFromPlayerLeaf(blackboard);
		}
		else if (name == "CircleAttackLeaf")
		{
			return new CircleAttackLeaf(blackboard);
		}
		else if (name == "AlwaysSuccessLeaf")
		{
			return new AlwaysSuccessLeaf(blackboard);
		}
		else if (name == "AlwaysFailLeaf")
		{
			return new AlwaysFailLeaf(blackboard);
		}
		else if (name == "DebugDrawLeaf")
		{
			int text = nodeJson["text"].get<int>();
			return new DebugDrawLeaf(blackboard, text);
		}

		// --- 未知のノード ---
		else
		{
			throw std::runtime_error("Unknown node type: " + name);
		}
	};

	// ルートノードを探す (parentが-1のノード)
	int rootId = -1;
	for (auto& [id, nodeJson] : nodeMap)
	{
		if (nodeJson["parent"].get<int>() == -1)
		{
			rootId = id;
			break;
		}
	}
	if (rootId == -1)
	{
		throw std::runtime_error("Root node not found in JSON");
	}

	return buildNode(rootId);
}
