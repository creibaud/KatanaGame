#include "Card.h"

Card::Card(CardType type) 
    : type(type) {
}

CardType Card::getType() const {
    return this->type;
}