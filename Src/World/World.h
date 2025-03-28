#pragma once

#include "World/IWorld.h"
#include "Scene/IScene.h"
#include "World/Field.h"
#include "Actor/ActorManager.h"

//ワールドクラス
class World : public IWorld {
public:
	//コンストラクタ
	World() = default;
	//デストラクタ
	~World();
	//更新
	void update(float delta_time);
	//描画
	void draw() const;
	//消去
	void clear();

	//現在のシーンの登録
	void set_scene(IScene* scene);

	//現在のシーンの取得
	virtual IScene* scene() override;

	//フィールドの登録
	void set_field(Field* field);

	//アクターを追加
	virtual void add_actor(Actor* actor) override;
	//アクターの検索
	virtual Actor* find_actor(const std::string& name) const override;
	//指定したタグ名を持つアクターの検索
	virtual std::vector<Actor*> find_actor_with_tag(const std::string& tag) const override;
	//アクター数を返す
	virtual int count_actor() const override;
	//指定したタグ名を持つアクター数を返す
	virtual int count_actor_with_tag(const std::string& tag) const override;
	//メッセージの送信
	virtual void send_message(const std::string& message, void* param = nullptr) override;

	//コピー禁止
	World(const World& other) = delete;
	World& operator = (const World& other) = delete;

private:
	//アクターマネージャー
	ActorManager mActorManager;
	//シーン
	IScene* mpScene{ nullptr };
	//フィールド
	Field* mpField{ nullptr };
};