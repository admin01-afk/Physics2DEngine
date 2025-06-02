#include <iostream>
#include "Vector2.h"
#include "window.h"
#include "Vector2.h"
#include "Shape.h"
#include "GameObject.h"

int main() {
    Window window("Game Window", 800, 600);
    
    GameObject box(Vector2(100, 100), Shape(ShapeType::Rectangle, 80, 40), SDL_Color{0, 255, 0, 255});
    GameObject circle(Vector2(400,300),Shape(ShapeType::Circle, 80, 80), SDL_Color{255, 0, 0});
    GameObject triangle(Vector2(400,300), Shape(ShapeType::Triangle,100,100),SDL_Color{0, 255, 0});

    //window.addGameObject(box);
    window.addGameObject(triangle);

    window.runLoop();
    return 0;
}