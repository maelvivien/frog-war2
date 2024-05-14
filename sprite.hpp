// sprite.hpp
#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "entity.hpp"
#include <vector> 

class Sprite : public Entity {
public:

    Sprite(SDL_Renderer* renderer, const std::string& name, const std::string& image_path, int x, int y, int width, int height, int frameWidth, int frameHeight, int numFrames, int numColumns, std::vector<Entity*>* collisionVector = nullptr);
    Sprite(SDL_Renderer* renderer, int x, int y, int width, int height);
    ~Sprite();

    virtual void display() override;
    void animate(int row, bool flip = false);
    std::string& getName() override;
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    bool test_collide(Entity* test, int dx, int dy);
    void move(int dx, int dy) override;

private:
    int _frameWidth, _frameHeight;
    int _numFrames, _numColumns;
    int _currentFrame;
    Uint32 _frameTime, _lastFrameTime;
    SDL_RendererFlip _flipType; // New member variable to store the flip state
    std::vector<Entity*>* _collisionVector = nullptr;
};

#endif // SPRITE_HPP