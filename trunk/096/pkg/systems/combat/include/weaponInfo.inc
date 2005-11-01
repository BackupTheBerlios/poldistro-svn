/*
 * $Id$
 *
 */

use cfgfile;

/*
 * CS_GetWeaponInfo(weapon, prop_name)
 *
 * Purpose
 * Retrieves a config property for a weapon.
 *
 * Parameters
 * weapon:	Weapon that is being looked up.
 * prop_name:	Itemdesc.cfg property to retrieve.
 *
 * Return value
 * Returns a string
 *
 */
function CS_GetWeaponInfo(weapon, prop_name)
	var config := ReadConfigFile(":*:itemdesc");
	config := Config[weapon.objtype];
	
	return GetConfigString(config, prop_name);
endfunction

