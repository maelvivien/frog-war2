#include "attacksprite.hpp"

AttackSprite::AttackSprite(SDL_Renderer* renderer, const std::string& name, const std::string& imagePath, int x, int y, int w, int h, int frameW, int frameH, int numFrames, int numCols, int numRows)
    : Sprite(renderer, name, imagePath, x, y, w, h, frameW, frameH, numFrames, numCols, numRows) {}



AttackSprite* AttackSprite::createFireball(SDL_Renderer* renderer, int x, int y, int fx, int fy, std::string owner) {
    const std::string& name = "fireball";
    const std::string imagePath = "texture/fireball.png";
    const int w = 100, h = 100, frameW = 150, frameH = 110;
    const int numFrames = 6, numCols = 6, numRows = 1;
    const int attackType = 1, damage = 2;
    AttackSprite* fireball = new AttackSprite(renderer, name, imagePath, x, y, w, h, frameW, frameH, numFrames, numCols, numRows);
    fireball->setFx(fx); // Set fx
    fireball->setFy(fy); // Set fy
    fireball->setOwner(owner);
    fireball->setDamage(damage);
    
    return fireball;
}

AttackSprite* AttackSprite::createSword(SDL_Renderer* renderer, int x, int y, std::string owner) {
    const std::string& name = "sword";
    const std::string imagePath = "texture/sword.png";
    const int w = 100, h = 100, frameW = 110, frameH = 100;
    const int numFrames = 5, numCols = 5, numRows = 1;
    const int attackType = 1, damage = 1;
    AttackSprite* sword = new AttackSprite(renderer, name, imagePath, x, y, w, h, frameW, frameH, numFrames, numCols, numRows);
    sword->setOwner(owner);
    sword->setDamage(damage);
    
    return sword;
}


void AttackSprite::move(int dx, int dy) {
    if (this->getName() == "fireball") {
        this->_x += this->getFx()*2;
        this->_y += this->getFy()*2;
    }
}

void AttackSprite::update(std::vector<Entity*>& entityvector) {
    for (auto it = entityvector.begin(); it != entityvector.end(); ) {
        if (AttackSprite* attackSprite = dynamic_cast<AttackSprite*>(*it)) {

            // Check for collisions with the window borders
            if (attackSprite->_x < 0 || attackSprite->_x + attackSprite->getWidth() > windowWidth || attackSprite->_y < 0 || attackSprite->_y > windowHeight) {
                // Collision with window border detected, remove the AttackSprite
                //delete attackSprite;
                it = entityvector.erase(it);
                continue;
            }

            bool collisionDetected = false;
            Sprite* collidedEntity = nullptr;
            
            // Check for collisions with other entities
            for (auto other : entityvector) {
                Sprite* otherEntity = dynamic_cast<Sprite*>(other);
                
                if (attackSprite != otherEntity && attackSprite->test_collide(otherEntity, 0, 0)) {
                    if (_owner != otherEntity->getName()) {
                        std::cout << _name << " / " << otherEntity->getName() << std::endl;
                        collisionDetected = true;
                        collidedEntity = otherEntity;
                        break;
                    }
                }
            }
    
            if (collisionDetected) {
                // Reduce player's health and remove the AttackSprite
                //collidedEntity->setHealth(collidedEntity->getHealth() - attackSprite->getDamage());
                std::cout << _damage << std::endl;
                collidedEntity->gotHit(_damage);
                //delete attackSprite;
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

