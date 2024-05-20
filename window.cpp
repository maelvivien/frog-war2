// window.cpp
#include "window.hpp"
#include <chrono>
#include <thread>

Window::Window(const std::string& image_path, int width, int height)
    : width(width), height(height), image_path(image_path) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0) {
        printf("Error initializing the process\n");
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        printf("Audio could not be initialized\n");
    }

    window = SDL_CreateWindow("Window Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        // handle error
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        // handle error
    }

    player2 = new Player(renderer, "Player2", "texture/small_frog.png", 100, 100, 100, 80, 150, 111, 21, 7, 3);
    player1 = new Player(renderer, "Player1", "texture/frogknight.png", 850, 100, 100, 120, 100, 120, 21, 7, 3);
    player1->setHealth(5);
    player2->setHealth(5);
    
    window_init();

}

void Window::window_init(){
    SDL_Surface* image = IMG_Load(image_path.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    collisionvector.clear();
    entityvector.clear();
    collisionvector.push_back(player1);
    if (player1->getHealth()) {
        collisionvector.push_back(player1);
    }
    if (player2->getHealth()) {
        collisionvector.push_back(player2);
    }
    if (player1->getHealth()) entityvector.push_back(player1);
    if (player2->getHealth()) entityvector.push_back(player2);

    if (image_path == "texture/map.png") {
        Sprite * collision = new Sprite(renderer, 0, 1000, 1920, 120);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 275, 950, 50, 100);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 320, 860, 130, 100);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 450, 900, 50, 100);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 695, 840, 140, 20);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 320, 505, 130, 20);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 90, 755, 140, 20);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 880, 680, 140, 20);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 870, 370, 160, 20);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 1170, 745, 170, 20);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 1320, 570, 140, 20);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 1570, 350, 170, 20);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 1715, 870, 140, 20);
        collisionvector.push_back(collision);

        Sprite::setCollisionVector(&collisionvector);
    }
    //if (image_path == "texture/background2.png") {
    //    gMusic = Mix_LoadMUS( "sound/music2.ogg");
    //}
    //Mix_PlayMusic( gMusic, -1 );
    
}

