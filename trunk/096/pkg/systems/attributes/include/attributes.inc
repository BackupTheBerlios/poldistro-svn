/*===============================================================
* Current Version
* ATTRIBUTES.INC - v1.0
* Updated 9/20/2005 10:30AM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;
use os;
use cfgfile;

include ":attributes:include/regen";
include ":attributes:include/skills";
include ":attributes:include/stats";
include ":attributes:include/vitals";

/*
 * AF_GetAttributeCfgElem(attribute)
 *
 * Purpose
 * Retrieves a config elem for an attribute in attributes.cfg
 *
 * Parameters
 * attribute:	Name of the attribute to get the elem of.
 *
 * Return value
 * Returns a config file elem.
 *
 */
function AF_GetAttributeCfgElem(attribute)
	var cfg := ReadConfigFile(":attributes:attributes");
	if ( cfg.errortext )
		SysLog("Error::AF_GetAttributeCfgElem() - Unable to open attributes.cfg ->"+cfg.errortext);
	endif
	
	var cfg_elem := cfg[attribute];
	if ( cfg_elem.errortext )
		SysLog("Error::AF_GetAttributeCfgElem() - unable to find cfg elem ["+attribute+"] ->"+cfg_elem.errortext);
	endif
	
	return cfg_elem;
endfunction

/*
 * AF_ListAttributesByType(type)
 *
 * Purpose
 * Gets the name of all attributes of a certain type.
 *
 * Parameters
 * Type:	String containing the type of attributes to list.
 *
 * Return value
 * Returns an array
 *
 */
function AF_ListAttributesByType(type)
	type := Lower(type);
	
	var list := array;
	var cfg := ReadConfigFile(":attributes:attributes");
	foreach elem_name in ( GetConfigStringKeys(cfg) )
		var elem_info := cfg[elem_name];
		if ( Lower(elem_info.AttributeType) == type )
			list.append(array);
		endif
		sleepms(2);
	endforeach
	
	return list;
endfunction
