#include "DebugFailLeaf.h"

#include "DxLib.h"

NodeResult DebugFailLeaf::Run()
{
    CheckFirstRun();

    printfDx("�f�o�b�O���s");

    mNodeResult = NodeResult::Fail;
    return mNodeResult;
}
