use uo;
use os;
use math;
use cfgfile;

include ":brainAI:npcUtil";

enum DAMAGE_TYPES
	DMG_DEFAULT	:= "Default",
	DMG_COLD	:= "Cold",
	DMG_FIRE	:= "Fire",
	DMG_POISON	:= "Poison",
	DMG_MAGERY	:= "Magery",
endenum

/* 
 * ApplyDamageEX(mobile, amount, type, source)
 *
 * Purpose
 *
 * Parameters
 * mobile:	
 * amount:	
 * type:	
 * source:	
 *
 * Return value
 *
 */
function ApplyDamageEX(mobile, amount, type:=DMG_DEFAULT, source:=0)
	amount := CInt(amount);
	amount := CalcDamageAmount(mobile, amount, type);
	
	if ( amount == error )
		return 0;
	elseif ( amount < 0 )
		HealDamage(mobile, Abs(amount));
	else
		if ( source )
			SetLastDamageInfo(mobile, amount, type, source);
			SetScriptController(source);
		endif
		ApplyDamage(mobile, amount);
	endif
	
	return amount;
endfunction

/* 
 * ApplyRawDamageEX(mobile, amount, type, source)
 *
 * Purpose
 *
 * Parameters
 * mobile:	
 * amount:	
 * type:	
 * source:	
 *
 * Return value
 *
 */
function ApplyRawDamageEX(mobile, amount, type:=DMG_DEFAULT, source:=0)
	amount := CInt(amount);
	amount := CalcDamageAmount(mobile, amount, type);
	
	if ( amount == error )
		return 0;	
	elseif ( amount < 0 )
		HealDamage(mobile, Abs(amount));
	else
		if ( source )
			SetLastDamageInfo(mobile, amount, type, source);
			SetScriptController(source);
		endif
		ApplyRawDamage(mobile, amount);
	endif
	
	return amount;
endfunction

/* 
 * CalcDamageAmount(mobile, amount, type)
 *
 * Purpose
 *
 * Parameters
 * mobile:	
 * amount:	
 * type:		
 *
 * Return value
 *
 */
function CalcDamageAmount(mobile, amount, type)
	amount := CInt(amount);
	
	var resistance_mult := error;
	var res_prop := GetObjProperty(mobile, "Resistances");
	if ( res_prop.Exists(type) )
		// Resistances CProp overrides the NPCDESC.CFG settings.
		// Can also be used on players for their resistances.
		resistance_mult := CDbl(res_prop[type]);
	elseif ( mobile.npctemplate )
		// Looks for type-ResistMult in the NPCDESC.CFG
		// Example 'Default-ResistMult 0.0' means the NPC is immune to normal damage.
		// 'Fire-ResistMult 2.0' means fire does double damage to the NPC.
		var npc_elem := NPC_GetNPCConfig(mobile);
		var temp := GetConfigReal(npc_elem, type+"-ResistMult");
		if (  temp != error )
			resistance_mult := temp;
		endif
	endif
			
	if ( resistance_mult == error )
		// Do nothing, there is no resistance.
	elseif ( resistance_mult == 0.0 )
		// Mobile is immune.
		amount := 0;
	elseif ( resistance_mult )
		// Mobile has a resistance multiplier
		amount := CInt(amount * resistance_mult);
	endif
		
	return CInt(amount);
endfunction

/* 
 * SetLastDamageInfo(mobile, amount, type, source)
 *
 * Purpose
 *
 * Parameters
 * mobile:	
 * amount:	
 * type:	
 * source:	
 *
 * Return value
 *
 */
function SetLastDamageInfo(mobile, amount, type, source)
	var last_damage := struct;
	last_damage.+serial	:= source.serial;
	last_damage.+time	:= polcore().systime;
	last_damage.+amount	:= amount;
	last_damage.+type	:= type;
	
	if ( last_damage.acctname )
		last_damage.+acctname := source.acctname;
	endif
	if ( source.name )
		last_damage.+name := source.name;
	else
		last_damage.+name := source.desc;
	endif
	
	SetObjProperty(mobile, "LastDamage", last_damage);
	
	return last_damage;
endfunction

/* 
 * GetLastDamageInfo(mobile)
 *
 * Purpose
 *
 * Parameters
 * mobile:	
 *
 * Return value
 *
 */
function GetLastDamageInfo(mobile)
	return GetObjProperty(mobile, "LastDamage");
endfunction

