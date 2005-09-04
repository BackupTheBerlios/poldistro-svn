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

include ":ai_brain:include/npcUtil";

/*
 * NPC_LoadCfgDefaults(template_name)
 *
 * Purpose
 * Loads settings for a template from npcdesc.cfg
 *
 * Parameters
 * source:	Name of the npc template to load settings for.
 *		Can also be an npc reference - if custom settings should be loaded off it.
 *
 * Return value
 * Returns a dictionary
 *
 */
function NPC_LoadTemplateSettings(source)
	var template:=source;
	if ( source.IsA(POLCLASS_NPC) )
		template := NPC_ParseTemplateName(source.npctemplate);
	elseif ( !template.package )
		template := NPC_ParseTemplateName(template);
	endif

	//
	// * Load config defaults first
	//
	var npc_cfg := ReadConfigFile(template.package+"npcdesc");
	var npc_elem := npc_cfg[template];

	var setting_list := GetConfigStringDictionary(npc_elem, "AISetting");
	
	var settings := dictionary;
	foreach setting_name in (setting_list.keys())
		settings[setting_name] := UnPack(setting_list[setting_name]);
		sleepms(2);
	endforeach

	//
	// * If the source is an npc, check it for custom settings.
	//
	if ( source.IsA(POLCLASS_NPC) )
		var cstm_scripts := GetObjProperty(source, "AISettings");
		foreach key in (cstm_scripts.keys())
			settings[key] := cstm_scripts[key];
			sleepms(2);
		endforeach
	endif
	
	return settings;
endfunction

/*
 * NPC_LoadScriptSettings(source)
 *
 * Purpose
 * Loads brain AI script settings for an NPC. Gives .script and .flag values for them.
 *
 * Parameters
 * source:	Name of the npc template to load settings for.
 *		Can also be an npc reference - if custom settings should be loaded off it.
 *
 * Return value
 * Returns a dictionary
 *
 */
function NPC_LoadScriptSettings(source)
	var template:=source;
	if ( source.IsA(POLCLASS_NPC) )
		template := NPC_ParseTemplateName(source.npctemplate);
	elseif ( !template.package )
		template := NPC_ParseTemplateName(template);
	endif

	//
	// * Load config defaults first
	//
	var npc_cfg := ReadConfigFile(template.package+"npcdesc");
	var npc_elem := npc_cfg[template];

	var script_list := GetConfigStringDictionary(npc_elem, "AIScript");
	var flag_list := GetConfigStringDictionary(npc_elem, "AIScriptFlag");

	var script_settings := dictionary;
	foreach script_type in (script_list.keys())
		var temp := struct;
		temp.+script := script_list[script_type];
		temp.+flags := UnPack(flag_list[script_type]);

		script_settings[script_type] := temp;
		sleepms(2);
	endforeach

	//
	// * If the source is an npc, check it for custom script settings.
	//   Assumes each key in the dictionary property has a .script and .flags pair already.
	//
	if ( source.IsA(POLCLASS_NPC) )
		var cstm_scripts := GetObjProperty(source, "AIScripts");
		foreach key in (cstm_scripts.keys())
			script_settings[key] := cstm_scripts[key];
			sleepms(2);
		endforeach
	endif
	
	return script_settings;
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
