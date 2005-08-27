use uo;
use os;
use cfgfile;

include ":datafile:include/datafile";
include ":spawnsystem:include/settings";

/*
 * SSGetEnginesList()
 *
 * Purpose
 * Retrieves the list of engines in :spawnsystem:configs/settings.cfg
 *
 * Parameters
 *
 * Return Value
 * Array of strings
 *
 */
function SSGetEnginesList()
	var cfg_file := SSGetSettingsCfgFile();
	var cfg_elem := SSGetSettingsCfgElem(cfg_file, "EngineList");
	
	return GetConfigStringArray(cfg_elem, "Engine");
endfunction

/*
 * SSEngineEnabled(engine_name)
 *
 * Purpose
 * Tells if an engine is set to be enabled or disabled
 *
 * Parameters
 * engine_name:	Name of the engine to check.
 *
 * Return Value
 * 1 if the engine is enabled
 *
 */
function SSEngineEnabled(engine_name)
	var settings := SSGetSettingsCfgFile(engine_name);
	settings := settings["Settings"];

	return CInt(settings.Enabled);
endfunction

/*
 * SSStartSpawnEngine(engine_name, realm_name, region_name, group_name)
 *
 * Purpose
 * Instructs an engine to do a spawn cycle
 *
 * Parameters
 * engine_name:	Name of the engine to start
 * realm_name:	Name of the realm the engine will run in
 * region_name:	Name of the regin that will be spawning
 * group_name:	Name of the spawn group that will be used
 *
 * Return Value
 * 1 on engine start
 *
 */
function SSStartSpawnEngine(engine_name, realm_name, region_name, group_name)
	var script := Start_Script(SSGetEnginePath(engine_name), {engine_name, realm_name, region_name, group_name});

	return script;
endfunction

/*
 * SSGetEnginePath(engine_name)
 *
 * Purpose
 * Takes in the name of the engine and gives the path to call configs/scripts in it.
 *
 * Parameters
 * engine_name:	Name of the engine to setup the path for.
 *
 * Return Value
 * String
 *
 */
function SSGetEnginePath(engine_name)
	return ":spawnsystem:engines/"+engine_name+"/spawncycle";
endfunction
