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
		SysLog("Error::GetAttributeCfgElem() - Unable to open attributes.cfg ->"+cfg.errortext);
	endif
	
	var cfg_elem := cfg[attribute];
	if ( cfg_elem.errortext )
		SysLog("Error::GetAttributeCfgElem() - in attributes.cfg ->"+cfg_elem.errortext);
	endif
	
	return cfg_elem;
endfunction
