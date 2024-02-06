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
        std::vector<Permanent*> *permanentCardsPlayed;

        int maxNbAttack;

    public:
        int HP;
        int honorPoints;
        bool asAttacked;
        int nbAttack;
        
        Player(Role *role, Character *character);

        Role* getRole() const;
        Character* getCharacter() const;
        std::vector<Card*>* getHand() const;
        std::vector<Permanent*>* getPermanentCardsPlayed() const;
        int getMaxNbAttack() const;

        void meditationFunction();

        int attackRapideFunction();
        int armureFunction();
        void concentrationFunction();

        bool isDown() const;

        void recover();
        ~Player();
};

#endif // PLAYER_H