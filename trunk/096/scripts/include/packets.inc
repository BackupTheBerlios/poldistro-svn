/* $Id: packets.inc,v 1.1 2004/03/16 14:05:46 folko Exp $
 *
 * Purpose
 * Provide various functions and constants for raw packets.
 *
 */

use polsys;

enum PACKET_ID
    PACKET_FEATURES     := 0xB9,
    PACKET_CLILOC       := 0xC1
endenum

enum FEATURE_BITS
    FEATURE_CHAT        := 0x0001,
    FEATURE_LBR         := 0x0002,
    FEATURE_AOS         := 0x0004
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

enum TEXT_FONTS
    FONT_BOLD           := 0x0000,
    FONT_SHADOW         := 0x0001,
    FONT_BOLDSHADOW     := 0x0002,
    FONT_NORMAL         := 0x0003,
    FONT_GOTHIC         := 0x0004,
    FONT_ITALIC         := 0x0005,
    FONT_SMALLDARK      := 0x0006,
    FONT_RUNE           := 0x0008,
    FONT_SMALLLIGHT     := 0x0009
endenum

/*
 * SendFeatures(who, features)
 *
 * Author: Folko
 *
 * Purpose
 * Enable OSI client features like the chat button or LBR graphics.
 *
 * Parameters
 * who:         The character on which to enable the features
 * features:    The features to enable, see enumeration above for possible features
 *
 * Return value
 * No return value
 * 
 * TODO:
 * Make sure the feature bits are right
 *
 */
function SendFeatures(who, features)
    var packet;
    
    packet := CreatePacket(PACKET_FEATURES, 0x03);
    packet.SetInt16(1, features);
    packet.SendPacket(who);
    return;
endfunction
