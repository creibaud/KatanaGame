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
    this->window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Katana");
    this->window->setFramerateLimit(FPS);

    this->game->setNbPlayers(this->nbPlayers);
    this->game->initRole();
    this->game->initCharacter();
    this->game->initCard();
    this->game->initPlayer();

    while (this->window->isOpen()) {
        sf::Event event;
        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->window->close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A) {
                    this->game->changePlayer();
                }
            }

            this->handleClickLogBtn(event);
        }

        this->window->clear(sf::Color::Black);

        this->update();
        this->display();

        this->window->display();
    }
}

void UI::update() {
    this->players = this->game->getPlayers();
    this->hand = this->players->at(this->game->getIndexActualPlayer())->getHand();
    this->stack = this->game->getCards();
    this->discardStack = this->game->getDiscards();
    this->logs = this->game->getLogs();
    this->setPlayersSprites();
    this->setActualPlayerSprite();
    this->setStackSprite();
    this->setDiscardStackSprite();
    this->setLogsTexts();
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

    for (std::vector<sf::Sprite*>::iterator it = this->actualPlayerCardSprites->begin(); it != this->actualPlayerCardSprites->end(); it++) {
        if ((*it)->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            (*it)->setPosition((*it)->getPosition().x, SCREEN_HEIGHT - 100 - (*it)->getTexture()->getSize().y - 20);
        } else {
            (*it)->setPosition((*it)->getPosition().x, SCREEN_HEIGHT - 100 - (*it)->getTexture()->getSize().y);
        }

        this->window->draw(*(*it));
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

    if (this->actualPlayerRoleSprite->getGlobalBounds().contains(mousePos.x, mousePos.y) || this->players->at(this->game->getIndexActualPlayer())->getRole()->getType() == RoleType::SHOGUN) {
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
        this->window->draw(*this->openLogsText);
    } else {
        this->window->draw(*this->closeLogsText);
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
    if (this->game->getIndexActualPlayer() + 1 < this->game->getNbPlayers()) {
        for (int i = this->game->getIndexActualPlayer() + 1; i < this->game->getNbPlayers(); i++) {
            this->setSpriteHonorCharactersHP(i);
            this->spriteShogunIndex++;
        }

        for (int i = 0; i < this->game->getIndexActualPlayer(); i++) {
            this->setSpriteHonorCharactersHP(i);
        }
    } else {
        for (int i = 0; i < this->game->getNbPlayers() - 1; i++) {
            this->setSpriteHonorCharactersHP(i);
        }

        this->spriteShogunIndex = 0;
    }

    if (this->players->at(this->game->getIndexActualPlayer())->getRole()->getType() == RoleType::SHOGUN) {
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
    Player* player = this->game->getPlayers()->at(this->game->getIndexActualPlayer());
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
        text->setPosition(2 * SCREEN_WIDTH / 3, 10 + i * 20);
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
}