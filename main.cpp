#include "src/UI/UI.h"

int main() {
    sf::Font *font = new sf::Font();
    font->loadFromFile("assets/fonts/aAbsoluteEmpire.ttf");

    sf::Image *bg1 = new sf::Image();
    bg1->loadFromFile("assets/images/bg1.png");

    sf::Image *bg2 = new sf::Image();
    bg2->loadFromFile("assets/images/bg2.png");

    sf::Image *backRole = new sf::Image();
    backRole->loadFromFile("assets/images/backRole.png");

    sf::Image *backRole2 = new sf::Image();
    backRole2->loadFromFile("assets/images/backRole2.png");

    std::vector<sf::Image*> *roleImages = new std::vector<sf::Image*>();
    for (int i = 0; i < 7; i++) {
        roleImages->push_back(backRole2);
    }

    std::vector<sf::Image*> *images = new std::vector<sf::Image*>();
    for (int i = 0; i < 12; i++) {
        images->push_back(backRole);
    }

    UI *ui = new UI(font);
    ui->init(bg1, bg2);
    ui->start(images, roleImages, backRole);
    delete ui;

    return 0;
}