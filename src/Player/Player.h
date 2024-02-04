#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "../includes/InitRole.h"
#include "../includes/InitCard.h"
#include "../includes/InitCharacter.h"

class Player {
    private:
        Role *role;
        Character *character;
        std::vector<Card*> *hand;

    public:
        int HP;
        int honorPoints;
        
        Player(Role *role, Character *character);
        Role* getRole() const;
        Character* getCharacter() const;
        std::vector<Card*>* getHand() const;
        ~Player();
};

#endif // PLAYER_H