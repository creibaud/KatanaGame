#include "UI.h"

UI::UI(sf::Font *font, sf::Image *HPImage, sf::Image *HonorImage, sf::Image *backRoleImage, sf::Image *backCardImage, std::vector<sf::Image*> *roleImages, std::vector<sf::Image*> *cardImages, std::vector<sf::Image*> *characterImages) 
    : font(font) {
    this->window = new sf::RenderWindow();

    this->HPTexture = new sf::Texture();
    this->HPTexture->loadFromImage(*HPImage);

    this->HonorTexture = new sf::Texture();
    this->HonorTexture->loadFromImage(*HonorImage);

    this->backRoleTexture = new sf::Texture();
    this->backRoleTexture->loadFromImage(*backRoleImage);

    this->backCardTexture = new sf::Texture();
    this->backCardTexture->loadFromImage(*backCardImage);

    this->roleTextures = new std::vector<sf::Texture*>();
    for (std::vector<sf::Image*>::iterator it = roleImages->begin(); it != roleImages->end(); it++) {
        sf::Texture *texture = new sf::Texture();
        texture->loadFromImage(*(*it));
        this->roleTextures->push_back(texture);
    }

    this->cardTextures = new std::vector<sf::Texture*>();
    for (std::vector<sf::Image*>::iterator it = cardImages->begin(); it != cardImages->end(); it++) {
        sf::Texture *texture = new sf::Texture();
        texture->loadFromImage(*(*it));
        this->cardTextures->push_back(texture);
    }

    this->characterTextures = new std::vector<sf::Texture*>();
    for (std::vector<sf::Image*>::iterator it = characterImages->begin(); it != characterImages->end(); it++) {
        sf::Texture *texture = new sf::Texture();
        texture->loadFromImage(*(*it));
        this->characterTextures->push_back(texture);
    }

    this->backRoleSprite = new sf::Sprite();
    this->backRoleSprite->setTexture(*this->backRoleTexture);
    this->backRoleSprite->setPosition(150, SCREEN_HEIGHT - 100 - this->backRoleSprite->getTexture()->getSize().y);

    this->playersSprites = new std::vector<sf::Sprite*>();

    this->HPSprites = new std::vector<sf::Sprite*>();
    this->HPTexts = new std::vector<sf::Text*>();
    this->HonorSprites = new std::vector<sf::Sprite*>();
    this->HonorTexts = new std::vector<sf::Text*>();
    
    this->actualPlayerSprite = new sf::Sprite();
    this->actualPlayerRoleSprite = new sf::Sprite();
    this->actualPlayerCardSprites = new std::vector<sf::Sprite*>();
    this->HPSpritePlayer = new sf::Sprite();
    this->HPTextPlayer = new sf::Text();
    this->HonorSpritePlayer = new sf::Sprite();
    this->HonorTextPlayer = new sf::Text();

    this->stackSprites = new std::vector<sf::Sprite*>();
    this->discardStackSprites = new std::vector<sf::Sprite*>();

    this->logs = new std::vector<std::string*>();
    this->logsTexts = new std::vector<sf::Text*>();
    this->logsBackground = new sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH / 3, SCREEN_HEIGHT));
    this->logsBackground->setFillColor(sf::Color(202, 199, 190));
    this->openLogsText = new sf::Text(">", *this->font, 75);
    this->openLogsText->setFillColor(sf::Color::White);
    this->openLogsBtn = new sf::RectangleShape(sf::Vector2f(75, 75));
    this->closeLogsText = new sf::Text("<", *this->font, 75);
    this->closeLogsText->setFillColor(sf::Color::White);
    this->closeLogsBtn = new sf::RectangleShape(sf::Vector2f(75, 75));
    this->isOpenLogsText = false;

    this->passParadeBtn = new Button(sf::Vector2f(SCREEN_WIDTH / 3 - 100, SCREEN_HEIGHT - 50), sf::Vector2f(200, 50), this->font, "No Parade", 20);
    this->endTurnBtn = new Button(sf::Vector2f(2 * SCREEN_WIDTH / 3 - 100, SCREEN_HEIGHT - 50), sf::Vector2f(200, 50), this->font, "End Turn", 20);
    this->discardingBtn = new Button(sf::Vector2f(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 50), sf::Vector2f(200, 50), this->font, "Discard", 20);
    this->isDiscarding = false;

    this->game = new Game();
    this->blocking = false;
    this->nbPlayers = 0;
    this->indexSelectedCard = -1;
    this->indexSelectedPlayer = -1;

    this->attackRapideNbDamage = 0;
}

void UI::menu(sf::Image *leftImage, sf::Image *rightImage) {
    this->window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Katana");
    this->window->setFramerateLimit(FPS);

    sf::Image icon;
    icon.loadFromFile("assets/images/icon.png");
    this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Menu *menu = new Menu(this->font, leftImage, rightImage);
    menu->display(*window);

    this->nbPlayers = menu->getNbPlayers();
    
    delete menu;
}

void UI::start() {
    this->window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Katana");
    this->window->setFramerateLimit(FPS);

    sf::Image icon;
    icon.loadFromFile("assets/images/icon.png");
    this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    this->game->setNbPlayers(this->nbPlayers);
    this->game->initRole();
    this->game->initCharacter();
    this->game->initCard();
    this->game->initPlayer();

    while (!this->game->isGameOver() && this->window->isOpen()) {
        sf::Event event;
        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->window->close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q) {
                    this->window->close();
                }
            }

            this->handleClickLogBtn(event);
            this->handleClickHandCard(event);
            this->handleClickPassParadeBtn(event);
            this->handleClickEndTurnBtn(event);
            this->handleClickDiscardingBtn(event);
            this->handleClickNobunaga(event);
        }

        this->window->clear(sf::Color::Black);

        this->update();
        this->display();

        this->window->display();
    }
}

void UI::update() {
    this->players = this->game->getPlayers();
    this->game->updateHonorPointsHP();
    if (!this->blocking) {
        this->indexActualPlayer = this->game->getIndexActualPlayer();
    }
    this->hand = this->players->at(this->indexActualPlayer)->getHand();
    this->stack = this->game->getCards();
    this->discardStack = this->game->getDiscards();
    this->logs = this->game->getLogs();

    this->setPlayersSprites();
    this->setActualPlayerSprite();
    this->setStackSprite();
    this->setDiscardStackSprite();
    this->setLogsTexts();

    if (this->isDiscarding && this->hand->size() <= 7) {
        this->isDiscarding = false;
    }
}

