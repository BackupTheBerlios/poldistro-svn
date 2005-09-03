/*===============================================================
* Current Version
* CFGFILE_EX.INC - v1.0
* Updated 8/30/2005 7:28AM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;
use os;
use cfgfile;


/////////////////////////////////////////////////////////////////
// * Function List *
// 
// GetConfigStringDict(cfg_elem, property_name)
//
/////////////////////////////////////////////////////////////////

/*
 * GetConfigStringDictionary(cfg_elem, property_name)
 *
 * Purpose
 * Works similarly as GetConfigStringArray() but sets up the data in a dictionary.
 *
 * Parameters
 * cfg_elem:		Config file element to pull the data from.
 * property_name:	Property name to use with GetConfigStringArray()
 *
 * Return value
 * Returns a dictionary
 *
 */
function GetConfigStringDictionary(cfg_elem, property_name)
	var array_data := GetConfigStringArray(cfg_elem, property_name);
	var dict := dictionary;
	
	foreach line in (array_data)
		var temp := SplitWords(line);
		var key := temp[1];
		var data := line[Len(temp)+1, Len(line)];
		
		dict[key] := data;
		sleepms(2);
	endforeach
	
	return dict;
endfunction
