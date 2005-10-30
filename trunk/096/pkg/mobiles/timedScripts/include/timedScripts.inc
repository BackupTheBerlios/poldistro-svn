use uo;
use cfgfile;
use os;

// Event flags
const EVENT_ADD_TIMER			:= 0x1;
const EVENT_CURE_TIMER			:= 0x2;
const EVENT_CURE_SPECIFIC_TIMER		:= 0x4;
const EVENT_DEAD			:= 0x8;
const EVENT_LOGOUT			:= 0x10;

/*
 * TS_GetCfgFile()
 *
 * Purpose
 * Retrieves timedScripts.cfg
 *
 * Parameters
 * None
 *
 * Return Value
 * Config file
 *
 */
function TS_GetCfgFile()
	var cfg := ReadConfigFile(":timedscripts:config/timedScripts");

	if ( cfg.errortext )
		SysLog("Error::TS_GetSettingsCfgFile() - Unable to open [:timedscripts:config/timedScripts] ->"+cfg.errortext);
	endif

	return cfg;
endfunction

/*
 * TS_GetCfgElem(elem_name, cfg_file)
 *
 * Purpose
 * Retrieves an elem from a config file. 
 *
 * Parameters
 * elem_name:	A string matching the elem name to be retrieved.
 * cfg_file:	Optional parameter - reference to a config already read in by TS_GetCfgFile()
 *
 * Return value
 * A config file elem.
 *
 */
function TS_GetCfgElem(elem_name, byref cfg_file:=0)
	if ( !cfg_file )
		cfg_file := TS_GetCfgFile();
	endif
	
	var elem := cfg_file[elem_name];

	if ( elem.errortext )
		SysLog("Error::TS_GetCfgElem - Unable to find elem ["+elem_name+"] ->"+elem.errortext);
	endif

	return elem;
endfunction

/* 
 * TS_GetControllerProcess(mobile)
 *
 * Purpose
 * Retrieves a script reference to the timer controller for a mobile.
 *
 * Parameters
 * mobile:	Mobile to get the timer controll process for.
 *
 * Return value
 * Returns a script reference.
 * Returns an error the controller is not running.
 *
 */
function TS_GetControllerProcess(mobile)
	var pid := CInt(GetObjProperty(mobile, "#TimerControlPid"));
	return GetProcess(pid);
endfunction

/* 
 * TS_GetTimerList(mobile)
 *
 * Purpose
 * Retrieves the timer_list dictionary on the mobile.
 *
 * Parameters
 * mobile:	Mobile to retrieve the timer list from.
 *
 * Return value
 * Returns a dictionary
 *
 */
function TS_GetTimerList(mobile)
	var timer_list := GetObjProperty(mobile, "%TimerList%");
	if ( Lower(TypeOf(timer_list)) != "dictionary" )
		timer_list := dictionary;
	endif
	
	return timer_list;
endfunction
	
/*
 * TS_SaveTimerList(mobile, timer_list)
 *
 * Purpose
 * Saves the timer_list dictionary on the mobile.
 *
 * Parameters
 * mobile:	Mobile to save the list on.
 * timer_list:	Dictionary timer_list to save.
 *
 */
function TS_SaveTimerList(mobile, byref timer_list)
	return SetObjProperty(mobile, "%TimerList%", timer_list);
endfunction

