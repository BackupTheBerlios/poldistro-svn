/*
 * $Id$
 *
 */

use os;
use util;
use cfgfile;

/*
 * RandomFoodObjType(category:="All")
 *
 * Purpose
 * Selects an objtype from food.cfg
 *
 * Parameters
 * category:	Elem to use in food.cfg
 *
 * Return value
 * Returns a number.
 *
 */
function RandomFoodObjType(category:=0)
	var cfg_file := ReadConfigFile(":food:config/food");
	
	var food_list := array{};
	if ( category )
		var cfg_elem := cfg_file[category];
		food_list := GetConfigStringArray(cfg_elem, "Food");
	else
		food_list := array{};
		foreach elem_name in ( GetConfigStringKeys(cfg_file) )
			var cfg_elem := cfg_file[elem_name];
			food_list := food_list + GetConfigStringArray(cfg_elem, "Food");
			sleepms(2);
		endforeach
	endif
	
	return food_list[RandomInt(food_list.size())+1];
endfunction