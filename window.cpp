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

    entity2 = new Sprite(renderer, "test1", "texture/frog2.png", 100, 100, 200, 200, 300, 250, 10, 10);
    entity = new Sprite(renderer, "test2", "texture/frogknight3.png", 850, 100, 300, 250, 100, 100, 16, 16);
    
    window_init();

}

void Window::window_init(){
    SDL_Surface* image = IMG_Load(image_path.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    collisionvector.clear();
    entityvector.clear();
    collisionvector.push_back(entity);
    if (entity2->getHealth()) {
        printf("Test\n");
        collisionvector.push_back(entity2);
    }
    entityvector.push_back(entity);
    if (entity2->getHealth()) entityvector.push_back(entity2);

    if (image_path == "texture/background.png") {
        //Sprite* plateform1 = new Sprite(renderer, 0, 200, 500, 120);
        //collisionvector.push_back(plateform1);
        //Sprite* plateform2 = new Sprite(renderer, 1500, 900, 1920, 120);
        //collisionvector.push_back(plateform2);
        Sprite * collision = new Sprite(renderer, 0, 900, 1920, 120);
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
        collisionvector.push_back(collision);
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
    delete entity2;
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
    bool flip = false; // Handle the direction of the sprite
    bool flip2 = false; // False if sprite is toward the right
    bool state = true;
    bool isJumping1 = false;
    bool isJumping2 = false;

    int dx1, dy1, dx2, dy2;
    while (running) {
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        dx1 = 0;
        dy1 = 0;
        if (keyState[SDL_SCANCODE_UP]) {
            dx1 = 0;
            dy1 = -1;
            isJumping1 = true;
        }
        if (keyState[SDL_SCANCODE_DOWN]) {
            dx1 = 0;
            dy1 = 1;
        }
        if (keyState[SDL_SCANCODE_LEFT]) {
            dx1 = -1;
            if (!keyState[SDL_SCANCODE_UP] && !keyState[SDL_SCANCODE_DOWN]) {
                dy1 = 0;
            }
            flip = true;
            std::cout << "Test" << std::endl;
        }
        if (keyState[SDL_SCANCODE_RIGHT]) {
            dx1 = 1;
            if (!keyState[SDL_SCANCODE_UP] && !keyState[SDL_SCANCODE_DOWN]) {
                dy1 = 0;
            }
            flip = false;
        }

        if (!keyState[SDL_SCANCODE_UP]) {
            isJumping1 = false;
        }

        ///////////////////////////////////////////////////////////////////////////

        dx2 = 0;
        dy2 = 0;

        if (keyState[SDL_SCANCODE_I]) {
            dx2 = 0;
            dy2 = -1; // move up
            isJumping2 = true;
        }
        if (keyState[SDL_SCANCODE_K]) {
            dx2 = 0;
            dy2 = 1; // move down
        }
        if (keyState[SDL_SCANCODE_J]) {
            dx2 = -1; // move left
            if (!keyState[SDL_SCANCODE_I] && !keyState[SDL_SCANCODE_K]) {
                dy2 = 0;
            }
            flip2 = true;
        }
        if (keyState[SDL_SCANCODE_L]) {
            dx2 = 1; // move right
            if (!keyState[SDL_SCANCODE_I] && !keyState[SDL_SCANCODE_K]) {
                dy2 = 0;
            }
            flip2 = false;
        }
        if (!keyState[SDL_SCANCODE_I]) {
            isJumping2 = false;
        }

        /////////////////////////////////////////////////////////////////////////////////

        if (keyState[SDL_SCANCODE_Q]) {
            
            if (!flip) { // Turned toward the right side of the screen
                entity->attack(1,50, entityvector);
            }
            else {
                entity->attack(1,-50, entityvector);
            }
        }
        std::cout << "dx1: " << dx1 << ", dy1: " << dy1 << std::endl;
        entity->move(dx1, dy1,isJumping1); // actualisation of the entity
        entity2->move(dx2,dy2,isJumping2);

        SDL_RenderClear(renderer); // Clear the current rendering target with the drawing color

        // Render the background
        SDL_Rect backgroundRect;
        backgroundRect.x = 0;
        backgroundRect.y = 0;
        backgroundRect.w = width;
        backgroundRect.h = height;
        SDL_RenderCopy(renderer, texture, NULL, &backgroundRect);

        SDL_Rect testrect = {entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight()};
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderDrawRect(renderer, &testrect);

        if (flip) {
            SDL_Rect testrecthitbox = {entity->getX()-50, entity->getY(), entity->getWidth(), entity->getHeight()};
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderDrawRect(renderer, &testrecthitbox);
        }
        else {
            SDL_Rect testrecthitbox = {entity->getX()+50, entity->getY(), entity->getWidth(), entity->getHeight()};
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderDrawRect(renderer, &testrecthitbox);
        }

        SDL_Rect testrect2 = {entity2->getX(), entity2->getY(), entity2->getWidth(), entity2->getHeight()};
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderDrawRect(renderer, &testrect2);

        // Animate and display the sprite
        Sprite* sprite = dynamic_cast<Sprite*>(entity);
        if (sprite != nullptr) {
            sprite->animate(0, flip); // Animate the first row of the sprite sheet
            entity->display(); // Render the sprite to the renderer
        }
        if (entity2->getHealth()) {
            Sprite* sprite2 = dynamic_cast<Sprite*>(entity2);
            if (sprite2 != nullptr) {
                sprite2->animate(0, flip2); // Animate the first row of the sprite sheet
                entity2->display(); // Render the sprite to the renderer
            }
        }
        if (test && !entity2->getHealth()) {
            window_init();
            test = false;
        }
        SDL_RenderPresent(renderer); // Update the screen with any rendering performed since the previous call
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}