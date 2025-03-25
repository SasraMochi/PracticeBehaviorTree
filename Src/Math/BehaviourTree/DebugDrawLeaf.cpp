#include "DebugDrawLeaf.h"

#include "DxLib.h"

DebugDrawLeaf::DebugDrawLeaf(int text)
    : mText(text)
{

}

DebugDrawLeaf::~DebugDrawLeaf()
{
}

NodeResult DebugDrawLeaf::Run()
{
    CheckFirstRun();

    printfDx("%i\n", mText);

    mNodeResult = NodeResult::Success;
    return mNodeResult;
}
