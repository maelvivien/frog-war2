#ifndef ATTACKSPRITE_HPP
#define ATTACKSPRITE_HPP

#include "sprite.hpp"
#include <vector>

class AttackSprite : public Sprite {
public:
    AttackSprite(SDL_Renderer* renderer, const std::string& name, const std::string& imagePath, int x, int y, int w, int h, int frameW, int frameH, int numFrames, int numCols, int numRows, int damage, int fx, int fy, std::string owner);
    void move(int dx, int dy); // Moves the AttackSprite
    void update(std::vector<Entity*>& entityvector); // Checks for collisions and destroys the AttackSprite if it touches something

    void setFx(int fx) { _fx = fx; }
    void setFy(int fy) { _fy = fy; }
    void setOwner(std::string owner) { _owner = owner; }
    void setDamage(int value) { _damage = value; }

    int getFx() const { return _fx; }
    int getFy() const { return _fy; }
    int getDamage() { return _damage; }
    std::string getOwner() { return _owner; }

private:
    std::string _owner;
    int _damage;
    int windowWidth = 1920;
    int windowHeight = 1080;
    int _fx, _fy;
};

#endif // ATTACKSPRITE_HPP