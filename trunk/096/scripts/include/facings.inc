/* $Id$
 *
 */
use uo;
use os;
use math;


/*
 * TurnObjectToward(object, x_pos, y_pos)
 *
 * Purpose
 * Sets an objects .facing member to face an x, y coordinate.
 *
 * Purpose
 * object:	Object to set the facing on.
 * x_pos:	X position to check.
 * y_pos:	Y position to check.
 *
 * Return value
 * Object's original facing
 *
 */
function TurnObjectToward(object, x_pos, y_pos)
	var orig := object.facing;

	object.facing := GetFacing(object.x, object.y, x_pos, y_pos);

	return orig;
endfunction


/*
 * IsFacing(mobile, x_pos, y_pos)
 *
 * Purpose
 * Determines if a mobile is facing a set of coordinates.
 *
 * Parameters
 * mobile:	Mobile to check the coordinates with.
 * x_pos:	X position to check.
 * y_pos:	Y position to check.
 *
 * Return value
 * Returns 1 if the mobile is facing the coordinates.
 * Returns 0 if not.
 *
 */
 function IsFacing(mobile, x, y)
	return ( mobile.facing == GetFacing(mobile.x, mobile.y, x, y) );
endfunction


/*
 * IsBehind(mobile, x_pos, y_pos)
 * Determines if a set of coordinates are behind a character.
 * Example ( ^ - character * - behind )
 *         ^
 *        ***
 *       *****
 *      *******
 *
 * Parameters
 * mobile:	Mobile to check the coordinates with.
 * x_pos:	X position to check.
 * y_pos:	Y position to check.
 *
 * Return value
 * Returns 1 if the coordinates are behind the mobile.
 * Returns 0 if not.
 *
 */
function IsBehind(tgt_mob, locx, locy)
	var frot := Abs(((tgt_mob.facing+4)%8)-GetFacing(tgt_mob.x,tgt_mob.y,locx,locy));
	if (frot > 4)
		frot := 8-frot;
	endif

	return (frot < 2);
endfunction
