#pragma once

#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// �K�����s��Ԃ��f�o�b�O�p�t�m�[�h
/// </summary>
class DebugSuccessLeaf : public LeafNodeBase {
public:
	explicit DebugSuccessLeaf(BlackBoard* black_board) : LeafNodeBase(black_board) {}

	~DebugSuccessLeaf() override = default;

	NodeResult get_node_result() const override {
		return NodeResult::Success;
	}
};