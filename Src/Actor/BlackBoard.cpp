#include "BlackBoard.h"

bool BlackBoard::HasKey(const std::string& key) const
{
	return data_.find(key) != data_.end();
}