void UI::display() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
    for (std::vector<sf::Sprite*>::size_type i = 0; i < this->playersSprites->size(); i++) {
        this->window->draw(*this->playersSprites->at(i));
        this->window->draw(*this->HPSprites->at(i));
        this->window->draw(*this->HPTexts->at(i));
        this->window->draw(*this->HonorSprites->at(i));
        this->window->draw(*this->HonorTexts->at(i));
    }

    this->window->draw(*this->actualPlayerSprite);
    this->window->draw(*this->HPSpritePlayer);
    this->window->draw(*this->HPTextPlayer);
    this->window->draw(*this->HonorSpritePlayer);
    this->window->draw(*this->HonorTextPlayer);

    for (std::vector<sf::Sprite*>::size_type i = 0; i < this->actualPlayerCardSprites->size(); i++) {
        sf::Sprite* sprite = this->actualPlayerCardSprites->at(i);
        if ((sprite->getGlobalBounds().contains(mousePos.x, mousePos.y) && this->indexSelectedCard == -1) || this->indexSelectedCard == static_cast<int>(i)) {
            sprite->setPosition(sprite->getPosition().x, SCREEN_HEIGHT - 100 - sprite->getTexture()->getSize().y - 20);
        } else {
            sprite->setPosition(sprite->getPosition().x, SCREEN_HEIGHT - 100 - sprite->getTexture()->getSize().y);
        }

        this->window->draw(*sprite);
    }

    if (this->spriteShogunIndex != -1) {
        sf::CircleShape *circleShapeShogunPlayer = new sf::CircleShape();
        circleShapeShogunPlayer->setRadius(20);
        circleShapeShogunPlayer->setFillColor(sf::Color::Red);
        circleShapeShogunPlayer->setPosition(this->playersSprites->at(this->spriteShogunIndex)->getPosition().x - 20, this->playersSprites->at(this->spriteShogunIndex)->getPosition().y - 20);

        sf::Text *textShogunPlayer = new sf::Text("S", *this->font, 25);
        textShogunPlayer->setFillColor(sf::Color::White);
        textShogunPlayer->setPosition(circleShapeShogunPlayer->getPosition().x + circleShapeShogunPlayer->getRadius() - textShogunPlayer->getGlobalBounds().width / 2, circleShapeShogunPlayer->getPosition().y + circleShapeShogunPlayer->getRadius() - 3 * textShogunPlayer->getGlobalBounds().height / 4 - 1);
        
        this->window->draw(*circleShapeShogunPlayer);
        this->window->draw(*textShogunPlayer);

        delete circleShapeShogunPlayer;
        delete textShogunPlayer;
    }

    if (this->actualPlayerRoleSprite->getGlobalBounds().contains(mousePos.x, mousePos.y) || this->players->at(this->indexActualPlayer)->getRole()->getType() == RoleType::SHOGUN) {
        this->window->draw(*this->actualPlayerRoleSprite);
    } else {
        this->window->draw(*this->backRoleSprite);
    }

    for (std::vector<sf::Sprite*>::iterator it = this->stackSprites->begin(); it != this->stackSprites->end(); it++) {
        this->window->draw(*(*it));
    }

    for (std::vector<sf::Sprite*>::iterator it = this->discardStackSprites->begin(); it != this->discardStackSprites->end(); it++) {
        this->window->draw(*(*it));
    }

    if (this->isOpenLogsText) {
        this->window->draw(*this->logsBackground);
        for (std::vector<sf::Text*>::iterator it = this->logsTexts->begin(); it != this->logsTexts->end(); it++) {
            this->window->draw(*(*it));
        }

        for (std::vector<sf::Text*>::iterator it = this->logsTexts->begin(); it != this->logsTexts->end(); it++) {
            this->window->draw(*(*it));
        }
        this->window->draw(*this->openLogsText);
    } else {
        this->window->draw(*this->closeLogsText);
    }

    if (this->blocking) {
        this->passParadeBtn->draw(*this->window);
    }

    if (this->hand->size() > 7 && !this->isDiscarding && !this->blocking) {
        this->discardingBtn->draw(*this->window);
    }

    if (this->hand->size() <= 7 && !this->isDiscarding && !this->blocking) {
        this->endTurnBtn->draw(*this->window);
    }
}

