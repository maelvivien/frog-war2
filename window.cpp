// window.cpp
#include "window.hpp"
#include "sprite.hpp"
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

    //entity = new Sprite(renderer, "test1", "texture/frog2.png", 100, 100, 300, 250, 150, 150, 10, 10);
    entity = new Sprite(renderer, "test1", "texture/frogknight3.png", 850, 100, 300, 250, 100, 100, 16, 16);
    entityvector.push_back(entity);
    window_init();

}

void Window::window_init(){
    SDL_Surface* image = IMG_Load(image_path.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    collisionvector.clear();
    
    if (image_path == "texture/background.png") {
        Sprite* plateform1 = new Sprite(renderer, 0, 200, 500, 120);
        collisionvector.push_back(plateform1);
        Sprite* plateform2 = new Sprite(renderer, 1500, 900, 1920, 120);
        collisionvector.push_back(plateform2);
        /*collision = new Sprite(renderer, 0, 900, 1920, 120);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 925, 775, 150, 220);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 1075, 535, 220, 620);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 1295, 655, 140, 220);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 1630, 0, 320, 185);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 1900, 150, 120, 150);
        collisionvector.push_back(collision);*/
        Sprite::setCollisionVector(&collisionvector);
        //gMusic = Mix_LoadMUS( "sound/music.ogg");
    }
    //if (image_path == "texture/background2.png") {
    //    gMusic = Mix_LoadMUS( "sound/music2.ogg");
    //}
    //Mix_PlayMusic( gMusic, -1 );
    
}

Window::~Window() {
    delete entity;
    for (long unsigned int i = 0; i < collisionvector.size(); i++){
        delete collisionvector[i];
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
    bool flip = false;
    bool flip2 = false;
    bool state = true;
    bool isJumping1 = false;
    bool isJumping2 = false;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        const Uint8* keyState = SDL_GetKeyboardState(NULL);

        if (keyState[SDL_SCANCODE_UP]) {
            entity->move(0, -1); // move up
            isJumping1 = true;
        } else if (keyState[SDL_SCANCODE_DOWN]) {
            entity->move(0, 1); // move down
        }

        if (keyState[SDL_SCANCODE_LEFT]) {
            entity->move(-1, 0); // move left
            flip = true;
        } else if (keyState[SDL_SCANCODE_RIGHT]) {
            entity->move(1, 0); // move right
            flip = false;
        }
<<<<<<< Updated upstream
        entity->move(0, 0); // actualisation of the entity
=======

        if (!keyState[SDL_SCANCODE_UP]) {
            isJumping1 = false;
        }
        
        ///////////////////////////////////////////////////////////////////////////

        if (keyState[SDL_SCANCODE_I]) {
            entity2->move(0, -1); // move up
        }
        if (keyState[SDL_SCANCODE_K]) {
            entity2->move(0, 1); // move down
        }
        if (keyState[SDL_SCANCODE_J]) {
            entity2->move(-1, 0); // move left
            flip2 = true;
        }
        if (keyState[SDL_SCANCODE_L]) {
            entity2->move(1, 0); // move right
            flip2 = false;
        }

        /////////////////////////////////////////////////////////////////////////////////

        if (keyState[SDL_SCANCODE_Q]) {
            
            if (1 != 1) { // Turned toward the right side of the screen
                for (long unsigned int i = 0; i < entityvector.size(); i++) {
                    if (entityvector[i]->getName() != entity->getName()){
                        if (entity->test_collide(entityvector[i], 50, 0)){
                            printf("collision\n");
                        }
                        else {
                            printf("miss\n");
                        }
                    }
                }
            }
            else {
                printf("PROC\n");
                for (long unsigned int i = 0; i < entityvector.size(); i++) {
                    printf("Test\n");
                    if (entityvector[i]->getName() != entity->getName()){
                        printf("TEST2\n");
                        if (entity->test_collide(entityvector[i], -50, 0)){
                            printf("collision\n");
                        }
                        else {
                            printf("miss\n");
                        }
                    }
                }
            }
        }


        entity->move(0, 0,isJumping1); // actualisation of the entity
        entity2->move(0,0);
>>>>>>> Stashed changes

        SDL_RenderClear(renderer); // Clear the current rendering target with the drawing color

        // Render the background
        SDL_Rect backgroundRect;
        backgroundRect.x = 0;
        backgroundRect.y = 0;
        backgroundRect.w = width;
        backgroundRect.h = height;
        SDL_RenderCopy(renderer, texture, NULL, &backgroundRect);

        // Animate and display the sprite
        Sprite* sprite = dynamic_cast<Sprite*>(entity);
        if (sprite != nullptr) {
            sprite->animate(0, flip); // Animate the first row of the sprite sheet
            entity->display(); // Render the sprite to the renderer
        }
<<<<<<< Updated upstream

        SDL_RenderPresent(renderer); // Update the screen with any rendering performed since the previous call
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
=======
        Sprite* sprite2 = dynamic_cast<Sprite*>(entity2);
        if (sprite2 != nullptr) {
            sprite2->animate(0, flip2); // Animate the first row of the sprite sheet
            entity2->display(); // Render the sprite to the renderer
        }
        SDL_RenderPresent(renderer); // Update the screen with any rendering performed since the previous call
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
>>>>>>> Stashed changes
    }
}