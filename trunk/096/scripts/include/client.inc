/* CLIENT.INC - defines client releated constants.
 *
 * This include file is designed to hold all the client lowlevel constants.
 * Not all constants might be usable as of now, but in the future, they
 * might be.
 */


//TODO: not complete
enum HUMAN_ANIMATIONS
	ANIM_WALK_UNARMED         :=  0x0000, // Walk unarmed.
	ANIM_WALK_ARMED           :=  0x0001, // Walk armed.
	ANIM_RUN_UNARMED          :=  0x0002, // Run unarmed.
	ANIM_RUN_ARMED            :=  0x0003, // Run armed.
	ANIM_STAND                :=  0x0004, // Stand.
	ANIM_FIDGET_1             :=  0x0005, // Twist a little (look around?).
	ANIM_FIDGET_2             :=  0x0006, // Look down.
	ANIM_STAND_1HAND          :=  0x0007, // Stand 1 handed attack.
	ANIM_STAND_2HAND          :=  0x0008, // Stand 2 handed attack.
	ANIM_ATTACK_1HAND_WIDE    :=  0x0009, // Attack 1 handed wide (sword/any).
	ANIM_ATTACK_1HAND_JAB     :=  0x000A, // Attack 1 handed jab (fencing).
	ANIM_ATTACK_1HAND_DOWN    :=  0x000B, // Attack 1 handed down (mace).
	ANIM_ATTACK_2HAND_DOWN    :=  0x000C, // Attack 2 handed jab (mace).
	ANIM_ATTACK_2HAND_WIDE    :=  0x000D, // Attack 2 handed wide.
	ANIM_ATTACK_2HAND_JAB     :=  0x000E, // Attack 2 handed jab (spear).
	ANIM_ATTACK_BOW           :=  0x0012, // Attack bow.
	ANIM_ATTACK_XBOW          :=  0x0013, // Attack xbow.
	ANIM_WALK_WARMODE         :=  0x000F, // Walk in warmode.
	ANIM_CAST_DIR             :=  0x0010, // Spellcasting direction.
	ANIM_CAST_AREA            :=  0x0011, // Spellcasting area.
	ANIM_HIT                  :=  0x0014, // Get hit.
	ANIM_DIE_BACK             :=  0x0015, // Die backward.
	ANIM_DIE_FOR              :=  0x0016, // Die forward.
	ANIM_BOW                  :=  0x0020, // Bow.
	ANIM_SALUTE               :=  0x0021, // Salute.
	ANIM_EAT                  :=  0x0022  // Eat.
endenum


enum LAYERS
	LAYER_NONE        :=  0x00,   // Not used?
	LAYER_HAND1       :=  0x01,   // One handed weapon.
	LAYER_HAND2       :=  0x02,   // Two handed weapon, shield or misc.
	LAYER_SHOES       :=  0x03,   // Shoes.
	LAYER_PANTS       :=  0x04,   // Pants.
	LAYER_SHIRT       :=  0x05,   // Shirt.
	LAYER_HELM        :=  0x06,   // Helm or Hat.
	LAYER_GLOVES      :=  0x07,   // Gloves.
	LAYER_RING        :=  0x08,   // Ring.
	LAYER_UNUSED9     :=  0x09,   // Unused.
	LAYER_NECK        :=  0x0a,   // Neck.
	LAYER_HAIR        :=  0x0b,   // Hair
	LAYER_WAIST       :=  0x0c,   // Waist (half apron).
	LAYER_CHEST       :=  0x0d,   // Torso (inner) (chest armor).
	LAYER_WRIST       :=  0x0e,   // Bracelet.
	LAYER_PACK2       :=  0x0f,   // Unused (backpack, but ord. bp is 0x15).
	LAYER_BEARD       :=  0x10,   // Facial hair.
	LAYER_TUNIC       :=  0x11,   // Torso (middle) (tunic, sash etc.).
	LAYER_EARS        :=  0x12,   // Earrings.
	LAYER_ARMS        :=  0x13,   // Arms.
	LAYER_CAPE        :=  0x14,   // Back (cloak).
	LAYER_PACK        :=  0x15,   // Backpack
	LAYER_ROBE        :=  0x16,   // Torso (outer) (robe)
	LAYER_SKIRT       :=  0x17,   // Legs (outer) (skirt/robe).
	LAYER_LEGS        :=  0x18,   // Legs (inner) (leg armor).
	LAYER_MOUNT       :=  0x19,   // Mount (horse, ostard etc.).
	LAYER_VENDORSTOCK :=  0x1a,   // This vendor will sell and restock.
	LAYER_VENDOREXTRA :=  0x1b,   // This vendor will resell to players but not restock.
	LAYER_VENDORBUY   :=  0x1c,   // This vendor can buy from players but does not stock.
	LAYER_BANKBOX     :=  0x1d,   // Contents of bankbox
	LAYER_TRADE       :=  0x1e    // Can be multiple of these, do not use directly.
