/* $Id$
 *
 * Purpose
 * Provide various functions and constants for the attribute system.
 *
 */
use uo;

enum VITALS
	VITAL_HITS         := "Hits",
	VITAL_MANA         := "Mana",
	VITAL_STAMINA      := "Stamina"
endenum

enum ATTRIBUTE_STATS
	ATTRIB_STRENGTH                  := "Strength",
	ATTRIB_DEXTERITY                 := "Dexterity",
	ATTRIB_INTELLIGENCE              := "Intelligence"
endenum

enum ATTRIBUTE_SKILLS
	ATTRIB_ALCHEMY                   := "Alchemy",
	ATTRIB_ANATOMY                   := "Anatomy",
	ATTRIB_ANIMAL_LORE               := "AnimalLore",
	ATTRIB_ITEM_IDENTIFICATION       := "ItemIdentification",
	ATTRIB_ARMS_LORE                 := "ArmsLore",
	ATTRIB_PARRY                     := "Parry",
	ATTRIB_BEGGING                   := "Begging",
	ATTRIB_BLACKSMITHY               := "Blacksmithy",
	ATTRIB_BOWCRAP_T_FLETCHING       := "BowcraftFletching",
	ATTRIB_PEACEMAKING               := "Peacemaking",
	ATTRIB_CAMPING                   := "Camping",
	ATTRIB_CARPENTRY                 := "Carpentry",
	ATTRIB_CARTOGRAPHY               := "Cartography",
	ATTRIB_COOKING                   := "Cooking",
	ATTRIB_DETECTING_HIDDEN          := "DetectingHidden",
	ATTRIB_DISCORDANCE               := "Discordance",
	ATTRIB_EVALUATING_INTELLIGENCE   := "EvaluatingIntelligence",
	ATTRIB_HEALING                   := "Healing",
	ATTRIB_FISHING                   := "Fishing",
	ATTRIB_FORENSIC_EVALUATION       := "ForensicEvaluation",
	ATTRIB_HERDING                   := "Herding",
	ATTRIB_HIDING                    := "Hiding",
	ATTRIB_PROVOCATION               := "Provocation",
	ATTRIB_INSCRIPTION               := "Inscription",
	ATTRIB_LOCKPICKING               := "Lockpicking",
	ATTRIB_MAGERY                    := "Magery",
	ATTRIB_RESISTING_SPELLS          := "ResistingSpells",
	ATTRIB_TACTICS                   := "Tactics",
	ATTRIB_SNOOPING                  := "Snooping",
	ATTRIB_MUSICIANSHIP              := "Musicianship",
	ATTRIB_POISONING                 := "Poisoning",
	ATTRIB_ARCHERY                   := "Archery",
	ATTRIB_SPIRIT_SPEAK              := "SpiritSpeak",
	ATTRIB_STEALING                  := "Stealing",
	ATTRIB_TAILORING                 := "Tailoring",
	ATTRIB_ANIMAL_TAMING             := "AnimalTaming",
	ATTRIB_TASTE_IDENTIFICATION      := "TasteIdentification",
	ATTRIB_TINKERING                 := "Tinkering",
	ATTRIB_TRACKING                  := "Tracking",
	ATTRIB_VETERINARY                := "Veterinary",
	ATTRIB_SWORDSMANSHIP             := "Swordsmanship",
	ATTRIB_MACE_FIGHTING             := "MaceFighting",
	ATTRIB_FENCING                   := "Fencing",
	ATTRIB_WRESTLING                 := "Wrestling",
	ATTRIB_LUMBERJACKING             := "Lumberjacking",
	ATTRIB_MINING                    := "Mining",
	ATTRIB_MEDITATION                := "Meditation",
	ATTRIB_STEALTH                   := "Stealth",
	ATTRIB_REMOVE_TRAP               := "RemoveTrap",
	ATTRIB_NECROMANCY                := "Necromancy",
	ATTRIB_BATTLE_FOCUS              := "BattleFocus",
	ATTRIB_CHIVALRY                  := "Chivalry"
endenum
