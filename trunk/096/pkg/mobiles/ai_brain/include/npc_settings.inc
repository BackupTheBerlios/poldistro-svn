/*===============================================================
* Current Version
* NPC_SETTINGS.INC - v1.0
* Updated 8/30/2005 7:28AM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;
use os;
use cfgfile;

include ":ai_brain:include/npc_util";

/*
 * NPC_LoadCfgDefaults(template_name)
 *
 * Purpose
 * Loads settings for a template from npcdesc.cfg
 *
 * Parameters
 * template:	Name of the npc template to load settings for.
 *
 * Return value
 * Returns a dictionary
 *
 */
function NPC_LoadCfgDefaults(template)
	if ( !template.package )
		template := NPC_ParseTemplateName(template);
	endif
	
	var npc_cfg := ReadConfigFile(template.package+"npcdesc");
	var npc_elem := npc_cfg[template];
	
	var settings := dictionary;
	/*
	 * NPC Settings - Step 1 - npcdesc.cfg defaults.
	 * Reads in the AISetting lines from the npcdesc.cfg elem.
	 * Values are stored in packed form.
	 */
	foreach setting in GetConfigStringArray(npc_elem, "AISetting")
		setting := SplitWords(setting);
		var key := setting[1];
		var value := setting[2];

		settings[key] := UnPack(value);

		sleepms(2);
	endforeach

	return settings;
endfunction

/*
 * NPC_LoadCustomSettings(npc_ref, settings:=0)
 * 
 * Purpose
 * Loads custom settings that are set on a specific npc.
 *
 * Parameters
 * npc_ref:		Mobile reference
 * settings:	Optional parameter
 *		Dictionary read in from LoadNPCCfgDefaults()
 *		Existing keys will be overwritten with any custom settings.
 * 
 * Return value
 * Returns a dictionary
 *		
 */
function NPC_LoadCustomSettings(npc_ref, settings:=0)
	if ( Lower(TypeOf(settings)) != "dictionary" )
		settings := dictionary;
	endif
	
	var cstm_settings := GetObjProperty(npc_ref, "AI_Settings");
	foreach key in (cstm_settings.keys())
		var value := cstm_settings[key];
		if ( value == error )
			settings.erase(key);
		else
			settings[key] := value;
		endif
		
		sleepms(2);
	endforeach
	
	return settings;
endfunction

/*
 * NPC_DefaultSettings(settings:=0)
 *
 * Purpose
 * Checks the settings dictionary to make sure required values are set.
 * If a dictionary is passed, it will check it for required parameters.
 * If they are not present, they will be set. 
 * Nothing will be overwritten in this function.
 *
 * Parameters
 * settings:	Optional parameter
 *		Dictionary read in from NPC_GetDefaultSettings()
 *
 * Return value
 * Returns a dictionary 
 *
 */
function NPC_GetDefaultSettings(settings:=0)
	if ( Lower(TypeOf(settings)) != "dictionary" )
		settings := dictionary;
	endif
	
	if ( CInt(settings.exists("cycle_wait")) <= 0 )
		settings["cycle_wait"] := 10;
	endif
	if ( CInt(settings.exists("sleep_time")) <= 0 )
		settings["sleep_time"] := 1024;
	endif
	if ( CInt(settings.exists("idle_ticks")) <= 0 )
		settings["idle_ticks"] := 5;
	endif
		
	return settings;
endfunction
