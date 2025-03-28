#pragma once

#include <list>
#include <vector>
#include <string>

class Actor;	//アクタークラスの前方宣言

//アクターマネージャー
class ActorManager {
public:
	//デフォルトコンストラクタ
	ActorManager() = default;
	//デストラクタ
	~ActorManager();
	//アクターの追加
	void add(Actor* actor);
	//アクターの更新
	void update(float delta_time);
	//アクターの遅延更新
	void late_update(float delta_time);
	//アクターの描画
	void draw() const;
	//半透明アクターの描画
	void draw_transparent() const;
	//アクターのGUI描画
	void draw_gui() const;
	//アクターの衝突判定
	void collide();
	//死亡しているアクターの削除
	void remove();
	//アクターの検索
	Actor* find(const std::string& name) const;
	//指定したタグ名を持つアクターの検索
	std::vector<Actor*> find_with_tag(const std::string& tag) const;
	//アクター数を返す
	int count() const;
	//指定したタグ名を持つアクター数を返す
	int count_with_tag(const std::string& tag) const;
	//メッセージの送信
	void send_message(const std::string& message, void* param);
	//消去
	void clear();
	//コピー禁止
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;

private:
	//アクターリスト
	std::list<Actor*> mpActors;
};