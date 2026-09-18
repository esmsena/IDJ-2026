#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect {
public:
    float x;
    float y;
    float w;
    float h;

    Rect(float x = 0.0f, float y = 0.0f, float w = 0.0f, float h = 0.0f)
        : x(x), y(y), w(w), h(h) {}

    Rect operator+(const Vec2& vector) const { return Rect(x + vector.x, y + vector.y, w, h); }
    Rect& operator+=(const Vec2& vector) { x += vector.x; y += vector.y; return *this; }
    Vec2 GetCenter() const { return Vec2(x + w / 2.0f, y + h / 2.0f); }
    float Distance(const Rect& other) const { return GetCenter().Distance(other.GetCenter()); }
    bool Contains(const Vec2& point) const {
        return point.x >= x && point.x <= x + w && point.y >= y && point.y <= y + h;
    }
};

#endif
