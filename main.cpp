#include "src/UI/UI.h"

int main() {
    sf::Font *font = new sf::Font();
    font->loadFromFile("assets/fonts/aAbsoluteEmpire.ttf");

    UI *ui = new UI(font);
    ui->init();
    ui->start();
    delete ui;

    return 0;
}