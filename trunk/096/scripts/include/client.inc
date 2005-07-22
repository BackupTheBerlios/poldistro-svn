/* CLIENT.INC - defines client releated constants.
 *
 * This include file is designed to hold all the client lowlevel constants.
 * Not all constants might be usable as of now, but in the future, they
 * might be.
 */


////
// Animations/Actions
///
// * Human animations (all humans have these) (this is not complete, will update later)
const ANIM_WALK_UNARMED         :=  0x0000; // Walk unarmed.
const ANIM_WALK_ARMED           :=  0x0001; // Walk armed.
const ANIM_RUN_UNARMED          :=  0x0002; // Run unarmed.
const ANIM_RUN_ARMED            :=  0x0003; // Run armed.
const ANIM_STAND                :=  0x0004; // Stand.
const ANIM_FIDGET_1             :=  0x0005; // Twist a little (look around?).
const ANIM_FIDGET_2             :=  0x0006; // Look down.
const ANIM_STAND_1HAND          :=  0x0007; // Stand 1 handed attack.
const ANIM_STAND_2HAND          :=  0x0008; // Stand 2 handed attack.
const ANIM_ATTACK_1HAND_WIDE    :=  0x0009; // Attack 1 handed wide (sword/any).
const ANIM_ATTACK_1HAND_JAB     :=  0x000a; // Attack 1 handed jab (fencing).
const ANIM_ATTACK_1HAND_DOWN    :=  0x000b; // Attack 1 handed down (mace).
const ANIM_ATTACK_2HAND_DOWN    :=  0x000c; // Attack 2 handed jab (mace).
const ANIM_ATTACK_2HAND_WIDE    :=  0x000d; // Attack 2 handed wide.
const ANIM_ATTACK_2HAND_JAB     :=  0x000e; // Attack 2 handed jab (spear).
const ANIM_ATTACK_BOW           :=  0x0012; // Attack bow.
const ANIM_ATTACK_XBOW          :=  0x0013; // Attack xbow.
const ANIM_WALK_WARMODE         :=  0x000f; // Walk in warmode.
const ANIM_CAST_DIR             :=  0x0010; // Spellcasting direction.
const ANIM_CAST_AREA            :=  0x0011; // Spellcasting area.
const ANIM_HIT                  :=  0x0014; // Get hit.
const ANIM_DIE_BACK             :=  0x0015; // Die backward.
const ANIM_DIE_FOR              :=  0x0016; // Die forward.
const ANIM_BOW                  :=  0x0020; // Bow.
const ANIM_SALUTE               :=  0x0021; // Salute.
const ANIM_EAT                  :=  0x0022; // Eat.

////
// Graphicaleffects (itemIDs)
///
// * general *
const FX_SPLASH         :=  0x352d; //
const FX_EXPLODE_1      :=  0x36ca; //
const FX_EXPLODE_2      :=  0x36bd; //
const FX_EXPLODE_3      :=  0x36b0; //
const FX_FIREBALL       :=  0x36d4; //
const FX_MAGIC_ARROW    :=  0x36e4; //
const FX_FIRE_BOLT      :=  0x36f4; // Firesnake. (pagan?)
const FX_EXPLODE_BALL   :=  0x36fe; // Not used.

const FX_FLAMESTRIKE    :=  0x3709; //
const FX_SMOKE          :=  0x3728;
const FX_TELE_VANISH    :=  0x372a; // Teleport vanish.
const FX_SPELL_FAIL     :=  0x3735; //
const FX_BLESS_EFFECT   :=  0x373a; //
const FX_CURSE_EFFECT   :=  0x374a; //
const FX_SPARK_EFFECT   :=  0x375a; //
const FX_HEAL_EFFECT    :=  0x376a; //
const FX_MARK_EFFECT    :=  0x3779;
const FX_BLUEMOONSTART  :=  0x3789; // Deathvortex?
const FX_ENERGY_BOLT    :=  0x379f; //
const FX_BLADES_EMERGE  :=  0x37a0; // Not used.
const FX_GLOW           :=  0x37b9; // Not used.
const FX_GLOW_SPIKE     :=  0x37c3; // Not used.
const FX_DEATH_FUNNEL   :=  0x37cc; //
const FX_BLADES         :=  0x37eb; //
const FX_STATIC         :=  0x3818; // Not used. (pink static)
const FX_POISON_F_EW    :=  0x3914; // Poison field.
const FX_POISON_F_NS    :=  0x3920; // Poison field.
const FX_ENERGY_F_EW    :=  0x3947; // Energy field.
const FX_ENERGY_F_NS    :=  0x3956; // Energy field.
const FX_PARA_F_EW      :=  0x3967; // Paralyze field.
const FX_PARA_F_NS      :=  0x3979; // Paralyze field.
const FX_FIRE_F_EW      :=  0x398c; // Fire field.
const FX_FIRE_F_NS      :=  0x3996; // Fire field.

