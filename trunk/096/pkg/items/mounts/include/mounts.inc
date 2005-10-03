// {$Id}

/*===============================================================
* Current Version
* MOUNTS.INC - v1.0
* Updated 10/3/2005 12:22PM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;
use os;
use cfgfile;

//Arbitrary objtype in the core.
const MOUNT_OBJTYPE := 0xF021;

include "include/client";


/*
 * MP_GetMountsCfgFile()
 *
 * Purpose
 * Retrieves the mounts.cfg file
 *
 * Parameters
 *
 * Return value
 * Returns a config file
 *
 */
function MP_GetMountsCfgFile()
	var cfg := ReadConfigFile(":mounts:config/mounts");

	if ( cfg.errortext )
		SysLog("Error::MP_GetMountsCfgFile() - Unable to open [:mounts:config/mounts.cfg] ->"+cfg.errortext);
	endif

	return cfg;
endfunction

/*
 * AP_GetMountsCfgElem(elem_name, cfg_file)
 *
 * Purpose
 * Retrieves an elem from a config file. 
 *
 * Parameters
 * elem_name:	A string matching the elem name to be retrieved.
 * cfg_file:	Optional parameter - reference to a config already read in by AP_GetMountsCfgFile()
 *
 * Return value
 * A config file elem.
 *
 */
function MP_GetMountsCfgElem(elem_name, byref cfg_file:=0)
	if ( !cfg_file )
		cfg_file := MP_GetMountsCfgFile();
	endif
	
	var elem := cfg_file[elem_name];

	if ( elem.errortext )
		SysLog("Error::MP_GetMountsCfgElem() - Unable to find elem ["+elem_name+"] ->"+elem.errortext);
	endif

	return elem;
endfunction

/*
 * MP_GetMountGraphic(mobile)
 *
 * Purpose
 * Finds what graphic a mount piece must be set to in order to match an npc.
 *
 * Parameters
 * mobile:	NPC to get the mount tile graphic for.
 *
 * Return value
 * Returns a graphic number.
 * Returns error if no match can be found.
 */
function MP_GetMountGraphic(mobile)
	var mobile_graphic;
	if ( mobile.IsA(POLCLASS_NPC) )
		mobile_graphic := Hex(mobile.graphic);
	else
		mobile_graphic := Hex(CInt(mobile));
	endif
	
	var elem := MP_GetMountsCfgElem("MobileToMount");
	var tile_graphic := GetConfigInt(elem, mobile_graphic);
	
	if ( tile_graphic )
		return tile_graphic;
	else
		return error{"errortext":="Error::MP_GetMountGraphic() - No mount tile graphic matches mobile graphic '"+mobile_graphic+"'"};
	endif
endfunction

/*
 * MP_GetMountTemplate(mount)
 *
 * Purpose
 * Finds what npc template must be used to match a mount tile's graphic.
 *
 * Parameters
 * mount:	Mount piece to find a matching npc template for.
 *
 * Return value
 * Returns a string.
 * Returns error if no match can be found.
 */
function MP_GetMountTemplate(mount)
	var mount_graphic;
	if ( mount.IsA(POLCLASS_ITEM) )
		mount_graphic := Hex(mount.graphic);
	else
		mount_graphic := Hex(CInt(mount));
	endif
	
	var elem := MP_GetMountsCfgElem("MountToMobile");
	var template := GetConfigString(elem, mount_graphic);
	
	if ( template )
		return template;
	else
		return error{"errortext":="Error::MP_GetMountTemplate() - No NPC template match for mount piece graphic '"+mount_graphic+"'"};
	endif
endfunction

