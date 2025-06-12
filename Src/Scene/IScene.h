#ifndef ISCENE_H_
#define ISCENE_H_

#include <string>

//シーン抽象インターフェース
class IScene {
public:
	//仮想デストラクタ
	virtual ~IScene() = default;
	//開始
	virtual void start() = 0;
	//更新
	virtual void update() = 0;
	//描画
	virtual void draw() const = 0;
	//デバッグ描画
	virtual void draw_debug() = 0;
	//終了しているか？
	virtual bool is_end() const = 0;
	//終了
	virtual void end() = 0;
	//次のシーンを設定
	void set_next(const std::string& next_scene);

	//ゲームスピードを設定
	void set_game_speed(const float game_speed);
	//ゲームスピードを取得
	float game_speed() const;

	//次のシーン名を返す
	std::string next() const;

protected:
	//ゲームスピード
	float game_speed_{ 1.0f };
	//次のシーン
	std::string next_scene_;
};

#endif // !ISCENE_H_
