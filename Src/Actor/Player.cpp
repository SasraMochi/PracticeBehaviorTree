#include "Player.h"

#include "Math/BehaviourTree/Selector.h"

Player::Player()
{
	mpBehaviourTree = new Selector();
	mpBehaviourTree->AddNode(Selector());
}

Player::~Player()
{
}

void Player::update()
{
}
