#ifndef GAME_H
#define GAME_H

#include <random>
#include <algorithm>
#include "../Player/Player.h"

class Game {
    private:
        std::vector<Role*> *roles;
        std::vector<Character*> *characters;
        std::vector<Player*> *players;

    public:
        Game();
        void initRole(int nbPlayers);
        void initCharacter();
        ~Game();
};

#endif // GAME_H