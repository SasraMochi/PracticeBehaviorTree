#pragma once

#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// �K�����s��Ԃ��f�o�b�O�p�t�m�[�h
/// </summary>
class DebugFailLeaf : public LeafNodeBase {
public:
	explicit DebugFailLeaf(BlackBoard* black_board) : LeafNodeBase(black_board) {}

	~DebugFailLeaf() override = default;

	NodeResult get_node_result() const override {
		return NodeResult::Fail;
	}
};