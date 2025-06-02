#include "GameObject.h"

const float GRAVITY = 500.0f; // pixels per second²

GameObject::GameObject(Vector2 pos, Shape shape, SDL_Color color)
    : position(pos), shape(shape), color(color) {}

void GameObject::update(float deltaTime, int windowHeight) {
    // Gravity acceleration
    const float gravity = 500.0f; // pixels per second squared

    // Apply gravity to vertical velocity
    velocityY += gravity * deltaTime;

    // Update vertical position
    position.y += velocityY * deltaTime;

    // Calculate the bottom of the object
    float bottom = position.y + shape.height;

    // Floor collision
    if (bottom >= windowHeight) {
        position.y = windowHeight - shape.height;
        velocityY = 0.0f;
    }
}

void GameObject::render(SDL_Surface* surface) {
    SDL_Rect rect = {
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        shape.width,
        shape.height
    };

    Uint32 sdlColor = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);

    switch (shape.type) {
        case ShapeType::Rectangle:
            SDL_FillRect(surface, &rect, sdlColor);
            break;

        case ShapeType::Circle: {
            int cx = rect.x + rect.w / 2;
            int cy = rect.y + rect.h / 2;
            int radius = std::min(rect.w, rect.h) / 2;

            for (int y = -radius; y <= radius; y++) {
                for (int x = -radius; x <= radius; x++) {
                    if (x * x + y * y <= radius * radius) {
                        int px = cx + x;
                        int py = cy + y;
                        if (px >= 0 && py >= 0 && px < surface->w && py < surface->h) {
                            Uint32* pixels = (Uint32*)surface->pixels;
                            pixels[py * surface->w + px] = sdlColor;
                        }
                    }
                }
            }
            break;
        }

        case ShapeType::Triangle: {
            int base = rect.w;
            int height = rect.h;
            int x0 = rect.x;
            int y0 = rect.y;

            // Triangle vertices (pointing up)
            int x1 = x0 + base / 2;
            int y1 = y0;
            int x2 = x0;
            int y2 = y0 + height;
            int x3 = x0 + base;
            int y3 = y0 + height;

            Uint32* pixels = (Uint32*)surface->pixels;

            for (int y = y1; y <= y2; ++y) {
                float t = (float)(y - y1) / (float)(y2 - y1);
                int startX = x1 + (x2 - x1) * t;
                int endX   = x1 + (x3 - x1) * t;

                if (startX > endX) std::swap(startX, endX);

                for (int x = startX; x <= endX; ++x) {
                    if (x >= 0 && y >= 0 && x < surface->w && y < surface->h) {
                        pixels[y * surface->w + x] = sdlColor;
                    }
                }
            }
            break;
        }

    }
}