void UI::setPlayersSprites() {
    for (std::vector<sf::Sprite*>::size_type i = 0; i < this->playersSprites->size(); i++) {
        delete this->playersSprites->at(i);
        delete this->HPSprites->at(i);
        delete this->HPTexts->at(i);
        delete this->HonorSprites->at(i);
        delete this->HonorTexts->at(i);
    }
    this->playersSprites->clear();
    this->HPSprites->clear();
    this->HPTexts->clear();
    this->HonorSprites->clear();
    this->HonorTexts->clear();

    this->spriteShogunIndex = 0;
    if (this->indexActualPlayer + 1 < this->game->getNbPlayers()) {
        for (int i = this->indexActualPlayer + 1; i < this->game->getNbPlayers(); i++) {
            this->setSpriteHonorCharactersHP(i);
            this->spriteShogunIndex++;
        }

        for (int i = 0; i < this->indexActualPlayer; i++) {
            this->setSpriteHonorCharactersHP(i);
        }
    } else {
        for (int i = 0; i < this->game->getNbPlayers() - 1; i++) {
            this->setSpriteHonorCharactersHP(i);
        }

        this->spriteShogunIndex = 0;
    }

    if (this->players->at(this->indexActualPlayer)->getRole()->getType() == RoleType::SHOGUN) {
        this->spriteShogunIndex = -1;
    }

    switch (this->game->getNbPlayers()) {
        case 4:
            this->playersSprites->at(0)->setPosition(150, SCREEN_HEIGHT / 2 - this->playersSprites->at(0)->getTexture()->getSize().y / 2 - 50);
            this->playersSprites->at(1)->setPosition(SCREEN_WIDTH / 2 - this->playersSprites->at(1)->getTexture()->getSize().x / 2, 100);
            this->playersSprites->at(2)->setPosition(SCREEN_WIDTH - 215 - this->playersSprites->at(2)->getTexture()->getSize().x / 2, SCREEN_HEIGHT / 2 - this->playersSprites->at(1)->getTexture()->getSize().y / 2 - 50);
            break;
        case 5:
            this->playersSprites->at(0)->setPosition(150, SCREEN_HEIGHT / 2 - this->playersSprites->at(0)->getTexture()->getSize().y / 2 - 50);
            this->playersSprites->at(1)->setPosition(SCREEN_WIDTH / 2 - this->playersSprites->at(1)->getTexture()->getSize().x / 2 - 250, 100);
            this->playersSprites->at(2)->setPosition(SCREEN_WIDTH / 2 - this->playersSprites->at(2)->getTexture()->getSize().x / 2 + 250, 100);
            this->playersSprites->at(3)->setPosition(SCREEN_WIDTH - 215 - this->playersSprites->at(3)->getTexture()->getSize().x / 2, SCREEN_HEIGHT / 2 - this->playersSprites->at(1)->getTexture()->getSize().y / 2 - 50);
            break;
        case 6:
            this->playersSprites->at(0)->setPosition(150, SCREEN_HEIGHT / 2 - this->playersSprites->at(0)->getTexture()->getSize().y / 2 - 50);
            this->playersSprites->at(1)->setPosition(SCREEN_WIDTH / 2 - this->playersSprites->at(1)->getTexture()->getSize().x / 2 - 375, 175);
            this->playersSprites->at(2)->setPosition(SCREEN_WIDTH / 2 - this->playersSprites->at(2)->getTexture()->getSize().x / 2, 100);
            this->playersSprites->at(3)->setPosition(SCREEN_WIDTH / 2 - this->playersSprites->at(3)->getTexture()->getSize().x / 2 + 375, 175);
            this->playersSprites->at(4)->setPosition(SCREEN_WIDTH - 215 - this->playersSprites->at(4)->getTexture()->getSize().x / 2, SCREEN_HEIGHT / 2 - this->playersSprites->at(1)->getTexture()->getSize().y / 2 - 50);
            break;
        case 7:
            this->playersSprites->at(0)->setPosition(150, SCREEN_HEIGHT / 2 - this->playersSprites->at(0)->getTexture()->getSize().y / 2 - 50);
            this->playersSprites->at(1)->setPosition(SCREEN_WIDTH / 2 - this->playersSprites->at(1)->getTexture()->getSize().x / 2 - 450, 175);
            this->playersSprites->at(2)->setPosition(SCREEN_WIDTH / 2 - this->playersSprites->at(2)->getTexture()->getSize().x / 2 - 150, 100);
            this->playersSprites->at(3)->setPosition(SCREEN_WIDTH / 2 - this->playersSprites->at(3)->getTexture()->getSize().x / 2 + 150, 100);
            this->playersSprites->at(4)->setPosition(SCREEN_WIDTH / 2 - this->playersSprites->at(4)->getTexture()->getSize().x / 2 + 450, 175);
            this->playersSprites->at(5)->setPosition(SCREEN_WIDTH - 215 - this->playersSprites->at(5)->getTexture()->getSize().x / 2, SCREEN_HEIGHT / 2 - this->playersSprites->at(1)->getTexture()->getSize().y / 2 - 50);
        default:
            break;
    }

    for (std::vector<sf::Sprite*>::size_type i = 0; i < this->playersSprites->size(); i++) {
        this->HPSprites->at(i)->setPosition(this->playersSprites->at(i)->getPosition().x + this->HPTexts->at(i)->getGlobalBounds().width + 25, this->playersSprites->at(i)->getPosition().y - 2 * this->HPSprites->at(i)->getTexture()->getSize().y / 3 - 5);
        this->HPTexts->at(i)->setPosition(this->playersSprites->at(i)->getPosition().x + 20, this->playersSprites->at(i)->getPosition().y - this->HPTexts->at(i)->getGlobalBounds().height - this->HPSprites->at(i)->getTexture()->getSize().y / 2);

        this->HonorSprites->at(i)->setPosition(this->HPSprites->at(i)->getPosition().x + this->HPTexture->getSize().x * 0.5 + 10 + this->HonorTexts->at(i)->getGlobalBounds().width + 5, this->playersSprites->at(i)->getPosition().y - 2 * this->HonorSprites->at(i)->getTexture()->getSize().y / 3 - 5);
        this->HonorTexts->at(i)->setPosition(this->HPSprites->at(i)->getPosition().x + this->HPTexture->getSize().x * 0.5 + 10, this->playersSprites->at(i)->getPosition().y - this->HPTexts->at(i)->getGlobalBounds().height - this->HPSprites->at(i)->getTexture()->getSize().y / 2);
    }
}

void UI::setActualPlayerSprite() {
    Player* player = this->game->getPlayers()->at(this->indexActualPlayer);
    int characterIndex = player->getCharacter()->getIndex();
    sf::Texture* texture = this->characterTextures->at(characterIndex);
    this->actualPlayerSprite->setTexture(*texture);
    this->actualPlayerSprite->setPosition(SCREEN_WIDTH - 150 - this->actualPlayerSprite->getTexture()->getSize().x, SCREEN_HEIGHT - 100 - this->actualPlayerSprite->getTexture()->getSize().y);

    int roleIndex = player->getRole()->getIndex();
    sf::Texture *roleTexture = this->roleTextures->at(roleIndex);
    this->actualPlayerRoleSprite->setTexture(*roleTexture);
    this->actualPlayerRoleSprite->setPosition(150, SCREEN_HEIGHT - 100 - this->actualPlayerRoleSprite->getTexture()->getSize().y);

    sf::Text *HPtext = new sf::Text(std::to_string(player->HP), *this->font, 20);
    HPtext->setFillColor(sf::Color::White);
    this->HPTextPlayer = HPtext;

    sf::Sprite *HPSprite = new sf::Sprite();
    HPSprite->setTexture(*this->HPTexture);
    HPSprite->setScale(0.5, 0.5);
    this->HPSpritePlayer = HPSprite;

    sf::Text *HonorText = new sf::Text(std::to_string(player->honorPoints), *this->font, 20);
    HonorText->setFillColor(sf::Color::White);
    this->HonorTextPlayer = HonorText;

    sf::Sprite *HonorSprite = new sf::Sprite();
    HonorSprite->setTexture(*this->HonorTexture);
    HonorSprite->setScale(0.5, 0.5);
    this->HonorSpritePlayer = HonorSprite;

    this->HPSpritePlayer->setPosition(this->actualPlayerSprite->getPosition().x + this->HPTextPlayer->getGlobalBounds().width + 15, this->actualPlayerSprite->getPosition().y - 2 * this->HPSpritePlayer->getTexture()->getSize().y / 3 - 5);
    this->HPTextPlayer->setPosition(this->actualPlayerSprite->getPosition().x + 10, this->actualPlayerSprite->getPosition().y - this->HPTextPlayer->getGlobalBounds().height - this->HPSpritePlayer->getTexture()->getSize().y / 2);

    this->HonorSpritePlayer->setPosition(this->HPSpritePlayer->getPosition().x + this->HPTexture->getSize().x * 0.5 + 10 + this->HonorTextPlayer->getGlobalBounds().width + 5, this->actualPlayerSprite->getPosition().y - 2 * this->HonorSpritePlayer->getTexture()->getSize().y / 3 - 5);
    this->HonorTextPlayer->setPosition(this->HPSpritePlayer->getPosition().x + this->HPTexture->getSize().x * 0.5 + 10, this->actualPlayerSprite->getPosition().y - this->HPTextPlayer->getGlobalBounds().height - this->HPSpritePlayer->getTexture()->getSize().y / 2);

    this->setHandSprite();
}