endenum


enum SPEECH_TYPES
	SPEECH_REGULAR      := 0x00,
	SPEECH_BROADCAST    := 0x01,
	SPEECH_EMOTE        := 0x02,
	SPEECH_LABEL        := 0x06,
	SPEECH_EMPHASIS     := 0x07,
	SPEECH_WHISPER      := 0x08,
	SPEECH_YELL         := 0x09,
	SPEECH_SPELL        := 0x0A
endenum


enum FONTS
	FONT_MAX          :=  0x09,   // Highest font.
	FONT_MIN          :=  0x00,   // Lowest font.

	FONT_BOLD         :=  0x00,   // Bold text.
	FONT_SHADOW       :=  0x01,   // Text with shadow.
	FONT_BOLD_SHAD    :=  0x02,   // Bold text with shadow.
	FONT_NORMAL       :=  0x03,   // Normal (default).
	FONT_GOTHIC       :=  0x04,   // Gothic.
	FONT_ITALIC       :=  0x05,   // Italic
	FONT_SMALL_DARK   :=  0x06,   // Small dark letters.
	FONT_COLOR        :=  0x07,   // Colorful font.
	FONT_RUNE         :=  0x08,   // Rune font (only capitals).
	FONT_SMALL_LIGHT  :=  0x09    // Small light letters.
endenum


enum DIRECTIONS
	MIN_DIR	:=  0x00,
	MAX_DIR :=  0x07,

	DIR_N	:=  0x00,   // North.
	DIR_NE	:=  0x01,   // Northeast.
	DIR_E	:=  0x02,   // East.
	DIR_SE	:=  0x03,   // Southeast.
	DIR_S	:=  0x04,   // South.
	DIR_SW	:=  0x05,   // Southwest.
	DIR_W	:=  0x06,   // West.
	DIR_NW	:=  0x07    // Northwest.
endenum

// SOUNDS ABC order by insideUO
// NOTE: Any number over 0xFF (255) will not work in older clients.
enum SOUNDS
	SFX_AGILITY		:= 0x1E8,
	SFX_AGILITY2		:= 0x28F,
	SFX_AIR_1		:= 0x291,
	SFX_AIR_2		:= 0x292,
	SFX_AIR_3		:= 0x293,
	SFX_AIR_4		:= 0x294,
	SFX_AIR_5		:= 0x295,
	SFX_AIRELEMENTAL_1	:= 0x108,
	SFX_AIRELEMENTAL_2	:= 0x109,
	SFX_AIRELEMENTAL_3	:= 0x10A,
	SFX_AIRELEMENTAL_4	:= 0x10B,
	SFX_AIRELEMENTAL_5	:= 0x10C,
	SFX_ALIGATOR_1		:= 0x5B,
	SFX_ALIGATOR_2		:= 0x5C,
	SFX_ALIGATOR_3		:= 0x5D,
	SFX_ALIGATOR_4		:= 0x5E,
	SFX_ALIGATOR_5		:= 0x5F,
	SFX_ALIGATORB_1		:= 0x295,
	SFX_ALIGATORB_2		:= 0x296,
	SFX_ALIGATORB_3		:= 0x297,
	SFX_ALIGATORB_4		:= 0x298,
	SFX_ALIGATORB_5		:= 0x299,
	SFX_ANVIL		:= 0x2B,
	SFX_ARCH_PROTECT	:= 0x1F8,
	SFX_AQUARIUM_DEADFISH	:= 0x5A3,
	SFX_AQUARIUM_REWARDS	:= 0x5A4,
	SFX_AQUARIUM_USE	:= 0x5A5,
	SFX_ARCANE_CIRCLE	:= 0x5A6
	SFX_ARCANE_EMPOWERMENT	:= 0x5C2,
	SFX_ARCANE_EMPOWER_END	:= 0x5C3,
	SFX_ARCH_CURE		:= 0x1E9,
	SFX_ARCH_CURE2		:= 0x29A,
	SFX_ATTUNE_WEAPON	:= 0x5C4,
	SFX_AXE_01		:= 0x233,
	SFX_BEAR_1		:= 0x60,
	SFX_BEAR_2		:= 0x61,
	SFX_BEAR_3		:= 0x62,
	SFX_BEAR_4		:= 0x63,
	SFX_BEAR_5		:= 0x64,
endenum
	