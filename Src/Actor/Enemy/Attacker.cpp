#include "Attacker.h"

#include "DxLib.h"
#include "World/IWorld.h"

#include "Actor/BlackBoard.h"
#include "Math/BehaviourTree/BehaviourTreeBulider.h"

#include "Math/BehaviourTree/Inverter.h"
#include "Math/BehaviourTree/Leaf/DebugDrawLeaf.h"
#include "Math/BehaviourTree/Leaf/DebugSuccessLeaf.h"
#include "Math/BehaviourTree/Leaf/DebugFailLeaf.h"

Attacker::Attacker()
{
	tag_ = "EnemyTag";
	name_ = "Attacker";

	black_board_ = new BlackBoard();
	black_board_->SetValue<IAgent*>("Agent", this);
	black_board_->SetValue<Vector2>("PlayerPos", Vector2::zero());

	mpBehaviourTree = BehaviourTreeBuilder::BuildAttackerTree(black_board_);
}

Attacker::~Attacker()
{
	delete(mpBehaviourTree);
}

void Attacker::update(float delta_time)
{
	Vector2 pos = world_->find_actor("Player")->position();
	black_board_->SetValue<Vector2>("PlayerPos", pos);

	mpBehaviourTree->Run();

	position_ += velocity_ * delta_time;
}

void Attacker::draw() const
{
	DrawCircle(position_.x, position_.y, 32, GetColor(255, 0, 0), TRUE);
}

void Attacker::draw_transparent() const
{
}

void Attacker::draw_gui() const
{
}

const Vector2& Attacker::GetPosition() const
{
	return position_;
}

void Attacker::MoveTowards(const Vector2& target, float speed)
{
	auto vector = target - position_;
	velocity_ = vector * speed;
}
