/*
 * $Id$
 *
 */

use uo;
use os;

include ":timedscripts:timedScripts";

/*
 * TS_CurePoisons()
 *
 * Purpose
 * Will take in a cure amount and try to cure / lower the duration 
 * of poisons running on a mobile.
 *
 * Parameters
 * mobile:	Mobile to cure the poisons on.
 * cure_amount:	Number of duration-lowering points.
 * cure_type:	Cures poisons (timers) of that type. (Note: Most are "P" for poison)
 *
 * Return value
 * Returns 1 if any curing took place
 * Returns 0 if no curing took place
 *
 */ 
function TS_CurePoison(mobile, cure_amount, cure_type)
	var poison_names := TS_GetTimerNames(mobile, cure_type);
	var timer_list := TS_GetTimerList(mobile);
	
	var num_cured := 0;
	//Run through all curable poisons, and keep curing until it runs out of curing power.
	foreach timer_name in ( poison_names )
		var timer_info := TS_GetTimerInfo(mobile, timer_name);
		var duration := timer_info.endtime - ReadGameClock(); // Number of seconds left to run.
		var elem_info := TS_GetCfgElem(timer_name);
		
		if ( elem_info.NoCure ) // Incurable
			continue; // Go to the next point in the loop.
		endif
		
		
	endforeach
endfunction

/*
//Run through all curable poisons, and keep curing until it runs out of curing power.

	var cure_type := Lower(event.curetype);
	foreach timer in ( timer_list )
		var elem_info := TS_GetCfgElem(_timer_iter);
		if ( !elem_info.NoCure ) // Its curable
			if ( !cure_type || cure_type == Lower(elem_info.Type) )
				event.name := _timer_iter;
				LowerDuration(mobile, event, timer_list, num_poisons);
			endif

			if( event.amount <= 0 ) // All out of cure power
				break;
			endif
			sleepms(2);
		endif
	endforeach
*/