#ifndef MENU_H
#define MENU_H

#include "../Button/Button.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

class Menu {
    private:
        sf::Font *font;
        sf::Text *title;
        std::vector<Button*> *buttons;
        sf::Texture *leftTexture;
        sf::Texture *rightTexture;
        sf::Sprite *leftSprite;
        sf::Sprite *rightSprite;
        int nbPlayers;
    
    public:
        Menu(sf::Font *font, sf::Image *leftImage, sf::Image *rightImage);
        int getNbPlayers() const;
        void display(sf::RenderWindow &window);
        ~Menu();
};

#endif // MENU_H