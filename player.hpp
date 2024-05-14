// player.hpp
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"

class Player : public Entity {
public:
    Player(const std::string& name, SDL_Renderer* renderer, int x, int y, int vx, int vy);
    ~Player() override;

    void move() override; // Now this method correctly overrides the base class method

    // ...
};

#endif // PLAYER_HPP