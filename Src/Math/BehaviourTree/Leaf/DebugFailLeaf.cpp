#include "DebugFailLeaf.h"

#include "DxLib.h"

NodeResult DebugFailLeaf::tick()
{
    check_first_run();

    printfDx("デバッグ失敗");

    mNodeResult = NodeResult::Fail;
    return mNodeResult;
}
