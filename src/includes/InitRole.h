/**
 * @file InitRole.h
 * @brief This file contains the initialization of roles.
 */

#ifndef INIT_ROLE_H
#define INIT_ROLE_H

#include "../Role/Role.h"

#define Shogun Role(RoleType::SHOGUN)           /**< Shogun role */
#define Samurai Role(RoleType::SAMURAI)         /**< Samurai role */
#define NinjaOne Role(RoleType::NINJA, 1)       /**< Ninja role level 1*/
#define NinjaTwo Role(RoleType::NINJA, 2)       /**< Ninja role level 2*/
#define NinjaThree Role(RoleType::NINJA, 3)     /**< Ninja role level 3*/
#define Ronin Role(RoleType::RONIN)             /**< Ronin role */

#endif // INIT_ROLE_H