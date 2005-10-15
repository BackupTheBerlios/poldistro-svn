/*
 * $Id$
 *
 * Purpose
 *
 * Functions for moving an item / mobile 
 * Will decide which function to use -
 * MoveItemToLocation, MoveCharacterToLocation, MoveObjectToRealm
 *
 */

use uo;


function MoveObjectToLocation(object, x, y, z, realm, flags:=MOVEITEM_NORMAL)
	realm := Lower(realm);
	
	if ( realm != object.realm )
		return MoveObjectToRealm(object, realm,.x, y, z, flags);
	else
		if ( object.IsA(POLCLASS_MOBILE) )
			return MoveCharacterToLocation(object, x, y, z, flags);
		else
			return MoveItemToLocation(object, x, y, z, flags);
		endif
	endif
	
	// Shouldn't ever reach this spot.
	return 0;
endfunction

