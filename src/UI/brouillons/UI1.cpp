#include "UI1.h"

UI1::UI1(sf::Font *font) 
    : font(font) {
    this->window = new sf::RenderWindow();
    this->window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Katana", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(FPS);

    this->game = new Game();
}

void UI1::init() {
    this->game->setNbPlayers(4);
    this->game->initRole();
    this->game->initCharacter();
    this->game->initCard();
    this->game->initPlayer();
}

void UI1::start(std::vector<sf::Image*> *characterImages, std::vector<sf::Image*> *roleImages, sf::Image *backRole, std::vector<sf::Image*> *cardImages, sf::Image *backCard, sf::Image *HP, sf::Image *Honor) {
    this->window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Katana", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(FPS);

    sf::Texture *roleTextureBack = new sf::Texture();
    roleTextureBack->loadFromImage(*backRole);

    sf::Texture *backCardTexture = new sf::Texture();
    backCardTexture->loadFromImage(*backCard);

    sf::Texture *textureHP = new sf::Texture();
    textureHP->loadFromImage(*HP);

    sf::Texture *textureHonorPoints = new sf::Texture();
    textureHonorPoints->loadFromImage(*Honor);

    while (this->window->isOpen()) {
        std::vector<Player*> *players = this->game->getPlayers();
        std::vector<sf::Sprite*> *spritePlayers = new std::vector<sf::Sprite*>();

        std::vector<Card*> *cards = this->game->getCards();
        std::vector<sf::Sprite*> *spriteCards = new std::vector<sf::Sprite*>();

        std::vector<Card*> *discards = this->game->getDiscards();
        std::vector<sf::Sprite*> *spriteDiscards = new std::vector<sf::Sprite*>();

        for (std::vector<Card*>::size_type i = 0; i < cards->size(); i++) {
            sf::Sprite *sprite = new sf::Sprite();
            sprite->setTexture(*backCardTexture);
            sprite->setPosition(SCREEN_WIDTH / 2 + 5, SCREEN_HEIGHT / 2 - sprite->getTexture()->getSize().y / 2 - i);
            spriteCards->push_back(sprite);
        }

        for (std::vector<Card*>::size_type i = 0; i < discards->size(); i++) {
            sf::Texture *texture = new sf::Texture();
            texture->loadFromImage(*cardImages->at(discards->at(i)->getIndex()));

            sf::Sprite *sprite = new sf::Sprite();
            sprite->setTexture(*texture);
            sprite->setPosition(SCREEN_WIDTH / 2 - sprite->getTexture()->getSize().x - 5, SCREEN_HEIGHT / 2 - sprite->getTexture()->getSize().y / 2 - i);
            spriteDiscards->push_back(sprite);
        }

        std::vector<sf::Text*> *textsHP = new std::vector<sf::Text*>();
        std::vector<sf::Text*> *textsHonorPoints = new std::vector<sf::Text*>();

        int spriteShogunIndex = 0;

        if (this->game->getIndexActualPlayer() + 1 < this->game->getNbPlayers()) {
            for (int i = this->game->getIndexActualPlayer() + 1; i < this->game->getNbPlayers(); i++) {
                sf::Texture *texture = new sf::Texture();
                texture->loadFromImage(*characterImages->at(players->at(i)->getCharacter()->getIndex()));

                sf::Text *textHP = new sf::Text(std::to_string(players->at(i)->HP), *this->font, 20);
                textHP->setFillColor(sf::Color::White);
                textsHP->push_back(textHP);

                sf::Text *textHonorPoints = new sf::Text(std::to_string(players->at(i)->honorPoints), *this->font, 20);
                textHonorPoints->setFillColor(sf::Color::White);
                textsHonorPoints->push_back(textHonorPoints);

                sf::Sprite *sprite = new sf::Sprite();
                sprite->setTexture(*texture);
                spritePlayers->push_back(sprite);
                spriteShogunIndex++;
            }

            for (int i = 0; i < this->game->getIndexActualPlayer(); i++) {
                sf::Texture *texture = new sf::Texture();
                texture->loadFromImage(*characterImages->at(players->at(i)->getCharacter()->getIndex()));

                sf::Text *textHP = new sf::Text(std::to_string(players->at(i)->HP), *this->font, 20);
                textHP->setFillColor(sf::Color::White);
                textsHP->push_back(textHP);

                sf::Text *textHonorPoints = new sf::Text(std::to_string(players->at(i)->honorPoints), *this->font, 20);
                textHonorPoints->setFillColor(sf::Color::White);
                textsHonorPoints->push_back(textHonorPoints);

                sf::Sprite *sprite = new sf::Sprite();
                sprite->setTexture(*texture);
                spritePlayers->push_back(sprite);
            }
        } else {
            for (int i = 0; i < this->game->getNbPlayers() - 1; i++) {
                sf::Texture *texture = new sf::Texture();
                texture->loadFromImage(*characterImages->at(players->at(i)->getCharacter()->getIndex()));

                sf::Text *textHP = new sf::Text(std::to_string(players->at(i)->HP), *this->font, 20);
                textHP->setFillColor(sf::Color::White);
                textsHP->push_back(textHP);

                sf::Text *textHonorPoints = new sf::Text(std::to_string(players->at(i)->honorPoints), *this->font, 20);
                textHonorPoints->setFillColor(sf::Color::White);
                textsHonorPoints->push_back(textHonorPoints);

                sf::Sprite *sprite = new sf::Sprite();
                sprite->setTexture(*texture);
                spritePlayers->push_back(sprite);
            }

            spriteShogunIndex = 0;
        }

        if (players->at(this->game->getIndexActualPlayer())->getRole()->getType() == RoleType::SHOGUN) {
            spriteShogunIndex = -1;
        }

        sf::Texture *characterTexture = new sf::Texture();
        characterTexture->loadFromImage(*characterImages->at(players->at(this->game->getIndexActualPlayer())->getCharacter()->getIndex()));

        sf::Sprite *characterSprite = new sf::Sprite();
        characterSprite->setTexture(*characterTexture);
        characterSprite->setPosition(SCREEN_WIDTH - 150 - characterSprite->getTexture()->getSize().x, SCREEN_HEIGHT - 100 - characterSprite->getTexture()->getSize().y);

        switch (this->game->getNbPlayers()) {
            case 4:
                spritePlayers->at(0)->setPosition(200, SCREEN_HEIGHT / 2 - spritePlayers->at(1)->getTexture()->getSize().y / 2 - 50);
                spritePlayers->at(1)->setPosition(SCREEN_WIDTH / 2 - spritePlayers->at(0)->getTexture()->getSize().x / 2, 100);
                spritePlayers->at(2)->setPosition(SCREEN_WIDTH - 200 - spritePlayers->at(0)->getTexture()->getSize().x / 2, SCREEN_HEIGHT / 2 - spritePlayers->at(1)->getTexture()->getSize().y / 2 - 50);
                break;
            case 5:
                spritePlayers->at(0)->setPosition(200, SCREEN_HEIGHT / 2 - spritePlayers->at(1)->getTexture()->getSize().y / 2 - 50);
                spritePlayers->at(1)->setPosition(SCREEN_WIDTH / 2 - spritePlayers->at(0)->getTexture()->getSize().x / 2 - 250, 100);
                spritePlayers->at(2)->setPosition(SCREEN_WIDTH / 2 - spritePlayers->at(0)->getTexture()->getSize().x / 2 + 250, 100);
                spritePlayers->at(3)->setPosition(SCREEN_WIDTH - 200 - spritePlayers->at(0)->getTexture()->getSize().x / 2, SCREEN_HEIGHT / 2 - spritePlayers->at(1)->getTexture()->getSize().y / 2 - 50);
                break;
            case 6:
                spritePlayers->at(0)->setPosition(200, SCREEN_HEIGHT / 2 - spritePlayers->at(1)->getTexture()->getSize().y / 2 - 50);
                spritePlayers->at(1)->setPosition(SCREEN_WIDTH / 2 - spritePlayers->at(0)->getTexture()->getSize().x / 2 - 375, 175);
                spritePlayers->at(2)->setPosition(SCREEN_WIDTH / 2 - spritePlayers->at(0)->getTexture()->getSize().x / 2, 100);
                spritePlayers->at(3)->setPosition(SCREEN_WIDTH / 2 - spritePlayers->at(0)->getTexture()->getSize().x / 2 + 375, 175);
                spritePlayers->at(4)->setPosition(SCREEN_WIDTH - 200 - spritePlayers->at(0)->getTexture()->getSize().x / 2, SCREEN_HEIGHT / 2 - spritePlayers->at(1)->getTexture()->getSize().y / 2 - 50);
                break;
            case 7:
                spritePlayers->at(0)->setPosition(225, SCREEN_HEIGHT / 2 - spritePlayers->at(1)->getTexture()->getSize().y / 2 - 50);
                spritePlayers->at(1)->setPosition(SCREEN_WIDTH / 2 - spritePlayers->at(0)->getTexture()->getSize().x / 2 - 450, 175);
                spritePlayers->at(2)->setPosition(SCREEN_WIDTH / 2 - spritePlayers->at(0)->getTexture()->getSize().x / 2 - 150, 100);
                spritePlayers->at(3)->setPosition(SCREEN_WIDTH / 2 - spritePlayers->at(0)->getTexture()->getSize().x / 2 + 150, 100);
                spritePlayers->at(4)->setPosition(SCREEN_WIDTH / 2 - spritePlayers->at(0)->getTexture()->getSize().x / 2 + 450, 175);
                spritePlayers->at(5)->setPosition(SCREEN_WIDTH - 225 - spritePlayers->at(0)->getTexture()->getSize().x / 2, SCREEN_HEIGHT / 2 - spritePlayers->at(1)->getTexture()->getSize().y / 2 - 50);
            default:
                break;
        }

        std::vector<Card*> *hand = players->at(this->game->getIndexActualPlayer())->getHand();
        std::vector<sf::Sprite*> *spriteHand = new std::vector<sf::Sprite*>();

        sf::Texture *roleTextureFace = new sf::Texture();
        roleTextureFace->loadFromImage(*roleImages->at(players->at(this->game->getIndexActualPlayer())->getRole()->getIndex()));

        sf::Sprite *roleSpriteFace = new sf::Sprite();
        roleSpriteFace->setTexture(*roleTextureFace);
        roleSpriteFace->setPosition(150, SCREEN_HEIGHT - 100 - roleSpriteFace->getTexture()->getSize().y);

        sf::Sprite *roleSpriteBack = new sf::Sprite();
        roleSpriteBack->setTexture(*roleTextureBack);
        roleSpriteBack->setPosition(150, SCREEN_HEIGHT - 100 - roleSpriteBack->getTexture()->getSize().y);

        for (std::vector<Card*>::size_type i = 0; i < hand->size(); i++) {
            sf::Texture *texture = new sf::Texture();
            texture->loadFromImage(*cardImages->at(hand->at(i)->getIndex()));

            sf::Sprite *sprite = new sf::Sprite();
            sprite->setTexture(*texture);
            sprite->setPosition(SCREEN_WIDTH / 2 - hand->size() * sprite->getTexture()->getSize().x / 2 + i * (sprite->getTexture()->getSize().x + 5), SCREEN_HEIGHT - 100 - sprite->getTexture()->getSize().y);
            spriteHand->push_back(sprite);
        }

        std::vector<sf::Sprite*> *spritesHP = new std::vector<sf::Sprite*>();
        std::vector<sf::Sprite*> *spritesHonorPoints = new std::vector<sf::Sprite*>();

        for (std::vector<sf::Sprite*>::size_type i = 0; i < spritePlayers->size(); i++) {
            sf::Sprite *spriteHP = new sf::Sprite();
            spriteHP->setTexture(*textureHP);
            spriteHP->setScale(0.5, 0.5);
            spriteHP->setPosition(spritePlayers->at(i)->getPosition().x + textsHP->at(i)->getGlobalBounds().width + 25, spritePlayers->at(i)->getPosition().y - 2 * spriteHP->getTexture()->getSize().y / 3 - 5);
            spritesHP->push_back(spriteHP);

            textsHP->at(i)->setPosition(spritePlayers->at(i)->getPosition().x + 20, spritePlayers->at(i)->getPosition().y - textsHP->at(i)->getGlobalBounds().height - spriteHP->getTexture()->getSize().y / 2);

            sf::Sprite *spriteHonorPoints = new sf::Sprite();
            spriteHonorPoints->setTexture(*textureHonorPoints);
            spriteHonorPoints->setScale(0.5, 0.5);
            spriteHonorPoints->setPosition(spriteHP->getPosition().x + textureHP->getSize().x * 0.5 + 10 + textsHonorPoints->at(i)->getGlobalBounds().width + 5, spritePlayers->at(i)->getPosition().y - 2 * spriteHonorPoints->getTexture()->getSize().y / 3 - 5);
            spritesHonorPoints->push_back(spriteHonorPoints);

            textsHonorPoints->at(i)->setPosition(spriteHP->getPosition().x + textureHP->getSize().x * 0.5 + 10, spritePlayers->at(i)->getPosition().y - textsHP->at(i)->getGlobalBounds().height - spriteHP->getTexture()->getSize().y / 2);
        }

        sf::Text *textActualPlayerHP = new sf::Text(std::to_string(players->at(this->game->getIndexActualPlayer())->HP), *this->font, 20);
        textActualPlayerHP->setFillColor(sf::Color::White);

        sf::Text *textActualPlayerHonorPoints = new sf::Text(std::to_string(players->at(this->game->getIndexActualPlayer())->honorPoints), *this->font, 20);
        textActualPlayerHonorPoints->setFillColor(sf::Color::White);

        sf::Sprite *spriteActualPlayerHP = new sf::Sprite();
        spriteActualPlayerHP->setTexture(*textureHP);
        spriteActualPlayerHP->setScale(0.5, 0.5);
        spriteActualPlayerHP->setPosition(characterSprite->getPosition().x + textActualPlayerHP->getGlobalBounds().width + 15, characterSprite->getPosition().y - 2 * spriteActualPlayerHP->getTexture()->getSize().y / 3 - 5);

        textActualPlayerHP->setPosition(characterSprite->getPosition().x + 10, characterSprite->getPosition().y - textActualPlayerHP->getGlobalBounds().height - spriteActualPlayerHP->getTexture()->getSize().y / 2);

        sf::Sprite *spriteActualPlayerHonorPoints = new sf::Sprite();
        spriteActualPlayerHonorPoints->setTexture(*textureHonorPoints);
        spriteActualPlayerHonorPoints->setScale(0.5, 0.5);
        spriteActualPlayerHonorPoints->setPosition(spriteActualPlayerHP->getPosition().x + textureHP->getSize().x * 0.5 + 10 + textActualPlayerHonorPoints->getGlobalBounds().width + 5, characterSprite->getPosition().y - 2 * spriteActualPlayerHonorPoints->getTexture()->getSize().y / 3 - 5);

        textActualPlayerHonorPoints->setPosition(spriteActualPlayerHP->getPosition().x + textureHP->getSize().x * 0.5 + 10, characterSprite->getPosition().y - textActualPlayerHP->getGlobalBounds().height - spriteActualPlayerHP->getTexture()->getSize().y / 2);

        sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
        sf::Event event;

        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->window->close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A) {
                    this->game->changePlayer();
                }
            }
        }

        this->window->clear(sf::Color::Black);

        for (std::vector<sf::Sprite*>::iterator it = spriteCards->begin(); it != spriteCards->end(); it++) {
            this->window->draw(*(*it));
        }

        for (std::vector<sf::Sprite*>::iterator it = spriteDiscards->begin(); it != spriteDiscards->end(); it++) {
            this->window->draw(*(*it));
        }

        for (std::vector<sf::Sprite*>::iterator it = spritePlayers->begin(); it != spritePlayers->end(); it++) {
            this->window->draw(*(*it));
        }

        for (std::vector<sf::Sprite*>::size_type i = 0; i < spritePlayers->size(); i++) {
            this->window->draw(*textsHP->at(i));
            this->window->draw(*spritesHP->at(i));
            this->window->draw(*textsHonorPoints->at(i));
            this->window->draw(*spritesHonorPoints->at(i));
        }

        for (std::vector<sf::Sprite*>::iterator it = spriteHand->begin(); it != spriteHand->end(); it++) {
            if ((*it)->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                (*it)->setPosition((*it)->getPosition().x, SCREEN_HEIGHT - 100 - (*it)->getTexture()->getSize().y - 20);
            } else {
                (*it)->setPosition((*it)->getPosition().x, SCREEN_HEIGHT - 100 - (*it)->getTexture()->getSize().y);
            }

            this->window->draw(*(*it));
        }

        if (roleSpriteFace->getGlobalBounds().contains(mousePos.x, mousePos.y) || players->at(this->game->getIndexActualPlayer())->getRole()->getType() == RoleType::SHOGUN) {
            this->window->draw(*roleSpriteFace);
        } else {
            this->window->draw(*roleSpriteBack);
        }

        this->window->draw(*characterSprite);
        this->window->draw(*textActualPlayerHP);
        this->window->draw(*spriteActualPlayerHP);
        this->window->draw(*textActualPlayerHonorPoints);
        this->window->draw(*spriteActualPlayerHonorPoints);

        if (spriteShogunIndex != -1) {
            sf::CircleShape *circleShapeShogunPlayer = new sf::CircleShape();
            circleShapeShogunPlayer->setRadius(20);
            circleShapeShogunPlayer->setFillColor(sf::Color::Red);
            circleShapeShogunPlayer->setPosition(spritePlayers->at(spriteShogunIndex)->getPosition().x - 20, spritePlayers->at(spriteShogunIndex)->getPosition().y - 20);

            sf::Text *textShogunPlayer = new sf::Text("S", *this->font, 25);
            textShogunPlayer->setFillColor(sf::Color::White);
            textShogunPlayer->setPosition(circleShapeShogunPlayer->getPosition().x + circleShapeShogunPlayer->getRadius() - textShogunPlayer->getGlobalBounds().width / 2, circleShapeShogunPlayer->getPosition().y + circleShapeShogunPlayer->getRadius() - 3 * textShogunPlayer->getGlobalBounds().height / 4 - 1);
            
            this->window->draw(*circleShapeShogunPlayer);
            this->window->draw(*textShogunPlayer);

            delete circleShapeShogunPlayer;
            delete textShogunPlayer;
        }

        this->window->display();

        for (std::vector<sf::Sprite*>::iterator it = spriteCards->begin(); it != spriteCards->end(); it++) {
            delete *it;
        }
        delete spriteCards;

        for (std::vector<sf::Sprite*>::iterator it = spriteDiscards->begin(); it != spriteDiscards->end(); it++) {
            delete *it;
        }
        delete spriteDiscards;

        for (std::vector<sf::Sprite*>::iterator it = spritePlayers->begin(); it != spritePlayers->end(); it++) {
            delete *it;
        }
        delete spritePlayers;

        for (std::vector<sf::Sprite*>::iterator it = spriteHand->begin(); it != spriteHand->end(); it++) {
            delete *it;
        }
        delete spriteHand;

        delete roleTextureFace;
        delete roleSpriteFace;
        delete roleSpriteBack;
        delete characterTexture;
        delete characterSprite;

        for (std::vector<sf::Text*>::iterator it = textsHP->begin(); it != textsHP->end(); it++) {
            delete *it;
        }
        delete textsHP;

        for (std::vector<sf::Text*>::iterator it = textsHonorPoints->begin(); it != textsHonorPoints->end(); it++) {
            delete *it;
        }
        delete textsHonorPoints;

        for (std::vector<sf::Sprite*>::iterator it = spritesHP->begin(); it != spritesHP->end(); it++) {
            delete *it;
        }
        delete spritesHP;

        for (std::vector<sf::Sprite*>::iterator it = spritesHonorPoints->begin(); it != spritesHonorPoints->end(); it++) {
            delete *it;
        }
        delete spritesHonorPoints;

        delete textActualPlayerHP;
        delete textActualPlayerHonorPoints;
        delete spriteActualPlayerHP;
        delete spriteActualPlayerHonorPoints;
    }

    delete roleTextureBack;
    delete backCardTexture;
    delete textureHP;
    delete textureHonorPoints;
}

UI1::~UI1() {
    delete this->window;
    delete this->game;
}