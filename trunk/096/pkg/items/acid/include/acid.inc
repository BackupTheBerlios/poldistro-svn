/* $Id$
 *
 */
use uo;
use cfgfile;
use util;

include ":brainAI:npcUtil";
include "include/packets";

/*
 * MakeBleed(object, blood_color)
 *
 * Purpose
 * Creates a blood tile where the object is and sets the blood to the appropriate color.
 *
 * Parameters
 * object:	The object to create the blood for.
 * blood_color:	Optional parameter. Will force the blood to be this color.
 *
 * Return value
 * Returns an item reference to the tile created.
 *
 */
function SpitAcid(spitter, spit_on)
	if( !CheckLineOfSight(spitter, spit_on) )
		return 0;
	endif
	var npc_info := NPC_GetNPCConfig(spitter.npctemplate);
	var acid_damage := 0;
	if( !npc_info.AcidDamage )
		// NPC doesn't Spit Acid
		return 0;
	else
		acid_damage := RandomDiceRoll(npc_info.AcidDamage);
	endif

	PlayMovingEffectXYZHued(spitter, spit_on, 0x36d4, 5, 1, 1, 0x47, 0);
	var acid_pool := CreateItemAtLocation(spit_on.x, spit_on.y, GetMapInfo(spit_on.x, spit_on.y).z, "acid",  1, spit_on.realm);
	ApplyRawDamage(spit_on, acid_damage);
	return acid_pool;
endfunction
