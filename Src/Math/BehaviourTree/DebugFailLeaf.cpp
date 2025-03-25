#include "DebugFailLeaf.h"

#include "DxLib.h"

NodeResult DebugFailLeaf::Run()
{
    CheckFirstRun();

    printfDx("デバッグ失敗");

    mNodeResult = NodeResult::Fail;
    return mNodeResult;
}
