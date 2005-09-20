/*===============================================================
* Current Version
* REGEN.INC - v1.0
* Updated 9/20/2005 4:09PM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;

/*
 * AF_SetVitalRegenRate(mobile, skill_name, points)
 *
 * Purpose
 * Sets the regeneration rate modifier for an attribute.
 * Base value is 1200.
 *
 * Parameters
 * mobile:	Mobile reference to set the modifier on.
 * skill_name:	Name of the vital to set the regen modifier for.
 * points:	Modifier (+/-) points to set for the regen rate.
 *
 * Return value
 * Returns 1
 *
 */
function AF_SetVitalRegenRate(mobile, vital_name, rate)
	if ( !Lower(vital_name["regeneration"]) )
		vital_name := vital_name+"Regeneration";
	endif
	
	SetAttributeBaseValue(mobile, vital_name, rate);
	RecalcVitals(mobile);
	
	return 1;
endfunction
