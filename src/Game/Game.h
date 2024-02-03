#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <random>
#include <algorithm>
#include "../Player/Player.h"

class Game {
    private:
        std::vector<Role*> *roles;
        std::vector<Character*> *characters;
        std::vector<Card*> *cards;
        std::vector<Player*> *players;
        int nbPlayers;
        int indexActualPlayer;

    public:
        Game();
        void initRole();
        void initCharacter();
        void initCard();
        void initPlayer();

        void setNbPlayers(int nbPlayers);

        int getNbPlayers() const;
        int getIndexActualPlayer() const;
        int getTurn() const;
        std::vector<Player*> *getPlayers() const;

        void changePlayer();

        ~Game();
};

#endif // GAME_H