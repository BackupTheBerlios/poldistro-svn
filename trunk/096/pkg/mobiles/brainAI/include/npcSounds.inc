/*===============================================================
* Current Version
* NPCSOUNDS.INC - v1.0
* Updated 11/01/2005 2:26AM
*
* -- Revision v1.0 --
* MuadDib:
*  Created include file
===============================================================*/
use uo;
use os;
use util;
use cfgfile;

include ":brainAI:npcUtil";
include ":brainAI:npcError";


/////////////////////////////////////////////////////////////////
// * Function List *
//
// NPC_GetIdleSound(mobile)
// NPC_GetDamagedSound(mobile)
// NPC_GetDeathSound(mobile)
// NPC_GetMissSound(mobile)
// NPC_GetHitSound(mobile)
//
/////////////////////////////////////////////////////////////////
// * Internal/Private Function List *
//
/////////////////////////////////////////////////////////////////


/*
 * NPC_GetIdleSound(mobile)
 *
 * Purpose
 * Gets the packed array form of IdleSounds Prop from NPC Template.
 *
 * Parameters
 * mobile:	Mobile to find the idle sound for.
 *
 * Return value
 * Returns an integer that is the sound ID to be played.
 *
 */
function NPC_GetIdleSound(mobile)
	var mobile_template := NPC_GetNPCConfig(mobile);
	var idle_sound_list := UnPack(mobile_template.IdleSounds);

	if( TypeOf(idle_sound_list) != "Array" )
		NPC_ErrorSysLog(mobile, "Invalid Idle Sound Setting");
		return 0;
	endif

	return RandomInt(idle_sound_list.size())+1;

endfunction


/*
 * NPC_GetDamagedSound(mobile)
 *
 * Purpose
 * Gets the packed array form of DamagedSounds Prop from NPC Template.
 *
 * Parameters
 * mobile:	Mobile to find the damaged sound for.
 *
 * Return value
 * Returns an integer that is the sound ID to be played.
 *
 */
function NPC_GetDamagedSound(mobile)
	var mobile_template := NPC_GetNPCConfig(mobile);
	var damaged_sound_list := UnPack(mobile_template.DamagedSounds);

	if( TypeOf(damaged_sound_list) != "Array" )
		NPC_ErrorSysLog(mobile, "Invalid Damaged Sound Setting");
		return 0;
	endif

	return RandomInt(damaged_sound_list.size())+1;

endfunction


/*
 * NPC_GetDeathSound(mobile)
 *
 * Purpose
 * Gets the packed array form of DeathSounds Prop from NPC Template.
 *
 * Parameters
 * mobile:	Mobile to find the death sound for.
 *
 * Return value
 * Returns an integer that is the sound ID to be played.
 *
 */
function NPC_GetDeathSound(mobile)
	var mobile_template := NPC_GetNPCConfig(mobile);
	var death_sound_list := UnPack(mobile_template.DeathSounds);

	if( TypeOf(death_sound_list) != "Array" )
		NPC_ErrorSysLog(mobile, "Invalid Death Sound Setting");
		return 0;
	endif

	return RandomInt(death_sound_list.size())+1;

endfunction


/*
 * NPC_GetMissSound(mobile)
 *
 * Purpose
 * Gets the packed array form of AttackMissSounds Prop from NPC Template.
 *
 * Parameters
 * mobile:	Mobile to find the attack and miss sound for.
 *
 * Return value
 * Returns an integer that is the sound ID to be played.
 *
 */
function NPC_GetMissSound(mobile)
	var mobile_template := NPC_GetNPCConfig(mobile);
	var miss_sound_list := UnPack(mobile_template.AttackMissSounds);

	if( TypeOf(miss_sound_list) != "Array" )
		NPC_ErrorSysLog(mobile, "Invalid Miss Sound Setting");
		return 0;
	endif

	return RandomInt(miss_sound_list.size())+1;

endfunction

/*
 * NPC_GetHitSound(mobile)
 *
 * Purpose
 * Gets the packed array form of AttackHitSounds Prop from NPC Template.
 *
 * Parameters
 * mobile:	Mobile to find the attack and hit sound for.
 *
 * Return value
 * Returns an integer that is the sound ID to be played.
 *
 */
function NPC_GetHitSound(mobile)
	var mobile_template := NPC_GetNPCConfig(mobile);
	var hit_sound_list := UnPack(mobile_template.AttackHitSounds);

	if( TypeOf(hit_sound_list) != "Array" )
		NPC_ErrorSysLog(mobile, "Invalid Hit Sound Setting");
		return 0;
	endif

	return RandomInt(hit_sound_list.size())+1;

endfunction