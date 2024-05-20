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
    ~Player();

    void gotHit(int damage);
    void displayHealth(int pv1, int pv2);
    void setAttackType(int attackType);
    int getAttackType();
    bool getStateInv();
    
private:
    Timer _invulnerabiltyFrames;
    SDL_Texture* player1Texture;
    SDL_Texture* player2Texture;
    SDL_Texture* blueHeartTexture;
    SDL_Texture* greenHeartTexture;
    int _attackType = 0;
    //int _health = 3;

};

#endif // PLAYER_HPP
