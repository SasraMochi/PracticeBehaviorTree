#include "Selector.h"

Selector::Selector(BlackBoard* black_board)
	: Composite(black_board)
{
}

Selector::~Selector()
{
}

NodeResult Selector::tick()
{
	check_first_run();

	NodeResult selector_result = NodeResult::Fail;
	for (auto& node : mChildNodes)
	{
		// ƒm[ƒh‚ª¬Œ÷‚©¸”s‚ğ•Ô‚·‚Ü‚ÅRun‚µ‘±‚¯‚é
		NodeResult result = NodeResult::None;
		do {
			result = node->tick();
		} while (result == NodeResult::Running);

		// ‘¦À‚É¬Œ÷‚ğ•Ô‚·
		if (result == NodeResult::Success) {
			mNodeResult = NodeResult::Success;
			return mNodeResult;
		}
	}

	mNodeResult = NodeResult::Fail;
	return mNodeResult;
}
