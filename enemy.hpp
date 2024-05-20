#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "sprite.hpp"
#include "player.hpp"
#include <vector>
#include <iostream> 

class Enemy : public Sprite {
public:
    Enemy(SDL_Renderer* renderer, const std::string& name, const std::string& image_path, int x, int y, int width, int height, int frameWidth, int frameHeight, int numFrames, int numColumns, int numRows);
    ~Enemy() override;

    void move(int dx, int dy);
    void update(std::vector<Entity*>& entityvector);
    void setFx(int fx) { _fx = fx; }
    void setFy(int fy) { _fy = fy; }
    int getFx() const { return _fx; }
    int getFy() const { return _fy; }
    void gotHit(int damage);
private:
    int _damage = 1;
    int windowWidth = 1920;
    int windowHeight = 1080;
    int _fx = 1;
    int _fy = 0;
    int _startX;
    int _startY;

};

#endif // ENEMY_HPP