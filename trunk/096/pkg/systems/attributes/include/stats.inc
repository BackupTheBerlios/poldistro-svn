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
 * AF_GetRawStat(mobile, stat_name)
 *
 * Purpose
 * Retrieves the value of the stat as it is stored in the core.
 *
 * Parameters
 * mobile:	Mobile reference to retrieve the points from.
 * stat_name:	Name of the stat to retrieve the points for.
 *
 * Return value
 * Returns an integer.
 *
 */
 function AF_GetRawStat(who, stat_name)
	return GetAttributeBaseValue(who, stat_name);
endfunction

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
	return (GetTrueStat(who, stat_name)+GetStatMod(who, stat_name));
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
	return (CDbl(GetAttributeBaseValue(who, stat_name)) / 10.0);
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
	return (CDbl(GetAttributeTemporaryMod(who, stat_name)) / 10.0);
endfunction