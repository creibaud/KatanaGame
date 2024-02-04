#ifndef UI1_H
#define UI1_H

#include <cmath>
#include "../Button/Button.h"
#include "../../Game/Game.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define FPS 60

class UI1 {
    private:
        sf::RenderWindow *window;
        sf::Font *font;
        Game *game;
    
    public:
        UI1(sf::Font *font);
        void init();
        void start(std::vector<sf::Image*> *characterImages, std::vector<sf::Image*> *roleImages, sf::Image *backRole, std::vector<sf::Image*> *cardImages, sf::Image *backCard, sf::Image *HP, sf::Image *Honor);
        ~UI1();
};

#endif // UI1_H