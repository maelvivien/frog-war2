// player.cpp
#include "player.hpp"

Player::Player(const std::string& name, const std::string& image_path, int x, int y, int vx, int vy)
    : Entity(name, image_path, x, y, vx, vy) {}

void Player::move() {
    x += vx;
    y += vy;
}