#include "DebugDrawLeaf.h"

#include "DxLib.h"

DebugDrawLeaf::DebugDrawLeaf(BlackBoard* black_board, int text)
	: INode(black_board),
	mText(text)
{

}

DebugDrawLeaf::~DebugDrawLeaf()
{
}

NodeResult DebugDrawLeaf::tick()
{
	check_first_run();

	printfDx("%i\n", mText);

	mNodeResult = NodeResult::Success;
	return mNodeResult;
}
