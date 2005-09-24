/*===============================================================
* Current Version
* VITALS.INC - v1.0
* Updated 9/20/2005 2:04PM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;
use os;
use cfgfile;

/*
 * attributes_GetVitalCfgElem(vital)
 *
 * Purpose
 * Retrieves a config elem for an vital in vitals.cfg
 *
 * Parameters
 * attribute:	Name of the vital to get the elem of.
 *
 * Return value
 * Returns a config file elem.
 *
 */
function attributes_GetVitalCfgElem(vital)
	var cfg := ReadConfigFile(":attributes:vitals");
	if ( cfg.errortext )
		SysLog("Error::attributes_GetVitalCfgElem() - Unable to open vitals.cfg ->"+cfg.errortext);
	endif
	
	var cfg_elem := cfg[vital];
	if ( cfg_elem.errortext )
		SysLog("Error::attributes_GetVitalsCfgElem() - unable to find cfg elem ["+vital+"] ->"+cfg_elem.errortext);
	endif
	
	return cfg_elem;
endfunction

/*
 * attributes_GetVital(mobile, vital_name)
 *
 * Purpose
 * Retrieves the number of vital points a mobile has.
 *
 * Parameters
 * mobile:	Mobile reference to retrieve the points from.
 * vital_name:	Name of the vital to retrieve the points for.
 *
 * Return value
 * Returns a double.
 *
 */
function attributes_GetVital(mobile, vital_name)
	return (GetVital(mobile, vital_name) / 100);
endfunction

/*
 * attributes_GetVital(mobile, vital_name)
 *
 * Purpose
 * Retrieves the maximum number of vital points a mobile can have.
 *
 * Parameters
 * mobile:	Mobile reference to check.
 * vital_name:	Name of the vital to retrieve the max. points for.
 *
 * Return value
 * Returns an integer.
 *
 */
function attributes_GetVitalMaximumValue(mobile, vital_name)
	return GetVitalMaximumValue(mobile, vital_name);
endfunction

/*
 * attributes_GetVitalRegenRate(mobile, vital_name)
 *
 * Purpose
 * Retrieves the regen rate of a vital on a mobile.
 *
 * Parameters
 * mobile:	Mobile reference to check.
 * vital_name:	Name of the vital to retrieve the regen rate of.
 *
 * Return value
 * Returns an integer.
 *
 */
function attributes_GetVitalRegenRate(mobile, vital_name)
	return GetVitalRegenRate(mobile, vital_name);
endfunction

/*
 * attributes_SetVital(mobile, vital_name, points)
 *
 * Purpose
 * Sets vital points on a mobile.
 *
 * Parameters
 * mobile:	Mobile reference to set the vital on.
 * vital_name:	Name of the vital to set.
 * points:	Number of points to set the vital to.
 *
 * Return value
 * Returns result of the SetVital() core function.
 *
 */
function attributes_SetVital(mobile, vital_name, amount)
	return SetVital(mobile, vital_name, CInt(CDbl(amount)*100.0));
endfunction

/*
 * attributes_RefreshVitals(mobile)
 *
 * Purpose
 * Sets all vitals on a mobile to their maximum values.
 *
 * Parameters
 * mobile:	Mobile to refresh.
 *
 * Return value
 * Returns 1
 *
 */
function attributes_RefreshVitals(mobile)
	var vital_cfg := ReadConfigFile(":attributes:vitals");
	foreach elem_name in GetConfigStringKeys(vital_cfg)
		attributes_SetVital(mobile, elem_name, attributes_GetVitalMaximumValue(mobile, elem_name));
		sleepms(2);
	endforeach

	return 1;
endfunction
