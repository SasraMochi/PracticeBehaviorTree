#include "Sequence.h"

Sequence::Sequence()
{
}

Sequence::~Sequence()
{
}

NodeResult Sequence::Run()
{
	for (auto& node : mChildNodes)
	{
		NodeResult result = NodeResult::None;
		if (result != NodeResult::Running) {
			result = node.Run();
			
			// Às’†‚É¸”s‚ğ•Ô‚µ‚½‚ç¸”s‚ğ•Ô‚·
			if (result == NodeResult::Fail) {
				return result;
			}
		}
	}

	return NodeResult::Success;
}
