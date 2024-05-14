// entity.cpp
#include "entity.hpp"

Entity::Entity(SDL_Renderer* renderer, const std::string& name, const std::string& image_path, int x, int y, int width, int height)
    : renderer(renderer), name(name), x(x), y(y), width(width), height(height) {
    SDL_Surface* image = IMG_Load(image_path.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
}

Entity::~Entity() {
    SDL_DestroyTexture(texture);
}

void Entity::display() {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}


void Entity::move(int dx, int dy) {
    // lateral movement
    if(x < 0) x=0;
    if(x > 1920-width) x=1920-width;

    if(dx == 1) xspeed = MAX_XSPEED;
    if(dx == -1) xspeed = -MAX_XSPEED;
    if(xspeed > 0) signe = 1; // à changer
    if(xspeed < 0) signe = -1;
    if(dx==0) xspeed -= signe * frottement; // apply friction
    x += xspeed;


    // Apply gravity    
    if(y < 1080 - height) { // Only apply gravity when not on the ground
        yspeed += gravity;
    } else {
        yspeed = 0; // Stop moving downwards when on the ground
        jumpTime = 0.0f; // Reset jump time when on the ground
 
    }

    if(dy == -1 && jumpTime < maxJumpTime ) { // Only allow jumping if jumpTime is less than maxJumpTime     
        yspeed = -15;
        jumpTime += 0.05f; // Increase jumpTime           
    }

    if(y + dy < 0) y=0;
    if(y > 1080 - height) y=1080 - height;
    y += yspeed;
    


}