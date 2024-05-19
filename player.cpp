// player.cpp
#include "player.hpp"

Player::Player(SDL_Renderer* renderer, const std::string& name, const std::string& image_path, int x, int y, int width, int height, int frameWidth, int frameHeight, int numFrames, int numColumns, int numRows)
    : Sprite(renderer, name, image_path, x, y, width, height, frameWidth, frameHeight, numFrames, numColumns, numRows) {
    }

Player::~Player() {
}


void Player::gotHit(int damage) {
    if (!_invulnerabiltyFrames.isStarted() || _invulnerabiltyFrames.getTime() >= 10000) {
        _invulnerabiltyFrames.start();
        std::cout << "HP = " << getHealth() << std::endl;
        setHealth(getHealth()-damage);
        std::cout << "HP = " << getHealth() << std::endl;
    }
}