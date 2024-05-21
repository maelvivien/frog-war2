#include "attacksprite.hpp"

AttackSprite::AttackSprite(SDL_Renderer* renderer, const std::string& name, const std::string& imagePath, int x, int y, int w, int h, int frameW, int frameH, int numFrames, int numCols, int numRows, int damage, int fx, int fy, std::string owner)
    : Sprite(renderer, name, imagePath, x, y, w, h, frameW, frameH, numFrames, numCols, numRows) {

    setFx(fx); // Set fx the direction of the fire ball
    setFy(fy); // Set fy
    setOwner(owner);
    setDamage(damage);
    
}

void AttackSprite::move(int dx, int dy) {
    if (this->getName() == "fireball") { // if we had other attack we would make a swith case to make other mouvements, here the fireball moove in the direction they have been set to
        this->_x += this->getFx()*2; // we can change the 2 to change the speed of the fire ball
        this->_y += this->getFy()*2;
    }
}

void AttackSprite::update(std::vector<Entity*>& entityvector) { // this method is here to test if any of the attack has tuched something 
    for (auto it = entityvector.begin(); it != entityvector.end(); ) {
        if (AttackSprite* attackSprite = dynamic_cast<AttackSprite*>(*it)) {

            // Check for collisions with the window borders
            if (attackSprite->_x < 0 || attackSprite->_x + attackSprite->getWidth() > windowWidth || attackSprite->_y < 0 || attackSprite->_y > windowHeight) {
                // Collision with window border detected, remove the AttackSprite
                it = entityvector.erase(it);
                continue;
            }

            bool collisionDetected = false;
            Sprite* collidedEntity = nullptr;
            
            // Check for collisions with other entities
            for (auto other : entityvector) {
                Sprite* otherEntity = dynamic_cast<Sprite*>(other);
                
                if (attackSprite != otherEntity && attackSprite->test_collide(otherEntity, 0, 0)) {
                    if (attackSprite->getOwner() != otherEntity->getName()) {
                        collisionDetected = true;
                        collidedEntity = otherEntity;
                        break;
                    }
                }
            }
    
            if (collisionDetected) {
                collidedEntity->gotHit(_damage);
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

