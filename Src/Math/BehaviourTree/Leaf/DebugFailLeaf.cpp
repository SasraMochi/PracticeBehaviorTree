#include "DebugFailLeaf.h"

#include "DxLib.h"

NodeResult DebugFailLeaf::tick()
{
    check_first_run();

    printfDx("�f�o�b�O���s");

    mNodeResult = NodeResult::Fail;
    return mNodeResult;
}
