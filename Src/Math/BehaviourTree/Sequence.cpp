#include "Sequence.h"

Sequence::Sequence(BlackBoard* black_board)
	: Composite(black_board)
{
}

Sequence::~Sequence()
{
}

NodeResult Sequence::Run()
{
	CheckFirstRun();

	for (auto& node : mChildNodes)
	{
		// ƒm[ƒh‚ª¬Œ÷‚©¸”s‚ğ•Ô‚·‚Ü‚ÅRun‚µ‘±‚¯‚é
		NodeResult result = NodeResult::None;
		do {
			result = node->Run();
		} while(result == NodeResult::Running);

		// Às’†‚É¸”s‚ğ•Ô‚µ‚½‚ç¸”s‚ğ•Ô‚·
		if (result == NodeResult::Fail) {
			mNodeResult = NodeResult::Fail;
			return mNodeResult;
		}
	}

	mNodeResult = NodeResult::Success;
	return NodeResult::Success;
}
