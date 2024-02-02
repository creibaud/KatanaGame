#include "Game.h"

Game::Game() {
    this->roles = new std::vector<Role*>();
    this->characters = new std::vector<Character*>();
    this->players = new std::vector<Player*>();
}

void Game::initRole(int nbPlayers) {
    this->roles->push_back(new Shogun);
    this->roles->push_back(new Samurai);

    std::vector<Role*> *ninja = new std::vector<Role*>();
    ninja->push_back(new NinjaOne);
    ninja->push_back(new NinjaTwo);
    ninja->push_back(new NinjaThree);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(ninja->begin(), ninja->end(), g);

    for (int i = 0; i < 2; i++) {
        this->roles->push_back(ninja->back());
        ninja->pop_back();
    }

    switch (nbPlayers) {
        case 5:
            this->roles->push_back(new Ronin);
            break;

        case 6:
            this->roles->push_back(new Ronin);
            this->roles->push_back(ninja->back());
            ninja->pop_back();
            break;

        case 7:
            this->roles->push_back(new Samurai);
            this->roles->push_back(new Ronin);
            this->roles->push_back(ninja->back());
            ninja->pop_back();
            break;
        
        default:
            break;
    }

    delete ninja;
    std::shuffle(this->roles->begin(), this->roles->end(), g);
}

void Game::initCharacter() {
    this->characters->push_back(new Hanzo);
    this->characters->push_back(new Ushiwaka);
    this->characters->push_back(new Chiyome);
    this->characters->push_back(new Hideyoshi);
    this->characters->push_back(new Ginchyo);
    this->characters->push_back(new Goemon);
    this->characters->push_back(new Nobunaga);
    this->characters->push_back(new Tomoe);
    this->characters->push_back(new Ieyasu);
    this->characters->push_back(new Benkei);
    this->characters->push_back(new Musashi);
    this->characters->push_back(new Kojiro);
}

Game::~Game() {
    for (std::vector<Role*>::iterator it = this->roles->begin(); it != this->roles->end(); ++it) {
        delete *it;
    }
    delete this->roles;

    for (std::vector<Character*>::iterator it = this->characters->begin(); it != this->characters->end(); ++it) {
        delete *it;
    }
    delete this->characters;

    for (std::vector<Player*>::iterator it = this->players->begin(); it != this->players->end(); ++it) {
        delete *it;
    }
    delete this->players;
}