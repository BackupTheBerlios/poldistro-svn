/*===============================================================
* Current Version
* NPCWATCHLIST.INC - v1.0
* Updated 9/13/2005 3:21AM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;
use os;

/////////////////////////////////////////////////////////////////
// * Function List *
//
//
/////////////////////////////////////////////////////////////////

/*
 * NPC_GetWatchList(npc)
 *
 * Purpose
 * 
 *
 * Parameters
 * npc:	
 *
 * Return value
 * 
 *
 */
function NPC_LoadWatchList(npc)
	var watch_dict := GetObjProperty(npc, "#WatchList");
	if ( Lower(TypeOf(watch_dict)) != "dictionary" )
		watch_dict := dictionary;
	endif
	
	return watch_dict;
endfunction

/*
 * NPC_SaveWatchList(npc)
 *
 * Purpose
 * 
 *
 * Parameters
 * npc:	
 *
 * Return value
 * 
 *
 */
function NPC_SaveWatchList(npc, dict_list)
	SetObjProprty(npc, "#WatchList", dict_list);
endfunction

/*
 * NPC_AddToWatchList(npc, mobile)
 *
 * Purpose
 * 
 *
 * Parameters
 * npc:	
 *
 * Return value
 * 
 *
 */
function NPC_AddToWatchList(npc, mobile)
	var watch_dict := NPC_GetWatchList(npc);
	if ( !watch_dict.Exists(mobile.serial) )
		watch_dict.Insert(mobile.serial, 1);
		NPC_SaveWatchList(npc, watch_dict);
	endif
endfunction

/*
 * NPC_RemoveFromWatchList(npc)
 *
 * Purpose
 * 
 *
 * Parameters
 * npc:	
 *
 * Return value
 * 
 *
 */
function NPC_RemoveFromWatchList(npc, mobile)
	
endfunction

/*
 * NPC_IsInWatchList(npc, mobile)
 *
 * Purpose
 * 
 *
 * Parameters
 * npc:	
 *
 * Return value
 * 
 *
 */
function NPC_IsInWatchList(npc, mobile)

endfunction
