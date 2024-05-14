// sprite.cpp
#include "sprite.hpp"
#include <vector>
#include <iostream>

Sprite::Sprite(SDL_Renderer* renderer, const std::string& name, const std::string& image_path, int x, int y, int width, int height, int frameWidth, int frameHeight, int numFrames, int numColumns, std::vector<Entity*>* collisionVector)
: _collisionVector(collisionVector) {
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
    _currentFrame = 0;
    _frameTime = 100;
    _lastFrameTime = 0;
    _flipType = SDL_FLIP_NONE;
    
    SDL_Surface* image = IMG_Load(image_path.c_str());
    _texture = SDL_CreateTextureFromSurface(_renderer, image);
    SDL_FreeSurface(image);
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

void Sprite::move(int dx, int dy) {
        // lateral movement
    if(_x < 0) _x=0;
    if(_x > 1920 - _width) _x = 1920 - _width;

    if(dx == 1) xspeed = MAX_XSPEED;
    if(dx == -1) xspeed = -MAX_XSPEED;
    if(xspeed > 0) signe = 1; // à changer
    if(xspeed < 0) signe = -1;
    if(dx==0) xspeed -= signe * frottement; // apply friction
    _x += xspeed;


    // Apply gravity    
    if(_y < 1080 - _height) { // Only apply gravity when not on the ground
        yspeed += gravity;
    } else {
        yspeed = 0; // Stop moving downwards when on the ground
        jumpTime = 0.0f; // Reset jump time when on the ground
 
    }

    if(dy == -1 && jumpTime < maxJumpTime ) { // Only allow jumping if jumpTime is less than maxJumpTime     
        yspeed = -15;
        jumpTime += 0.05f; // Increase jumpTime           
    }

    if(_y + dy < 0) _y=0;
    if(_y > 1080 - _height) _y=1080 - _height;
    _y += yspeed;
    std::cout << "X: " << _x << ", Y: " << _y << std::endl;


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
    if ((getX() + getWidth() + xspeed >= test->getX() && getX() + xspeed <= test->getX() + test->getWidth())
        && (getY() + getHeight() + yspeed >= test->getY() && getY() + yspeed <= test->getY() + test->getHeight())) return true;
    return false;
}