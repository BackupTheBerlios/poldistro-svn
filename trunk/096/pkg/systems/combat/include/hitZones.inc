/* $Id$
 *
 */

use uo;
use os;
use util;
use cfgfile;

/*
 * CS_GetHitZone(defender)
 *
 * Purpose
 * Reads in pol/config/armrzone.cfg and based on the 'chance' settings,
 * selects a zone that was hit.
 *
 * Parameters
 * None
 *
 * Return Value
 * String
 *
 */
function CS_GetHitZone()
	//This function assumes that the 'Chance' totals in
	//armrzone.cfg all add up to 100.

	var armrzones := ReadConfigFile("::armrzone");

	//last_num stores the max roll for that zone
	var last_num := 0;
	var max_num := 0;

	//Roll determines the layer we hit.
	//In the future, we may want to have anatomy affect this?
	var roll := RandomInt(100)+1;
	foreach zone_name in ( GetConfigStringKeys(armrzones) )
		var zone := armrzones[zone_name];
		last_num := max_num;
		max_num := last_num + CInt(zone.Chance);
		
		if ( roll > last_num && roll <= max_num  )
			return zone_name;
		endif
		sleepms(2);
	endforeach
	
	return error{"errortext":="Could not select a hit zone!"};
endfunction

/*
 * CS_GetEquipmentInArmorZone(defender)
 *
 * Purpose
 * Returns a list of all equipment that a mobile is wearing
 * that covers an armor zone.
 *
 * Parameters
 * mobile:	Mobile to evaluate the equipment on.
 * zone_name:	Armor zone to find equipment for.
 *
 * Return Value
 * String
 *
 */
function CS_GetEquipmentInArmorZone(mobile, zone_name)
	var itemdesc_cfg := ReadConfigFile(":*:itemdesc");
	var equip_list := array{};
	
	zone_name := Lower(zone_name);
	
	foreach item in ( ListEquippedItems(mobile) )
		var item_info := itemdesc_cfg[item.objtype];
		
		foreach zone in ( GetConfigStringArray(item_info, "Coverage") )
			if ( Lower(zone) == zone_name )
				equip_list.Append(item);
				break;
			endif
		endforeach
		
		sleepms(2);
	endforeach
	
	return equip_list;
endfunction
