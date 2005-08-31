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
	g_settings := NPC_LoadCfgDefaults(npc.npctemplate);
	g_settings := NPC_LoadCustomSettings(npc, g_settings);
	g_settings := NPC_GetDefaultSettings(g_settings);
	
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
	if ( g_settings.exists("listen_script") )
		EnableEvents(SYSEVENT_SPEECH, g_settings["listen_range"]);
	endif
	if ( g_settings.exists("ghost_listen_script") )
		EnableEvents(SYSEVENT_GHOST_SPEECH, g_settings["listen_range"]);
	endif
	
	//
	// * Events that use the core 'area size' range.
	//
	if ( g_settings.exists("enter_react_script") )
		EnableEvents(SYSEVENT_ENTEREDAREA, g_settings["area_size"]);
	endif
	if ( g_settings.exists("leave_react_script") )
		EnableEvents(SYSEVENT_LEFTAREA, g_settings["area_size"]);
	endif
	if ( g_settings.exists("gone_criminal_script") )
		EnableEvents(SYSEVENT_GONE_CRIMINAL, g_settings["area_size"]);
	endif
	
	//
	// * Events that do not have a core range check.
	//
	if ( g_settings.exists("dbl_click_script") )
		EnableEvents(SYSEVENT_DOUBLECLICKED, g_settings["dbl_click_range"]);
	endif
	if ( g_settings.exists("given_item_script") )
		EnableEvents(SYSEVENT_ITEM_GIVEN);
	endif
	if ( g_settings.exists("disengage_script") )
		EnableEvents(SYSEVENT_DISENGAGED);
	endif
	if ( g_settings.exists("merchant_script") )
		EnableEvents(SYSEVENT_MERCHANT_BOUGHT);
		EnableEvents(SYSEVENT_MERCHANT_SOLD);
	endif
	if ( g_settings.exists("combat_script") )
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
 * Always returns 1
 *
 */
function StartupScripts()
	if ( GetObjProperty(npc, "npc_info") )
		//This can only happen if restart() was done on the npc or when POL starts up.
		
		SetWarmode(0);
		//StopNerves();
		
		if ( g_settings.exists("restart_script") )
			var restart_script := Run_Script_To_Completion(g_settings["restart_script"], {npc, g_settings});
			if ( restart_script.errortext )
				//KillMe("Restart script failed:"+restart_script.errortext);
				return 0;
			endif
		endif
	else
		var npc_info := struct{"npctemplate":=npc.npctemplate, "serial":=npc.serial};
		SetObjProperty(npc, "npc_info", npc_info);
		
		if ( g_settings.exists("init_script") )
			var init_script := Run_Script_To_Completion(g_settings["init_script"], {npc, g_settings});
			if ( init_script.errortext )
				//KillMe("Init script failed:"+init_script.errortext);
				return 0;
			endif
		endif
	endif
	
	return 1;
endfunction