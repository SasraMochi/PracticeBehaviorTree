#include "SceneManager.h"
#include "SceneNull.h"

static SceneNull scene_null;	//nullシーン

//コンストラクタ
SceneManager::SceneManager() :
	mpCurrentScene{ &scene_null } {
}

//デストラクタ
SceneManager::~SceneManager() {
	clear();
}

//更新
void SceneManager::update() {
	//シーンの更新
	mpCurrentScene->update();
	//シーンが終了しているか？
	if (mpCurrentScene->is_end()) {
		//シーンを変更する
		change(mpCurrentScene->next());
	}
}

//描画
void SceneManager::draw() const {
	//現在のシーンを描画
	mpCurrentScene->draw();
}

//終了
void SceneManager::end() {
	//現在のシーンを終了
	mpCurrentScene->end();
	//nullシーンにしておく
	mpCurrentScene = &scene_null;
}

//シーンの追加
void SceneManager::add(const std::string& name, IScene* scene) {
	mScenes[name] = scene;
}

//シーンの変更
void SceneManager::change(const std::string& name, const std::string& next) {
	//現在のシーンを終了
	end();
	//現在のシーンを変更
	mpCurrentScene = mScenes[name];
	//現在のシーンのnextSceneを設定
	mpCurrentScene->set_next(next);
	//現在のシーンを開始
	mpCurrentScene->start();
}

//シーンの消去
void SceneManager::clear() {
	//念の為シーンの終了を呼び出す
	end();
	//unordered_map内のシーンをすべて削除
	for (const auto& pair : mScenes) {
		delete pair.second;	//シーンの削除
	}
	//unordered_mapを消去
	mScenes.clear();
}