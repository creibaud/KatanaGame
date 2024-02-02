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

void Game::initCard() {
    this->cards = new std::vector<Card*>();

    int *nbCopy = new int[25] {
        NB_COPY_CRI_DE_GUERRE,
        NB_COPY_DAIMYO,
        NB_COPY_DIVERSION,
        NB_COPY_GEISHA,
        NB_COPY_MEDITATION,
        NB_COPY_PARADE,
        NB_COPY_CEREMONIE_DU_THE,
        NB_COPY_JU_JITSU,
        NB_COPY_ATTAQUE_RAPIDE,
        NB_COPY_CODE_DU_BUSHIDO,
        NB_COPY_ARMURE,
        NB_COPY_CONCENTRATION,
        NB_COPY_NODACHI,
        NB_COPY_NAGINATA,
        NB_COPY_NAGAYARI,
        NB_COPY_TANEGASHIMA,
        NB_COPY_DAIKYU,
        NB_COPY_BO,
        NB_COPY_KUSARIGAMA,
        NB_COPY_KATANA,
        NB_COPY_SHURIKEN,
        NB_COPY_KANABO,
        NB_COPY_BOKKEN,
        NB_COPY_KISERU,
        NB_COPY_WAKIZASHI
    };

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < nbCopy[i]; j++) {
            switch (i) {
                case 0:
                    this->cards->push_back(new CriDeGuerre);
                    break;
                case 1:
                    this->cards->push_back(new Daimyo);
                    break;
                case 2:
                    this->cards->push_back(new Diversion);
                    break;
                case 3:
                    this->cards->push_back(new Geisha);
                    break;
                case 4:
                    this->cards->push_back(new Meditation);
                    break;
                case 5:
                    this->cards->push_back(new Parade);
                    break;
                case 6:
                    this->cards->push_back(new CeremonieDuThe);
                    break;
                case 7:
                    this->cards->push_back(new JuJitsu);
                    break;
                case 8:
                    this->cards->push_back(new AttaqueRapide);
                    break;
                case 9:
                    this->cards->push_back(new CodeDuBushido);
                    break;
                case 10:
                    this->cards->push_back(new Armure);
                    break;
                case 11:
                    this->cards->push_back(new Concentration);
                    break;
                case 12:
                    this->cards->push_back(new Nodachi);
                    break;
                case 13:
                    this->cards->push_back(new Naginata);
                    break;
                case 14:
                    this->cards->push_back(new Nagayari);
                    break;
                case 15:
                    this->cards->push_back(new Tanegashima);
                    break;
                case 16:
                    this->cards->push_back(new Daikyu);
                    break;
                case 17:
                    this->cards->push_back(new Bo);
                    break;
                case 18:
                    this->cards->push_back(new Kusarigama);
                    break;
                case 19:
                    this->cards->push_back(new Katana);
                    break;
                case 20:
                    this->cards->push_back(new Shuriken);
                    break;
                case 21:
                    this->cards->push_back(new Kanabo);
                    break;
                case 22:
                    this->cards->push_back(new Bokken);
                    break;
                case 23:
                    this->cards->push_back(new Kiseru);
                    break;
                case 24:
                    this->cards->push_back(new Wakizashi);
                    break;
            }
        }
    }

    delete[] nbCopy;

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(this->cards->begin(), this->cards->end(), g);
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

    for (std::vector<Card*>::iterator it = this->cards->begin(); it != this->cards->end(); ++it) {
        delete *it;
    }
    delete this->cards;

    for (std::vector<Player*>::iterator it = this->players->begin(); it != this->players->end(); ++it) {
        delete *it;
    }
    delete this->players;
}