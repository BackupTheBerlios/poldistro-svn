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
 * AF_GetStat(mobile, stat_name)
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
function AF_GetStat(who, stat_name)
	return AF_GetTrueStat(who, stat_name)+AF_GetStatMod(who, stat_name);
endfunction

/*
 * AF_GetTrueStat(mobile, stat_name)
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
function AF_GetTrueStat(who, stat_name)
	return CDbl(GetAttributeBaseValue(who, stat_name)) / 10.0;
endfunction

/*
 * AF_GetStatMod(mobile, stat_name)
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
function AF_GetStatMod(who, stat_name)
	return CDbl(GetAttributeTemporaryMod(who, stat_name)) / 10.0;
endfunction

/*
 * AF_SetTrueStat(mobile, stat_name, points)
 *
 * Purpose
 * Sets the value of the stat.
 * Example: AF_SetTrueStat(mobile, "strength", 44.5)
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
function AF_SetTrueStat(mobile, stat_name, points)
	SetAttributeBaseValue(mobile, stat_name, CInt(CDbl(points) * 10.0));
endfunction

/*
 * AF_SetStatMod(mobile, stat_name, points)
 *
 * Purpose
 * Sets the modifier value for the stat.
 * Example: AF_SetStatMod(mobile, "strength", -15.3)
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
function AF_SetStatMod(mobile, stat_name, points)
	SetAttributeTemporaryMod(mobile, stat_name, CInt(CDbl(points) * 10.0));
endfunction
