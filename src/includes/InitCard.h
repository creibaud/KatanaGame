#ifndef INIT_CARD_H
#define INIT_CARD_H

#include "../Card/Action/Action.h"
#include "../Card/Permanent/Permanent.h"
#include "../Card/Weapon/Weapon.h"

#define CriDeGuerre Action(ActionType::CRI_DE_GUERRE)
#define Daimyo Action(ActionType::DAIMYO)
#define Diversion Action(ActionType::DIVERSION)
#define Geisha Action(ActionType::GEISHA)
#define Meditation Action(ActionType::MEDITATION)
#define Parade Action(ActionType::PARADE)
#define CeremonieDuThe Action(ActionType::CEREMONIE_DU_THE)
#define JuJitsu Action(ActionType::JU_JITSU)

#define AttaqueRapide Permanent(PermanentType::ATTAQUE_RAPIDE)
#define CodeDuBushido Permanent(PermanentType::CODE_DU_BUSHIDO)
#define Armure Permanent(PermanentType::ARMURE)
#define Concentration Permanent(PermanentType::CONCENTRATION)

#define Nodachi Weapon(WeaponType::NODACHI, 3, 3)
#define Naginata Weapon(WeaponType::NAGINATA, 1, 4)
#define Nagayari Weapon(WeaponType::NAGAYARI, 2, 4)
#define Tanegashima Weapon(WeaponType::TANEGASHIMA, 1, 5)
#define Daikyu Weapon(WeaponType::DAIKYU, 2, 5)
#define Bo Weapon(WeaponType::BO, 1, 6)
#define Kusarigama Weapon(WeaponType::KUSARIGAMA, 2, 2)
#define Katana Weapon(WeaponType::KATANA, 3, 2)
#define Shuriken Weapon(WeaponType::SHURIKEN, 1, 3)
#define Kanabo Weapon(WeaponType::KANABO, 2, 3)
#define Bokken Weapon(WeaponType::BOKKEN, 1, 1)
#define Kiseru Weapon(WeaponType::KISERU, 2, 1)
#define Wakizashi Weapon(WeaponType::WAKIZASHI, 3, 1)

#define NB_COPY_CRI_DE_GUERRE 4
#define NB_COPY_DAIMYO 3
#define NB_COPY_DIVERSION 5
#define NB_COPY_GEISHA 6
#define NB_COPY_MEDITATION 3
#define NB_COPY_PARADE 15
#define NB_COPY_CEREMONIE_DU_THE 4
#define NB_COPY_JU_JITSU 3

#define NB_COPY_ATTAQUE_RAPIDE 3
#define NB_COPY_CODE_DU_BUSHIDO 2
#define NB_COPY_ARMURE 4
#define NB_COPY_CONCENTRATION 6

#define NB_COPY_NODACHI 1
#define NB_COPY_NAGINATA 2
#define NB_COPY_NAGAYARI 1
#define NB_COPY_TANEGASHIMA 1
#define NB_COPY_DAIKYU 1
#define NB_COPY_BO 5
#define NB_COPY_KUSARIGAMA 4
#define NB_COPY_KATANA 1
#define NB_COPY_SHURIKEN 3
#define NB_COPY_KANABO 1
#define NB_COPY_BOKKEN 6
#define NB_COPY_KISERU 5
#define NB_COPY_WAKIZASHI 1

#endif // INIT_CARD_H