#include "EditBehaviorTreeScene.h"

void EditBehaviorTreeScene::start()
{
	mIsEnd = false;

	set_next("TitleScene");

	mpBehaviorTree = new BehaviorTreeGraph(true);
}

void EditBehaviorTreeScene::update()
{
	// ツリーエディターの更新
	mpBehaviorTree->update();
}

void EditBehaviorTreeScene::draw() const
{
}

void EditBehaviorTreeScene::draw_debug()
{
	mpBehaviorTree->draw();
}

bool EditBehaviorTreeScene::is_end() const
{
	return mIsEnd;
}

void EditBehaviorTreeScene::end()
{
	delete(mpBehaviorTree);
}
