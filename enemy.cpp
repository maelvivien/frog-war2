// enemy.cpp
#include "enemy.hpp"


Enemy::Enemy(SDL_Renderer* renderer, const std::string& name, const std::string& image_path, int x, int y, int width, int height, int frameWidth, int frameHeight, int numFrames, int numColumns, int numRows)
    : Sprite(renderer, name, image_path, x, y, width, height, frameWidth, frameHeight, numFrames, numColumns, numRows) {}

Enemy::~Enemy() {
}

void Enemy::move(int dx, int dy) {
    //WIP
}
