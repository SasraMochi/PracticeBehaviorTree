#include "Sequence.h"

Sequence::Sequence()
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
			node->CheckFirstRun();
			result = node->Run();
		} while(result == NodeResult::Running);

		// Às’†‚É¸”s‚ğ•Ô‚µ‚½‚ç¸”s‚ğ•Ô‚·
		if (result == NodeResult::Fail) {
			return result;
		}
	}

	return NodeResult::Success;
}
