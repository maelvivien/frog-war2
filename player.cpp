// player.cpp
#include "player.hpp"

Player::Player(SDL_Renderer* renderer, const std::string& name, const std::string& image_path, int x, int y, int width, int height, int frameWidth, int frameHeight, int numFrames, int numColumns, int numRows)
    : Sprite(renderer, name, image_path, x, y, width, height, frameWidth, frameHeight, numFrames, numColumns, numRows) {
    
    
    SDL_Surface* player1 = IMG_Load("texture/player1.png");
    player1Texture = SDL_CreateTextureFromSurface(_renderer, player1);
    SDL_FreeSurface(player1);

    SDL_Surface* player2 = IMG_Load("texture/player2.png");
    player2Texture = SDL_CreateTextureFromSurface(_renderer, player2);
    SDL_FreeSurface(player2);

    SDL_Surface* blueHeart = IMG_Load("texture/coeurbleu.png");
    blueHeartTexture = SDL_CreateTextureFromSurface(_renderer, blueHeart);
    SDL_FreeSurface(blueHeart);

    SDL_Surface* greenHeart = IMG_Load("texture/coeurvert.png");
    greenHeartTexture = SDL_CreateTextureFromSurface(_renderer, greenHeart);
    SDL_FreeSurface(greenHeart);
    
    
    }

Player::~Player() {
    SDL_DestroyTexture(player1Texture);
    SDL_DestroyTexture(player2Texture);
    SDL_DestroyTexture(blueHeartTexture);
    SDL_DestroyTexture(greenHeartTexture);
}


void Player::gotHit(int damage) {
    if (!_invulnerabiltyFrames.isStarted() || _invulnerabiltyFrames.getTime() >= 10000) {
        _invulnerabiltyFrames.start();
        std::cout << "HP = " << getHealth() << std::endl;
        setHealth(getHealth()-damage);
        std::cout << "HP = " << getHealth() << std::endl;
    }
}

void Player::displayHealth(int pv1, int pv2) {
    // Render the player 1 texture
    if (player1Texture) {
        SDL_Rect player1Dst = {70, 20, 170, 50};
        SDL_RenderCopy(_renderer, player1Texture, NULL, &player1Dst);
    } 
    else {
        std::cerr << "player1Texture is NULL\n";
    }

    // Render the player 2 texture
    if (player2Texture) {
        SDL_Rect player2Dst = {1400, 20, 170, 50};
        SDL_RenderCopy(_renderer, player2Texture, NULL, &player2Dst);
    }
    else {
        std::cerr << "player2Texture is NULL\n";
    }

    // Set the position of the hearts
    int x1 = 270;
    int y1 = 20;

    int x2 = 1600;
    int y2 = 20;
    for (int i = 0; i < pv1; i++) {
        // Set the destination rectangle for the heart
        SDL_Rect dst;
        dst.x = x1 + i * 50; // space between the hearts
        dst.y = y1;
        dst.w = 50;
        dst.h = 50;

        // Render the heart
        SDL_RenderCopy(_renderer, blueHeartTexture, NULL, &dst);
    }

    for (int i = 0; i < pv2; i++) {
        // Set the destination rectangle for the heart
        SDL_Rect dst;
        dst.x = x2 + i * 50; // space between the hearts
        dst.y = y2;
        dst.w = 50;
        dst.h = 50;

        // Render the heart
        SDL_RenderCopy(_renderer, greenHeartTexture, NULL, &dst);
    }
}

int Player::getAttackType() {
    return _attackType;
}