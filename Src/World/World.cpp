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
	mActorManager.update(delta_time);
	//アクターの衝突
	mActorManager.collide();
	//アクターの遅延更新
	mActorManager.late_update(delta_time);
	//アクターの消去
	mActorManager.remove();
}

//描画
void World::draw() const {
	//フィールド描画
	mpField->draw();
	//アクターの描画
	mActorManager.draw();
	//半透明アクターの描画
	mActorManager.draw_transparent();
	//GUIの描画
	mActorManager.draw_gui();
}

//消去
void World::clear() {
	//アクターの消去
	mActorManager.clear();
}

//シーンの登録
void World::set_scene(IScene* scene) {
	mpScene = scene;
}

//シーンの取得
IScene* World::scene() {
	return mpScene;
}

void World::set_field(Field* field)
{
	mpField = field;
}

//アクターの追加
void World::add_actor(Actor* actor) {
	mActorManager.add(actor);
}

//アクターの検索
Actor* World::find_actor(const std::string& name) const {
	return mActorManager.find(name);
}

//指定したタグ名を持つアクターの検索
std::vector<Actor*> World::find_actor_with_tag(const std::string& tag) const {
	return mActorManager.find_with_tag(tag);
}

//アクター数を返す
int World::count_actor() const {
	return mActorManager.count();
}

//指定したタグ名を持つアクター数を返す
int World::count_actor_with_tag(const std::string& tag) const {
	return mActorManager.count_with_tag(tag);
}

//メッセージ送信
void World::send_message(const std::string& message, void* param) {
	mActorManager.send_message(message, param);
}