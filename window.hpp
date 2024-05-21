// window.hpp
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "enemy.hpp"
#include "player.hpp"
#include "timer.hpp"
#include "attacksprite.hpp"
#include <vector>
#include <SDL2/SDL_mixer.h>
#include <iostream>

class Window {
public:
    Window(const std::string& image_path, int width, int height);
    void window_init();
    ~Window();
    void display(); // main game loop
    void displayImagesWithTransition(const char* imagePath1, const char* imagePath2, const char* imagePath3, const char* imagePath4, int displayDuration, int transitionDuration); // small intro
    int menu(const char* backgroundImagePath);

private:
    int width, height;
    std::string image_path;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    Player* player1;
    Player* player2;
    std::vector<Entity*> entityvector;
    std::vector<Entity*> collisionvector;
    Mix_Music* gMusic;
    bool alive = true;
    void fadeTransition(SDL_Texture* startTexture, SDL_Texture* endTexture, int transitionDuration);
};

#endif // WINDOW_HPP