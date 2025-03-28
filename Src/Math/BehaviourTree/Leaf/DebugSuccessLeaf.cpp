#include "DebugSuccessLeaf.h"

#include "DxLib.h"

NodeResult DebugSuccessLeaf::tick()
{
    check_first_run();

    printfDx("デバッグ成功");

    mNodeResult = NodeResult::Success;
    return mNodeResult;
}
