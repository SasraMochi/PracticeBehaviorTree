#include "DebugSuccessLeaf.h"

#include "DxLib.h"

NodeResult DebugSuccessLeaf::tick()
{
    check_first_run();

    printfDx("�f�o�b�O����");

    mNodeResult = NodeResult::Success;
    return mNodeResult;
}
