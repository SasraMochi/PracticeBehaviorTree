#include "DebugSuccessLeaf.h"

#include "DxLib.h"

NodeResult DebugSuccessLeaf::tick()
{
    check_first_run();

    mNodeResult = NodeResult::Success;
    return mNodeResult;
}
