// window.cpp
#include "window.hpp"
#include "sprite.hpp"
#include <chrono>
#include <thread>

// window.cpp
    Window::Window(const std::string& image_path, int world_width, int world_height, int view_width, int view_height)
    : view_width(view_width), view_height(view_height), image_path(image_path), viewport_x(0) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0) {
        printf("Error initializing the process\n");
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        printf("Audio could not be initialized\n");
    }

    window = SDL_CreateWindow("Frogwar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, view_width, view_height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        // faudrait gerer les erreurs
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        //
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

    if (image_path == "texture/grandbackground.png") {
        //Sprite* plateform1 = new Sprite(renderer, 0, 200, 500, 120);
        //collisionvector.push_back(plateform1);
        //Sprite* plateform2 = new Sprite(renderer, 1500, 900, 1920, 120);
        //collisionvector.push_back(plateform2);
        Sprite * collision = new Sprite(renderer, 0, 800, 2000, 120);
        collisionvector.push_back(collision);
        collision = new Sprite(renderer, 1620, 700, 20, 120);
        collisionvector.push_back(collision);
         collision = new Sprite(renderer, 1000, 500, 20, 300);
        collisionvector.push_back(collision);
        /*collision = new Sprite(renderer, 925, 775, 150, 220);
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
    while (running) {
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        if (keyState[SDL_SCANCODE_UP]) {
            entity->move(0, -1); // move up
            isJumping1 = true;
        }
        if (keyState[SDL_SCANCODE_DOWN]) {
            entity->move(0, 1); // move down
        }
        if (keyState[SDL_SCANCODE_LEFT]) {
            entity->move(-1, 0); // move left
            flip = true;
        }
        if (keyState[SDL_SCANCODE_RIGHT]) {
            entity->move(1, 0); // move right
            flip = false;
        }

        if (!keyState[SDL_SCANCODE_UP]) {
            isJumping1 = false;
        }

        ///////////////////////////////////////////////////////////////////////////

        if (keyState[SDL_SCANCODE_I]) {
            entity2->move(0, -1); // move up
            isJumping2 = true;
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

        entity->move(0, 0,isJumping1); // actualisation of the entity
        entity2->move(0,0,isJumping2);

        SDL_RenderClear(renderer); // Clear the current rendering target with the drawing color

        // Get the x-coordinate of the first sprite
        int sprite_x = entity->getX();

        // Calculate the new viewport x-coordinate
        int new_viewport_x = sprite_x - view_width / 2;

        // Ensure that the new viewport x-coordinate is within the bounds of the texture
        new_viewport_x = std::max(0, std::min(new_viewport_x, 2692 - view_width));

        // Render a part of the background
        SDL_Rect srcRect = {new_viewport_x, 0, view_width, view_height}; // Set the source rectangle to the current
        SDL_Rect destRect = {0, 0, view_width, view_height}; // Set the destination rectangle to the size of the window
        SDL_RenderCopy(renderer, texture, &srcRect, &destRect); // Render the part of the texture that's in the viewport to the window


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
        sprite->animate(0, flip);
        int render_x = sprite->getX() - new_viewport_x;
        sprite->display(render_x);
    }

    if (entity2->getHealth()) {
        Sprite* sprite2 = dynamic_cast<Sprite*>(entity2);
        if (sprite2 != nullptr) {
            sprite2->animate(0, flip2);
            int render_x = sprite2->getX() - new_viewport_x;
            sprite2->display(render_x);
        }
    }

    if (test && !entity2->getHealth()) {
        window_init();
        test = false;
    }

    // Update the screen with any rendering performed since the previous call
    SDL_RenderPresent(renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}