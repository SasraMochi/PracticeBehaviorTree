#include "Actor.h"

void Actor::update(float delta_time){}

void Actor::late_update(float delta_time){}

void Actor::draw() const{}

void Actor::draw_transparent() const{}

void Actor::draw_gui() const{}

void Actor::react(Actor& other){}

void Actor::handle_message(const std::string& message, void* param){}

void Actor::collide(Actor& other){
    //どちらのアクターも衝突判定が有効か？
    if (mIsEnableCollider && other.mIsEnableCollider) {
        //衝突判定をする
        if (is_collide(other)) {
            //衝突した場合は、お互いに衝突リアクションをする
            react(other);
            other.react(*this);
        }
    }
}

void Actor::die(){
    mIsDead = true;
}

bool Actor::is_dead() const{
    return mIsDead;
}

bool Actor::is_collide(const Actor& other) const
{
    return collider().intersects(other.collider());
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

//攻撃力を取得する
float Actor::attack_power() const{
    return mAttackPower;
}

MyRectangle Actor::collider() const
{
    return mCollider;
}

void Actor::damage(const float damage_value)
{
    // 衝突判定が無効の場合はスキップ
    if (!mIsEnableCollider) return;

    mHealth.Damage(damage_value);

    mIsEnableCollider = false;
    mCoolTimer.reset();

    if (mHealth.GetIsDead()) {
        die();
    }
}
