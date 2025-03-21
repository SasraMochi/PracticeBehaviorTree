#ifndef MATHF_H_
#define MATHF_H_

#include <cmath>
#include <limits>

struct Mathf {
public:
    // 円周率
    static float pi() {
        return 3.14159265358979f;
    }
    // 度からラジアンに変換する定数
    static float deg_to_rad() {
        return  pi() * 2.0f / 360.0f;
    }
    // ラジアンから度に変換する定数
    static float rad_to_deg() {
        return 1.0f / deg_to_rad();
    }
    // f の符号を返します
    static float sign(float f) {
        return f >= 0.0f ? 1.0f : -1.0f;
    }
    // 無限大を表現します
    static float infinity() {
        return std::numeric_limits<float>::infinity();
    }
    // 負の無限大を表現します
    static float negative_infinity() {
        return -std::numeric_limits<float>::infinity();
    }
    // 与えられた最小 float 値と最大 float 値の範囲に値を制限します。
    static float clamp(float value, float min, float max) {
        return (value < min) ? min : (value > max) ? max : value;
    }
    // 0 と 1 の間に値を制限し、その値を返します。。
    static float clamp01(float value) {
        return clamp(value, 0.0f, 1.0f);
    }
    // current から target まで、maxDelta のスピードで移動します
    static float move_towards(float current, float target, float max_delta) {
        if (std::abs(target - current) <= max_delta)
            return target;
        return current + sign(target - current) * max_delta;
    }
    // a と b の間で t による線形補間します
    static float lerp(float a, float b, float t) {
        return a + (b - a) * clamp01(t);
    }
    // a と b の間で t による線形補間します。t に制限はありません。
    static float lerp_unclamped(float a, float b, float t) {
        return a + (b - a) * t;
    }
};

#endif