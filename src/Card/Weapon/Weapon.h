/**
 * @file Weapon.h
 * @brief This file contains the declaration of the Weapon class and the enum class WeaponType.
*/

#ifndef WEAPON_H
#define WEAPON_H

#include "../Card.h"

/**
 * @enum WeaponType
 * @brief Represents the type of a Weapon.
 * @note The type of a Weapon is also the index of the Weapon in the Image List
 * and as the name of the Weapon
 */
enum class WeaponType {
    NODACHI,        /**< NODACHI weapon type*/
    NAGINATA,       /**< NAGINATA weapon type*/
    NAGAYARI,       /**< NAGAYARI weapon type*/
    TANEGASHIMA,    /**< TANEGASHIMA weapon type*/
    DAIKYU,         /**< DAIKYU weapon type*/
    BO,             /**< BO weapon type*/
    KUSARIGAMA,     /**< KUSARIGAMA weapon type*/
    KATANA,         /**< KATANA weapon type*/
    SHURIKEN,       /**< SHURIKEN weapon type*/
    KANABO,         /**< KANABO weapon type*/
    BOKKEN,         /**< BOKKEN weapon type*/
    KISERU,         /**< KISERU weapon type*/
    WAKIZASHI       /**< WAKIZASHI weapon type*/
};

/**
 * @class Weapon
 * @brief The Weapon class represents a weapon card in the game.
 * 
 * This class inherits from the Card class and provides additional
 * functionality specific to weapons, such as weapon type, damage,
 * and range.
 */
class Weapon : public Card {
    private:
        WeaponType weaponType;  /**< Type of weapon card */
        int damage;             /**< Damage value of the weapon */
        int range;              /**< Range value of the weapon */
    
    public:
        /**
         * @brief Constructs a new Weapon object.
         * 
         * @param weaponType The type of the weapon.
         * @param damage The damage value of the weapon.
         * @param range The range value of the weapon.
         */
        Weapon(WeaponType weaponType, int damage, int range);

        /**
         * @brief Gets the weapon type.
         * 
         * @return The weapon type.
         */
        WeaponType getWeaponType() const;

        /**
         * @brief Gets the damage value of the weapon.
         * 
         * @return The damage value.
         */
        int getDamage() const;

        /**
         * @brief Gets the range value of the weapon.
         * 
         * @return The range value.
         */
        int getRange() const;

        /**
         * @brief Gets the index of the weapon.
         * 
         * @return The index of the weapon.
         */
        int getIndex() override;
};

#endif // WEAPON_H