Window::~Window() {
    for (long unsigned int i = 0; i < entityvector.size(); i++){
        entityvector.erase(entityvector.begin());
    }
    for (long unsigned int i = 0; i < collisionvector.size(); i++){
        collisionvector.erase(collisionvector.begin());
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void Window::display() {
    bool running = true;
    SDL_Event event;

    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    bool flip = false; // Handle the direction of the sprite
    bool flip2 = false;// False if sprite is toward the right
    bool sensattack = false;
    bool state = true;
    bool isJumping = false;
    int action = 0;
    int dx = 0, dy = 0;
    int swordP = 0; // to indicate what player is attacking with a sword
    Timer attackCooldown = Timer();
    Timer heartDisplayCoolDown = Timer();
    Timer swordanim = Timer();

    Timer spawnDelay1 = Timer();
    spawnDelay1.start();

    Timer spawnDelay2 = Timer();
    spawnDelay2.start();

    Timer spawnDelay3 = Timer();
    spawnDelay3.start();

    Timer spawnDelayboss = Timer();
    spawnDelayboss.start();
    Enemy* enemySpawn1 = NULL;
    Timer attackCooldownenemy1 = Timer();
    Enemy* enemySpawn2 = NULL;
    Timer attackCooldownenemy2 = Timer();
    Enemy* enemySpawn3 = NULL;
    Timer attackCooldownenemy3 = Timer();
    Enemy* boss = NULL;
    Timer attackCooldownboss = Timer();

    while (running) {


        SDL_RenderClear(renderer); // Clear the current rendering target with the drawing color

        // Render the background
        SDL_Rect backgroundRect;
        backgroundRect.x = 0;
        backgroundRect.y = 0;
        backgroundRect.w = width;
        backgroundRect.h = height;
        SDL_RenderCopy(renderer, texture, NULL, &backgroundRect);
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        if (keyState[SDL_SCANCODE_ESCAPE]) {
            std::cout << player1->getHealth() << " / " << player2->getHealth() << std::endl;
            running = false;
        }

        // Player 1
        dx = 0;
        dy = 0;
        isJumping = false;

        if (keyState[SDL_SCANCODE_UP]) {
            dx = 0;
            dy = -1;
            isJumping = true;
        }
        if (keyState[SDL_SCANCODE_DOWN]) {
            dx = 0;
            dy = 1;
        }
        if (keyState[SDL_SCANCODE_LEFT]) {
            dx = -1;
            if (!keyState[SDL_SCANCODE_UP] && !keyState[SDL_SCANCODE_DOWN]) {
                dy = 0;
            }
            flip = true;
        }
        if (keyState[SDL_SCANCODE_RIGHT]) {
            dx = 1;
            if (!keyState[SDL_SCANCODE_UP] && !keyState[SDL_SCANCODE_DOWN]) {
                dy = 0;
            }
            flip = false;
        }

        if (!keyState[SDL_SCANCODE_UP]) {
            isJumping = false;
        }
        player1->setAttackType(0);

        if(player1->getHealth() > 0){

        
            if (keyState[SDL_SCANCODE_SPACE]) {
                if (!attackCooldown.isStarted() || attackCooldown.getTime() >= 500) {   
                    if (player1->getAttackType() == 0) { 
                        
                        swordanim.start();
                        swordP = 1;
                        if (!flip) { // Turned toward the right side of the screen
                            player1->attack(1,50, entityvector);
                        }
                        else {
                            player1->attack(1,-50, entityvector);
                        }
                    }
                    else if (player1->getAttackType() == 1) {
                        int sens = flip ? -1 : 1;
                        std::string owner = "Player1";
                        AttackSprite* fireball = AttackSprite::createFireball(renderer, player1->getX(), player1->getY(), sens, 0, owner);

                        // Add the fireball to the list of entities
                        entityvector.push_back(fireball);
                        sensattack = flip;
                    }
                    if (!attackCooldown.isStarted()) attackCooldown.start();
                    else {
                        // Reset the timer and make it run again from 0
                        attackCooldown.stop();
                        attackCooldown.start();
                    }
                }
            }
        }
        player1->move(dx, dy, isJumping); // actualisation of the player

        // Animate and display the sprite
        if (isJumping) action = 1;
        else action = 0;


        if (player1->getHealth() > 0) {
            Sprite* sprite = dynamic_cast<Sprite*>(player1);
            if (sprite != nullptr) {
                sprite->animate(0, flip); // Animate the first row of the sprite sheet
                player1->display(); // Render the sprite to the renderer
            }
        }

        if (test && player1->getHealth() <= 0) {
            window_init();
            test = false;
        }


        /////////////////////////////////////////////////////////////////////////////
        // Player 2

        action = 0;
        isJumping = false;
        dx = 0;
        dy = 0;
        player2->setAttackType(1);
        if (keyState[SDL_SCANCODE_I]) {
            dx = 0;
            dy = -1; // move up
            isJumping = true;
        }
        if (keyState[SDL_SCANCODE_K]) {
            dx = 0;
            dy = 1; // move down
        }
        if (keyState[SDL_SCANCODE_J]) {
            dx = -1; // move left
            if (!keyState[SDL_SCANCODE_I] && !keyState[SDL_SCANCODE_K]) {
                dy = 0;
            }
            flip2 = true;
        }
        if (keyState[SDL_SCANCODE_L]) {
            dx = 1; // move right
            if (!keyState[SDL_SCANCODE_I] && !keyState[SDL_SCANCODE_K]) {
                dy = 0;
            }
            flip2 = false;
        }
        if (!keyState[SDL_SCANCODE_I]) {
            isJumping = false;
        }

        if(player2->getHealth() > 0){
            if (keyState[SDL_SCANCODE_Q]) {
                if (!attackCooldown.isStarted() || attackCooldown.getTime() >= 500) {   
                    if (player2->getAttackType() == 0) { 
                        swordP = 2;
                        swordanim.start();
                        if (!flip) { // Turned toward the right side of the screen
                            player2->attack(1,50, entityvector);
                        }
                        else {
                            player2->attack(1,-50, entityvector);
                        }
                    }
                    else if (player2->getAttackType() == 1) {
                        int sens = flip2 ? -1 : 1;
                        std::string owner = "Player2";
                        AttackSprite* fireball = AttackSprite::createFireball(renderer, player2->getX(), player2->getY(), sens, 0, owner);

                        // Add the fireball to the list of entities
                        entityvector.push_back(fireball);
                        sensattack = flip2;
                    }
                    if (!attackCooldown.isStarted()) attackCooldown.start();
                    else {
                        // Reset the timer and make it run again from 0
                        attackCooldown.stop();
                        attackCooldown.start();
                    }
                }
            }

        }

        player2->move(dx, dy, isJumping);

        if(isJumping)action = 1;
        else action = 0;

        if (player2->getHealth() > 0) {
            Sprite* sprite2 = dynamic_cast<Sprite*>(player2);
            if (sprite2 != nullptr) {
                sprite2->animate(0, flip2); // Animate the first row of the sprite sheet
                player2->display(); // Render the sprite to the renderer
            }
        }

        if (test && player2->getHealth() <= 0) {
            window_init();
            test = false;
        }

        ///////////////////////////////////////////////////////////////////////////
        /*SDL_Rect testrect = {player->getX(), player->getY(), player->getWidth(), player->getHeight()};
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderDrawRect(renderer, &testrect);

        if (flip) {
            SDL_Rect testrecthitbox = {player->getX()-50, player->getY(), player->getWidth(), player->getHeight()};
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderDrawRect(renderer, &testrecthitbox);
        }
        else {
            SDL_Rect testrecthitbox = {player->getX()+50, player->getY(), player->getWidth(), player->getHeight()};
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderDrawRect(renderer, &testrecthitbox);
        }

        SDL_Rect testrect2 = {player2->getX(), player2->getY(), player2->getWidth(), player2->getHeight()};
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderDrawRect(renderer, &testrect2);
        */
        if((!heartDisplayCoolDown.isStarted() || heartDisplayCoolDown.getTime() >= 5)){
            player1->displayHealth(player1->getHealth(),player2->getHealth());
            if (!heartDisplayCoolDown.isStarted()) heartDisplayCoolDown.start();
            else {
                // Reset the timer and make it run again from 0
                heartDisplayCoolDown.stop();
                heartDisplayCoolDown.start();
            }
        }

        if (swordanim.isStarted() && swordanim.getTime() < 200) {
            SDL_Surface* swordsurf = IMG_Load("texture/sword.png");
            SDL_Texture* swordtext = SDL_CreateTextureFromSurface(renderer, swordsurf);
            SDL_FreeSurface(swordsurf);
            SDL_Rect swordbox;
            int x1 = flip ? player1->getX()-player1->getWidth() : player1->getX()+player1->getWidth();
            int x2 = flip2 ? player2->getX()-player2->getWidth() : player2->getX()+player2->getWidth();
            if(swordP == 1)swordbox = {x1, player1->getY()+player1->getHeight()/2, 112, 51};
            if(swordP == 2)swordbox = {x2, player2->getY()+player2->getHeight()/2, 112, 51};
            SDL_RendererFlip _flipType = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE; // Update flipType
            SDL_RenderCopyEx(renderer, swordtext, NULL, &swordbox, 0, NULL, _flipType);
    
        }
        else if (swordanim.isStarted() && swordanim.getTime() > 200) {
            swordanim.stop();
        }
        /////bot1
	    if (enemySpawn1 == NULL && spawnDelay1.getTime() >= 3000 && boss == NULL) {
            enemySpawn1 = new Enemy(renderer, "bot1", "texture/bot1.png", 850, 500, 100, 100, 100, 100, 21, 7, 3);
            entityvector.push_back(enemySpawn1);
        }

        if (enemySpawn1 != NULL) {
            if (enemySpawn1->getHealth() <= 0) {
                for (int i = 0; i < entityvector.size(); i++) {
                    if (entityvector[i]->getName() == "bot1") {
                        entityvector.erase(entityvector.begin()+i);
                    }
                }
                delete enemySpawn1;
                enemySpawn1 = NULL;
                spawnDelay1.start();
            }
        }

        ///bot 2
        /*if (enemySpawn2 == NULL && spawnDelay2.getTime() >= 3000) {
            enemySpawn2 = new Enemy(renderer, "bot2", "texture/bot2.png", 900, 100, 100, 120, 100, 100, 14, 7, 2);
            entityvector.push_back(enemySpawn2);
        }

        if (enemySpawn2 != NULL) {
            if (enemySpawn2->getHealth() <= 0) {
                for (int i = 0; i < entityvector.size(); i++) {
                    if (entityvector[i]->getName() == "bot2") {
                        entityvector.erase(entityvector.begin()+i);
                    }
                }
                delete enemySpawn1;
                enemySpawn2 = NULL;
                spawnDelay2.start();
            }
        }*/

        if (boss == NULL && spawnDelay1.getTime() >= 10000) {
            boss = new Enemy(renderer, "boss", "texture/boss.png", 850, 800, 200, 200, 200, 200, 21, 7, 3);
            entityvector.push_back(boss);
            for (int i = 0; i < entityvector.size(); i++) {
                    if (entityvector[i]->getName() == "bot1") {
                        entityvector.erase(entityvector.begin()+i);
                    }
                }
            
        }

        if (boss!= NULL) {
            if (boss->getHealth() <= 0) {
                for (int i = 0; i < entityvector.size(); i++) {
                    if (entityvector[i]->getName() == "boss") {
                        entityvector.erase(entityvector.begin()+i);
                    }
                }
                delete boss;
            }
        }
        
        for (Entity* entity : entityvector) {
            AttackSprite* attack = dynamic_cast<AttackSprite*>(entity);
            if (attack != nullptr) {
                // Update the movement of Attacks sprites
                attack->move(0, 0);
                attack->update(entityvector); 
                attack->animate(0, sensattack); // Animate the first row of the sprite sheet
                attack->display(); // Render the sprite to the renderer
            }
            Enemy* enemy = dynamic_cast<Enemy*>(entity);
            if (enemy != nullptr) {
                // Update the movement of Attacks sprites
                if (!attackCooldownenemy1.isStarted() || attackCooldownenemy1.getTime() >= 2000) {
                    std::cout << "test" << std::endl;
                    std::string owner = "bot1";
                    AttackSprite* fireball1 = AttackSprite::createFireball(renderer, enemySpawn1->getX(), enemySpawn1->getY()+100, 0, 1, owner);
                    entityvector.push_back(fireball1);
                    AttackSprite* fireball2 = AttackSprite::createFireball(renderer, enemySpawn1->getX(), enemySpawn1->getY()-100, 0, -1, owner);
                    entityvector.push_back(fireball2);
                    AttackSprite* fireball3 = AttackSprite::createFireball(renderer, enemySpawn1->getX()+100, enemySpawn1->getY()+100, 1, 0, owner);
                    entityvector.push_back(fireball3);
                    AttackSprite* fireball4 = AttackSprite::createFireball(renderer, enemySpawn1->getX()-100, enemySpawn1->getY()-100, -1, 0, owner);
                    entityvector.push_back(fireball4);
                    attackCooldownenemy1.start();
                }
                enemy->move(0, 0);
                enemy->update(entityvector); 
                enemy->animate(0, 1); // Animate the first row of the sprite sheet
                enemy->display(); // Render the sprite to the renderer
            }
        }

        SDL_RenderPresent(renderer); // Update the screen with any rendering performed since the previous call
        std::this_thread::sleep_for(std::chrono::milliseconds(8));
    }
}

void Window::displayImagesWithTransition(const char* imagePath1, const char* imagePath2, const char* imagePath3, const char* imagePath4, int displayDuration, int transitionDuration) {
    SDL_Texture* texture1 = IMG_LoadTexture(renderer, imagePath1);
    SDL_Texture* texture2 = IMG_LoadTexture(renderer, imagePath2);
    SDL_Texture* texture3 = IMG_LoadTexture(renderer, imagePath3);
    SDL_Texture* texture4 = IMG_LoadTexture(renderer, imagePath4);

    // Render and present the first image
    SDL_RenderCopy(renderer, texture1, NULL, NULL);
    SDL_RenderPresent(renderer);

    // Sleep the thread for displayDuration milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(displayDuration));

    fadeTransition(texture1, texture2, transitionDuration);

    // Render and present the second image
    SDL_RenderCopy(renderer, texture2, NULL, NULL);
    SDL_RenderPresent(renderer);

    // Sleep the thread for displayDuration milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(displayDuration));

    fadeTransition(texture2, texture3, transitionDuration);

    // Render and present the third image
    SDL_RenderCopy(renderer, texture3, NULL, NULL);
    SDL_RenderPresent(renderer);

    // Sleep the thread for displayDuration milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(displayDuration));

    fadeTransition(texture3, texture4, transitionDuration);

    // Render and present the fourth image
    SDL_RenderCopy(renderer, texture4, NULL, NULL);
    SDL_RenderPresent(renderer);

    // Cleanup textures after use
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture3);
    SDL_DestroyTexture(texture4);
}


void Window::fadeTransition(SDL_Texture* startTexture, SDL_Texture* endTexture, int transitionDuration) {
    const int FRAMES_PER_SECOND = 60;
    const int FRAME_DURATION = 1000 / FRAMES_PER_SECOND; // Duration of each frame in milliseconds

    SDL_SetTextureBlendMode(startTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(endTexture, SDL_BLENDMODE_BLEND);

    Uint32 startTime = SDL_GetTicks();
    Uint32 endTime = startTime + transitionDuration;

    while (SDL_GetTicks() < endTime) {
        Uint32 now = SDL_GetTicks();
        double progress = (double)(now - startTime) / (double)(transitionDuration);

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the start texture with decreasing alpha
        SDL_SetTextureAlphaMod(startTexture, (1.0 - progress) * 255);
        SDL_RenderCopy(renderer, startTexture, NULL, NULL);

        // Draw the end texture with increasing alpha
        SDL_SetTextureAlphaMod(endTexture, progress * 255);
        SDL_RenderCopy(renderer, endTexture, NULL, NULL);

        // Update the screen
        SDL_RenderPresent(renderer);

        // Delay to control the speed of the transition
        if (transitionDuration > FRAME_DURATION) {
            SDL_Delay(FRAME_DURATION);
        } else {
            SDL_Delay(transitionDuration);
        }
    }

    // Reset the alpha mod of the textures
    SDL_SetTextureAlphaMod(startTexture, 255);
    SDL_SetTextureAlphaMod(endTexture, 255);
}

int Window::menu(const char* backgroundImagePath) {
    SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, backgroundImagePath);

    SDL_Rect buttonRect;
    buttonRect.x = 700; // Set the x position of the button
    buttonRect.y = 400; // Set the y position of the button
    buttonRect.w = 600; // Set the width of the button
    buttonRect.h = 100;  // Set the height of the button

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (SDL_PointInRect(new SDL_Point{mouseX, mouseY}, &buttonRect)) {
                    // The button area was clicked, return 0 to start the game
                    return 0;
                }
            }
        }

        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL); // Render the background
        SDL_RenderPresent(renderer); // Update the screen

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    SDL_DestroyTexture(backgroundTexture);

    return 1;
}
