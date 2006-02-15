use uo;
use os;
use math;
use cfgfile;

include ":brainAI:npcUtil";

/*
 * http://uo.stratics.com/content/guides/resistance.shtml
 * These could be attributes, but not every shard will want to
 * follow OSI. This gives more freedom to make custom resistances
 * and remove existing ones more easily.
 */
enum DAMAGE_TYPES
	DMG_FORCED	:= -1, // Ignores resistance
	DMG_PHYSICAL	:= "Physical",
	DMG_FIRE	:= "Fire",
	DMG_COLD	:= "Cold",
	DMG_POISON	:= "Poison",
	DMG_ENERGY	:= "Energy"
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
function ApplyDamageEX(mobile, amount, type:=DMG_FORCED, source:=0)
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
function ApplyRawDamageEX(mobile, amount, type:=DMG_FORCED, source:=0)
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
 * Calculates the amount of damage based on the damage type and resistance.
 *
 * Parameters
 * mobile:	Mobile that is being damaged and to check resistances on.
 * amount:	Amount of base damage to deal.
 * type:	Type of damage that is being dealt.
 *
 * Return value
 * Integer
 *
 *---------------------------
 * Notes:
 * AOS deals with resistances as percentages. To keep POL more flexible, it uses multipliers. 
 * Stratics reports the max for any resistance type is 80% (80/100 = 0.8). 
 * % to Mult	(100-80)*0.010 = 0.2
 * Mult to %	100-(0.2*100) = 80
 *
 * Examples: 
 * NPC resists 25% (1/4) of cold damage.
 * Cold-ResistMult 0.75
 * (10 * 0.75 = 7.5) // Removes 2.5 points of damage. 
 *
 * NPC resists 50% (1/2) of cold damage.
 * Cold-ResistMult 0.5
 * (10 * 0.5 = 5) // Removes 5 points of damage.
 *
 * NPC resists 75% (3/4) of cold damage.
 * Cold-ResistMult 0.25
 * (10 * 0.25 = 2.5) // Removes 7.5 points of damage.
 *
 * NPC resists 80% (4/5 max AOS resitance)
 * Cold-ResistMult 0.80
 * (10 * 0.2 = 2) // Removes 8 points of damae.
 *
 * NPC is immune to fire damage
 * Fire-ResistMult 0.0
 * (10 * 0.0 = 0) Removes all points of damage.
 *
 * Energy damage actually heals
 * Energy-ResistMult -10.0
 * (10 * -10.0 = -10) Heals 10 points of damage.
 *
 * Physical damage is double
 * Physical-ResistMult 2.0
 * (10 * 2.0 = 20) Adds 10 points of damage.
 *
 */
function CalcDamageAmount(mobile, amount, type)
	amount := CInt(amount);
	if ( type == DMG_FORCED )
		return amount;
	endif
	
	var resistance_mult := error;
	var res_prop := GetObjProperty(mobile, "Resistances");
	if ( res_prop.Exists(type) )
		// Resistances CProp overrides the NPCDESC.CFG settings.
		// Can also be used on players for their resistances.
		resistance_mult := CDbl(res_prop[type]);
	elseif ( mobile.npctemplate )
		// Looks for type-ResistMult in the NPCDESC.CFG
		// Example 'Physical-ResistMult 0.0' means the NPC is immune to physical damage.
		// 'Fire-ResistMult 2.0' means fire does double damage to the NPC.
		// 'Energy-ResistMult 0.5' means 50% reduction.
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