////
// Layers
///
const LAYER_NONE        :=  0x00;   // Not used?
const LAYER_HAND1       :=  0x01;   // One handed weapon.
const LAYER_HAND2       :=  0x02;   // Two handed weapon, shield or misc.
const LAYER_SHOES       :=  0x03;   // Shoes.
const LAYER_PANTS       :=  0x04;   // Pants.
const LAYER_SHIRT       :=  0x05;   // Shirt.
const LAYER_HELM        :=  0x06;   // Helm or Hat.
const LAYER_GLOVES      :=  0x07;   // Gloves.
const LAYER_RING        :=  0x08;   // Ring.
const LAYER_UNUSED9     :=  0x09;   // Unused.
const LAYER_NECK        :=  0x0a;   // Neck.
const LAYER_HAIR        :=  0x0b;   // Hair
const LAYER_WAIST       :=  0x0c;   // Waist (half apron).
const LAYER_CHEST       :=  0x0d;   // Torso (inner) (chest armor).
const LAYER_WRIST       :=  0x0e;   // Bracelet.
const LAYER_PACK2       :=  0x0f;   // Unused (backpack, but ord. bp is 0x15).
const LAYER_BEARD       :=  0x10;   // Facial hair.
const LAYER_TUNIC       :=  0x11;   // Torso (middle) (tunic, sash etc.).
const LAYER_EARS        :=  0x12;   // Earrings.
const LAYER_ARMS        :=  0x13;   // Arms.
const LAYER_CAPE        :=  0x14;   // Back (cloak).
const LAYER_PACK        :=  0x15;   // Backpack
const LAYER_ROBE        :=  0x16;   // Torso (outer) (robe)
const LAYER_SKIRT       :=  0x17;   // Legs (outer) (skirt/robe).
const LAYER_LEGS        :=  0x18;   // Legs (inner) (leg armor).
const LAYER_MOUNT       :=  0x19;   // Mount (horse, ostard etc.).
const LAYER_VENDORSTOCK :=  0x1a;   // This vendor will sell and restock.
const LAYER_VENDOREXTRA :=  0x1b;   // This vendor will resell to players but not restock.
const LAYER_VENDORBUY   :=  0x1c;   // This vendor can buy from players but does not stock.
const LAYER_BANKBOX     :=  0x1d;   // Contents of bankbox
const LAYER_TRADE       :=  0x1e;   // Can be multiple of these, do not use directly.

////
// Fonts
///
const FONT_MAX          :=  0x09;   // Highest font.
const FONT_MIN          :=  0x00;   // Lowest font.

const FONT_BOLD         :=  0x00;   // Bold text.
const FONT_SHADOW       :=  0x01;   // Text with shadow.
const FONT_BOLD_SHAD    :=  0x02;   // Bold text with shadow.
const FONT_NORMAL       :=  0x03;   // Normal (default).
const FONT_GOTHIC       :=  0x04;   // Gothic.
const FONT_ITALIC       :=  0x05;   // Italic
const FONT_SMALL_DARK   :=  0x06;   // Small dark letters.
const FONT_COLOR        :=  0x07;   // Colorful font.
const FONT_RUNE         :=  0x08;   // Rune font (only capitals).
const FONT_SMALL_LIGHT  :=  0x09;   // Small light letters.

