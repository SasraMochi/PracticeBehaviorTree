#pragma once

class Selector;

class Player {
public:
	Player();

	~Player();

public:
	void update();

private:
	Selector* mpBehaviourTree = nullptr;
};