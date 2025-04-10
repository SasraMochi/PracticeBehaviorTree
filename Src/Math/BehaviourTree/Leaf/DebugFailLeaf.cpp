#include "DebugFailLeaf.h"

#include "DxLib.h"

NodeResult DebugFailLeaf::tick()
{
    check_first_run();

    mNodeResult = NodeResult::Fail;
    return mNodeResult;
}
