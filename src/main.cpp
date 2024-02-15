/**
 * @file main.cpp
 * @brief The main function of the game.
*/

#include "UI/UI.h"

/**
 * @brief The main function of the program.
 * 
 * This function is the entry point of the program. It initializes various objects, loads images and fonts,
 * creates UI elements, and manages the flow of the game. It also deallocates memory before exiting.
 * 
 * @return int The exit status of the program.
 */
int main() {
    sf::Font *font = new sf::Font();
    font->loadFromFile("assets/fonts/aAbsoluteEmpire.ttf");

    sf::Image *rightImage = new sf::Image();
    rightImage->loadFromFile("assets/images/bg1.png");

    sf::Image *leftImage = new sf::Image();
    leftImage->loadFromFile("assets/images/bg2.png");

    sf::Image *HP = new sf::Image();
    HP->loadFromFile("assets/images/HP.png");

    sf::Image *Honor = new sf::Image();
    Honor->loadFromFile("assets/images/Honor.png");

    std::string *rolePath = new std::string[4] {
        "Shogun",
        "Samurai",
        "Ninja",
        "Ronin"
    };

    std::string *cardPath = new std::string[25] {
        "CriDeGuerre",
        "Daimyo",
        "Diversion",
        "Geisha",
        "Meditation",
        "Parade",
        "CeremonieDuThe",
        "JuJitsu",
        "AttaqueRapide",
        "CodeDuBushido",
        "Armure",
        "Concentration",
        "Nodachi",
        "Naginata",
        "Nagayari",
        "Tanegashima",
        "Daikyu",
        "Bo",
        "Kusarigama",
        "Katana",
        "Shuriken",
        "Kanabo",
        "Bokken",
        "Kiseru",
        "Wakizashi"
    };

    std::string *characterPath = new std::string[12] {
        "Hanzo",
        "Ushiwaka",
        "Chiyome",
        "Hideyoshi",
        "Ginchyo",
        "Goemon",
        "Nobunaga",
        "Tomoe",
        "Ieyasu",
        "Benkei",
        "Musashi",
        "Kojiro"
    };

    sf::Image *backRole = new sf::Image();
    backRole->loadFromFile("assets/images/RoleBack.png");

    sf::Image *backCard = new sf::Image();
    backCard->loadFromFile("assets/images/CardBack.png");

    std::vector<sf::Image*> *roleImages = new std::vector<sf::Image*>();;
    for (int i = 0; i < 4; i++) {
        sf::Image *image = new sf::Image();
        image->loadFromFile("assets/images/roles/" + rolePath[i] + ".png");
        roleImages->push_back(image);
    }

    std::vector<sf::Image*> *cardImages = new std::vector<sf::Image*>();
    for (int i = 0; i < 25; i++) {
        sf::Image *image = new sf::Image();
        image->loadFromFile("assets/images/cards/" + cardPath[i] + ".png");
        cardImages->push_back(image);
    }

    std::vector<sf::Image*> *characterImages = new std::vector<sf::Image*>();;
    for (int i = 0; i < 12; i++) {
        sf::Image *image = new sf::Image();
        image->loadFromFile("assets/images/characters/" + characterPath[i] + ".png");
        characterImages->push_back(image);
    }

    UI *ui = new UI(font, HP, Honor, backRole, backCard, roleImages, cardImages, characterImages);
    ui->menu(leftImage, rightImage);
    ui->start();
    ui->score();
    delete ui;

    delete font;
    delete rightImage;
    delete leftImage;
    delete HP;
    delete Honor;
    delete[] rolePath;
    delete[] cardPath;
    delete[] characterPath;
    delete backRole;
    delete backCard;

    for (std::vector<sf::Image*>::iterator it = roleImages->begin(); it != roleImages->end(); it++) {
        delete *it;
    }
    delete roleImages;

    for (std::vector<sf::Image*>::iterator it = cardImages->begin(); it != cardImages->end(); it++) {
        delete *it;
    }
    delete cardImages;
    
    for (std::vector<sf::Image*>::iterator it = characterImages->begin(); it != characterImages->end(); it++) {
        delete *it;
    }
    delete characterImages;
    
    return 0;
}