#include "BlackBoard.h"

bool BlackBoard::has_key(const std::string& key) const
{
	return mData.find(key) != mData.end();
}
