/*===============================================================
* Current Version
* SETUP.INC - v1.0
* Updated 8/31/2005 4:54AM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

/*
 * InitializeSettings()
 * 
 * Purpose
 * Initializes g_settings in the brain.
 *
 * Parameters
 *
 * Return value
 * Always returns 1
 *
 */
function InitializeSettings()
	
	g_settings := NPC_LoadTemplateSettings(npc);
	g_settings := NPC_GetDefaultSettings(g_settings);
	g_scripts := NPC_LoadScriptSettings(npc);
		
	return 1;
endfunction

/*
 * InitializeEvents()
 *
 * Purpose
 * Enables system events the core sends based on g_settings
 *
 * Parameters
 *
 * Return value
 * Always returns 1
 *
 */
function InitializeEvents()
	//
	// * Events that use the core 'speech' range.
	//
	if ( g_scripts.Exists("Listen") )
		if ( g_settings["HearSpeech"] )
			EnableEvents(SYSEVENT_SPEECH, g_settings["ListenRange"]);
		endif
		if ( g_settings["HearGhosts"] )
			EnableEvents(SYSEVENT_GHOST_SPEECH, g_settings["ListenRange"]);
		endif
	endif
		
	//
	// * Events that use the core 'area size' range.
	//
	if ( g_scripts.Exists("EnterArea") )
		EnableEvents(SYSEVENT_ENTEREDAREA, g_settings["AreaSize"]);
	endif
	if ( g_scripts.Exists("LeftArea") )
		EnableEvents(SYSEVENT_LEFTAREA, g_settings["AreaSize"]);
	endif
	if ( g_scripts.Exists("GoneCriminal") )
		EnableEvents(SYSEVENT_GONE_CRIMINAL, g_settings["AreaSize"]);
	endif
	
	//
	// * Events that do not have a core range check.
	//
	if ( g_scripts.Exists("DblClick") )
		EnableEvents(SYSEVENT_DOUBLECLICKED, 20);
	endif
	if ( g_scripts.Exists("ItemGiven") )
		EnableEvents(SYSEVENT_ITEM_GIVEN);
	endif
	if ( g_scripts.Exists("Disengaged") )
		EnableEvents(SYSEVENT_DISENGAGED);
	endif
	if ( g_scripts.Exists("Merchant") )
		EnableEvents(SYSEVENT_MERCHANT_BOUGHT);
		EnableEvents(SYSEVENT_MERCHANT_SOLD);
	endif
	if ( g_scripts.Exists("Combat") )
		EnableEvents(SYSEVENT_ENGAGED+SYSEVENT_DAMAGED);
	endif
	
	return 1;
endfunction

/*
 * StartupScripts()
 *
 * Purpose
 * Runs the restart_script or init_script. Sets up the npc_info cprop.
 *
 * Parameters
 *
 * Return value
 * Returns 1 on success
 *
 */
function StartupScripts()
	if ( GetObjProperty(npc, "npc_info") )
		//This can only happen if restart() was done on the npc or when POL starts up.
		
		SetWarmode(0);
		//StopNerves();
		
		if ( g_scripts.Exists("restart_script") )
			var restart_script := Run_Script_To_Completion(g_scripts["restart_script"], {npc, g_settings});
			if ( restart_script.errortext )
				FatalError("Error - StartupScripts() :: Restart script failed: "+restart_script.errortext);
				return 0;
			endif
		endif
	else
		var npc_info := struct{"npctemplate":=npc.npctemplate, "serial":=npc.serial};
		SetObjProperty(npc, "npc_info", npc_info);
		
		if ( g_scripts.Exists("init_script") )
			var init_script := Run_Script_To_Completion(g_scripts["init_script"], {npc, g_settings});
			if ( init_script.errortext )
				FatalError("Error - StartupScripts() :: Init script failed:"+init_script.errortext);
				return 0;
			endif
		endif
	endif
	
	return 1;
endfunction