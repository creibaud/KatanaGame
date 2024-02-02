#include "UI.h"

UI::UI(sf::Font *font) 
    : font(font) {
    this->window = new sf::RenderWindow();
    this->window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Katana", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(FPS);

    this->game = new Game();
}

void UI::init(sf::Image *image1, sf::Image *image2) {
    int nbPlayers;

    sf::Text *title = new sf::Text("Katana", *this->font, 200);
    title->setFillColor(sf::Color::Red);
    title->setPosition(SCREEN_WIDTH / 2 - title->getGlobalBounds().width / 2, 50);

    std::vector<Button*> *buttons = new std::vector<Button*>();

    for (int i = 0; i < 4; i++) {
        std::string text = std::to_string(4 + 3 - i) + " Players";
        buttons->push_back(new Button(sf::Vector2f(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 200 - 150 * i), sf::Vector2f(300, 100), this->font, text, 25));
    }

    sf::Texture *texture1 = new sf::Texture();
    texture1->loadFromImage(*image1);

    sf::Texture *texture2 = new sf::Texture();
    texture2->loadFromImage(*image2);

    sf::Sprite *sprite1 = new sf::Sprite();
    sprite1->setTexture(*texture1);
    sprite1->setScale(1.5, 1.5);
    sprite1->setPosition(SCREEN_WIDTH - 484 * 1.5, SCREEN_HEIGHT - 515 * 1.5);

    sf::Sprite *sprite2 = new sf::Sprite();
    sprite2->setTexture(*texture2);
    sprite2->setPosition(200, SCREEN_HEIGHT / 2 - 75);

    while (this->window->isOpen()) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
        sf::Event event;

        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->window->close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (std::vector<Button*>::iterator it = buttons->begin(); it != buttons->end(); it++) {
                        if ((*it)->getShape().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            nbPlayers = 4 + 3 - std::distance(buttons->begin(), it);
                            this->window->close();
                            break;
                        }
                    }
                }
            }
        }

        this->window->clear(sf::Color::Black);

        this->window->draw(*sprite1);
        this->window->draw(*sprite2);
        this->window->draw(*title);
        
        for (std::vector<Button*>::iterator it = buttons->begin(); it != buttons->end(); it++) {
            if ((*it)->getShape().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                (*it)->draw(*this->window, sf::Color::Red);
            } else {
                (*it)->draw(*this->window, sf::Color::White);
            }
        }

        this->window->display();
    }

    delete title;

    for (std::vector<Button*>::iterator it = buttons->begin(); it != buttons->end(); it++) {
        delete *it;
    }
    delete buttons;

    delete texture1;
    delete texture2;

    delete sprite1;
    delete sprite2;

    this->game->setNbPlayers(nbPlayers);
    this->game->initRole();
    this->game->initCharacter();
    this->game->initCard();
    this->game->initPlayer();
}

void UI::start(std::vector<sf::Image*> *images) {
    this->window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Katana", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(FPS);


    std::vector<Player*> *players = this->game->getPlayers();
    std::vector<sf::Sprite*> *spritePlayers = new std::vector<sf::Sprite*>();

    for (int i = 1; i < this->game->getNbPlayers(); i++) {
        sf::Texture *texture = new sf::Texture();
        texture->loadFromImage(*images->at(players->at(i)->getCharacter()->getIndex()));

        sf::Sprite *sprite = new sf::Sprite();
        sprite->setTexture(*texture);
        spritePlayers->push_back(sprite);
    }

    switch (this->game->getNbPlayers()) {
        case 4:
            spritePlayers->at(0)->setPosition(200, SCREEN_HEIGHT / 2 - spritePlayers->at(1)->getTexture()->getSize().y / 2 - 50);
            spritePlayers->at(1)->setPosition(SCREEN_WIDTH / 2 - spritePlayers->at(0)->getTexture()->getSize().x / 2, 100);
            spritePlayers->at(2)->setPosition(SCREEN_WIDTH - 200 - spritePlayers->at(0)->getTexture()->getSize().x / 2, SCREEN_HEIGHT / 2 - spritePlayers->at(1)->getTexture()->getSize().y / 2 - 50);
            break;
        
        default:
            break;
    }

    std::vector<Card*> *hand = players->at(this->game->getIndexActualPlayer())->getHand();
    std::vector<sf::Sprite*> *spriteHand = new std::vector<sf::Sprite*>();

    for (std::vector<Card*>::size_type i = 0; i < hand->size(); i++) {
        sf::Texture *texture = new sf::Texture();
        texture->loadFromImage(*images->at(0));

        sf::Sprite *sprite = new sf::Sprite();
        sprite->setTexture(*texture);
        sprite->setPosition(SCREEN_WIDTH / 2 - hand->size() * sprite->getTexture()->getSize().x / 2 + i * (sprite->getTexture()->getSize().x + 5), SCREEN_HEIGHT - 100 - sprite->getTexture()->getSize().y);
        spriteHand->push_back(sprite);
    }
    
    while (this->window->isOpen()) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
        sf::Event event;

        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->window->close();
            }
        }

        this->window->clear();

        for (std::vector<sf::Sprite*>::iterator it = spritePlayers->begin(); it != spritePlayers->end(); it++) {
            this->window->draw(*(*it));
        }

        for (std::vector<sf::Sprite*>::iterator it = spriteHand->begin(); it != spriteHand->end(); it++) {
            if ((*it)->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                (*it)->setPosition((*it)->getPosition().x, SCREEN_HEIGHT - 100 - (*it)->getTexture()->getSize().y - 20);
            } else {
                (*it)->setPosition((*it)->getPosition().x, SCREEN_HEIGHT - 100 - (*it)->getTexture()->getSize().y);
            }

            this->window->draw(*(*it));
        }

        this->window->display();
    }

    for (std::vector<sf::Sprite*>::iterator it = spritePlayers->begin(); it != spritePlayers->end(); it++) {
        delete *it;
    }
    delete spritePlayers;

    for (std::vector<sf::Sprite*>::iterator it = spriteHand->begin(); it != spriteHand->end(); it++) {
        delete *it;
    }
    delete spriteHand;
}

UI::~UI() {
    delete this->window;
    delete this->game;
}