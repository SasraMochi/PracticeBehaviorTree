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

INode* BehaviourTreeBuilder::BuildAttackerTree(BlackBoard* blackboard)
{
	// ��������
#if 0
	auto chase_inverter = new Inverter(blackboard, new ChasePlayerLeaf(blackboard));

	auto root_sequence = new Sequence(blackboard);
	root_sequence->add_node(new CheckNearPlayer(blackboard, new EscapeFromPlayerLeaf(blackboard), new ChasePlayerLeaf(blackboard), 500.0f));
	return root_sequence;
#endif

#if 1
	// JSON�t�@�C����ǂݍ���
	std::ifstream file("behavior_tree.json");
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open behavior_tree.json");
	}

	json j;
	file >> j;

	// ID����JSON�v�f�ւ̃}�b�s���O���\�z����
	std::unordered_map<int, json> nodeMap;
	for (auto& node : j)
	{
		int id = node["id"].get<int>();
		nodeMap[id] = node;
	}

	// �ċA�I�Ƀm�[�h���\�z���郉���_�֐�
	std::function<INode* (int)> buildNode = [&](int nodeId) -> INode*
		{
			if (nodeMap.find(nodeId) == nodeMap.end())
			{
				throw std::runtime_error("Node id not found in JSON: " + std::to_string(nodeId));
			}
			auto nodeJson = nodeMap[nodeId];
			std::string name = nodeJson["name"].get<std::string>();

			if (name == "Sequence")
			{
				Sequence* seq = new Sequence(blackboard);
				for (auto childId : nodeJson["children"])
				{
					seq->add_node(buildNode(childId.get<int>()));
				}
				return seq;
			}
			else if (name == "Inverter")
			{
				// Inverter�͎q��1���Ɖ���
				int childId = nodeJson["children"][0].get<int>();
				return new Inverter(blackboard, buildNode(childId));
			}
			else if (name == "CheckNearPlayer")
			{
				// true_child �� false_child ���g���ĕ��򂷂�
				int trueChildId = nodeJson["true_child"].get<int>();
				int falseChildId = nodeJson["false_child"].get<int>();
				float limitDistance = nodeJson["limit_distance"].get<float>();
				return new CheckNearPlayer(blackboard, buildNode(trueChildId), buildNode(falseChildId), limitDistance);
			}
			else if (name == "CircleAttackLeaf")
			{
				return new CircleAttackLeaf(blackboard);
			}
			else if (name == "EscapeFromPlayerLeaf")
			{
				return new EscapeFromPlayerLeaf(blackboard);
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
			else if (name == "CheckFarPlayer")
			{
				int trueChildId = nodeJson["true_child"].get<int>();
				int falseChildId = nodeJson["false_child"].get<int>();
				float limitDistance = nodeJson["limit_distance"].get<float>();
				return new CheckFarPlayer(blackboard, buildNode(trueChildId), buildNode(falseChildId), limitDistance);
			}
			else if (name == "DebugDrawLeaf")
			{
				int text = nodeJson["text"].get<int>();
				return new DebugDrawLeaf(blackboard, text);
			}
			else if (name == "AlwaysFailLeaf")
			{
				return new AlwaysFailLeaf(blackboard);
			}
			else if (name == "WaitLeaf")
			{
				float waitTime = nodeJson["wait_time"].get<float>();
				return new WaitLeaf(blackboard, waitTime);
			}
			else if (name == "AlwaysSuccessLeaf")
			{
				return new AlwaysSuccessLeaf(blackboard);
			}
			else if (name == "ChasePlayerLeaf")
			{
				return new ChasePlayerLeaf(blackboard);
			}
			// ���̃m�[�h�ɂ��Ă��K�v�ɉ����Ď�����ǉ�����
			else
			{
				throw std::runtime_error("Unknown node type: " + name);
			}
		};

	// ���[�g�m�[�h��T�� (parent��-1�̃m�[�h)
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
#endif
}