void UI::setSpriteHonorCharactersHP(int index) {
    Player* player = this->game->getPlayers()->at(index);
    int characterIndex = player->getCharacter()->getIndex();

    sf::Texture* texture = this->characterTextures->at(characterIndex);
    sf::Sprite* sprite = new sf::Sprite();
    sprite->setTexture(*texture);
    this->playersSprites->push_back(sprite);

    sf::Text *HPtext = new sf::Text(std::to_string(players->at(index)->HP), *this->font, 20);
    HPtext->setFillColor(sf::Color::White);
    this->HPTexts->push_back(HPtext);
    
    sf::Sprite *HPSprite = new sf::Sprite();
    HPSprite->setTexture(*this->HPTexture);
    HPSprite->setScale(0.5, 0.5);
    this->HPSprites->push_back(HPSprite);
    
    sf::Text *HonorText = new sf::Text(std::to_string(players->at(index)->honorPoints), *this->font, 20);
    HonorText->setFillColor(sf::Color::White);
    this->HonorTexts->push_back(HonorText);

    sf::Sprite *HonorSprite = new sf::Sprite();
    HonorSprite->setTexture(*this->HonorTexture);
    HonorSprite->setScale(0.5, 0.5);
    this->HonorSprites->push_back(HonorSprite);
}

void UI::setHandSprite() {
    for (std::vector<sf::Sprite*>::iterator it = this->actualPlayerCardSprites->begin(); it != this->actualPlayerCardSprites->end(); it++) {
        delete *it;
    }
    this->actualPlayerCardSprites->clear();

    for (std::vector<Card*>::size_type i = 0; i < this->hand->size(); i++) {
        int index = this->hand->at(i)->getIndex();
        sf::Sprite *sprite = new sf::Sprite();
        sprite->setTexture(*this->cardTextures->at(index));
        sprite->setPosition(SCREEN_WIDTH / 2 - hand->size() * sprite->getTexture()->getSize().x / 2 + i * (sprite->getTexture()->getSize().x + 5), SCREEN_HEIGHT - 100 - sprite->getTexture()->getSize().y);
        this->actualPlayerCardSprites->push_back(sprite);
    }
}

void UI::setStackSprite() {
    for (std::vector<sf::Sprite*>::iterator it = this->stackSprites->begin(); it != this->stackSprites->end(); it++) {
        delete *it;
    }
    this->stackSprites->clear();

    for (std::vector<Card*>::size_type i = 0; i < this->stack->size(); i++) {
        sf::Sprite *sprite = new sf::Sprite();
        sprite->setTexture(*backCardTexture);
        sprite->setPosition(SCREEN_WIDTH / 2 + 5, SCREEN_HEIGHT / 2 - sprite->getTexture()->getSize().y / 2 - i);
        this->stackSprites->push_back(sprite);
    }
}

void UI::setDiscardStackSprite() {
    for (std::vector<sf::Sprite*>::iterator it = this->discardStackSprites->begin(); it != this->discardStackSprites->end(); it++) {
        delete *it;
    }
    this->discardStackSprites->clear();

    for (std::vector<Card*>::size_type i = 0; i < this->discardStack->size(); i++) {
        int index = this->discardStack->at(i)->getIndex();

        sf::Sprite *sprite = new sf::Sprite();
        sprite->setTexture(*this->cardTextures->at(index));
        sprite->setPosition(SCREEN_WIDTH / 2 - 5 - sprite->getTexture()->getSize().x, SCREEN_HEIGHT / 2 - sprite->getTexture()->getSize().y / 2 - i);
        this->discardStackSprites->push_back(sprite);
    }
}

void UI::setLogsTexts() {
    this->closeLogsText->setPosition(SCREEN_WIDTH - this->closeLogsText->getGlobalBounds().width - 25, SCREEN_HEIGHT / 2 - this->closeLogsText->getGlobalBounds().height / 2);
    this->closeLogsBtn->setPosition(SCREEN_WIDTH - this->closeLogsText->getGlobalBounds().width - 45, SCREEN_HEIGHT / 2 - this->closeLogsText->getGlobalBounds().height / 2);
    this->openLogsText->setPosition(2 * SCREEN_WIDTH / 3 - this->openLogsText->getGlobalBounds().width - 25, SCREEN_HEIGHT / 2 - this->openLogsText->getGlobalBounds().height / 2);
    this->openLogsBtn->setPosition(2 * SCREEN_WIDTH / 3 - this->openLogsText->getGlobalBounds().width - 45, SCREEN_HEIGHT / 2 - this->openLogsText->getGlobalBounds().height / 2);

    for (std::vector<sf::Text*>::iterator it = this->logsTexts->begin(); it != this->logsTexts->end(); it++) {
        delete *it;
    }
    this->logsTexts->clear();

    for (std::vector<std::string*>::size_type i = 0; i < this->logs->size(); i++) {
        sf::Text *text = new sf::Text(*this->logs->at(i), *this->font, 20);
        text->setFillColor(sf::Color::White);
        text->setPosition(2 * SCREEN_WIDTH / 3 + 10, 10 + i * 20);
        this->logsTexts->push_back(text);
    }

    if (this->isOpenLogsText) {
        this->logsBackground->setPosition(2 * SCREEN_WIDTH / 3, 0);
    } else {
        this->logsBackground->setPosition(SCREEN_WIDTH, 0);
    }
}

void UI::handleClickLogBtn(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (this->isOpenLogsText) {
                if (this->openLogsBtn->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    this->isOpenLogsText = false;
                }
            } else {
                if (this->closeLogsBtn->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    this->isOpenLogsText = true;
                }
            }
        }
    }
}

