#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "entity.hpp"
#include <vector> 

class Sprite : public Entity {
public:

    Sprite(SDL_Renderer* renderer, const std::string& name, const std::string& image_path, int x, int y, int width, int height, int frameWidth, int frameHeight, int numFrames, int numColumns, int numRows);
    Sprite(SDL_Renderer* renderer, int x, int y, int width, int height);
    ~Sprite();

    static std::vector<Entity*>* _collisionvector;
    static void setCollisionVector(std::vector<Entity*>* collisionvector);
    virtual void display() override; 
    void animate(int row, bool flip = false);
    std::string& getName() override;
    bool test_collide(Entity* test, int dx, int dy);
    void move(int dx, int dy, bool jump = true) override;
    void attack(int damage, int size, std::vector<Entity*> entityvector);
    void setHealth(int value);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    int getHealth();
    void gotHit(int damage) override;
    virtual bool getStateInv() { return true;}

private:
    int _health = 3;
    // variable to animate the sprite
    int _frameWidth, _frameHeight;
    int _numFrames, _numColumns,_numRows;
    int _currentFrame,_currentRow;
    Uint32 _frameTime, _lastFrameTime;
    SDL_RendererFlip _flipType; // New member variable to store the flip state
};

#endif // SPRITE_HPP
