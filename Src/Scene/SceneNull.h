#ifndef SCENE_NULL_H_
#define SCENE_NULL_H_

#include "IScene.h"

//ヌルシーン
class SceneNull : public IScene {
public:
	//開始
	virtual void start() override {}
	//更新
	virtual void update() override {}
	//描画
	virtual void draw() const override {}
	//デバッグ描画
	virtual void draw_debug() override {}
	//終了しているか？
	virtual bool is_end() const override {
		return false;
	}

	//終了
	virtual void end() override {}
};

#endif // !SCENE_NULL_H_