void UI::handleClickHandCard(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
            for (std::vector<sf::Sprite*>::size_type i = 0; i < this->actualPlayerCardSprites->size(); i++) {
                if (!this->blocking) {
                    if (this->actualPlayerCardSprites->at(i)->getGlobalBounds().contains(mousePos.x, mousePos.y) && this->indexSelectedCard == -1) {
                        this->indexSelectedCard = i;

                        if (this->hand->at(i)->getType() == CardType::WEAPON && this->players->at(this->indexActualPlayer)->nbAttack >= this->players->at(this->indexActualPlayer)->getMaxNbAttack()) {
                            this->indexSelectedCard = -1;
                            break;
                        }

                        if (this->isDiscarding) {
                            this->indexSelectedCard = -1;
                            this->game->discard(this->players->at(this->indexActualPlayer), this->hand->at(i));
                            break;
                        } else if (!this->isDiscarding && this->hand->at(i)->getType() != CardType::WEAPON) {
                            this->indexSelectedCard = -1;
                            
                            switch (this->hand->at(i)->getType()) {
                                case CardType::ACTION: {
                                    Action *action = dynamic_cast<Action*>(this->hand->at(i));
                                    switch (action->getActionType()) {
                                        case ActionType::CRI_DE_GUERRE: {
                                            this->game->criDeGuerreFunction();
                                            this->game->discard(this->players->at(this->indexActualPlayer), this->hand->at(i));
                                            break;
                                        }
                                        case ActionType::DAIMYO: {
                                            this->game->daimyoFunction();
                                            this->game->discard(this->players->at(this->indexActualPlayer), this->hand->at(i));
                                            break;
                                        }
                                        case ActionType::DIVERSION: {
                                            this->indexSelectedCard = i;
                                            break;
                                        }
                                        case ActionType::GEISHA: {
                                            this->indexSelectedCard = i;
                                            break;
                                        }
                                        case ActionType::MEDITATION: {
                                            this->players->at(this->indexActualPlayer)->meditationFunction();
                                            this->indexSelectedCard = i;
                                            break;
                                        }
                                        case ActionType::PARADE: {
                                            break;
                                        }
                                        case ActionType::CEREMONIE_DU_THE: {
                                            this->game->ceremonieDuTheFunction();
                                            this->game->discard(this->players->at(this->indexActualPlayer), this->hand->at(i));
                                            break;
                                        }
                                        case ActionType::JU_JITSU: {
                                            this->game->juJitsuFunction();
                                            this->game->discard(this->players->at(this->indexActualPlayer), this->hand->at(i));
                                            break;
                                        }
                                        default: {
                                            break;
                                        }
                                    }
                                    break;
                                }
                                case CardType::PERMANENT: {
                                    Permanent *permanent = dynamic_cast<Permanent*>(this->hand->at(i));

                                    switch (permanent->getPermanentType()) {
                                        case PermanentType::ATTAQUE_RAPIDE: {
                                            this->players->at(this->indexActualPlayer)->getPermanentCardsPlayed()->push_back(permanent);
                                            this->hand->erase(this->hand->begin() + i);
                                            this->attackRapideNbDamage = this->players->at(this->game->getIndexActualPlayer())->attackRapideFunction();
                                            break;
                                        }
                                        case PermanentType::CODE_DU_BUSHIDO: {
                                            if (!this->game->isCarteDuBushidoInGame) {
                                                int copyIndexActualPlayer = this->indexActualPlayer;
                                                copyIndexActualPlayer++;

                                                if (copyIndexActualPlayer == this->nbPlayers) {
                                                    copyIndexActualPlayer = 0;
                                                }

                                                this->players->at(copyIndexActualPlayer)->getPermanentCardsPlayed()->push_back(permanent);
                                                this->hand->erase(this->hand->begin() + i);
                                                this->game->isCarteDuBushidoInGame = true;
                                            }
                                            break;
                                        }
                                        case PermanentType::ARMURE: {
                                            this->players->at(this->indexActualPlayer)->getPermanentCardsPlayed()->push_back(permanent);
                                            this->hand->erase(this->hand->begin() + i);
                                            break;
                                        }
                                        case PermanentType::CONCENTRATION: {
                                            this->players->at(this->indexActualPlayer)->getPermanentCardsPlayed()->push_back(permanent);
                                            this->hand->erase(this->hand->begin() + i);
                                            this->players->at(this->game->getIndexActualPlayer())->concentrationFunction();
                                            break;
                                        }
                                        default: {
                                            break;
                                        }
                                    }
                                    break;
                                }
                                case CardType::WEAPON: {
                                    break;
                                }
                                default: {
                                    break;
                                }
                            }
                            break;
                        }
                    } else if (this->actualPlayerCardSprites->at(i)->getGlobalBounds().contains(mousePos.x, mousePos.y) && this->indexSelectedCard == static_cast<int>(i)) {
                        this->indexSelectedCard = -1;
                        break;
                    }
                } else {
                    if (this->actualPlayerCardSprites->at(i)->getGlobalBounds().contains(mousePos.x, mousePos.y) && this->hand->at(i)->getType() == CardType::ACTION) {
                        Action *action = dynamic_cast<Action *>(this->hand->at(i));
                        if (action && action->getActionType() == ActionType::PARADE) {
                            this->game->discard(this->players->at(this->indexActualPlayer), this->hand->at(i));
                            this->blocking = false;
                            this->indexActualPlayer = this->game->getIndexActualPlayer();
                            break;
                        }
                    } else if (this->actualPlayerCardSprites->at(i)->getGlobalBounds().contains(mousePos.x, mousePos.y) && this->players->at(this->indexActualPlayer)->getCharacter()->getType() == CharacterType::HANZO && this->hand->at(i)->getType() == CardType::WEAPON) {
                        this->game->discard(this->players->at(this->indexActualPlayer), this->hand->at(i));
                        this->blocking = false;
                        this->indexActualPlayer = this->game->getIndexActualPlayer();
                        break;
                    }
                }
            }

            if (this->indexSelectedCard != -1 && this->indexSelectedPlayer == -1 && !this->blocking) {
                for (std::vector<sf::Sprite*>::size_type i = 0; i < this->playersSprites->size(); i++) {
                    if (this->playersSprites->at(i)->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        this->indexSelectedPlayer = (i + this->indexActualPlayer + 1) % this->nbPlayers;

                        if (this->hand->at(this->indexSelectedCard)->getType() == CardType::WEAPON) {
                            Weapon *weapon = dynamic_cast<Weapon*>(this->hand->at(this->indexSelectedCard));
                            if (weapon && this->game->attack(weapon, this->players->at(this->indexSelectedPlayer)) && this->players->at(this->indexActualPlayer)->nbAttack < this->players->at(this->indexActualPlayer)->getMaxNbAttack()) {
                                this->game->discard(this->players->at(this->indexActualPlayer), this->hand->at(this->indexSelectedCard));
                                
                                this->players->at(this->indexActualPlayer)->nbAttack++;
                                this->indexActualPlayer = this->indexSelectedPlayer;
                                if (this->game->canBlock(this->players->at(this->indexActualPlayer))) {
                                    this->blocking = true;
                                } else {
                                    int damage = weapon->getDamage() + this->attackRapideNbDamage;
                
                                    if (this->players->at(this->indexSelectedPlayer)->getCharacter()->getType() == CharacterType::GINCHIYO) {
                                        damage = std::min(1, damage - 1);
                                    } else if (this->players->at(this->game->getIndexActualPlayer())->getCharacter()->getType() == CharacterType::MUSASHI) {
                                        damage++;
                                    } else if (this->players->at(this->game->getIndexActualPlayer())->getCharacter()->getType() == CharacterType::TOMOE) {
                                        this->game->pick(this->players->at(this->game->getIndexActualPlayer()), 1);
                                    } else if (this->players->at(this->indexSelectedPlayer)->getCharacter()->getType() == CharacterType::USHIWAKA) {
                                        this->game->pick(this->players->at(this->indexSelectedPlayer), damage);
                                    }

                                    this->players->at(this->indexSelectedPlayer)->HP -= damage;

                                    if (this->players->at(this->indexSelectedPlayer)->HP <= 0) {
                                        this->players->at(this->indexSelectedPlayer)->honorPoints--;
                                        this->players->at(this->game->getIndexActualPlayer())->honorPoints++;
                                    }
                                    this->blocking = false;
                                }
                            }
                        } else if (this->hand->at(this->indexSelectedCard)->getType() == CardType::ACTION) {
                            Action *action = dynamic_cast<Action*>(this->hand->at(this->indexSelectedCard));

                            if (action->getActionType() == ActionType::DIVERSION) {
                                std::vector<Card*> *targetHand = this->players->at(this->indexSelectedPlayer)->getHand();

                                std::random_device rd;
                                std::mt19937 g(rd());

                                if (!targetHand->empty() && !this->players->at(this->indexSelectedPlayer)->isDown()) {
                                    std::uniform_int_distribution<int> distribution(0, targetHand->size() - 1);
                                    int randomIndex = distribution(g);
                                    Card* randomCard = targetHand->at(randomIndex);

                                    targetHand->erase(targetHand->begin() + randomIndex);
                                    this->hand->push_back(randomCard);
                                    this->game->discard(this->players->at(this->indexActualPlayer), this->hand->at(this->indexSelectedCard));
                                }
                            } else if (action->getActionType() == ActionType::MEDITATION) {
                                this->game->pick(this->players->at(this->indexSelectedPlayer), 1);
                                this->game->discard(this->players->at(this->indexActualPlayer), this->hand->at(this->indexSelectedCard));
                            } else if (action->getActionType() == ActionType::GEISHA) {
                                this->game->geishaFunction(this->players->at(this->indexSelectedPlayer));
                                this->game->discard(this->players->at(this->indexActualPlayer), this->hand->at(this->indexSelectedCard));
                            }
                        }

                        this->indexSelectedCard = -1;
                        this->indexSelectedPlayer = -1;
                        break;
                    } else if (this->actualPlayerSprite->getGlobalBounds().contains(mousePos.x, mousePos.y) && this->indexSelectedPlayer == -1) {
                        if (this->hand->at(this->indexSelectedCard)->getType() == CardType::ACTION) {
                            Action *action = dynamic_cast<Action*>(this->hand->at(this->indexSelectedCard));
                            if (action->getActionType() == ActionType::GEISHA) {
                                this->game->geishaFunction();
                                this->game->discard(this->players->at(this->indexActualPlayer), this->hand->at(this->indexSelectedCard));
                                this->indexSelectedCard = -1;
                                this->indexSelectedPlayer = -1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

void UI::handleClickPassParadeBtn(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (this->blocking && this->passParadeBtn->isClicked(*this->window)) {
                Weapon *weapon = dynamic_cast<Weapon*>(this->discardStack->back());
                int damage = weapon->getDamage() + this->attackRapideNbDamage;
                
                if (this->players->at(this->indexActualPlayer)->getCharacter()->getType() == CharacterType::GINCHIYO) {
                    damage = std::min(1, damage - 1);
                } else if (this->players->at(this->game->getIndexActualPlayer())->getCharacter()->getType() == CharacterType::MUSASHI) {
                    damage++;
                } else if (this->players->at(this->game->getIndexActualPlayer())->getCharacter()->getType() == CharacterType::TOMOE) {
                    this->game->pick(this->players->at(this->game->getIndexActualPlayer()), 1);
                } else if (this->players->at(this->indexActualPlayer)->getCharacter()->getType() == CharacterType::USHIWAKA) {
                    this->game->pick(this->players->at(this->indexActualPlayer), damage);
                }

                this->players->at(this->indexActualPlayer)->HP -= damage;
                if (this->players->at(this->indexActualPlayer)->HP <= 0) {
                    this->players->at(this->indexActualPlayer)->honorPoints--;
                    this->players->at(this->game->getIndexActualPlayer())->honorPoints++;
                }
                this->blocking = false;
            }
        }
    }
}

void UI::handleClickEndTurnBtn(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (this->hand->size() <= 7 && this->endTurnBtn->isClicked(*this->window)) {
                this->game->changePlayer();
            }
        }
    }
}

void UI::handleClickDiscardingBtn(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (this->hand->size() > 7 && !this->isDiscarding && !this->blocking && this->discardingBtn->isClicked(*this->window)) {
                this->isDiscarding = true;
            }
        }
    }
}

