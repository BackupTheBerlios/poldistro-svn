/*
 * $Id$
 *
 */

use uo;

include ":gumps:gumps";
include "include/client";

function ResurrectionGump(mobile)
	var gump := GFCreateGump();
	
	return gump;
endfunction

function Resurrection(mobile)
	if ( !mobile.IsA(POLCLASS_MOBILE) )
		return error{"errortext":="object is not a mobile."};
	elseif ( !mobile.dead )
		return error{"errortext":="mobile is not dead."};
	endif
	
	return Resurrect(mobile);
endfunction

	