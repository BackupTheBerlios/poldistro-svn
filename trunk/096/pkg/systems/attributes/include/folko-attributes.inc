/* $Id: attributes.inc,v 1.5 2004/05/02 12:20:56 melanius Exp $
 *
 * Purpose
 * Provide various functions and constants for the attribute system.
 *
 */
use uo;

enum ATTRIBUTE_CUSTOM
	ATTRIBUTE_HITS_REGENERATION         := "HitsRegeneration",
	ATTRIBUTE_MANA_REGENERATION         := "ManaRegeneration",
	ATTRIBUTE_STAMINA_REGENERATION      := "StaminaRegeneration"
endenum

enum ATTRIBUTE_STATS
	ATTRIBUTE_STRENGTH                  := "Strength",
	ATTRIBUTE_DEXTERITY                 := "Dexterity",
	ATTRIBUTE_INTELLIGENCE              := "Intelligence"
endenum

enum ATTRIBUTE_SKILLS
	ATTRIBUTE_ALCHEMY                   := "Alchemy",
	ATTRIBUTE_ANATOMY                   := "Anatomy",
	ATTRIBUTE_ANIMAL_LORE               := "AnimalLore",
	ATTRIBUTE_ITEM_IDENTIFICATION       := "ItemIdentification",
	ATTRIBUTE_ARMS_LORE                 := "ArmsLore",
	ATTRIBUTE_PARRYING                  := "Parrying",
	ATTRIBUTE_BEGGING                   := "Begging",
	ATTRIBUTE_BLACKSMITHY               := "Blacksmithy",
	ATTRIBUTE_BOWCRAFT_FLETCHING        := "BowcraftFletching",
    ATTRIBUTE_PEACEMAKING               := "Peacemaking",
    ATTRIBUTE_CAMPING                   := "Camping",
    ATTRIBUTE_CARPENTRY                 := "Carpentry",
    ATTRIBUTE_CARTOGRAPHY               := "Cartography",
    ATTRIBUTE_COOKING                   := "Cooking",
    ATTRIBUTE_DETECTING_HIDDEN          := "DetectingHidden",
    ATTRIBUTE_DISCORDANCE               := "Discordance",
    ATTRIBUTE_EVALUATING_INTELLIGENCE   := "EvaluatingIntelligence",
    ATTRIBUTE_HEALING                   := "Healing",
    ATTRIBUTE_FISHING                   := "Fishing",
    ATTRIBUTE_FORENSIC_EVALUATION       := "ForensicEvaluation",
    ATTRIBUTE_HERDING                   := "Herding",
    ATTRIBUTE_HIDING                    := "Hiding",
    ATTRIBUTE_PROVOCATION               := "Provocation",
    ATTRIBUTE_INSCRIPTION               := "Inscription",
    ATTRIBUTE_LOCKPICKING               := "Lockpicking",
    ATTRIBUTE_MAGERY                    := "Magery",
    ATTRIBUTE_RESISTING_SPELLS          := "ResistingSpells",
    ATTRIBUTE_TACTICS                   := "Tactics",
    ATTRIBUTE_SNOOPING                  := "Snooping",
    ATTRIBUTE_MUSICIANSHIP              := "Musicianship",
    ATTRIBUTE_POISONING                 := "Poisoning",
    ATTRIBUTE_ARCHERY                   := "Archery",
    ATTRIBUTE_SPIRIT_SPEAK              := "SpiritSpeak",
    ATTRIBUTE_STEALING                  := "Stealing",
    ATTRIBUTE_TAILORING                 := "Tailoring",
    ATTRIBUTE_ANIMAL_TAMING             := "AnimalTaming",
    ATTRIBUTE_TASTE_IDENTIFICATION      := "TasteIdentification",
    ATTRIBUTE_TINKERING                 := "Tinkering",
    ATTRIBUTE_TRACKING                  := "Tracking",
    ATTRIBUTE_VETERINARY                := "Veterinary",
    ATTRIBUTE_SWORDSMANSHIP             := "Swordsmanship",
    ATTRIBUTE_MACE_FIGHTING             := "MaceFighting",
    ATTRIBUTE_FENCING                   := "Fencing",
    ATTRIBUTE_WRESTLING                 := "Wrestling",
    ATTRIBUTE_LUMBERJACKING             := "Lumberjacking",
    ATTRIBUTE_MINING                    := "Mining",
    ATTRIBUTE_MEDITATION                := "Meditation",
    ATTRIBUTE_STEALTH                   := "Stealth",
    ATTRIBUTE_REMOVE_TRAP               := "RemoveTrap",
    ATTRIBUTE_NECROMANCY                := "Necromancy",
    ATTRIBUTE_BATTLE_FOCUS              := "BattleFocus",
    ATTRIBUTE_CHIVALRY                  := "Chivalry"
