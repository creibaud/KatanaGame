#include "Player.h"

Player::Player(Role *role, Character *character) 
    : role(role), character(character) {
    this->hand = new std::vector<Card*>();
    this->HP = character->getHP();
    this->honorPoints = 0;
    this->asAttacked = false;
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