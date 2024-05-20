// enemy.cpp
#include "enemy.hpp"


Enemy::Enemy(SDL_Renderer* renderer, const std::string& name, const std::string& image_path, int x, int y, int width, int height, int frameWidth, int frameHeight, int numFrames, int numColumns, int numRows)
    : Sprite(renderer, name, image_path, x, y, width, height, frameWidth, frameHeight, numFrames, numColumns, numRows), _startX(x), _startY(y) {}

Enemy::~Enemy() {
}

void Enemy::move(int dx, int dy) {

    if (this->getName() == "bot1") {
        if (_x > _startX + 400 || _x < _startX - 400) {
        setFx(-getFx());
        }
        _x += getFx()*2;
        
    }

    if (this->getName() == "bot2") {
        if (_x > _startX + 400 || _x < _startX - 400) {
        setFx(-getFx());
        }
        _x += getFx()*2;
    
    }
    
    
}

void Enemy::gotHit(int damage) {
    setHealth(0);
}


void Enemy::update(std::vector<Entity*>& entityvector) {
    //Same idea as the attackSprite update
    for (auto it = entityvector.begin(); it != entityvector.end(); ) {
        if (Enemy* enemy = dynamic_cast<Enemy*>(*it)) {
            /*if (enemy->getHealth() <= 0) {
                it = entityvector.erase(it);
            }*/
            // Check for collisions with the window borders
            if (enemy->_x < 0 || enemy->_x + enemy->getWidth() > windowWidth || enemy->_y < 0 || enemy->_y > windowHeight) {
                // Collision with window border detected, remove the Enemy
                enemy->setHealth(0);
                it = entityvector.erase(it);
                continue;
            }

            bool collisionDetected = false;
            Sprite* collidedEntity = nullptr;
            
            // Check for collisions with other entities
            for (auto other : entityvector) {
                Sprite* otherEntity = dynamic_cast<Sprite*>(other);
                
                if (enemy != otherEntity && enemy->test_collide(otherEntity, 0, 0)) {
                    if (!otherEntity->getStateInv()) {
                        std::cout << "Collision avec " << otherEntity->getName() << std::endl;
                        collisionDetected = true;
                        collidedEntity = otherEntity;
                        break;
                    }
                }
            }
    
            if (collisionDetected) {
                // Reduce player's health
                collidedEntity->gotHit(_damage);
                enemy->setHealth(0);
                it = entityvector.erase(it);
            } 
            else {
                ++it;
            }
        } else {
            ++it;
        }
    }
}

