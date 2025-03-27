#pragma once

#include <string>
#include <vector>
#include "Math/Vector2.h"

class IWorld;	//ワールド抽象インターフェースの前方宣言
class BlackBoard;
class Vector2;

//アクタークラス
class Actor {
public:
	//コンストラクタ
	Actor() = default;
	//仮想デストラクタ
	virtual ~Actor() = default;
	//更新
	virtual void update(float delta_time);
	//遅延更新
	virtual void late_update(float delta_time);
	//描画
	virtual void draw() const;
	//半透明の描画
	virtual void draw_transparent() const;
	//GUIの描画
	virtual void draw_gui() const;
	//衝突リアクション
	virtual void react(Actor& other);
	//メッセージ処理
	virtual void handle_message(const std::string& message, void* param);
	//衝突判定
	void collide(Actor& other);
	//死亡する
	void die();
	//死亡しているか？
	bool is_dead() const;
	//名前を取得
	const std::string& name() const;
	//タグ名を取得
	const std::string& tag() const;
	//現在位置を取得
	const Vector2& position() const;

	//攻撃力を取得
	float attack_power() const;

	//コピー禁止
	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;

protected:
	//ワールド
	IWorld* world_{ nullptr };
	//ブラックボード
	BlackBoard* black_board_{ nullptr };
	//タグ名
	std::string tag_;
	//名前
	std::string name_;
	//トランスフォーム
	Vector2 position_;
	//移動量
	Vector2 velocity_{ 0.0f,0.0f };
	//衝突判定が有効か？
	bool enable_collider_{ true };
	//死亡フラグ
	bool dead_{ false };
	//攻撃力
	float attack_power_{ 0.0f };
};