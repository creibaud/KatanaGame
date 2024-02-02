#include "Character.h"

Character::Character(CharacterType type, int HP) : type(type), HP(HP) {}

CharacterType Character::getType() const {
    return this->type;
}

int Character::getHP() const {
    return this->HP;
}

int Character::getIndex() const {
    return static_cast<int>(this->type);
}