#pragma once

#include "Math/Vector2.h"

#include <DxLib.h>

class MyRectangle {
public:
	// デフォルトコンストラクタ(Actorの宣言に必要?)
	MyRectangle();

	// コンストラクタ
	explicit MyRectangle(float left, float top, float right, float bottom);
	explicit MyRectangle(const Vector2& min, const Vector2& max);

	// 点が矩形の内側に入っているか判定する
	bool contains(const Vector2& position) const;

	// 矩形が重なっているか判定する
	bool intersects(const MyRectangle& other) const;

	// 平行移動
	MyRectangle translate(const Vector2& position) const;

	// 拡張する
	MyRectangle expand(const Vector2& size) const;

	// 幅を取得
	float width() const;

	// 高さを取得
	float height() const;

	// 左上の座標を取得
	const Vector2& get_min() const;

	// 右下の座標を取得
	const Vector2& get_max() const;

	// デバッグ描画
	void draw_debug(int is_fill = 0, unsigned int color = GetColor(0, 0, 255)) const;

private:
	Vector2 mMin; // 矩形の左上
	Vector2 mMax; // 矩形の右下
};