#include "Permanent.h"

Permanent::Permanent(PermanentType permanentType) 
    : Card(CardType::PERMANENT), permanentType(permanentType) {
}

PermanentType Permanent::getPermanentType() const {
    return this->permanentType;
}

int Permanent::getIndex() {
    return static_cast<int>(this->permanentType) + 8;
}