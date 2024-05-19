// main.cpp
#include "window.hpp"

int main() {
    Window window("texture/map.png", 1920, 1080);
    window.displayImagesWithTransition("texture/intro1.png", "texture/intro2.png", "texture/intro3.png","texture/menu.png", 4000,2000);
    window.menu("texture/menu.png");
    window.display();
    return 0;
}