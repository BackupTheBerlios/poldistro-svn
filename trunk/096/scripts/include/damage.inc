use uo;
use os;
use math;
use cfgfile;

enum DAMAGE_TYPES
	DMG_DEFAULT	:= "Default",
	DMG_COLD	:= "Cold",
	DMG_FIRE	:= "Fire",
	DMG_POISON	:= "Poison",
	DMG_MAGERY	:= "Magery",
endenum

function ApplyDamageEX(mobile, amount, type:=DMG_DEFAULT, source:=0)
	amount := CalcDamageAmount(mobile, amount, type, source);
	
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

function ApplyRawDamageEX(mobile, amount, type:=DMG_DEFAULT, source:=0)
	amount := CalcDamageAmount(mobile, amount, type, source);
	
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

function CalcDamageAmount(mobile, amount, type, source)
	var resistance := error;
	var res_prop := GetObjProperty(mobile, "Resistances");
	if ( res_prop.Exists(type) )
		resistance := CDbl(res_prop[type]);
	elseif ( mobile.npctemplate )
		var npc_cfg := ReadConfigFile("::npcdesc");
		var npc_elem := npc_cfg[mobile.npctemplate];
		if ( GetConfigReal(npc_elem, type+"-ResistMult") != error )
			resistance := GetConfigReal(npc_elem, type+"-ResistMult");
		endif
	endif
			
	if ( resistance == error )
		// Do nothing, there is no resistance.
	elseif ( resistance == 0.0 )
		// mobile is immune.
		amount := 0;
	elseif ( resistance )
		// NPC has a resistance multiplier
		amount := CInt(amount * resistance);
	endif
		
	return CInt(amount);
endfunction

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

function GetLastDamageInfo(mobile)
	return GetObjProperty(mobile, "LastDamage");
endfunction

