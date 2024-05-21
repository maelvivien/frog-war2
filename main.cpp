// main.cpp
#include "window.hpp"

int main() {
    Window window("texture/map.png", 1920, 1080); // we create a window
    window.displayImagesWithTransition("texture/intro1.png", "texture/intro2.png", "texture/intro3.png","texture/menu.png", 5000,500); // we strt by displaying a small intro
    window.menu("texture/menu.png"); // at the moment the menu only offer to start the game
    window.display(); // main game loop
    return 0;
}