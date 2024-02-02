#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include "../Game/Game.h"

#define FPS 60

class UI {
    private:
        sf::RenderWindow *window;
        Game *game;
    
    public:
        UI();
        void start();
        ~UI();
};

#endif // UI_H