#ifndef UI_H
#define UI_H

#include "Menu/Menu.h"
#include "../Game/Game.h"

#define FPS 60
class UI {
    private:
        sf::RenderWindow *window;
        sf::Font *font;

        Game *game;
        int nbPlayers;
    
    public:
        UI(sf::Font *font);
        void menu(sf::Image *leftImage, sf::Image *rightImage);
        void start();
        ~UI();
};

#endif // UI_H