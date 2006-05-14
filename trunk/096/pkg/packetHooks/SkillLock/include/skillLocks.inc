/*
 * $Id$
 *
 */

include ":datafile:datafile";

/*
 * SLPH_GetRealmDataFile()
 * 
 * Purpose
 * Quickly pull up the datafile.
 *
 * Parameters
 *
 * Return Value
 * Data file reference
 *
 */
function SLPH_GetDataFile()
	var data_file := DFOpenDataFile(":skilllock:settings", DF_CREATE);
	return data_file;
endfunction

/*
 * SLPH_GetDataElem(elem_name)
 * 
 * Purpose
 * Quickly retrieve a data elem.
 *
 * Parameters
 * elem_name:	Name of the elem to retrieve
 *
 * Return Value
 * A datafile elem reference.
 *
 */
function SLPH_GetDataElem(elem_name)
	var data_file := SLPH_GetDataFile();
	var realm_elem := DFFindElement(data_file, elem_name, DF_CREATE);

	return realm_elem;
endfunction

/*
 * SLPH_GetLockState(player, skill_id)
 * 
 * Purpose
 * Retrieves the skill lock state for a skill ID.
 *
 * Parameters
 * mobile:	Mobile to retrieve the settings for.
 * skill_id:	Skill ID to retrieve the flag for.
 *
 * Return Value
 * An integer
 *
 */
function SLPH_GetLockState(mobile, skill_id)
	var data_elem := SLPH_GetDataElem(Hex(mobile.serial));
	var lock_list := data_elem.GetProp("SkillLocks");
	
	// +1 is added because skills start at 0 and arrays start at 1
	return CInt(lock_list[skill_id + 1]);
endfunction

/*
 * SLPH_SaveLockState(player, skill_id, state)
 * 
 * Purpose
 * Retrieves the skill lock state for a skill ID.
 *
 * Parameters
 * mobile:	Mobile to retrieve the settings for.
 * skill_id:	Skill ID to retrieve the flag for.
 * state:	State of the skill lock.
 *
 * Return Value
 * An integer
 *
 */
function SLPH_SaveLockState(mobile, skill_id, state)
	var data_elem := SLPH_GetDataElem(Hex(mobile.serial));
	var lock_list := data_elem.GetProp("SkillLocks");
	
	if ( Lower(TypeOf(lock_list)) != "array" )
		lock_list := array{};
	endif
	
	state := CInt(state);
	
	// +1 is added because skills start at 0 and arrays start at 1
	if ( state == 0 )
		// Keeps array smaller and more tidy.
		lock_list.Erase(skill_id + 1);
	else
		lock_list[skill_id + 1] := CInt(state);
	endif
	
	return data_elem.SetProp("SkillLocks", lock_list);
endfunction

