#include "Inverter.h"

#include <assert.h>

Inverter::Inverter(BlackBoard* black_board, INode* child_node)
	: DecoratorNodeBase(black_board)
{
	set_node(child_node);
}

Inverter::~Inverter()
{
}

void Inverter::tick()
{
	// 子ノードを実行
	mChildNode->tick();
	// 子ノードの結果を取得
	NodeResult result = mChildNode->get_node_result();
	// 結果を反転させる
	if (result == NodeResult::Success) {
		mNodeResult = NodeResult::Fail;
		return;
	}
	else if (result == NodeResult::Fail) {
		mNodeResult = NodeResult::Success;
		return;
	}

	// 子ノードが実行中の場合は、Inverterも実行中にする
	mNodeResult = NodeResult::Running;
}
