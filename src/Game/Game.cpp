#include "Game.h"

Game::Game() {
    this->roles = new std::vector<Role*>();
    this->characters = new std::vector<Character*>();
    this->cards = new std::vector<Card*>();
    this->discards = new std::vector<Card*>();
    this->players = new std::vector<Player*>();
    this->logs = new std::vector<std::string*>();
    this->indexActualPlayer = 0;
    this->isCarteDuBushidoInGame = false;
}

void Game::initRole() {
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

    switch (this->nbPlayers) {
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

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(this->characters->begin(), this->characters->end(), g);
}

void Game::initCard() {
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

void Game::initPlayer() {
    for (int i = 0; i < this->nbPlayers; i++) {
        this->players->push_back(new Player(this->roles->back(), this->characters->back()));
        this->roles->pop_back();
        this->characters->pop_back();
    }
    delete this->roles;

    for (std::vector<Character*>::iterator it = this->characters->begin(); it != this->characters->end(); ++it) {
        delete *it;
    }
    delete this->characters;
    
    int indexShogun = -1;
    for (int i = 0; i < this->nbPlayers; i++) {
        if (this->players->at(i)->getRole()->getType() == RoleType::SHOGUN) {
            indexShogun = i;
            break;
        }
    }

    std::rotate(this->players->begin(), this->players->begin() + indexShogun, this->players->end());

    for (int i = 0; i < this->nbPlayers; i++) {
        int nbCard;

        switch (i) {
            case 0:
                nbCard = 4;
                break;
            case 1:
            case 2:
                nbCard = 5;
                break;
            case 3:
            case 4:
                nbCard = 6;
                break;
            case 5:
            case 6:
                nbCard = 7;
                break;
            default:
                break;
        }

        for (int j = 0; j < nbCard; j++) {
            this->players->at(i)->getHand()->push_back(this->cards->back());
            this->cards->pop_back();
        }
    }

    for (std::vector<Player*>::iterator it = this->players->begin(); it != this->players->end(); ++it) {
        if ((*it)->getRole()->getType() == RoleType::SHOGUN) {
            (*it)->honorPoints = 5;
        } else if (this->nbPlayers < 6) {
            (*it)->honorPoints = 3;
        } else {
            (*it)->honorPoints = 4;
        }
    }
}

void Game::setNbPlayers(int nbPlayers) {
    this->nbPlayers = nbPlayers;
}

int Game::getNbPlayers() const {
    return this->nbPlayers;
}

int Game::getIndexActualPlayer() const {
    return this->indexActualPlayer;
}

std::vector<Player*> *Game::getPlayers() const {
    return this->players;
}

std::vector<Card*> *Game::getCards() const {
    return this->cards;
}

std::vector<Card*> *Game::getDiscards() const {
    return this->discards;
}

std::vector<std::string*> *Game::getLogs() const {
    return this->logs;
}

void Game::updateHonorPointsHP() {
    for (std::vector<Player*>::iterator it = this->players->begin(); it != this->players->end(); it++) {
        if ((*it)->isDown()) {
            (*it)->HP = 0;
        }

        if ((*it)->honorPoints <= 0) {
            (*it)->honorPoints = 0;
        }
    }
}

void Game::recoverHP() {
    this->players->at(this->indexActualPlayer)->recover();
}

void Game::pick(Player *player, int nbCard) {
    for (int i = 0; i < nbCard; i++) {
        if (this->cards->size() <= 0) {
            this->recoverCards();
        }
        
        player->getHand()->push_back(this->cards->back());
        this->cards->pop_back();
        std::string *log = new std::string("Le joueur a pioche une carte.");
        this->logs->push_back(log);
    }
}

bool Game::attack(Weapon *card, Player *player) {
    int range = card->getRange();
    if (player->isDown()) {
        return false;
    } else if (this->calculateDistance(player) <= range || player->getCharacter()->getType() == CharacterType::KOJIRO) {
        return true;
    } else {
        return false;
    }
}

int Game::calculateDistance(Player *playerTarget) {    
    bool findPlayerTarget = false;
    int distanceClockwise = 0;
    
    std::vector<Player*>::size_type indexDifferenceClockwise = this->indexActualPlayer - (this->players->begin() - this->players->begin());
    for (std::vector<Player*>::size_type i = indexDifferenceClockwise + 1; i < this->players->size(); i++) {
        if (!this->players->at(i)->isDown()) {
            distanceClockwise++;
            if (this->players->at(i) == playerTarget) {
                findPlayerTarget = true;
                break;
            }
        }
    }

    if (!findPlayerTarget) {
        indexDifferenceClockwise = std::distance(this->players->begin(), this->players->begin() + this->indexActualPlayer);
        for (std::vector<Player*>::size_type i = 0; i < indexDifferenceClockwise; i++) {
            if (!this->players->at(i)->isDown()) {
                distanceClockwise++;
                if (this->players->at(i) == playerTarget) {
                    findPlayerTarget = true;
                    break;
                }
            }
        }
    }

    findPlayerTarget = false;
    int distanceCounterClockwise = 0;

    std::vector<Player*>::size_type indexDifferenceCounterClockwise = std::distance(this->players->begin(), this->players->begin() + this->indexActualPlayer);
    for (std::vector<Player*>::size_type i = indexDifferenceCounterClockwise - 1; i < this->players->size(); i--) {
        if (!this->players->at(i)->isDown()) {
            distanceCounterClockwise++;
            if (this->players->at(i) == playerTarget) {
                findPlayerTarget = true;
                break;
            }
        }
    }

    if (!findPlayerTarget) {
        indexDifferenceCounterClockwise = this->indexActualPlayer - std::distance(this->players->begin(), this->players->end());
        for (std::vector<Player*>::size_type i = this->players->size() - 1; i > indexDifferenceCounterClockwise; i--) {
            if (!this->players->at(i)->isDown()) {
                distanceCounterClockwise++;
                if (this->players->at(i) == playerTarget) {
                    findPlayerTarget = true;
                    break;
                }
            }
        }
    }

    int moreRange = 0;
    if (playerTarget->getCharacter()->getType() == CharacterType::BENKEI) {
        moreRange = 1;
    }

    moreRange += playerTarget->armureFunction();
    
    return std::min(distanceClockwise, distanceCounterClockwise) + moreRange;
}

bool Game::canBlock(Player *player) {
    for (std::vector<Card*>::iterator it = player->getHand()->begin(); it != player->getHand()->end(); it++) {
        if ((*it)->getType() == CardType::ACTION) {
            Action *action = dynamic_cast<Action*>(*it);
            if (action->getActionType() == ActionType::PARADE) {
                return true;
            }
        } else if (player->getCharacter()->getType() == CharacterType::HANZO && (*it)->getType() == CardType::WEAPON && player->getHand()->size() > 1) {
            return true;
        }
    }

    return false;
}

void Game::discard(Player *player, Card* card) {
    this->discards->push_back(card);
    player->getHand()->erase(std::remove(player->getHand()->begin(), player->getHand()->end(), card), player->getHand()->end());
}

void Game::changePlayer() {
    this->players->at(this->indexActualPlayer)->nbAttack = 0;
    this->indexActualPlayer++;
    if (this->indexActualPlayer == this->nbPlayers) {
        this->indexActualPlayer = 0;
    }

    this->recoverHP();

    if (this->players->at(this->indexActualPlayer)->asCodeDuBushido().first != nullptr) {
        this->codeDuBushidoFunction();
    }

    int nbCards = 2;

    if (this->players->at(this->indexActualPlayer)->getCharacter()->getType() == CharacterType::HIDEYOSHI) {
        nbCards++;
    }

    if (this->players->at(this->indexActualPlayer)->getCharacter()->getType() == CharacterType::IEYASU) {
        this->players->at(this->indexActualPlayer)->getHand()->push_back(this->discards->back());
        this->discards->pop_back();
        this->pick(this->players->at(this->indexActualPlayer), 1);
    } else {
        this->pick(this->players->at(this->indexActualPlayer), nbCards);
    }
}

void Game::recoverCards() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(this->discards->begin(), this->discards->end(), g);

    for (std::vector<Card*>::iterator it = this->discards->begin(); it != this->discards->end(); it++) {
        this->cards->push_back(*it);
    }
    this->discards->clear();

    for (std::vector<Player*>::iterator it = this->players->begin(); it != this->players->end(); it++) {
        (*it)->honorPoints--;
    }
}

void Game::criDeGuerreFunction() {
    for (std::vector<Player*>::iterator it1 = this->players->begin(); it1 != this->players->end(); it1++) {
        if (!(*it1)->isDown()) {
            std::vector<Card*> *hand = (*it1)->getHand();

            bool asDiscarded = false;
            for (std::vector<Card*>::iterator it2 = hand->begin(); it2 != hand->end(); it2++) {
                if ((*it2)->getType() == CardType::ACTION) {
                    Action *action = dynamic_cast<Action*>(*it2);
                    if (action->getActionType() == ActionType::PARADE) {
                        this->discard(*it1, *it2);
                        asDiscarded = true;
                        break;
                    }
                }
            }

            if (!asDiscarded && (*it1)->getCharacter()->getType() == CharacterType::HANZO) {
                for (std::vector<Card*>::iterator it2 = hand->begin(); it2 != hand->end(); it2++) {
                    if ((*it2)->getType() == CardType::WEAPON && hand->size() > 1) {
                        this->discard(*it1, *it2);
                        asDiscarded = true;
                        break;
                    }
                }
            }

            if (!asDiscarded && (*it1)->getCharacter()->getType() != CharacterType::CHIYOME) {
                (*it1)->HP--;
                if ((*it1) != this->players->at(this->indexActualPlayer)) {
                    (*it1)->honorPoints--;
                    this->players->at(this->indexActualPlayer)->honorPoints++;
                }
            }
        }
    }
}

void Game::daimyoFunction() {
    this->pick(this->players->at(this->indexActualPlayer), 2);
}

void Game::geishaFunction(Player *player) {
    if (player != nullptr) {
        if (!player->isDown()) {
            std::vector<Card*> *hand = player->getHand();
            if (!hand->empty()) {
                std::random_device rd;
                std::mt19937 g(rd());
                std::uniform_int_distribution<int> distribution(0, hand->size() - 1);
                int randomIndex = distribution(g);
                Card *randomCard = hand->at(randomIndex);
                this->discard(player, randomCard);
            }
        }
    } else {
        std::vector<std::vector<Permanent*>*> *playersPermanentCards = new std::vector<std::vector<Permanent*>*>();
        for (std::vector<Player*>::size_type i = 0; i != this->players->size(); i++) {
            playersPermanentCards->push_back(new std::vector<Permanent*>());
            for (std::vector<Permanent*>::iterator it = this->players->at(i)->getPermanentCardsPlayed()->begin(); it != this->players->at(i)->getPermanentCardsPlayed()->end(); it++) {
                playersPermanentCards->at(i)->push_back(*it);
            }
        }
        
        if (!playersPermanentCards->empty()) {
            std::random_device rd;
            std::mt19937 g(rd());
            std::uniform_int_distribution<int> distribution(0, playersPermanentCards->size() - 1);
            int randomPlayerIndex = distribution(g);
            
            if (randomPlayerIndex == this->indexActualPlayer) {
                randomPlayerIndex++;
                if (randomPlayerIndex == this->nbPlayers) {
                    randomPlayerIndex = 0;
                }
            }

            std::vector<Permanent*> *randomPlayerPermanentCards = playersPermanentCards->at(randomPlayerIndex);
            if (!randomPlayerPermanentCards->empty()) {
                std::uniform_int_distribution<int> distribution2(0, randomPlayerPermanentCards->size() - 1);
                int randomCardIndex = distribution2(g);
                Permanent *randomPermanentCard = randomPlayerPermanentCards->at(randomCardIndex);
                this->players->at(randomPlayerIndex)->getPermanentCardsPlayed()->erase(this->players->at(randomPlayerIndex)->getPermanentCardsPlayed()->begin() + randomCardIndex);
                this->discards->push_back(randomPermanentCard);
            }           
        }

        for (std::vector<std::vector<Permanent*>*>::iterator it = playersPermanentCards->begin(); it != playersPermanentCards->end(); it++) {
            delete *it;
        }
        delete playersPermanentCards;
    }
}

void Game::ceremonieDuTheFunction() {
    for (std::vector<Player*>::size_type i = 0; i != this->players->size(); i++) {
        if (static_cast<int>(i) == this->indexActualPlayer) {
            this->pick(this->players->at(i), 3);
        } else {
            this->pick(this->players->at(i), 1);
        }
    }
}

void Game::juJitsuFunction() {
    for (std::vector<Player*>::iterator it1 = this->players->begin(); it1 != this->players->end(); it1++) {
        if (!(*it1)->isDown()) {
            std::vector<Card*> *hand = (*it1)->getHand();

            bool asDiscarded = false;
            for (std::vector<Card*>::iterator it2 = hand->begin(); it2 != hand->end(); it2++) {
                if ((*it2)->getType() == CardType::WEAPON) {
                    this->discard(*it1, *it2);
                    asDiscarded = true;
                    break;
                }
            }

            if (!asDiscarded && (*it1)->getCharacter()->getType() != CharacterType::CHIYOME) {
                (*it1)->HP--;
                if ((*it1) != this->players->at(this->indexActualPlayer)) {
                    (*it1)->honorPoints--;
                    this->players->at(this->indexActualPlayer)->honorPoints++;
                }
            }
        }
    }
}

void Game::codeDuBushidoFunction() {
    Card *pickedCard = this->cards->back();
    this->cards->pop_back();
    this->discards->push_back(pickedCard);

    if (pickedCard->getType() == CardType::WEAPON) {
        std::vector<Card*> *hand = this->players->at(this->indexActualPlayer)->getHand();

        bool asDiscarded = false;
        for (std::vector<Card*>::iterator it = hand->begin(); it != hand->end(); it++) {
            if ((*it)->getType() == CardType::WEAPON) {
                this->discard(this->players->at(this->indexActualPlayer), *it);
                asDiscarded = true;
                break;
            }
        }

        if (!asDiscarded) {
            this->players->at(this->indexActualPlayer)->honorPoints -= 1;
            std::vector<Permanent*> *playerPermanentCards = this->players->at(this->indexActualPlayer)->getPermanentCardsPlayed();
            playerPermanentCards->erase(playerPermanentCards->begin() + this->players->at(this->indexActualPlayer)->asCodeDuBushido().second);
            this->isCarteDuBushidoInGame = false;
        } else {
            int copyIndexActualPlayer = this->indexActualPlayer;
            copyIndexActualPlayer++;
            if (copyIndexActualPlayer == this->nbPlayers) {
                copyIndexActualPlayer = 0;
            }

            Permanent *codeDuBushidoCard = this->players->at(this->indexActualPlayer)->asCodeDuBushido().first;
            std::vector<Permanent*> *playerPermanentCards = this->players->at(this->indexActualPlayer)->getPermanentCardsPlayed();
            playerPermanentCards->erase(playerPermanentCards->begin() + this->players->at(this->indexActualPlayer)->asCodeDuBushido().second);

            this->players->at(copyIndexActualPlayer)->getPermanentCardsPlayed()->push_back(codeDuBushidoCard);
        }
    } else {
        int copyIndexActualPlayer = this->indexActualPlayer;
        copyIndexActualPlayer++;
        if (copyIndexActualPlayer == this->nbPlayers) {
            copyIndexActualPlayer = 0;
        }

        Permanent *codeDuBushidoCard = this->players->at(this->indexActualPlayer)->asCodeDuBushido().first;
        std::vector<Permanent*> *playerPermanentCards = this->players->at(this->indexActualPlayer)->getPermanentCardsPlayed();
        playerPermanentCards->erase(playerPermanentCards->begin() + this->players->at(this->indexActualPlayer)->asCodeDuBushido().second);

        this->players->at(copyIndexActualPlayer)->getPermanentCardsPlayed()->push_back(codeDuBushidoCard);
    }
}

bool Game::isGameOver() {
    for (std::vector<Player*>::iterator it = this->players->begin(); it != this->players->end(); it++) {
        if ((*it)->honorPoints <= 0) {
            return true;
        }
    }
    return false;
}

Game::~Game() {
    for (std::vector<Card*>::iterator it = this->cards->begin(); it != this->cards->end(); ++it) {
        delete *it;
    }
    delete this->cards;

    for (std::vector<Card*>::iterator it = this->discards->begin(); it != this->discards->end(); ++it) {
        delete *it;
    }
    delete this->discards;

    for (std::vector<Player*>::iterator it = this->players->begin(); it != this->players->end(); ++it) {
        delete *it;
    }
    delete this->players;
}