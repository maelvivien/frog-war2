// sprite.cpp
#include "sprite.hpp"
#include <vector>
#include <iostream>

Sprite::Sprite(SDL_Renderer* renderer, const std::string& name, const std::string& image_path, int x, int y, int width, int height, int frameWidth, int frameHeight, int numFrames, int numColumns, int numRows)
{
    _renderer = renderer;
    _name = name;
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _frameWidth = frameWidth;
    _frameHeight = frameHeight;
    _numFrames = numFrames;
    _numColumns = numColumns;
    _numRows = numRows;
    _currentFrame = 0;
    _currentRow = 0;
    _frameTime = 100;
    _lastFrameTime = 0;
    _flipType = SDL_FLIP_NONE;
    
    SDL_Surface* image = IMG_Load(image_path.c_str());
    _texture = SDL_CreateTextureFromSurface(_renderer, image);
    SDL_FreeSurface(image);
}

std::vector<Entity*>* Sprite::_collisionvector = nullptr;

void Sprite::setCollisionVector(std::vector<Entity*>* collisionvector) {
    _collisionvector = collisionvector;
}



Sprite::Sprite(SDL_Renderer* renderer, int x, int y, int width, int height) {
    _renderer = renderer;
    _name = "";
    _x = x;
    _y = y;
    _width = width;
    _height = height;

}

Sprite::~Sprite() {
}

void Sprite::display() {
    SDL_Rect srcRect;
    srcRect.x = (_currentFrame % _numColumns) * _frameWidth;
    srcRect.y = (_currentFrame / _numColumns) * _frameHeight;
    srcRect.w = _frameWidth;
    srcRect.h = _frameHeight;

    SDL_Rect dstRect;
    dstRect.x = _x;
    dstRect.y = _y;
    dstRect.w = _width;
    dstRect.h = _height;

    SDL_RenderCopyEx(_renderer, _texture, &srcRect, &dstRect, 0, NULL, _flipType); // Use SDL_RenderCopyEx and flipType
}

void Sprite::animate(int row, bool flip) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime > _lastFrameTime + _frameTime) {
        _currentFrame = (_currentFrame + 1) % _numFrames;
        _lastFrameTime = currentTime;
    }

    _currentRow = row; // Update _currentRow

    SDL_Rect srcRect;
    srcRect.x = (_currentFrame % _numColumns) * _frameWidth;
    srcRect.y = row * _frameHeight;
    srcRect.w = _frameWidth;
    srcRect.h = _frameHeight;

    SDL_Rect dstRect;
    dstRect.x = _x;
    dstRect.y = _y;
    dstRect.w = _width;
    dstRect.h = _height;

    _flipType = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE; // Update flipType
    SDL_RenderCopyEx(_renderer, _texture, &srcRect, &dstRect, 0, NULL, _flipType);
}

void Sprite::move(int dx, int dy, bool jump) {
        // lateral movement
    if(_x < 0) _x=0;
    if(_x > 1920 - _width) _x = 1920 - _width;

    if(dx == 1) xspeed = MAX_XSPEED;
    if(dx == -1) xspeed = -MAX_XSPEED;
    
   if(xspeed>0)xspeed -= frottement;
   if(xspeed<0)xspeed += frottement;


    // Apply gravity    
    if(_y < 1080 - _height) { // Only apply gravity when not on the ground
        yspeed += gravity;
    } else {
        yspeed = 0; // Stop moving downwards when on the ground
        jumpTime = 0.0f; // Reset jump time when on the ground
 
    }

    if(dy == -1 && jumpTime < maxJumpTime ) { // Only allow jumping if jumpTime is less than maxJumpTime     
        yspeed = -16;
        jumpTime += 0.05f; // Increase jumpTime           
    }

    if(_y + dy < 0) _y=0;
    if(_y > 1080 - _height) _y=1080 - _height;


    bool isColliding = false;
    bool onGround = false;

    for (auto& other : *_collisionvector) {
        if (other != this) {
            // Check for horizontal collision
            if (xspeed != 0 && this->test_collide(other, xspeed, 0)) {
                // Adjust the sprite's horizontal position
                if (xspeed > 0) { // Moving right
                    _x -= 1;
                } else if (xspeed < 0) { // Moving left
                    _x += 1;
                }
                if (!onGround) {
                    xspeed = 0; // Stop horizontal movement
                }
            }

            // Check for vertical collision
            if (yspeed != 0 && this->test_collide(other, 0, yspeed)) {
                // Adjust the sprite's vertical position
                if (yspeed > 0) { // Moving down
                    _y -= 1;
                    yspeed = 0; // Stop falling
                    onGround = true;
                } else if (yspeed < 0) { // Moving up
                    _y += 1;
                    yspeed = 0; // Stop vertical movement
                }
            }
        }
    }

    if (!onGround) {
        _y += yspeed; // Apply gravity
    }
     else if(!jump){
        jumpTime = 0;
    }

    _x += xspeed;
}

void Sprite::attack(int damage, int size, std::vector<Entity*> entityvector){
    for (long unsigned int i = 0; i < entityvector.size(); i++) {
        if (entityvector[i]->getName() != getName()){
            if (test_collide(entityvector[i], size, 0)){
                printf("collision\n");
                entityvector[i]->gotHit(damage);
            }
            else {
                printf("miss\n");
            }
        }
    }
}

void Sprite::setHealth(int value) {
    _health = value;
}

int Sprite::getHealth() {
    return _health;
}

std::string& Sprite::getName(){
    return _name;
}

int Sprite::getX() {
    return _x;
}

int Sprite::getY() {
    return _y;
}

int Sprite::getHeight() {
    return _height;
}

int Sprite::getWidth() {
    return _width;
}

bool Sprite::test_collide(Entity* test, int dx, int dy){
    if ((getX() + getWidth() + dx > test->getX() && getX() + dx < test->getX() + test->getWidth())
        && (getY() + getHeight() + dy > test->getY() && getY() + dy < test->getY() + test->getHeight())) return true;
    return false;
}

void Sprite::gotHit(int damage){}