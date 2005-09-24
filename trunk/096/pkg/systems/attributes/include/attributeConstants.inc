/* $Id: attributes.inc,v 1.5 2004/05/02 12:20:56 melanius Exp $
 *
 * Purpose
 * Provide various functions and constants for the attribute system.
 *
 */
use uo;

enum VITALS
	VITAL_HITS         := "HitsRegeneration",
	VITAL_MANA         := "ManaRegeneration",
	VITAL_STAMINA      := "StaminaRegeneration"
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
	ATTRIBUTE_PARRY                     := "Parry",
	ATTRIBUTE_BEGGING                   := "Begging",
	ATTRIBUTE_BLACKSMITHY               := "Blacksmithy",
	ATTRIBUTE_BOWCRAP_T_FLETCHING        := "BowcrAP_tFletching",
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
