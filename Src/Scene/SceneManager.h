#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <unordered_map>
#include <string>

class IScene;

//シーン管理クラス
class SceneManager {
public:
	//コンストラクタ
	SceneManager();
	//デストラクタ
	~SceneManager();
	//更新
	void update();
	//描画
	void draw() const;
	//デバッグ描画
	void draw_debug();
	//終了
	void end();
	//シーンの追加
	void add(const std::string& name, IScene* scene);
	//シーンの変更
	void change(const std::string& name, const std::string& next = "TitleScene");
	//シーンの消去
	void clear();
	//コピー禁止
	SceneManager(const SceneManager& other) = delete;
	SceneManager& operator = (const SceneManager& other) = delete;

private:
	//シーン
	std::unordered_map<std::string, IScene*> scenes_;
	//現在のシーン
	IScene* current_scene_;
};

#endif // !SCENE_MANAGER_H_
