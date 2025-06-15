#pragma once

#include <string>

class INode;
class BlackBoard;

class BehaviourTreeBuilder {
public:
	static INode* BuildAttackerTree(std::string file_path, BlackBoard* blackboard);
};