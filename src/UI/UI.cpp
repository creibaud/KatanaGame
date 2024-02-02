#include "UI.h"

UI::UI() {
    this->window = new sf::RenderWindow();
    this->window->create(sf::VideoMode::getDesktopMode(), "Katana", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(FPS);

    this->game = new Game();
}

void UI::start() {
    while (this->window->isOpen()) {
        sf::Event event;
        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->window->close();
            }
        }

        this->window->clear();
        this->window->display();
    }
}

UI::~UI() {
    delete this->window;
    delete this->game;
}