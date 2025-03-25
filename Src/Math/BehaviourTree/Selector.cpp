#include "Selector.h"

Selector::Selector()
{
}

Selector::~Selector()
{
}

NodeResult Selector::Run()
{
	CheckFirstRun();

	NodeResult selector_result = NodeResult::Fail;
	for (auto& node : mChildNodes)
	{
		// ƒm[ƒh‚ª¬Œ÷‚©¸”s‚ğ•Ô‚·‚Ü‚ÅRun‚µ‘±‚¯‚é
		NodeResult result = NodeResult::None;
		do {
			result = node->Run();
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
