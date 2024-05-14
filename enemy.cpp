// enemy.cpp
#include "enemy.hpp"

Enemy::Enemy(const std::string& name, int x, int y, int vx, int vy)
    : Entity(name, x, y, vx, vy) {}

void Enemy::move() {
    // Implement enemy movement
}