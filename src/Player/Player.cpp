#include "Player.h"

Player::Player(Role *role, Character *character) 
    : role(role), character(character) {
    this->hand = new std::vector<Card*>();
    this->permanentCardsPlayed = new std::vector<Permanent*>();
    this->HP = character->getHP();
    this->honorPoints = 0;
    this->asAttacked = false;
    this->maxNbAttack = 1;
    this->nbAttack = 0;

    if (character->getType() == CharacterType::GOEMON) {
        this->maxNbAttack++;
    }
}

Role* Player::getRole() const {
    return this->role;
}

Character* Player::getCharacter() const {
    return this->character;
}

std::vector<Card*>* Player::getHand() const {
    return this->hand;
}

std::vector<Permanent*>* Player::getPermanentCardsPlayed() const {
    return this->permanentCardsPlayed;
}

int Player::getMaxNbAttack() const {
    return this->maxNbAttack;
}

bool Player::isDown() const {
    return this->HP <= 0 || this->hand->size() <= 0;
}

void Player::meditationFunction() {
    this->HP = this->character->getHP();
}

int Player::attackRapideFunction() {
    int nbDamage = 0;
    for (std::vector<Permanent*>::iterator it = this->permanentCardsPlayed->begin(); it != this->permanentCardsPlayed->end(); ++it) {
        if ((*it)->getPermanentType() == PermanentType::ATTAQUE_RAPIDE) {
            nbDamage++;
        }
    }
    return nbDamage;
}

void Player::concentrationFunction() {
    this->maxNbAttack++;
}

void Player::recover() {
    if (this->HP <= 0) {
        this->HP = this->character->getHP();
    }
}

Player::~Player() {
    delete this->role;
    delete this->character;

    for (std::vector<Card*>::iterator it = this->hand->begin(); it != this->hand->end(); ++it) {
        delete *it;
    }
}