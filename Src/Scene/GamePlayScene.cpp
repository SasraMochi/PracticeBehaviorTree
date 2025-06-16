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
	if (CheckHitKey(KEY_INPUT_Q))
	{
		mIsEnd = true;
	}

	float delta_time = 1.f;
	mWorld.update(delta_time);

	// TODO:Œã‚Å®—
	// Œ»İ“®‚©‚µ‚Ä‚¢‚éƒm[ƒh‚ÌID‚ğæ“¾
	const auto& attacker_actor = mWorld.find_actor("Attacker");
	const Attacker* attacker = dynamic_cast<const Attacker*>(attacker_actor);
	mRunnningNodeId = attacker->get_behaviortree_running_node_id();

	mpBehaviorTreeGraph->set_runnning_node_id(mRunnningNodeId);

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