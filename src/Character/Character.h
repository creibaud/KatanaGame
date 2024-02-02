#ifndef CHARACTER_H
#define CHARACTER_H

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
        int getHP() const;
};

#endif // CHARACTER_H