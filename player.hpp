// player.hpp
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "sprite.hpp"
#include "timer.hpp"
#include <vector>
#include <iostream>

class Player : public Sprite {
public:
    Player(SDL_Renderer* renderer, const std::string& name, const std::string& image_path, int x, int y, int width, int height, int frameWidth, int frameHeight, int numFrames, int numColumns, int numRows);
    ~Player() override;

    void gotHit(int damage);

private:
    Timer _invulnerabiltyFrames;
    //int _health = 3;

};

#endif // PLAYER_HPP