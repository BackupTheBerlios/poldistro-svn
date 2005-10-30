use uo;
use cfgfile;
use os;

// Event flags
const EVENT_ADD_TIMER			:= 0x1;
const EVENT_CURE_TIMER			:= 0x2;
const EVENT_CURE_SPECIFIC_TIMER		:= 0x4;
const EVENT_DEAD			:= 0x8;
const EVENT_LOGOUT			:= 0x10;



//
// ListPoisonsByType(mobile, type)
// Returns an array of strings listing poisons names
// running on the targetted mobile that are of the type
// passed.
//
function ListTimersByType(mobile, type_name)
	var p_list := array{};
	var temp_list := GetObjProperty(mobile, "#TimerScripts");
	
	type_name := Lower(type_name);
	foreach timer_name in (temp_list.keys())
		if ( Lower(PW_CfgInfo(timer_name).Type) == type_name )
			p_list.Append(timer_name);
		endif
		sleepms(2);
	endforeach

	return p_list;
endfunction


//
// GetAllPoisons(mobile)
// Returns an array of strings listing the poison names
// running on the mobile passed.
//
function GetAllPoisons(mobile)
	var p_list := array;
	var temp_list := GetObjProperty(mobile, "#TimerScripts");
	
	foreach poison_name in (temp_list.keys())
		p_list.append(poison_name);
		sleepms(2);
	endforeach

	return p_list;
endfunction


//
// AddPoison(mobile, poison_name, amount, attacker, level)
// Adds a poison to the mobile for 'amount' seconds.
// Attacker is usually set to be the drinker or eater if the poison is
// from food or a potion.
// Level applies if the poison comes in levels, as the default poison does.
//
function AddPoison(mobile, poison_name, duration, attacker := 0, level := 1)
	var event := struct;
	event.+ type := EVENT_ADD_TIMER;
	event.+ name := poison_name;
	event.+ amount := duration;
	event.+ attacker := attacker;
	event.+ level := CInt(level);

	return PW_GetScript(mobile).SendEvent(event);
endfunction


//
// CurePoison(mobile, amount)
// Cures 'amount' of seconds of poison from
// the mobile. This will only cure poisons that
// are NOT set to 'NoCure 1'.
// Poisontype is for if we group poisons into families that have seperate
// scripts and as such CureSpecific is not appropriate.
// Level is for the level of the cure. A level 2 cure will be twice
// as effective against a level 1 poison and half as effective against
// a level 4 poison.
//
function CurePoison(mobile, amount, poisontype := "", level := 1)
	var event := struct;
	event.+ type;
	event.+ name;
	event.+ amount;
	event.+ poisontype;
	event.+ level;

	event.type := EVENT_CURE_TIMER;
	event.amount := amount;
	event.poisontype := poisontype;
	event.level := level;

	PW_GetScript(mobile).SendEvent(event);

	return;
endfunction


//
// CureSpecific(mobile, poison_name, amount)
// Cures 'amount' seconds of a specific poison.
// Ignores the 'NoCure' setting.
//
function CureSpecific(mobile, poison_name, amount, level := 1)
	var event := struct;
	event.+ type;
	event.+ name;
	event.+ amount;
	event.+ level;

	event.type := EVENT_CURE_SPECIFIC_TIMER;
	event.name := poison_name;
	event.amount := amount;
	event.level := level;

	PW_GetScript(mobile).SendEvent(event);

	return;
endfunction


//
// PW_GetScript(mobile)
// Returns the process of the poison watcher.
// If the poison watcher is not running, it will
// start it up on the mobile unless no_start is set to
// a non-zero value.
//
function PW_GetScript(mobile, no_start := 0)
	var poison_pid := CInt(GetObjProperty(mobile, "#PoisonPID"));
	var poison_watcher := GetProcess(poison_pid);

	if (!poison_watcher && !no_start)
		//How to start it on an npc!
		poison_watcher := start_script(":poisonwatcher:poisonwatcher", {mobile});

		if ( poison_watcher.errortext )
			PrintTextAbove(mobile, "Poison Watcher PW_GetScript() " + poison_watcher.errortext);
		endif
	endif

	return poison_watcher;
endfunction


//
// PW_CfgInfo(poison_name)
// Returns config information about the poison name passed.
//
function TC_CfgInfo(poison_name)
	var cfg_file := ReadConfigFile(":poisonwatcher:config/poisons");
	if ( cfg_file.errortext )
		SysLog("Error::PW_CfgInfo() - Unable to open poisons.cfg -> "+cfg_file.errortext);
		return 0;
	endif

	return cfg_file[poison_name];
endfunction
