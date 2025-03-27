#pragma once

class INode;
class BlackBoard;

class BehaviourTreeBuilder {
public:
	static INode* BuildAttackerTree(BlackBoard* blackboard);
};