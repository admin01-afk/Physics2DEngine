#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "GameObject.h"

class Window {
public:
    Window(const std::string& title, int width, int height);

    std::vector<GameObject> gameObjects;
    void addGameObject(const GameObject& obj);

    void runLoop(); 

    ~Window();

    void showFor(int milliseconds);

private:
    SDL_Window* window = nullptr;
};