#ifndef VEC2_H
#define VEC2_H

#include <cmath>

class Vec2 {
public:
    float x;
    float y;

    Vec2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    Vec2 operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }
    Vec2 operator-(const Vec2& other) const { return Vec2(x - other.x, y - other.y); }
    Vec2 operator*(float scalar) const { return Vec2(x * scalar, y * scalar); }
    Vec2& operator+=(const Vec2& other) { x += other.x; y += other.y; return *this; }
    Vec2& operator-=(const Vec2& other) { x -= other.x; y -= other.y; return *this; }

    float Magnitude() const { return std::sqrt(x * x + y * y); }
    Vec2 Normalized() const {
        const float magnitude = Magnitude();
        return magnitude == 0.0f ? Vec2() : Vec2(x / magnitude, y / magnitude);
    }
    float Distance(const Vec2& other) const { return (*this - other).Magnitude(); }
    float Inclination() const { return std::atan2(y, x); }
    Vec2 Rotated(float angle) const {
        return Vec2(x * std::cos(angle) - y * std::sin(angle),
                    y * std::cos(angle) + x * std::sin(angle));
    }
};

#endif
