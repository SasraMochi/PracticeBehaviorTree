#include "DebugSuccessLeaf.h"

#include "DxLib.h"

NodeResult DebugSuccessLeaf::Run()
{
    CheckFirstRun();

    printfDx("デバッグ成功");

    mNodeResult = NodeResult::Success;
    return mNodeResult;
}
