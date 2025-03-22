#include "ActorManager.h"
#include "Actor.h"

#include <algorithm>
#include <iterator>

//デストラクタ
ActorManager::~ActorManager(){
    clear();
}

//アクターの追加
void ActorManager::add(Actor* actor){
    actors_.push_back(actor);
}

//アクターの更新
void ActorManager::update(float delta_time){
    for (auto actor : actors_) {
        actor->update(delta_time);
    }
}

//アクターの遅延更新
void ActorManager::late_update(float delta_time){
    for (auto actor : actors_) {
        actor->late_update(delta_time);
    }
}

//アクターの描画
void ActorManager::draw() const{
    for (auto actor : actors_) {
        actor->draw();
    }
}

//半透明アクターの描画
void ActorManager::draw_transparent() const{
    for (auto actor : actors_) {
        actor->draw_transparent();
    }
}

//アクターのGUI描画
void ActorManager::draw_gui() const{
    for (auto actor : actors_) {
        actor->draw_gui();
    }
}

//アクターの衝突判定
void ActorManager::collide(){
    for (auto i = actors_.begin(); i != actors_.end(); ++i) {
        for (auto j = std::next(i); j != actors_.end(); ++j) {
            (*i)->collide(**j);
        }
    }
}

//死亡しているアクターの削除
void ActorManager::remove(){
    for (auto i = actors_.begin(); i != actors_.end();) {
        if ((*i)->is_dead()) {
            delete* i;
            i = actors_.erase(i);
        }else {
            ++i;
        }
    }
}

//アクターの検索
Actor* ActorManager::find(const std::string& name) const{
    auto result = std::find_if(
        actors_.begin(), actors_.end(), 
        [&](Actor* actor) { return actor->name() == name; }
    );

    if (result == actors_.end()) return nullptr;

    return *result;
}

//指定したタグ名を持つアクターの検索
std::vector<Actor*> ActorManager::find_with_tag(const std::string& tag) const{
    std::vector<Actor*> result;

    std::copy_if(actors_.begin(), actors_.end(), std::back_inserter(result),
        [&](Actor* actor) { return actor->tag() == tag; });

    return result;
}

//アクター数を返す
int ActorManager::count() const{
    return (int)actors_.size();
}

//指定したタグのアクター数を返す
int ActorManager::count_with_tag(const std::string& tag) const{
    auto result = std::count_if(
        actors_.begin(), actors_.end(), 
        [&](Actor* actor) { return actor->tag() == tag; }
    );

    return static_cast<int>(result);
}

//メッセージの送信
void ActorManager::send_message(const std::string& message, void* param){
    for (auto actor : actors_) {
        actor->handle_message(message, param);
    }
}

//消去
void ActorManager::clear(){
    for (auto actor : actors_) {
        delete actor;
    }
    actors_.clear();
}