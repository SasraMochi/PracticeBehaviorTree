#include "Attacker.h"

#include "DxLib.h"
#include "World/IWorld.h"

#include "Actor/BlackBoard.h"
#include "Actor/AttackCollider.h"
#include "Math/BehaviourTree/BehaviourTreeBulider.h"

Attacker::Attacker(IWorld* world, std::string behavior_tree_file_path)
	: mHealthBar{ this , mHealth.GetHealth() }
{
	mpWorld = world;
	mTag = "EnemyTag";
	mName = "Attacker";
	mAttackPower = 1;

	mpBlackBoard = new BlackBoard();
	mpBlackBoard->set_value<IAgent*>("Agent", this);

	auto* p_player = mpWorld->find_actor("Player");
	if (p_player == nullptr) {
		return;
	}
	Vector2 pos = p_player->position();
	mpBlackBoard->set_value<Vector2>("PlayerPos", pos);

	mpBehaviourTree = BehaviourTreeBuilder::BuildAttackerTree(behavior_tree_file_path, mpBlackBoard);
	mpBehaviourTree->init();

	Vector2 min = mPosition - Vector2{ 30.f, 30.f };
	Vector2 max = mPosition + Vector2{ 30.f, 30.f };
	mCollider = MyRectangle{ min, max };

	mCoolTimer.reset(cCoolTime);
}

Attacker::~Attacker()
{
	delete(mpBehaviourTree);
}

void Attacker::update(float delta_time)
{
	if (!mIsEnableCollider) {
		mCoolTimer.update(delta_time);

		if (mCoolTimer.is_end()) {
			mIsEnableCollider = true;
		}
	}

	auto* p_player = mpWorld->find_actor("Player");

	if (p_player == nullptr) {
		return;
	}

	Vector2 pos = p_player->position();
	mpBlackBoard->set_value<Vector2>("PlayerPos", pos);

	mpBehaviourTree->tick();

	move(delta_time);

	mVelocity = Vector2::zero();

	mHealthBar.update(delta_time, mHealth.GetHealth());
}

void Attacker::draw() const
{
	DrawCircle(mPosition.x, mPosition.y, 32, GetColor(255, 0, 0), TRUE);
	mHealthBar.draw();
}

void Attacker::draw_transparent() const
{
}

void Attacker::draw_gui() const
{
	mCollider.draw_debug();
}

void Attacker::react(Actor& other)
{
	if (other.tag() == "PlayerTag") {
		damage(other.attack_power());
	}
}

const int Attacker::get_behaviortree_running_node_id() const
{
	return mpBehaviourTree->get_running_node_id();
}

const Vector2& Attacker::get_position() const
{
	return mPosition;
}

void Attacker::move_towards(const Vector2& target, float speed)
{
	mVelocity = target * speed;
}

const float Attacker::get_health() const
{
	return mHealth.GetHealth();
}

void Attacker::attack()
{
	Vector2 min, max;

	min = mPosition - Vector2{ 75.f, 75.f };
	max = mPosition + Vector2{ 75.f, 75.f };
	MyRectangle attack_collider{ min, max };

	mpWorld->add_actor(new AttackCollider{ mpWorld,attack_collider, mTag, 15.f , 10.f });
}

void Attacker::move(float delta_time)
{
	Vector2 velocity = mVelocity * delta_time;
	mPosition += velocity;
	mCollider = mCollider.translate(velocity);
}