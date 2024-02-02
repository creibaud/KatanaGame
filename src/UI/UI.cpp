#include "UI.h"

UI::UI(sf::Font *font) 
    : font(font) {
    this->window = new sf::RenderWindow();
    this->window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Katana", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(FPS);

    this->game = new Game();
}

void UI::init() {
    int nbPlayers;

    sf::Text *title = new sf::Text("Katana", *this->font, 200);
    title->setFillColor(sf::Color::Red);
    title->setPosition(SCREEN_WIDTH / 2 - title->getGlobalBounds().width / 2, 50);

    Button *btn1 = new Button(sf::Vector2f(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 650), sf::Vector2f(300, 100), sf::Color::White, this->font, "4 Players", 25);
    Button *btn2 = new Button(sf::Vector2f(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 500), sf::Vector2f(300, 100), sf::Color::White, this->font, "5 Players", 25);
    Button *btn3 = new Button(sf::Vector2f(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 350), sf::Vector2f(300, 100), sf::Color::White, this->font, "6 Players", 25);
    Button *btn4 = new Button(sf::Vector2f(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 200), sf::Vector2f(300, 100), sf::Color::White, this->font, "7 Players", 25);

    while (this->window->isOpen()) {
        sf::Event event;
        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->window->close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);

                    if (btn1->getShape().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        nbPlayers = 4;
                        this->window->close();
                    } else if (btn2->getShape().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        nbPlayers = 5;
                        this->window->close();
                    } else if (btn3->getShape().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        nbPlayers = 6;
                        this->window->close();
                    } else if (btn4->getShape().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        nbPlayers = 7;
                        this->window->close();
                    }
                }
            }
        }

        this->window->clear();

        this->window->draw(*title);
        btn1->draw(*this->window);
        btn2->draw(*this->window);
        btn3->draw(*this->window);
        btn4->draw(*this->window);

        this->window->display();
    }

    delete title;

    delete btn1;
    delete btn2;
    delete btn3;
    delete btn4;

    this->game->setNbPlayers(nbPlayers);
    this->game->initRole();
    this->game->initCharacter();
    this->game->initCard();
    this->game->initPlayer();
}

void UI::start() {
    this->window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Katana", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(FPS);
    
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