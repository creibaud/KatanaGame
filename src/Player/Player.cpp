#include "Player.h"

Player::Player(Role *role, Character *character) 
    : role(role), character(character) {
    this->hand = new std::vector<Card*>();
}

Player::~Player() {
    delete this->role;
    delete this->character;

    for (std::vector<Card*>::iterator it = this->hand->begin(); it != this->hand->end(); ++it) {
        delete *it;
    }
}