void UI::handleClickNobunaga(sf::Event event) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (this->players->at(this->game->getIndexActualPlayer())->getCharacter()->getType() == CharacterType::NOBUNAGA) {
                if (this->actualPlayerSprite->getGlobalBounds().contains(mousePos.x, mousePos.y) && !this->isDiscarding && !this->blocking) {
                    if (this->players->at(this->game->getIndexActualPlayer())->HP > 1) {
                        this->game->pick(this->players->at(this->game->getIndexActualPlayer()), 1);
                        this->players->at(this->game->getIndexActualPlayer())->HP -= 1;
                    }
                }
            }
        }
    }
}

void UI::score() {
    this->window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Katana");
    this->window->setFramerateLimit(FPS);

    sf::Text *text = new sf::Text("Score", *this->font, 50);
    text->setFillColor(sf::Color::Red);
    text->setPosition(SCREEN_WIDTH / 2 - text->getGlobalBounds().width / 2, 50);

    std::vector<sf::Text*> texts;
    std::vector<sf::RectangleShape*> rectangles;

    int shogunTeamScore = 0;
    int ninjaTeamScore = 0;
    int roninTeamScore = 0;

    int scorePlayer = 0;

    for (std::vector<Player*>::iterator it = this->players->begin(); it != this->players->end(); it++) {
        scorePlayer = 0;

        switch ((*it)->getRole()->getType()){
            case RoleType::SHOGUN: {
                scorePlayer = (*it)->honorPoints;
                shogunTeamScore += scorePlayer;
                break;
            }
            case RoleType::SAMURAI: {
                if (this->nbPlayers == 4 || this->nbPlayers == 6) {
                    scorePlayer = (*it)->honorPoints * 2;
                } else {
                    scorePlayer = (*it)->honorPoints;
                }
                shogunTeamScore += scorePlayer;
                break;
            }
            case RoleType::NINJA: {
                if (this->nbPlayers == 4) {
                    int highestLevel = 0;
                    int smallestLevel = 0;

                    for (std::vector<Player*>::iterator it = this->players->begin(); it != this->players->end(); it++) {
                        if ((*it)->getRole()->getLevel() > highestLevel) {
                            highestLevel = (*it)->getRole()->getLevel();
                        }

                        if ((*it)->getRole()->getLevel() < smallestLevel) {
                            smallestLevel = (*it)->getRole()->getLevel();
                        }
                    }

                    if ((*it)->getRole()->getLevel() == highestLevel) {
                        scorePlayer = (*it)->honorPoints * 2;
                    } else {
                        scorePlayer = (*it)->honorPoints;
                    }
                } else {
                    scorePlayer = (*it)->honorPoints;
                }
                ninjaTeamScore += scorePlayer;
                break;
            }
            case RoleType::RONIN: {
                if (this->nbPlayers == 6 || this->nbPlayers == 7) {
                    scorePlayer = (*it)->honorPoints * 3;
                } else {
                    scorePlayer = (*it)->honorPoints * 2;
                }
                roninTeamScore += scorePlayer;
                break;
            }
            default:
                break;
        }

        sf::RectangleShape *rect = new sf::RectangleShape(sf::Vector2f(600, 75));
        rect->setFillColor(sf::Color::White);
        rect->setPosition(150, 200 + (it - this->players->begin()) * 125);
        rectangles.push_back(rect);

        sf::Text *text = new sf::Text((*it)->getCharacter()->getName() + " (" + (*it)->getRole()->getName() + ") : ", *this->font, 30);
        text->setFillColor(sf::Color::Black);
        text->setPosition(15 + rect->getPosition().x, rect->getPosition().y + rect->getSize().y / 2 - text->getGlobalBounds().height / 2 - 3);
        texts.push_back(text);

        sf::Text *textHonor = new sf::Text(std::to_string(scorePlayer), *this->font, 30);
        textHonor->setFillColor(sf::Color::Black);
        textHonor->setPosition(rect->getPosition().x + rect->getSize().x - textHonor->getGlobalBounds().width - 15, rect->getPosition().y + rect->getSize().y / 2 - textHonor->getGlobalBounds().height / 2 - 3);
        texts.push_back(textHonor);
    }

    sf::RectangleShape *shogunTeam = new sf::RectangleShape(sf::Vector2f(600, 75));
    shogunTeam->setFillColor(sf::Color::Yellow);
    shogunTeam->setPosition(SCREEN_WIDTH - 150 - shogunTeam->getSize().x, 200);

    sf::Text *shogunTeamText = new sf::Text("Team Shogun & Samurai :", *this->font, 30);
    shogunTeamText->setFillColor(sf::Color::Black);
    shogunTeamText->setPosition(15 + shogunTeam->getPosition().x, shogunTeam->getPosition().y + shogunTeam->getSize().y / 2 - shogunTeamText->getGlobalBounds().height / 2 - 4);

    sf::Text *shogunTeamScoreText = new sf::Text(std::to_string(shogunTeamScore), *this->font, 30);
    shogunTeamScoreText->setFillColor(sf::Color::Black);
    shogunTeamScoreText->setPosition(shogunTeam->getPosition().x + shogunTeam->getSize().x - shogunTeamScoreText->getGlobalBounds().width - 15, shogunTeam->getPosition().y + shogunTeam->getSize().y / 2 - shogunTeamScoreText->getGlobalBounds().height / 2 - 4);

    sf::RectangleShape *ninjaTeam = new sf::RectangleShape(sf::Vector2f(600, 75));
    ninjaTeam->setFillColor(sf::Color::Blue);
    ninjaTeam->setPosition(SCREEN_WIDTH - 150 - ninjaTeam->getSize().x, 200 + 125);

    sf::Text *ninjaTeamText = new sf::Text("Team Ninja :", *this->font, 30);
    ninjaTeamText->setFillColor(sf::Color::White);
    ninjaTeamText->setPosition(15 + ninjaTeam->getPosition().x, ninjaTeam->getPosition().y + ninjaTeam->getSize().y / 2 - ninjaTeamText->getGlobalBounds().height / 2 - 4);

    sf::Text *ninjaTeamScoreText = new sf::Text(std::to_string(ninjaTeamScore), *this->font, 30);
    ninjaTeamScoreText->setFillColor(sf::Color::White);
    ninjaTeamScoreText->setPosition(ninjaTeam->getPosition().x + ninjaTeam->getSize().x - ninjaTeamScoreText->getGlobalBounds().width - 15, ninjaTeam->getPosition().y + ninjaTeam->getSize().y / 2 - ninjaTeamScoreText->getGlobalBounds().height / 2 - 4);

    sf::RectangleShape *roninTeam = new sf::RectangleShape(sf::Vector2f(600, 75));
    roninTeam->setFillColor(sf::Color::Red);
    roninTeam->setPosition(SCREEN_WIDTH - 150 - roninTeam->getSize().x, 200 + 250);

    sf::Text *roninTeamText = new sf::Text("Team Ronin :", *this->font, 30);
    roninTeamText->setFillColor(sf::Color::White);
    roninTeamText->setPosition(15 + roninTeam->getPosition().x, roninTeam->getPosition().y + roninTeam->getSize().y / 2 - roninTeamText->getGlobalBounds().height / 2 - 4);

    sf::Text *roninTeamScoreText = new sf::Text(std::to_string(roninTeamScore), *this->font, 30);
    roninTeamScoreText->setFillColor(sf::Color::White);
    roninTeamScoreText->setPosition(roninTeam->getPosition().x + roninTeam->getSize().x - roninTeamScoreText->getGlobalBounds().width - 15, roninTeam->getPosition().y + roninTeam->getSize().y / 2 - roninTeamScoreText->getGlobalBounds().height / 2 - 4);

    sf::Text *victory = new sf::Text("Victory ->", *this->font, 50);
    victory->setFillColor(sf::Color::Green);

    if (shogunTeamScore > ninjaTeamScore && shogunTeamScore > roninTeamScore) {
        victory->setPosition(shogunTeam->getPosition().x - victory->getGlobalBounds().width - 25, shogunTeam->getPosition().y + shogunTeam->getSize().y / 2 - victory->getGlobalBounds().height / 2 - 6);
    } else if (ninjaTeamScore > shogunTeamScore && ninjaTeamScore > roninTeamScore) {
        victory->setPosition(ninjaTeam->getPosition().x - victory->getGlobalBounds().width - 25, ninjaTeam->getPosition().y + ninjaTeam->getSize().y / 2 - victory->getGlobalBounds().height / 2 - 6);
    } else if (roninTeamScore > shogunTeamScore && roninTeamScore > ninjaTeamScore) {
        victory->setPosition(roninTeam->getPosition().x - victory->getGlobalBounds().width - 25, roninTeam->getPosition().y + roninTeam->getSize().y / 2 - victory->getGlobalBounds().height / 2 - 6);
    } else {
        if (ninjaTeam == shogunTeam || ninjaTeam == roninTeam) {
            victory->setPosition(ninjaTeam->getPosition().x - victory->getGlobalBounds().width - 25, ninjaTeam->getPosition().y + ninjaTeam->getSize().y / 2 - victory->getGlobalBounds().height / 2 - 6);
        } else if (shogunTeam == roninTeam) {
            victory->setPosition(shogunTeam->getPosition().x - victory->getGlobalBounds().width - 25, shogunTeam->getPosition().y + shogunTeam->getSize().y / 2 - victory->getGlobalBounds().height / 2 - 6);
        }
    }

    while (true) {
        sf::Event event;
        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->window->close();
            }
        }

        this->window->clear(sf::Color::Black);

        this->window->draw(*text);
        for (std::vector<sf::RectangleShape*>::iterator it = rectangles.begin(); it != rectangles.end(); it++) {
            this->window->draw(**it);
        }

        for (std::vector<sf::Text*>::iterator it = texts.begin(); it != texts.end(); it++) {
            this->window->draw(**it);
        }

        this->window->draw(*shogunTeam);
        this->window->draw(*ninjaTeam);

        this->window->draw(*shogunTeamText);
        this->window->draw(*ninjaTeamText);

        this->window->draw(*shogunTeamScoreText);
        this->window->draw(*ninjaTeamScoreText);

        if (this->nbPlayers > 4) {
            this->window->draw(*roninTeam);
            this->window->draw(*roninTeamText);
            this->window->draw(*roninTeamScoreText);
        }

        this->window->draw(*victory);
        
        this->window->display();
    }
}