endenum


/*
 * GetCustomAttributes()
 *
 * Author: Melanius [x90]
 * Last-Edit: Folko
 *
 * Purpose
 * Returns an array with all the custom attribute names.
 *
 * Parameters
 * No parameters
 *
 * Return value
 * Array containing the names of all custom attributes.
 *
 */
function GetCustomAttributes()
	return(
		{
			ATTRIBUTE_HITS_REGENERATION,
			ATTRIBUTE_MANA_REGENERATION,
			ATTRIBUTE_STAMINA_REGENERATION
		}
	);
endfunction


/*
 * GetStatAttributes()
 *
 * Author: Melanius [x90]
 * Last-Edit: Folko
 *
 * Purpose
 * Returns an array with the names of all stat attributes.
 *
 * Parameters
 * No parameters
 *
 * Return value
 * Array containing the names of all stat attribuets.
 *
 */
function GetStatAttributes()
	return(
		{
			ATTRIBUTE_STRENGTH,
			ATTRIBUTE_DEXTERITY,
			ATTRIBUTE_INTELLIGENCE
		}
	);
endfunction


/*
 * GetSkillAttributes()
 *
 * Author: Melanius [x90]
 * Last-Edit: Folko
 *
 * Purpose
 * Returns an array with the names of all skill attributes.
 *
 * Parameters
 * No parameters
 *
 * Return value
 * Array containing the names of all attributes.
 *
 */
function GetSkillAttributes()
	return(
		{
			ATTRIBUTE_ALCHEMY,
			ATTRIBUTE_ANATOMY,
			ATTRIBUTE_ANIMAL_LORE,
            ATTRIBUTE_ITEM_IDENTIFICATION,
            ATTRIBUTE_ARMS_LORE,
            ATTRIBUTE_PARRYING,
            ATTRIBUTE_BEGGING,
            ATTRIBUTE_BLACKSMITHY,
            ATTRIBUTE_BOWCRAFT_FLETCHING,
            ATTRIBUTE_PEACEMAKING,
            ATTRIBUTE_CAMPING,
            ATTRIBUTE_CARPENTRY,
            ATTRIBUTE_CARTOGRAPHY,
            ATTRIBUTE_COOKING,
            ATTRIBUTE_DETECTING_HIDDEN,
            ATTRIBUTE_DISCORDANCE,
            ATTRIBUTE_EVALUATING_INTELLIGENCE,
            ATTRIBUTE_HEALING,
            ATTRIBUTE_FISHING,
            ATTRIBUTE_FORENSIC_EVALUATION,
            ATTRIBUTE_HERDING,
            ATTRIBUTE_HIDING,
            ATTRIBUTE_PROVOCATION,
            ATTRIBUTE_INSCRIPTION,
            ATTRIBUTE_LOCKPICKING,
            ATTRIBUTE_MAGERY,
            ATTRIBUTE_RESISTING_SPELLS,
            ATTRIBUTE_TACTICS,
            ATTRIBUTE_SNOOPING,
            ATTRIBUTE_MUSICIANSHIP,
            ATTRIBUTE_POISONING,
            ATTRIBUTE_ARCHERY,
            ATTRIBUTE_SPIRIT_SPEAK,
            ATTRIBUTE_STEALING,
            ATTRIBUTE_TAILORING,
            ATTRIBUTE_ANIMAL_TAMING,
            ATTRIBUTE_TASTE_IDENTIFICATION,
            ATTRIBUTE_TINKERING,
            ATTRIBUTE_TRACKING,
            ATTRIBUTE_VETERINARY,
            ATTRIBUTE_SWORDSMANSHIP,
            ATTRIBUTE_MACE_FIGHTING,
            ATTRIBUTE_FENCING,
            ATTRIBUTE_WRESTLING,
            ATTRIBUTE_LUMBERJACKING,
            ATTRIBUTE_MINING,
            ATTRIBUTE_MEDITATION,
            ATTRIBUTE_STEALTH,
            ATTRIBUTE_REMOVE_TRAP,
			ATTRIBUTE_NECROMANCY,
			ATTRIBUTE_BATTLE_FOCUS,
			ATTRIBUTE_CHIVALRY
		}
	);
endfunction
