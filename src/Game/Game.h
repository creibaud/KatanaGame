#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <random>
#include <algorithm>
#include <string>
#include "../Player/Player.h"

class Game {
    private:
        std::vector<Role*> *roles;
        std::vector<Character*> *characters;
        std::vector<Card*> *cards;
        std::vector<Card*> *discards;
        std::vector<Player*> *players;
        std::vector<std::string*> *logs;
        int nbPlayers;
        int indexActualPlayer;

    public:
        bool isCarteDuBushidoInGame;

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
        std::vector<std::string*> *getLogs() const;

        void updateHonorPointsHP();

        void recoverHP();
        void pick(Player *player, int nbCard);
        bool attack(Weapon *card, Player *player);
        int calculateDistance(Player *playerTarget);
        bool canBlock(Player *player);
        void discard(Player *player, Card* card);
        void recoverCards();
        void changePlayer();

        void criDeGuerreFunction();
        void daimyoFunction();
        void geishaFunction(Player *player = nullptr);
        void ceremonieDuTheFunction();
        void juJitsuFunction();

        void codeDuBushidoFunction();

        bool isGameOver();

        ~Game();
};

#endif // GAME_H