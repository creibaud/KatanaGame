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

std::string Character::getName() const {
    switch (this->type) {
        case CharacterType::HANZO:
            return "Hanzo";
        case CharacterType::USHIWAKA:
            return "Ushiwaka";
        case CharacterType::CHIYOME:
            return "Chiyome";
        case CharacterType::HIDEYOSHI:
            return "Hideyoshi";
        case CharacterType::GINCHIYO:
            return "Ginchyo";
        case CharacterType::GOEMON:
            return "Goemon";
        case CharacterType::NOBUNAGA:
            return "Nobunaga";
        case CharacterType::TOMOE:
            return "Tomoe";
        case CharacterType::IEYASU:
            return "Ieyasu";
        case CharacterType::BENKEI:
            return "Benkei";
        case CharacterType::MUSASHI:
            return "Musashi";
        case CharacterType::KOJIRO:
            return "Kojiro";
        default:
            return "";
    }
}