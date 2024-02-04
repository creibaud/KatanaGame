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
        std::vector<Card*> *discards;
        std::vector<Player*> *players;
        int nbPlayers;
        int indexActualPlayer;
        int indexPlayerAttacked;

    public:
        Game();
        void initRole();
        void initCharacter();
        void initCard();
        void initPlayer();

        void setNbPlayers(int nbPlayers);

        int getNbPlayers() const;
        int getIndexActualPlayer() const;
        int getIndexPlayerAttacked() const;
        int getTurn() const;
        std::vector<Player*> *getPlayers() const;
        std::vector<Card*> *getCards() const;
        std::vector<Card*> *getDiscards() const;

        void recover();
        void pick();
        bool attack(Weapon *card, Player *player);
        int calculateDistance(Player *player);
        bool canBlock(Player *player);
        void discard(Player *player, Card* card);
        void changePlayer();

        ~Game();
};

#endif // GAME_H