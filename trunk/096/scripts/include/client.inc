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
	DIR_N	:=  0x00,   // North.
	DIR_NE	:=  0x01,   // Northeast.
	DIR_E	:=  0x02,   // East.
	DIR_SE	:=  0x03,   // Southeast.
	DIR_S	:=  0x04,   // South.
	DIR_SW	:=  0x05,   // Southwest.
	DIR_W	:=  0x06,   // West.
	DIR_NW	:=  0x07    // Northwest.
endenum


// * Colors *
// This is not suposed to be a "complete" colorchart, but a
// quick way to access normal colors.
const COLOR_DEFAULT         := 0x0000;
const COLOR_BLACK           := 0x0001;
const COLOR_INDIGO_DARK     := 0x0007;
const COLOR_INDIGO          := 0x0008;
const COLOR_INDIGO_LIGHT    := 0x0009;

const COLOR_VIOLET_DARK     := 0x000c;
const COLOR_VIOLET          := 0x000d;
const COLOR_VIOLET_LIGHT    := 0x000e;
const COLOR_MAGENTA_DARK    := 0x0011;
const COLOR_MAGENTA         := 0x0012;
const COLOR_MAGENTA_LIGHT   := 0x0013;
const COLOR_RED_DARK        := 0x0020;
const COLOR_RED             := 0x0022;
const COLOR_RED_LIGHT       := 0x0023;
const COLOR_ORANGE_DARK     := 0x002a;
const COLOR_ORANGE          := 0x002b;
const COLOR_ORANGE_LIGHT    := 0x002c;
const COLOR_YELLOW_DARK     := 0x0034;
const COLOR_YELLOW          := 0x0035;
const COLOR_YELLOW_LIGHT    := 0x0036;
const COLOR_GREEN_DARK      := 0x003e;
const COLOR_GREEN           := 0x003f;
const COLOR_GREEN_LIGHT     := 0x0040;
const COLOR_CYAN_DARK       := 0x0057;
const COLOR_CYAN            := 0x0058;
const COLOR_CYAN_LIGHT      := 0x0059;
const COLOR_BLUE_DARK       := 0x0061;
const COLOR_BLUE            := 0x0062;
const COLOR_BLUE_LIGHT      := 0x0063;
const COLOR_GRAY_DARK       := 0x0386;
const COLOR_GRAY            := 0x0387;
const COLOR_GRAY_LIGHT      := 0x0388;
const COLOR_BLACKMETAL      := 0x044e;
const COLOR_GOLDMETAL       := 0x046e;
const COLOR_BSHIMMER        := 0x0480;	// T2A Only : Waterelemental color.
const COLOR_WHITE           := 0x0481;	// T2A Only : True white.
const COLOR_STONE           := 0x0482;	// T2A Only : Rock ( stoneharpy?)
const COLOR_SPECTRAL        := 0x4631;  // Spectral
const COLOR_TRANSLUCENT     := 0x7cf8;  // Translucent

////
// Font Colours.
////
const FONTCOLOR_RED := 38;
const FONTCOLOR_GREEN :=68;
const FONTCOLOR_BLUE := 90;
const FONTCOLOR_MAUVE := 30;
const FONTCOLOR_LAVENDER := 20;
const FONTCOLOR_BLACK := 1;
const FONTCOLOR_BROWN := 46;
const FONTCOLOR_YELLOW := 53;
