#pragma once

enum class ShapeType {
    Rectangle,
    Circle,
    Triangle  // implement this later
};

struct Shape {
    ShapeType type;
    int width;
    int height;

    Shape(ShapeType type = ShapeType::Rectangle, int w = 0, int h = 0)
        : type(type), width(w), height(h) {}
};
