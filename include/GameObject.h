#pragma once
#include <SDL2/SDL.h>
#include "Vector2.h"
#include "Shape.h"

class GameObject {
public:
    GameObject(Vector2 position, Shape shape, SDL_Color color);
    void update(float deltaTime, int windowHeight);
    void render(SDL_Surface* surface);

private:
    Vector2 position;
    Shape shape;
    SDL_Color color;
    float velocityY = 0.0f;
};
