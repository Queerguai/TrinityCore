/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TRINITYCORE_PET_DEFINES_H
#define TRINITYCORE_PET_DEFINES_H

#include "Define.h"
#include "Optional.h"
#include <array>
#include <string>
#include <vector>

enum ReactStates : uint8;

enum PetType : uint8
{
    SUMMON_PET              = 0,
    HUNTER_PET              = 1,
    MAX_PET_TYPE            = 4
};

#define MAX_PET_STABLES         4

// stored in character_pet.slot
enum PetSaveMode : int16
{
    PET_SAVE_AS_DELETED        = -2,                        // not saved in fact
    PET_SAVE_AS_CURRENT        =  0,                        // in current slot (with player)
    PET_SAVE_FIRST_STABLE_SLOT =  1,
    PET_SAVE_LAST_STABLE_SLOT  =  MAX_PET_STABLES,          // last in DB stable slot index (including), all higher have same meaning as PET_SAVE_NOT_IN_SLOT
    PET_SAVE_NOT_IN_SLOT       = -1                         // for avoid conflict with stable size grow will use negative value
};

enum PetSpellState
{
    PETSPELL_UNCHANGED = 0,
    PETSPELL_CHANGED   = 1,
    PETSPELL_NEW       = 2,
    PETSPELL_REMOVED   = 3
};

enum PetSpellType
{
    PETSPELL_NORMAL = 0,
    PETSPELL_FAMILY = 1,
    PETSPELL_TALENT = 2
};

enum class PetActionFeedback : uint8
{
    None            = 0,
    Dead            = 1,
    NoTarget        = 2,
    InvalidTarget   = 3,
    NoPath          = 4
};

enum PetTalk
{
    PET_TALK_SPECIAL_SPELL  = 0,
    PET_TALK_ATTACK         = 1
};

#define PET_FOLLOW_DIST  1.0f
#define PET_FOLLOW_ANGLE float(M_PI)

enum class PetTameResult : uint8
{
    Ok                      = 0,
    InvalidCreature         = 1,
    TooMany                 = 2,
    CreatureAlreadyOwned    = 3,
    NotTameable             = 4,
    AnotherSummonActive     = 5,
    UnitsCantTame           = 6,
    NoPetAvailable          = 7,
    InternalError           = 8,
    TooHighLevel            = 9,
    Dead                    = 10,
    NotDead                 = 11,
    CantControlExotic       = 12,
    InvalidSlot             = 13,
    EliteTooHighLevel       = 14
};

class PetStable
{
public:
    struct PetInfo
    {
        PetInfo() { }

        std::string Name;
        std::string ActionBar;
        uint32 PetNumber = 0;
        uint32 CreatureId = 0;
        uint32 DisplayId = 0;
        uint32 Experience = 0;
        uint32 Health = 0;
        uint32 Mana = 0;
        uint32 LastSaveTime = 0;
        uint32 CreatedBySpellId = 0;
        uint16 SpecializationId = 0;
        uint8 Level = 0;
        ReactStates ReactState = ReactStates(0);
        PetType Type = MAX_PET_TYPE;
        bool WasRenamed = false;
    };

    Optional<PetInfo> CurrentPet;                                   // PET_SAVE_AS_CURRENT
    std::array<Optional<PetInfo>, MAX_PET_STABLES> StabledPets;     // PET_SAVE_FIRST_STABLE_SLOT - PET_SAVE_LAST_STABLE_SLOT
    std::vector<PetInfo> UnslottedPets;                             // PET_SAVE_NOT_IN_SLOT

    PetInfo const* GetUnslottedHunterPet() const
    {
        return UnslottedPets.size() == 1 && UnslottedPets[0].Type == HUNTER_PET ? &UnslottedPets[0] : nullptr;
    }
};

#endif
