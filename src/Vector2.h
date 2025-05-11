#pragma once

#include <cmath>

struct Vector2 {
    float x, y;
    Vector2(float x = 0, float y = 0) : x(x), y(y) {}

    Vector2 operator+(const Vector2& v) const {
        return Vector2(x + v.x, y + v.y);
    }

    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2 normalized() const {
        float m = magnitude();
        return (m == 0) ? Vector2(0, 0) : Vector2(x / m, y / m);
    }
};