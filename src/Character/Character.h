/**
 * @file Character.h
 * @brief This file contains the declaration of the Character class and the enum class CharacterType.
*/

#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

/**
 * @enum CharacterType
 * @brief Represents the type of a Character.
 * @note The type of a Character is also the index of the Character in the Image List
 * and as the name of the Character
 */
enum class CharacterType {
    HANZO,          /**< HANZO character type*/
    USHIWAKA,       /**< USHIWAKA character type*/
    CHIYOME,        /**< CHIYOME character type*/
    HIDEYOSHI,      /**< HIDEYOSHI character type*/
    GINCHIYO,       /**< GINCHIYO character type*/
    GOEMON,         /**< GOEMON character type*/
    NOBUNAGA,       /**< NOBUNAGA character type*/
    TOMOE,          /**< TOMOE character type*/
    IEYASU,         /**< IEYASU character type*/
    BENKEI,         /**< BENKEI character type*/
    MUSASHI,        /**< MUSASHI character type*/
    KOJIRO          /**< KOJIRO character type*/
};

/**
 * @class Character
 * @brief The Character class represents a character in the game.
 * 
 * This class stores information about the character's type, HP (hit points), and provides
 * methods to access and modify these attributes.
 */
class Character {
    private:
        CharacterType type;     /**< Type of character */
        int HP;                 /**< Health point of the character */
    
    public:
        /**
         * @brief Constructs a new Character object.
         * 
         * @param type The type of the character.
         * @param HP The initial hit points of the character.
         */
        Character(CharacterType type, int HP);

        /**
         * @brief Gets the type of the character.
         * 
         * @return The character type.
         */
        CharacterType getType() const;

        /**
         * @brief Gets the index of the character.
         * 
         * @return The character index.
         */
        int getIndex() const;

        /**
         * @brief Gets the hit points of the character.
         * 
         * @return The character's hit points.
         */
        int getHP() const;

        /**
         * @brief Gets the name of the character.
         * 
         * @return The character's name.
         */
        std::string getName() const;
};

#endif // CHARACTER_H