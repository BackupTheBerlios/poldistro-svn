/*===============================================================
* Current Version
* STATS.INC - v1.0
* Updated 9/20/2005 2:20PM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;

/*
 * attributes_GetStat(mobile, stat_name)
 *
 * Purpose
 * Retrieves the base value of the stat plus its mod value.
 *
 * Parameters
 * mobile:	Mobile reference to retrieve the points from.
 * stat_name:	Name of the stat to retrieve the points for.
 *
 * Return value
 * Returns an integer.
 *
 */
function attributes_GetStat(who, stat_name)
	return attributes_GetTrueStat(who, stat_name)+attributes_GetStatMod(who, stat_name);
endfunction

/*
 * attributes_GetTrueStat(mobile, stat_name)
 *
 * Purpose
 * Retrieves the base value of the stat and turns it into a usable number.
 *
 * Parameters
 * mobile:	Mobile reference to retrieve the points from.
 * stat_name:	Name of the stat to retrieve the points for.
 *
 * Return value
 * Returns a double.
 *
 */
function attributes_GetTrueStat(who, stat_name)
	return CDbl(GetAttributeBaseValue(who, stat_name)) / 10.0;
endfunction

/*
 * attributes_GetStatMod(mobile, stat_name)
 *
 * Purpose
 * Retrieves the base value of the stat mod and turns it into a usable number.
 *
 * Parameters
 * mobile:	Mobile reference to retrieve the points from.
 * stat_name:	Name of the stat to retrieve the modifier points for.
 *
 * Return value
 * Returns a double.
 *
 */
function attributes_GetStatMod(who, stat_name)
	return CDbl(GetAttributeTemporaryMod(who, stat_name)) / 10.0;
endfunction

/*
 * attributes_SetTrueStat(mobile, stat_name, points)
 *
 * Purpose
 * Sets the value of the stat.
 * Example: attributes_SetTrueStat(mobile, "strength", 44.5)
 *
 * Parameters
 * mobile:	Mobile reference to set the points on.
 * stat_name:	Name of the stat to set the points on.
 * points:	Number of points to set the stat at.
 *
 * Return value
 * Returns a double.
 *
 */
function attributes_SetTrueStat(mobile, stat_name, points)
	SetAttributeBaseValue(mobile, stat_name, CInt(CDbl(points) * 10.0));
endfunction

/*
 * attributes_SetStatMod(mobile, stat_name, points)
 *
 * Purpose
 * Sets the modifier value for the stat.
 * Example: attributes_SetStatMod(mobile, "strength", -15.3)
 *
 * Parameters
 * mobile:	Mobile reference to set the modifier points on.
 * stat_name:	Name of the stat to set the modifier points on.
 * points:	Number of points to set the modifier stat at.
 *
 * Return value
 * Returns a double.
 *
 */
function attributes_SetStatMod(mobile, stat_name, points)
	SetAttributeTemporaryMod(mobile, stat_name, CInt(CDbl(points) * 10.0));
endfunction
