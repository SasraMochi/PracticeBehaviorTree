#include "GamePlayScene.h"
#include "DxLib.h"

#include "Actor/Player.h"
#include "Actor/Enemy/Attacker.h"

#include "Math/BehaviourTree/BehaviorTreeUtility.h"

void GamePlayScene::start() {
	mIsEnd = false;
	set_next("TitleScene");

	mpBehaviorTreeGraph = new BehaviorTreeGraph(false);
	mpBehaviorTreeGraph->select_load_file();
	auto behavior_tree_file_path = mpBehaviorTreeGraph->get_loading_file();

	mWorld.add_actor(new Player());
	mWorld.add_actor(new Attacker(&mWorld, behavior_tree_file_path));
	mWorld.set_field(new Field(1920, 64));
}

void GamePlayScene::update() {
	if (CheckHitKey(KEY_INPUT_RETURN)) 
	{
		mIsEnd = true;
	}

	float delta_time = 1.f;
	mWorld.update(delta_time);

	mpBehaviorTreeGraph->update();
}

void GamePlayScene::draw() const {
	mWorld.draw();
}

void GamePlayScene::draw_debug()
{
	mpBehaviorTreeGraph->draw();
}

bool GamePlayScene::is_end() const {
	return mIsEnd;
}

void GamePlayScene::end() {
	mWorld.clear();
	delete(mpBehaviorTreeGraph);
}