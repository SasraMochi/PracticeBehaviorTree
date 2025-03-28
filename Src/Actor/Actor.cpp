#include "Actor.h"

void Actor::update(float delta_time){}

void Actor::late_update(float delta_time){}

void Actor::draw() const{}

void Actor::draw_transparent() const{}

void Actor::draw_gui() const{}

void Actor::react(Actor& other){}

void Actor::handle_message(const std::string& message, void* param){}

void Actor::collide(Actor& other){
    // TODO ŒãXˆ—‚ğ’Ç‰Á
}

void Actor::die(){
    mIsDead = true;
}

bool Actor::is_dead() const{
    return mIsDead;
}

const std::string& Actor::name() const{
    return mName;
}

const std::string& Actor::tag() const{
    return mTag;
}

const Vector2& Actor::position() const
{
    return mPosition;
}

//UŒ‚—Í‚ğæ“¾‚·‚é
float Actor::attack_power() const{
    return mAttackPower;
}