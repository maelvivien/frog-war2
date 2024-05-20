#include "player.hpp"
#include "window.hpp"
#define BOOST_TEST_MODULE functions test
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( Functions_Test )

BOOST_AUTO_TEST_CASE( Deplacement_Test )
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    window = SDL_CreateWindow("Window Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 1080, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        // handle error
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        // handle error
    }
    Player player1 = Player(renderer, "Player1", "texture/small_frog.png", 100, 100, 100, 80, 150, 111, 21, 7, 3);
    Player player2 = Player(renderer, "Player2", "texture/small_frog.png", 120, 100, 100, 80, 150, 111, 21, 7, 3);
    BOOST_CHECK(player1.getX()+20 == player2.getX());
}

BOOST_AUTO_TEST_CASE( Health_Test )
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    window = SDL_CreateWindow("Window Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 1080, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        // handle error
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        // handle error
    }
    Player player1 = Player(renderer, "Player1", "texture/small_frog.png", 100, 100, 100, 80, 150, 111, 21, 7, 3);
    Player player2 = Player(renderer, "Player2", "texture/small_frog.png", 120, 100, 100, 80, 150, 111, 21, 7, 3);
    player1.setHealth(2);
    BOOST_CHECK(player1.getHealth() == player2.getHealth()-1);
}

BOOST_AUTO_TEST_CASE( Damage_Test )
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    window = SDL_CreateWindow("Window Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 1080, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        // handle error
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        // handle error
    }
    Player player1 = Player(renderer, "Player1", "texture/small_frog.png", 100, 100, 100, 80, 150, 111, 21, 7, 3);
    Player player2 = Player(renderer, "Player2", "texture/small_frog.png", 120, 100, 100, 80, 150, 111, 21, 7, 3);
    player1.gotHit(1);
    BOOST_CHECK(player1.getHealth() == player2.getHealth()-1);
}

BOOST_AUTO_TEST_CASE( Timer_Test )
{
    Timer test_timer = Timer();
    test_timer.start();
    BOOST_CHECK(test_timer.isStarted());
}

BOOST_AUTO_TEST_CASE( Timer_Test2 )
{
    Timer test_timer = Timer();
    test_timer.start();
    test_timer.pause();
    BOOST_CHECK(test_timer.isStarted() && test_timer.isPaused());
}

BOOST_AUTO_TEST_SUITE_END()