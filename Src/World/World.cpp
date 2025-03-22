#include "World/World.h"
#include "Scene/IScene.h"
#include "Actor/Actor.h"

//デストラクタ
World::~World() {
	clear();
}

//更新
void World::update(float delta_time) {
	//アクターの更新
	actors_.update(delta_time);
	//アクターの衝突
	actors_.collide();
	//アクターの遅延更新
	actors_.late_update(delta_time);
	//アクターの消去
	actors_.remove();
}

//描画
void World::draw() const {
	//アクターの描画
	actors_.draw();
	//半透明アクターの描画
	actors_.draw_transparent();
	//GUIの描画
	actors_.draw_gui();
}

//消去
void World::clear() {
	//アクターの消去
	actors_.clear();
}

//シーンの登録
void World::set_scene(IScene* scene) {
	scene_ = scene;
}

//シーンの取得
IScene* World::scene() {
	return scene_;
}

//アクターの追加
void World::add_actor(Actor* actor) {
	actors_.add(actor);
}

//アクターの検索
Actor* World::find_actor(const std::string& name) const {
	return actors_.find(name);
}

//指定したタグ名を持つアクターの検索
std::vector<Actor*> World::find_actor_with_tag(const std::string& tag) const {
	return actors_.find_with_tag(tag);
}

//アクター数を返す
int World::count_actor() const {
	return actors_.count();
}

//指定したタグ名を持つアクター数を返す
int World::count_actor_with_tag(const std::string& tag) const {
	return actors_.count_with_tag(tag);
}

//メッセージ送信
void World::send_message(const std::string& message, void* param) {
	actors_.send_message(message, param);
}