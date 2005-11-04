/* $Id$
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

	return 1;
endfunction
