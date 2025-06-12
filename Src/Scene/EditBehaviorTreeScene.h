#ifndef EDIT_BEHAVIOR_TREE_SCENE_H_
#define EDIT_BEHAVIOR_TREE_SCENE_H_

#include"IScene.h"
#include"Math/BehaviourTree/BehaviorTreeUtility.h"

class EditBehaviorTreeScene : public IScene {
public:
	//開始
	virtual void start() override;
	//更新
	virtual void update() override;
	//描画
	virtual void draw() const override;
	//デバッグ描画
	virtual void draw_debug() override;

	//終了しているか？
	virtual bool is_end() const override;

	//終了
	virtual void end() override;

private:
	bool mIsEnd;
	BehaviorTreeGraph* mpBehaviorTree;
};
#endif // !EDIT_BEHAVIOR_TREE_SCENE_H_