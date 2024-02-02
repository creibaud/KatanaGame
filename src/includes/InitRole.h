#ifndef INIT_ROLE_H
#define INIT_ROLE_H

#include "../Role/Role.h"

#define Shogun Role(RoleType::SHOGUN)
#define Samurai Role(RoleType::SAMURAI)
#define NinjaOne Role(RoleType::NINJA, 1)
#define NinjaTwo Role(RoleType::NINJA, 2)
#define NinjaThree Role(RoleType::NINJA, 3)
#define Ronin Role(RoleType::RONIN)

#endif // INIT_ROLE_H