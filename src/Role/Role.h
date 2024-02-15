/**
 * @file Role.h
 * @brief This file contains the declaration of the Role class and the enum class RoleType.
*/

#ifndef ROLE_H
#define ROLE_H

#include <string>

/**
 * @enum RoleType
 * @brief Represents the type of a Role.
 * @note The type of a Role is also the index of the Role in the Image List
 * and as the name of the Role
 */
enum class RoleType {
    SHOGUN,     /**< SHOGUN role type*/
    SAMURAI,    /**< SAMURAI role type*/
    NINJA,      /**< NINJA role type*/
    RONIN       /**< RONIN role type*/
};

/**
 * @class Role
 * @brief The Role class represents a role in the game.
 * 
 * A role has a type and a level. The type determines the role's abilities and characteristics,
 * while the level represents the role's progression or experience.
 */
class Role {
    private:
        RoleType type;  /**< Type of the role */
        int level;      /**< Level of the role */

    public:
        /**
         * @brief Constructs a new Role object.
         * 
         * @param type The type of the role.
         * @param level The level of the role (default is 0).
         */
        Role(RoleType type, int level = 0);

        /**
         * @brief Gets the type of the role.
         * 
         * @return The type of the role.
         */
        RoleType getType() const;

        /**
         * @brief Gets the level of the role.
         * 
         * @return The level of the role.
         */
        int getLevel() const;

        /**
         * @brief Gets the index of the role.
         * 
         * @return The index of the role.
         */
        int getIndex() const;

        /**
         * @brief Gets the name of the role.
         * 
         * @return The name of the role.
         */
        std::string getName() const;
};

#endif // ROLE_H