UI::~UI() {
    delete this->window;
    delete this->game;

    delete this->HPTexture;
    delete this->HonorTexture;
    delete this->backRoleTexture;
    delete this->backCardTexture;

    for (std::vector<sf::Texture*>::iterator it = this->roleTextures->begin(); it != this->roleTextures->end(); it++) {
        delete *it;
    }
    delete this->roleTextures;

    for (std::vector<sf::Texture*>::iterator it = this->cardTextures->begin(); it != this->cardTextures->end(); it++) {
        delete *it;
    }
    delete this->cardTextures;

    for (std::vector<sf::Texture*>::iterator it = this->characterTextures->begin(); it != this->characterTextures->end(); it++) {
        delete *it;
    }
    delete this->characterTextures;

    for (std::vector<sf::Sprite*>::iterator it = this->playersSprites->begin(); it != this->playersSprites->end(); it++) {
        delete *it;
    }
    delete this->playersSprites;

    for (std::vector<sf::Sprite*>::iterator it = this->HPSprites->begin(); it != this->HPSprites->end(); it++) {
        delete *it;
    }
    delete this->HPSprites;

    for (std::vector<sf::Text*>::iterator it = this->HPTexts->begin(); it != this->HPTexts->end(); it++) {
        delete *it;
    }
    delete this->HPTexts;

    for (std::vector<sf::Sprite*>::iterator it = this->HonorSprites->begin(); it != this->HonorSprites->end(); it++) {
        delete *it;
    }
    delete this->HonorSprites;

    for (std::vector<sf::Text*>::iterator it = this->HonorTexts->begin(); it != this->HonorTexts->end(); it++) {
        delete *it;
    }
    delete this->HonorTexts;

    delete this->actualPlayerSprite;
    delete this->actualPlayerRoleSprite;

    for (std::vector<sf::Sprite*>::iterator it = this->actualPlayerCardSprites->begin(); it != this->actualPlayerCardSprites->end(); it++) {
        delete *it;
    }
    delete this->actualPlayerCardSprites;

    for (std::vector<sf::Sprite*>::iterator it = this->stackSprites->begin(); it != this->stackSprites->end(); it++) {
        delete *it;
    }
    delete this->stackSprites;

    for (std::vector<sf::Sprite*>::iterator it = this->discardStackSprites->begin(); it != this->discardStackSprites->end(); it++) {
        delete *it;
    }
    delete this->discardStackSprites;

    for (std::vector<sf::Text*>::iterator it = this->logsTexts->begin(); it != this->logsTexts->end(); it++) {
        delete *it;
    }
    delete this->logsTexts;

    delete this->logsBackground;
    delete this->openLogsText;
    delete this->openLogsBtn;
    delete this->closeLogsText;
    delete this->closeLogsBtn;
}