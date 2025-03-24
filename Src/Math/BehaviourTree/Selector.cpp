#include "Selector.h"

Selector::Selector()
{
}

Selector::~Selector()
{
}

NodeResult Selector::Run()
{
	NodeResult selector_result = NodeResult::Fail;
	for (auto& node : mChildNodes)
	{
		// ƒm[ƒh‚ª¬Œ÷‚©¸”s‚ğ•Ô‚·‚Ü‚ÅRun‚µ‘±‚¯‚é
		NodeResult result = NodeResult::None;
		do {
			node->CheckFirstRun();
			result = node->Run();
		} while (result == NodeResult::Running);

		// ‚Ç‚ê‚©ˆê‚Â‚Å‚à¬Œ÷‚ğ•Ô‚µ‚Ä‚½‚ç‘¦À‚É¬Œ÷‚ğ•Ô‚·
		if (result == NodeResult::Success)
			return NodeResult::Success;
	}

	return NodeResult::Fail;
}