////
// Creature IDs ( hardcoded graphic IDs )
///
const CID_ZERO              :=  0x000;  // Not used.
const CID_OGRE              :=  0x001;  // Ogre.
const CID_ETTIN             :=  0x002;  // Ettin.
const CID_ZOMBIE            :=  0x003;  // Zombie.
const CID_GARGOYLE          :=  0x004;  // Gargoyle.
const CID_EAGLE             :=  0x005;  // Eagle.
const CID_BIRD              :=  0x006;  // Bird.
const CID_ORC_LORD          :=  0x007;  // Orc Lord.
const CID_CORPSER           :=  0x008;  // Corpser.
const CID_DAEMON            :=  0x009;  // Daemon.
const CID_DAEMON_SWORD      :=  0x00a;  // Daemon with sword.
const CID_DRAGON_GREY       :=  0x00c;  // Dragon grey.
const CID_AIR_ELEMENTAL     :=  0x00d;  // Air Elemental.
const CID_EARTH_ELEMENTAL   :=  0x00e;  // Earth Elemental.
const CID_FIRE_ELEMENTAL    :=  0x00f;  // Fire Elemental.
const CID_WATER_ELEMENTAL   :=  0x010;  // Water elemental.
const CID_ORC               :=  0x011;  // Orc.
const CID_ETTIN_AXE         :=  0x012;  // Ettin with axe.
const CID_GIANT_SNAKE       :=  0x015;  // Giant

const CID_HUMAN_MALE        :=  0x190;
const CID_HUMAN_FEMALE      :=  0x191;
const CID_GM		    :=  0x03db;

////
// Directions
///
const DIR_N             :=  0x00;   // North.
const DIR_NE            :=  0x01;   // Northeast.
const DIR_E             :=  0x02;   // East.
const DIR_SE            :=  0x03;   // Southeast.
const DIR_S             :=  0x04;   // South.
const DIR_SW            :=  0x05;   // Southwest.
const DIR_W             :=  0x06;   // West.
const DIR_NW            :=  0x07;   // Northwest.

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

////
// SkillIDs
///
const SKILLID_ALCHEMY           := 0;
const SKILLID_ANATOMY           := 1;
const SKILLID_ANIMALLORE        := 2;
const SKILLID_ITEMID            := 3;
const SKILLID_ARMSLORE          := 4;
const SKILLID_PARRY		:= 5;
const SKILLID_BEGGING           := 6;
const SKILLID_BLACKSMITHY       := 7;
const SKILLID_BOWCRAFT          := 8;
const SKILLID_PEACEMAKING       := 9;
const SKILLID_CAMPING           := 10;
const SKILLID_CARPENTRY         := 11;
const SKILLID_CARTOGRAPHY       := 12;
const SKILLID_COOKING           := 13;
const SKILLID_DETECTINGHIDDEN   := 14;
const SKILLID_ENTICEMENT        := 15;
const SKILLID_EVALINT           := 16;
const SKILLID_HEALING           := 17;
const SKILLID_FISHING           := 18;
const SKILLID_FORENSICS         := 19;
const SKILLID_HERDING           := 20;
const SKILLID_HIDING            := 21;
const SKILLID_PROVOCATION       := 22;
const SKILLID_INSCRIPTION       := 23;
const SKILLID_LOCKPICKING       := 24;
const SKILLID_MAGERY            := 25;
const SKILLID_MAGICRESISTANCE   := 26;
const SKILLID_TACTICS           := 27;
const SKILLID_SNOOPING          := 28;
const SKILLID_MUSICIANSHIP      := 29;
const SKILLID_POISONING         := 30;
const SKILLID_ARCHERY           := 31;
const SKILLID_SPIRITSPEAK       := 32;
const SKILLID_STEALING          := 33;
const SKILLID_TAILORING         := 34;
const SKILLID_TAMING            := 35;
const SKILLID_TASTEID           := 36;
const SKILLID_TINKERING         := 37;
const SKILLID_TRACKING          := 38;
const SKILLID_VETERINARY        := 39;
const SKILLID_SWORDSMANSHIP     := 40;
const SKILLID_MACEFIGHTING      := 41;
const SKILLID_FENCING           := 42;
const SKILLID_WRESTLING         := 43;
const SKILLID_LUMBERJACKING     := 44;
const SKILLID_MINING            := 45;
const SKILLID_MEDITATION        := 46;
const SKILLID_STEALTH           := 47;
const SKILLID_REMOVETRAP        := 48;
const SKILLID_NECROMANCY        := 49;
const SKILLID_FOCUS             := 50;
const SKILLID_CHIVALRY          := 51;
const SKILLID__HIGHEST          := 48;
const SKILLID_AOS_HIGHEST       := 51;
