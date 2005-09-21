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
 * AF_SetVitalRegenRate(mobile, vital_name, number)
 *
 * Purpose
 * Sets the regeneration rate modifier for an attribute.
 * Base value is 1200 (unless you changed it)
 *
 * Parameters
 * mobile:	Mobile reference to set the modifier on.
 * skill_name:	Name of the vital to set the regen modifier for.
 * number:	Modifier (+/-) points to set for the regen rate.
 *
 * Return value
 * Returns 1
 *
 */
function AF_SetVitalRegenRateMod(mobile, vital_name, number)
	vital_name := Lower(vital_name);
	number := CInt(number);
	
	var regen_prop := AF_LoadVitalRegenRateProp(mobile);
		
	if ( number == 0 )
		// Remove keys with no modifier
		regen_prop.Erase(vital_name);
	else
		regen_prop[vital_name] := CInt(number);
	endif
	
	AF_SaveVitalRegenRateProp(mobile, regen_prop);
	return 1;
endfunction

/*
 * AF_GetVitalRegenRateMod(mobile, vital_name)
 *
 * Purpose
 * Gets the regeneration rate modifier for a vital.
 *
 * Parameters
 * mobile:	Mobile reference to get the regen information from.
 * vital_name:	Name of the vital to get the regeneration rate for.
 *
 * Return value
 * Returns an integer.
 *
 */
function AF_GetVitalRegenRateMod(mobile, vital_name)
	vital_name := Lower(vital_name);
	
	var regen_prop := AF_LoadVitalRegenRateProp(mobile);
	return CInt(regen_prop[vital_name]);
endfunction

/*
 * AF_LoadVitalRegenRateProp(mobile)
 *
 * Purpose
 * Loads the dictionary of regeneration settings from a mobile.
 *
 * Parameters
 * mobile:	Mobile reference to get the regen information from.
 *
 * Return value
 * Returns a dictionary
 *
 */
function AF_LoadVitalRegenRateProp(mobile)
	var regen_prop := GetObjProperty(mobile, "%RegenRates%");
	if ( Lower(TypeOf(regen_prop)) != "dictionary" )
		regen_prop := dictionary;
	endif
	
	return regen_prop;
endfunction

/*
 * AF_SaveVitalRegenRateProp(mobile, regen_prop)
 *
 * Purpose
 * Saves the dictionary of regeneration settings on a mobile.
 *
 * Parameters
 * mobile:	Mobile reference to save the regen information on.
 * regen_prop:	Dictionary containing regeneration modifier values.
 *
 * Return value
 * Returns the result of saving the property.
 *
 */
function AF_SaveVitalRegenRateProp(mobile, byref regen_prop)
	if ( Lower(TypeOf(regen_prop)) != "dictionary" )
		return error{"errortext":="Regen prop must be a dictionary."};
	endif
	
	RecalcVitals(mobile);
	
	return SetObjProperty(mobile, "%RegenRates%", regen_prop);
endfunction