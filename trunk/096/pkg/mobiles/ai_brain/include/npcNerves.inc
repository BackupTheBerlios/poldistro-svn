/*===============================================================
* Current Version
* NERVES.INC - v1.0
* Updated 9/1/2005 6:15PM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;
use os;

include ":ai_brain:include/npc_error";

/////////////////////////////////////////////////////////////////
// * Function List *
//
// GetNerveFlags(mobile, nerve_name, byref nerve_dict:=0)
// GetNerveProcess(mobile, nerve_name, byref nerve_dict:=0)
// LoadNerves(mobile)
// SaveNerves(mobile, nerve_dict)
// StartNerve(mobile, nerve_name, nerve_script, data:=array, flags:=NF_NO_FLAGS, byref nerve_dict:=0)
// StopNerve(mobile, nerve_name, byref nerve_dict:=0)
//
/////////////////////////////////////////////////////////////////
// * Global Varibles *
//
// Nerve flags
const NF_NO_FLAGS		:= 0x0;
const NF_CONTINUE_ON_SLEEP	:= 0x1;
//
/////////////////////////////////////////////////////////////////

/*
 * LoadNerves()
 *
 * Purpose
 * Loads nerve information for an npc.
 *
 * Parameters
 * mobile:	NPC to get the nerve settings from.
 *
 * Return value
 * Returns a dictionary
 *
 */
function LoadNerves(mobile)
	var nerve_dict := GetObjProperty(mobile, "#NerveInfo");
	if ( Lower(TypeOf(nerve_dict)) != "dictionary" )
		nerve_dict := dictionary;
	endif

	return nerve_dict;
endfunction

/*
 * SaveNerves(mobile, nerve_dict)
 *
 * Purpose
 * Saves nerve information for an npc.
 *
 * Parameters
 * mobile:	NPC to save the nerve settings on.
 * nerve_dict:	Dictionary containing nerve information.
 *
 * Return value
 * Returns 1 on success
 *
 */
function SaveNerves(mobile, byref nerve_dict)
	return SetObjProperty(mobile, "#NerveInfo", nerve_dict);
endfunction

/*
 * GetNerveProcess(mobile, nerve_name, byref nerve_dict)
 *
 * Purpose
 * Retrieves a reference to a running nerve script.
 *
 * Parameters
 * mobile:	NPC to get the nerve information from.
 * nerve_name:	Name of the nerve to get the information for.
 * nerve_dict:	Optional parameter. Use if the settings were already loaded for faster access.
 *
 * Return value
 * Returns a script reference.
 *
 */
function GetNerveProcess(mobile, nerve_name, byref nerve_dict:=0)
	if ( !nerve_dict )
		nerve_dict := LoadNerves(mobile);
	endif

	if ( nerve_dict.exists(nerve_name) )
		return GetProcess(CInt(nerve_dict[nerve_name].pid));
	else
		return error{"errortext" := "GetNerveProcess() - Invalid nerve name  ["+nerve_name+"]"};
	endif
endfunction

/*
 * GetNerveFlags(mobile, nerve_name, byref nerve_dict)
 *
 * Purpose
 * Retrieves the flag setting set on a nerve.
 *
 * Parameters
 * mobile:	NPC to get the nerve information from.
 * nerve_name:	Name of the nerve to get the information for.
 * nerve_dict:	Optional parameter. Use if the settings were already loaded for faster access.
 *
 * Return value
 * Returns a script reference.
 *
 */
function GetNerveFlags(mobile, nerve_name, byref nerve_dict:=0)
	if ( !nerve_dict )
		nerve_dict := LoadNerves(mobile);
	endif

	if ( nerve_dict.exists(nerve_name) )
		return GetProcess(CInt(nerve_dict[nerve_name].flags));
	else
		return error{"errortext" := "GetNerveProcess() - Invalid nerve name  ["+nerve_name+"]"};
	endif
endfunction

/*
 * StartNerve(mobile, nerve_name, nerve_script, data, flags, byref nerve_dict)
 *
 * Purpose
 * Starts up a nerve script.
 *
 * Parameters
 * mobile:	NPC the nerve will be running for.
 * nerve_name:	The name the nerve script will be run under. (Example: "CombatScript" or "EnterReact")
 * data:	Array of data to send to the nerve script when it starts.
 * flags:	Can contain anything - but should use NF_* flags for bitwise checks.
 * nerve_dict:	Optional parameter. Use if the settings were already loaded for faster access.
 *
 * Notes:
 * data[1] - Will contain the mobile argument.
 * data[2] - Will contain the nerve name argument.
 * If data is not an array, it will be placed at index[3].
 * If data is sent as an array, it will begin at the index of [3].
 *
 * Return value
 * Returns a script reference to the nerve script.
 *
 */
function StartNerve(mobile, nerve_name, nerve_script, data:=array, flags:=NF_NO_FLAGS, byref nerve_dict:=0)
	if ( Lower(TypeOf(data)) != "array")
		data := array{data};
	endif
	//Mobile is always the begining of the data array.
	data.Insert(1, mobile);
	//Nerve name is always the second part of the data array.
	data.Insert(2, nerve_name);

	var process := start_script(nerve_script, data);

	if ( process.errortext )
		var errmsg := "StartNerve() ["+nerve_name+"] ["+nerve_script+"] failed to start! ->"+process.errortext;
		NPC_ErrorSysLog(mobile, errmsg);
		return error{"errortext":=errmsg};
	else
		//Before setting the new nerve, check if one is already running.
		if ( nerve_dict.exists(nerve_name) )
			//Stop the old nerve, before storing the new one.
			StopNerve(mobile, nerve_name, nerve_dict);
		endif
		var nerve_info := struct;
		nerve_info.+pid := process.pid;
		nerve_info.+flags := flags;
		nerve_dict[nerve_name] := nerve_info;

		SaveNerves(mobile, nerve_dict);

		return process;
	endif
endfunction

/*
 * StopNerve(mobile, nerve_name, byref nerve_dict)
 *
 * Purpose
 * Starts up a nerve script.
 *
 * Parameters
 * mobile:	NPC the nerve will be stopped on.
 * nerve_name:	The name of the nerve script to stop.
 * nerve_dict:	Optional parameter. Use if the settings were already loaded for faster access.
 *
 * Return value
 * Returns 1 on success.
 *
 */
function StopNerve(mobile, nerve_name, byref nerve_dict:=0)
	if ( !nerve_dict )
		nerve_dict := LoadNerves(mobile);
	endif

	if ( nerve_dict.Exists(nerve_name) )
		GetNerveProcess(mobile, nerve_name, nerve_dict).kill();
		nerve_dict.Erase(nerve_name);

		return SaveNerves(mobile, nerve_dict);
	else
		return error{"errortext" := "StopNerve() - Invalid nerve name  ["+nerve_name+"]"};
	endif
endfunction

