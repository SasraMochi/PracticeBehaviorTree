#include "DebugSuccessLeaf.h"

#include "DxLib.h"

NodeResult DebugSuccessLeaf::Run()
{
    CheckFirstRun();

    printfDx("�f�o�b�O����");

    mNodeResult = NodeResult::Success;
    return mNodeResult;
}
