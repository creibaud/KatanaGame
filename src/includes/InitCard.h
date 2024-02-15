/**
 * @file InitCard.h
 * @brief This file contains the initialization of various cards, actions, permanents, and weapons.
 */

#ifndef INIT_CARD_H
#define INIT_CARD_H

#include "../Card/Action/Action.h"
#include "../Card/Permanent/Permanent.h"
#include "../Card/Weapon/Weapon.h"

#define CriDeGuerre Action(ActionType::CRI_DE_GUERRE)               /**< CRI_DE_GUERRE action card */
#define Daimyo Action(ActionType::DAIMYO)                           /**< DAIMYO action card */
#define Diversion Action(ActionType::DIVERSION)                     /**< DIVERSION action card */
#define Geisha Action(ActionType::GEISHA)                           /**< GEISHA action card */
#define Meditation Action(ActionType::MEDITATION)                   /**< MEDITATION action card */
#define Parade Action(ActionType::PARADE)                           /**< PARADE action card */
#define CeremonieDuThe Action(ActionType::CEREMONIE_DU_THE)         /**< CEREMONIE_DU_THE action card */
#define JuJitsu Action(ActionType::JU_JITSU)                        /**< JU_JITSU action card */

#define AttaqueRapide Permanent(PermanentType::ATTAQUE_RAPIDE)      /**< ATTAQUE_RAPIDE permanent card */
#define CodeDuBushido Permanent(PermanentType::CODE_DU_BUSHIDO)     /**< CODE_DU_BUSHIDO permanent card */
#define Armure Permanent(PermanentType::ARMURE)                     /**< ARMURE permanent card */
#define Concentration Permanent(PermanentType::CONCENTRATION)       /**< CONCENTRATION permanent card */

#define Nodachi Weapon(WeaponType::NODACHI, 3, 3)                   /**< NODACHI weapon card */
#define Naginata Weapon(WeaponType::NAGINATA, 1, 4)                 /**< NAGINATA weapon card */
#define Nagayari Weapon(WeaponType::NAGAYARI, 2, 4)                 /**< NAGAYARI weapon card */
#define Tanegashima Weapon(WeaponType::TANEGASHIMA, 1, 5)           /**< TANEGASHIMA weapon card */
#define Daikyu Weapon(WeaponType::DAIKYU, 2, 5)                     /**< DAIKYU weapon card */
#define Bo Weapon(WeaponType::BO, 1, 2)                             /**< BO weapon card */
#define Kusarigama Weapon(WeaponType::KUSARIGAMA, 2, 2)             /**< KUSARIGAMA weapon card */
#define Katana Weapon(WeaponType::KATANA, 3, 2)                     /**< KATANA weapon card */
#define Shuriken Weapon(WeaponType::SHURIKEN, 1, 3)                 /**< SHURIKEN weapon card */
#define Kanabo Weapon(WeaponType::KANABO, 2, 3)                     /**< KANABO weapon card */
#define Bokken Weapon(WeaponType::BOKKEN, 1, 1)                     /**< BOKKEN weapon card */
#define Kiseru Weapon(WeaponType::KISERU, 2, 1)                     /**< KISERU weapon card */
#define Wakizashi Weapon(WeaponType::WAKIZASHI, 3, 1)               /**< WAKIZASHI weapon card */

#define NB_COPY_CRI_DE_GUERRE 4         /**< Number of copies of CRI_DE_GUERRE action card */
#define NB_COPY_DAIMYO 3                /**< Number of copies of DAIMYO action card */
#define NB_COPY_DIVERSION 5             /**< Number of copies of DIVERSION action card */
#define NB_COPY_GEISHA 6                /**< Number of copies of GEISHA action card */
#define NB_COPY_MEDITATION 3            /**< Number of copies of MEDITATION action card */
#define NB_COPY_PARADE 15               /**< Number of copies of PARADE action card */
#define NB_COPY_CEREMONIE_DU_THE 4      /**< Number of copies of CEREMONIE_DU_THE action card */
#define NB_COPY_JU_JITSU 3              /**< Number of copies of JU_JITSU action card */

#define NB_COPY_ATTAQUE_RAPIDE 3        /**< Number of copies of ATTAQUE_RAPIDE permanent card */
#define NB_COPY_CODE_DU_BUSHIDO 2       /**< Number of copies of CODE_DU_BUSHIDO permanent card */
#define NB_COPY_ARMURE 4                /**< Number of copies of ARMURE permanent card */
#define NB_COPY_CONCENTRATION 6         /**< Number of copies of CONCENTRATION permanent card */

#define NB_COPY_NODACHI 1               /**< Number of copies of NODACHI weapon card */
#define NB_COPY_NAGINATA 2              /**< Number of copies of NAGINATA weapon card */
#define NB_COPY_NAGAYARI 1              /**< Number of copies of NAGAYARI weapon card */
#define NB_COPY_TANEGASHIMA 1           /**< Number of copies of TANEGASHIMA weapon card */
#define NB_COPY_DAIKYU 1                /**< Number of copies of DAIKYU weapon card */
#define NB_COPY_BO 5                    /**< Number of copies of BO weapon card */
#define NB_COPY_KUSARIGAMA 4            /**< Number of copies of KUSARIGAMA weapon card */
#define NB_COPY_KATANA 1                /**< Number of copies of KATANA weapon card */
#define NB_COPY_SHURIKEN 3              /**< Number of copies of SHURIKEN weapon card */
#define NB_COPY_KANABO 1                /**< Number of copies of KANABO weapon card */
#define NB_COPY_BOKKEN 6                /**< Number of copies of BOKKEN weapon card */
#define NB_COPY_KISERU 5                /**< Number of copies of KISERU weapon card */
#define NB_COPY_WAKIZASHI 1             /**< Number of copies of WAKIZASHI weapon card */

#endif // INIT_CARD_H