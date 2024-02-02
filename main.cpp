#include "src/UI/UI.h"

int main() {
    sf::Font *font = new sf::Font();
    font->loadFromFile("assets/fonts/aAbsoluteEmpire.ttf");

    sf::Image *bg1 = new sf::Image();
    bg1->loadFromFile("assets/images/bg1.png");

    sf::Image *bg2 = new sf::Image();
    bg2->loadFromFile("assets/images/bg2.png");

    UI *ui = new UI(font);
    ui->init(bg1, bg2);
    ui->start();
    delete ui;

    return 0;
}