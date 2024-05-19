#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "sprite.hpp"
#include <vector>
#include <iostream> 

class Enemy : public Sprite {
public:
    Enemy(SDL_Renderer* renderer, const std::string& name, const std::string& image_path, int x, int y, int width, int height, int frameWidth, int frameHeight, int numFrames, int numColumns, int numRows);
    ~Enemy() override;

    void move(int dx, int dy);
private:

};

#endif // ENEMY_HPP