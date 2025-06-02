#include "window.h"
#include <iostream>

Window::Window(const std::string& title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
        return;
    }

    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
    std::cout << "Window(" << SDL_GetWindowTitle(window) << ") created!" << std::endl;

    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
        SDL_Quit();
    }
}

void Window::runLoop() {
    bool running = true;
    SDL_Event event;

    Uint32 lastTicks = SDL_GetTicks(); // Start time

    while (running) {
        Uint32 currentTicks = SDL_GetTicks();
        float deltaTime = (currentTicks - lastTicks) / 1000.0f; // in seconds
        lastTicks = currentTicks;

        // --- Handle Events ---
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Update all game objects
        int winW, winH;
        SDL_GetWindowSize(window, &winW, &winH);

        for (auto& obj : gameObjects) {
            obj.update(deltaTime, winH);  // NEW
        }

        // --- Render ---
        SDL_Surface* surface = SDL_GetWindowSurface(window);
        SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0, 0, 0)); // Clear to black

        // Render all GameObjects
        for (auto& obj : gameObjects) {
            obj.render(surface);
        }

        SDL_UpdateWindowSurface(window);
        // --- Frame Delay (cap at ~60 FPS) ---
        SDL_Delay(16); // ~16 ms = 60 FPS
    }
}

void Window::addGameObject(const GameObject& obj) {
    gameObjects.push_back(obj);
}

Window::~Window() {
    std::cout << "Window(" << SDL_GetWindowTitle(window) << ") destroyed!" << std::endl;
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::showFor(int milliseconds) {
    SDL_Delay(milliseconds);
}