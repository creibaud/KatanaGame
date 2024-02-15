#ifndef UI_H
#define UI_H

#include "Menu/Menu.h"
#include "../Game/Game.h"

#define FPS 60
class UI {
    private:
        sf::RenderWindow *window;
        sf::Font *font;

        sf::Texture *HPTexture;
        sf::Texture *HonorTexture;
        sf::Texture *backRoleTexture;
        sf::Texture *backCardTexture;
        std::vector<sf::Texture*> *roleTextures;
        std::vector<sf::Texture*> *cardTextures;
        std::vector<sf::Texture*> *characterTextures;

        sf::Sprite *backRoleSprite;
        std::vector<sf::Sprite*> *playersSprites;
        std::vector<sf::Sprite*> *HPSprites;
        std::vector<sf::Text*> *HPTexts;
        std::vector<sf::Sprite*> *HonorSprites;
        std::vector<sf::Text*> *HonorTexts;

        sf::Sprite *actualPlayerSprite;
        sf::Sprite *actualPlayerRoleSprite;
        std::vector<sf::Sprite*> *actualPlayerCardSprites;
        sf::Sprite *HPSpritePlayer;
        sf::Text *HPTextPlayer;
        sf::Sprite *HonorSpritePlayer;
        sf::Text *HonorTextPlayer;

        std::vector<sf::Sprite*> *stackSprites;
        std::vector<sf::Sprite*> *discardStackSprites;

        std::vector<Player*> *players;
        std::vector<Card*> *hand;
        std::vector<Card*> *stack;
        std::vector<Card*> *discardStack;

        std::vector<std::string*> *logs;
        std::vector<sf::Text*> *logsTexts;
        sf::RectangleShape *logsBackground;
        sf::Text *openLogsText;
        sf::RectangleShape *openLogsBtn;
        sf::Text *closeLogsText;
        sf::RectangleShape *closeLogsBtn;
        bool isOpenLogsText;

        Button *passParadeBtn;
        Button *endTurnBtn;
        Button *discardingBtn;
        bool isDiscarding;

        Game *game;
        int indexActualPlayer;
        bool blocking;
        int nbPlayers;
        int spriteShogunIndex;
        int indexSelectedCard;
        int indexSelectedPlayer;

        int attackRapideNbDamage;
    
    public:
        UI(sf::Font *font, sf::Image *HPImage, sf::Image *HonorImage, sf::Image *backRoleImage, sf::Image *backCardImage, std::vector<sf::Image*> *roleImages, std::vector<sf::Image*> *cardImages, std::vector<sf::Image*> *characterImages);
        
        void menu(sf::Image *leftImage, sf::Image *rightImage);
        void start();
        void update();
        void display();
        void setPlayersSprites();
        void setSpriteHonorCharactersHP(int index);
        void setActualPlayerSprite();
        void setHandSprite();
        void setStackSprite();
        void setDiscardStackSprite();
        void setLogsTexts();
        void setPermanentCircleSprites();

        void handleClickLogBtn(sf::Event event);
        void handleClickHandCard(sf::Event event);
        void handleClickPassParadeBtn(sf::Event event);
        void handleClickEndTurnBtn(sf::Event event);
        void handleClickDiscardingBtn(sf::Event event);
        void handleClickNobunaga(sf::Event event);

        void score();

        ~UI();
};

#endif // UI_H