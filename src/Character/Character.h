#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

enum class CharacterType {
    HANZO,
    USHIWAKA,
    CHIYOME,
    HIDEYOSHI,
    GINCHIYO,
    GOEMON,
    NOBUNAGA,
    TOMOE,
    IEYASU,
    BENKEI,
    MUSASHI,
    KOJIRO
};

class Character {
    private:
        CharacterType type;
        int HP;
    
    public:
        Character(CharacterType type, int HP);
        CharacterType getType() const;
        int getIndex() const;
        int getHP() const;
        std::string getName() const;
};

#endif // CHARACTER_H