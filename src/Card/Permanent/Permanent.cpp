#include "Permanent.h"

Permanent::Permanent(PermanentType permanentType) 
    : Card(CardType::PERMANENT), permanentType(permanentType) {
}

PermanentType Permanent::getPermanentType() const {
    return this->permanentType;
}