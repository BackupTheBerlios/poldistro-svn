/*
 * $Id$
 *
 */

use uo;

include ":itemutils:itemdesc";

/*
 * KP_ToggleLock(object)
 *
 * Purpose
 * Toggles the locked member of an object.
 *
 * Parameters
 * object:	Container or door to toggle the locked status on.
 * mobile:	Optional - Mobile to show the locked status to.
 *
 * Return value
 * Returns 1
 *
 */
function KP_ToggleLock(object, mobile:=0)
	if ( object.locked )
		PrintTextAbovePrivate(object, "*unlocked*", mobile);
		object.locked := 0;
	else
		PrintTextAbovePrivate(object, "*locked*", mobile);
		object.locked := 1;
	endif
	
	return 1;
endfunction

/*
 * KP_IsLockable(object)
 * 
 * Purpose
 * Determines if an item is lockable or not.
 *
 * Parameters
 * Object:	Object to check.
 *
 * Return value
 * Returns 1 if the object is lockable
 * Returns 0 if the object is not lockable.
 *
 */
function KP_IsLockable(object)
	if ( object.IsA(POLCLASS_ITEM) )
		object := object.objtype;
	endif
	
	return GetItemDescInfo(object).Lockable;
endfunction