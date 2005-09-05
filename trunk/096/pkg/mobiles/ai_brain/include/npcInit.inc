/*===============================================================
* Current Version
* NPC_UTIL.INC - v1.0
* Updated 9/4/2005 3:43PM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/
use uo;
use os;
use util;
use cfgfile;

include ":ai_brain:include/npcUtil";
include ":ai_brain:include/npcError";

/*
 * NPC_GiveBackPack(mobile)
 *
 * Purpose
 * Creates a backpack and places it on an npc. If it can't equip it, it removes it.
 *
 * Parameters
 * mobile:	Mobile to equip the backpack onto.
 *
 * Return value
 * Returns an item reference on success or if there already is one.
 *
 */
function NPC_GiveBackPack(mobile)
	if ( !mobile.backpack )
		var backpack := CreateItemAtLocation(mobile.x, mobile.y, mobile.z, "BackPack", 1);
		var result := EquipItem(mobile, backpack);
		if ( !result )
			DestroyItem(backpack);
			return result;
		else
			return backpack;
		endif
	endif
	
	return mobile.backpack;
endfunction

/*
 * NPC_SetupAmmunition(mobile)
 *
 * Purpose
 * Creates ammunition in the npc's pack based on its 'AmmoType' and 'AmmoAmount' 
 * settings in its npcdesc.cfg template.
 *
 * mobile:	The npc that will be given the ammunition.
 *
 * Return value
 * Returns 1 or error
 *
 */
function NPC_SetupAmmo(mobile)
	var npc_elem := NPC_GetNPCConfig(mobile);
	
	if ( npc_elem.MissileWeapon )
		var weapon := CreateItemAtLocation(mobile.x, mobile.y, mobile.z, npc_elem.MissileWeapon, 1, mobile.realm);
		weapon.newbie := 1;
		if ( !EquipItem(mobile, weapon) )
			DestroyItem(weapon);
		endif
	endif
		
	if ( npc_elem.AmmoType )
		if ( CInt(npc_elem.AmmoAmount) > 0 )
			var ammo := CreateItemInBackpack(mobile, npc_elem.AmmoType, npc_elem.AmmoAmount);
			if ( !ammo )
				return ammo; // Will return an error with .errortext
			endif
			
			ammo.newbie := 1;
			return 1;
		endif
	else
		var temp := error{"errortext":="Error - NPC_SetupAmmo() :: No 'AmmoType' was specified."};
		
		NPC_ErrorSysLog(mobile, temp.errortext);
		PrintTextAbove(mobile, temp.errortext);
		return temp;
	endif
endfunction

/* 
 * NPC_SetupEquipment(mobile, elem_name)
 *
 * Purpose
 * Equips an NPC with EquipFromTemplate() and ::equip.cfg
 *
 * Parameters
 * mobile:	The mobile to place equipment onto
 * elem_name:	Name of the equipment template to use.
 *		If no name is set, it will use the EquipTemplate line in the npc's template.
 *
 * Return value
 * Returns 1 or error
 *
 */
function NPC_SetupEquipment(mobile, elem_name:=0)
	var equip_cfg := ReadConfigFile("::equip");
	
	if ( !elem_name )
		var npc_elem := NPC_GetNPCConfig(mobile);
		elem_name := npc_elem.EquipTemplate;
	endif
	
	if ( !elem_name )
		return NPC_GiveBackPack(mobile);
	elseif ( !equip_cfg[elem_name] )
		var errmsg := error{"errortext":="Error - NPC_SetupEquipment() :: There is no elem ["+elem_name+"] in '::equip.cfg'"};
		PrintTextAbove(mobile, errmsg);
		return errmsg;
	else
		return EquipFromTemplate(mobile, elem_name);
	endif
	
	return 0;
endfunction
	
	
/*
 * NPC_SetupName(mobile, name_elem)
 * 
 * Purpose
 * Replaces every instance of <random> in an npc's name with a valid name using ::names.cfg
 *
 * Parameters
 * mobile:	The mobile to do a name check on.
 * name_elem:	Name elem in names.cfg to use
 *		If no name is set, it will use the NameList line in the npc's template.
 *
 * Return value
 * Returns 1 or error
 *
 */
 
function NPC_SetupName(mobile, name_elem:=0)
	if ( !mobile.name["<random>"] )
		return 1;
	elseif ( !name_elem )
		var npc_elem := NPC_GetNPCConfig(mobile);
		name_elem := npc_elem.NameTemplate;
		if ( name_elem.errortext )
			return name_elem;
		endif
	endif
	
	var npc_names := ReadConfigFile("::names");
	if ( !npc_names[name_elem] )
		var temp := error;
		temp.+errortext := "There is no elem ["+name_elem+"] in NAMES.CFG";
		
		NPC_ErrorSysLog(moble, "Error - NPC_SetupName() :: "+temp.errortext);
		PrintTextAbove(mobile, temp.errortext);
		return temp;
	endif
	
	var name_list := GetConfigStringArray(npc_names[name_elem], "Name");
	if ( name_list.size() < 1 )
		var temp := error{"errortext":="No names were found in the ["+name_elem+"] elem for names.cfg"};
	
		SysLog("Error - NPC_SetupName() :: "+temp.errortext);
		PrintTextAbove(mobile, temp.errortext);
	
		return temp;
	endif
	
	var my_name := mobile.name;
	while ( my_name["<random>"] )
		var replacement := name_list[RandomInt(name_list.size())+1];
		my_name["<random>"] := replacement;
		sleepms(2);
	endwhile
	
	SetName(mobile, my_name);
	
	return 1;
endfunction

