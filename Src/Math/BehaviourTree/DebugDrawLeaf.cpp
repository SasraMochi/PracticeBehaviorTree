#include "DebugDrawLeaf.h"

#include <iostream>

DebugDrawLeaf::DebugDrawLeaf(std::string text)
    : mText(text)
{

}

DebugDrawLeaf::~DebugDrawLeaf()
{
}

NodeResult DebugDrawLeaf::Run()
{
    CheckFirstRun();

    std::cout << mText << std::endl;

    mNodeResult = NodeResult::Success;
    return mNodeResult;
}
