#include "UI.h"

UI::UI(sf::Font *font) 
    : font(font) {
    this->window = new sf::RenderWindow();
    this->game = new Game();
    this->nbPlayers = 0;
}

void UI::menu(sf::Image *leftImage, sf::Image *rightImage) {
    this->window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Katana");
    this->window->setFramerateLimit(FPS);

    Menu *menu = new Menu(this->font, leftImage, rightImage);
    menu->display(*window);

    this->nbPlayers = menu->getNbPlayers();
    
    delete menu;
}

void UI::start() {
    std::cout << this->nbPlayers << std::endl;
}

UI::~UI() {
    delete this->window;
    delete this->game;
}