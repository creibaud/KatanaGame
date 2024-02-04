#ifndef UI_H
#define UI_H

#include <cmath>
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
        void init(sf::Image *image1, sf::Image *image2);
        void start(std::vector<sf::Image*> *characterImages, std::vector<sf::Image*> *roleImages, sf::Image *backRole, std::vector<sf::Image*> *cardImages, sf::Image *backCard, sf::Image *HP, sf::Image *Honor);
        ~UI();
};

#endif // UI_H