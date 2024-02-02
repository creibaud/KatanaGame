#ifndef UI_H
#define UI_H

#include <iostream>
#include "Button/Button.h"
#include "../Game/Game.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define FPS 60

class UI {
    private:
        sf::RenderWindow *window;
        sf::Font *font;
        Game *game;
    
    public:
        UI(sf::Font *font);
        void init();
        void start();
        ~UI();
};

#endif // UI_H