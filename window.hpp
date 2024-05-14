// window.hpp
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "sprite.hpp"
#include <vector>
#include <SDL2/SDL_mixer.h>
#include <iostream>

class Window {
public:
    Window(const std::string& image_path, int width, int height);
    void window_init();
    ~Window();
    void display();

private:
    int width, height;
    std::string image_path;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    Sprite* entity;
    std::vector<Entity*> entityvector;
    std::vector<Entity*> collisionvector;
    Mix_Music* gMusic;
};

#endif // WINDOW_HPP