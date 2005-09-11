/*===============================================================
* Current Version
* SLEEP.INC - v1.0
* Updated 9/11/2005 2:06AM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

/*
 * EnterSleepMode()
 *
 * Purpose
 * Starts the sleep script if the npc has one.
 *
 * Parameters
 *
 * Return value
 * Always returns 1
 *
 */
function EnterSleepMode()
	if ( !sleep_mode )
		if ( g_scripts["Sleep"] )
			var process := GetNerveProcess(npc, "Sleep");
			if ( !process )
				StartNerve(npc, "Sleep", g_scripts["Sleep"].script, array{g_settings, g_scripts}, g_scripts["Sleep"].flags);
			endif
		endif
					
		//The brain is now in sleep mode, isn't it cute?
		sleep_mode := 1;
	endif
	
	return 1;
endfunction

/*
 * LeaveSleepMode()
 *
 * Purpose
 * Brings the npc out of sleep mode.
 *
 * Parameters
 *
 * Return value
 * Always returns 1
 *
 */
function LeaveSleepMode()
	StopNerve(npc, "Sleep");
	idle_ticks := 0;
	sleep_mode := 0;
endfunction

/*
 * ShouldSleep()
 *
 * Purpose
 * Determines if it is time to sleep
 *
 * Parameters
 *
 * Return Value
 * Returns 0 or 1
 *
 */
function ShouldSleep()
	if ( sleep_mode )
		//Already asleep
		return 0;
	elseif ( Events_Waiting() )
		//Events are waiting to process.
		return 0;
	elseif ( idle_ticks < g_settings["idle_ticks"] )
		//Not enough idle ticks have gone by yet.
		return 0;
	endif
	
	return 1;
endfunction
