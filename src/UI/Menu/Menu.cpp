#include "Menu.h"

Menu::Menu(sf::Font *font, sf::Image *leftImage, sf::Image *rightImage)
    : font(font) {
    this->leftTexture = new sf::Texture();
    leftTexture->loadFromImage(*leftImage);

    this->leftSprite = new sf::Sprite();
    leftSprite->setTexture(*leftTexture);
    leftSprite->setPosition(200, SCREEN_HEIGHT / 2 - 75);

    this->rightTexture = new sf::Texture();
    rightTexture->loadFromImage(*rightImage);

    this->rightSprite = new sf::Sprite();
    rightSprite->setTexture(*rightTexture);
    rightSprite->setScale(1.5, 1.5);
    rightSprite->setPosition(SCREEN_WIDTH - 484 * 1.5, SCREEN_HEIGHT - 515 * 1.5);

    this->title = new sf::Text("Katana", *font, 200);
    this->title->setFillColor(sf::Color::Red);
    this->title->setPosition(SCREEN_WIDTH / 2 - title->getGlobalBounds().width / 2, 50);

    this->buttons = new std::vector<Button*>();
    for (int i = 0; i < 4; i++) {
        std::string text = std::to_string(4 + 3 - i) + " Players";
        this->buttons->push_back(new Button(sf::Vector2f(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 200 - 150 * i), sf::Vector2f(300, 100), this->font, text, 25));
    }

    this->nbPlayers = 0;
}

int Menu::getNbPlayers() const {
    return this->nbPlayers;
}

void Menu::display(sf::RenderWindow &window) {
    while (this->nbPlayers == 0) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            for (int i = 0; i < 4; i++) {
                if (this->buttons->at(i)->isClicked(window)) {
                    this->nbPlayers = 4 + 3 - i;
                    break;
                }
            }
        }

        window.clear(sf::Color::Black);

        window.draw(*this->title);
        window.draw(*this->leftSprite);
        window.draw(*this->rightSprite);

        for (std::vector<Button*>::iterator it = this->buttons->begin(); it != this->buttons->end(); it++) {
            (*it)->draw(window);
        }

        window.display();
    }
}

Menu::~Menu() {
    delete this->title;

    for (std::vector<Button*>::iterator it = this->buttons->begin(); it != this->buttons->end(); it++) {
        delete *it;
    }
    delete this->buttons;
    
    delete this->leftTexture;
    delete this->rightTexture;
    delete this->leftSprite;
    delete this->rightSprite;
}