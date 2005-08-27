use uo;
use os;

include ":datafile:include/datafile";

/*
 * SSGetGroupDataFile()
 *
 * Purpose
 * Quickly pull up the datafile that stores group information.
 *
 * Parameters
 *
 * Return Value
 * Data file reference
 *
 */
function SSGetGroupDataFile()
	var data_file := DFOpenDataFile(":spawnsystem:Groups", DF_CREATE);
		
	return data_file;
endfunction

/*
 * SSGetGroupDataElem(elem_name)
 *
 * Purpose
 * Quickly retrieve a group elem for the spawner.
 *
 * Parameters
 * elem_name:	Name of the elem to retrieve
 *
 * Return Value
 * A datafile elem reference.
 *
 */
function SSGetGroupDataElem(elem_name)
	var data_file := SSGetGroupDataFile();
	var group_elem := DFFindElement(data_file, elem_name, DF_NO_CREATE);
	
	return group_elem;
endfunction

/* 
 * SSAddGroup(group_name, engine_type)
 * 
 * Purpose
 * Created a new group elem in the data file.
 *
 * Parameters
 * group_name:	String containing the name of the group.
 * engine_type:	Optional parameter to set the engine the group uses.
 *
 * Return Value
 * Returns the result of the elem creation
 *
 */
function SSAddGroup(group_name, engine_type:="")
	var data_file := SSGetGroupDataFile();
	var result := data_file.CreateElement(group_name);
	
	if ( engine_type && result )
		SSSetGroupEngine(group_name, engine_type);
	endif
	
	return result;
endfunction

/*
 * SSRemoveGroup(group_name)
 *
 * Purpose
 * Removes a group elem from the groups list
 *
 * Parameters
 * group_name:	A string containing the name of the group to remove.
 *
 * Return Value
 * Result of the elem deletion.
 *
 */
function SSRemoveGroup(group_name)
	var data_file := SSGetGroupDataFile();
	return data_file.DeleteElement(group_name);
endfunction

/*
 * SSGetGroupNames()
 *
 * Purpose
 * Retrieves a list of group names listed in the spawner.
 *
 * Parameters
 * 
 * Return Value
 * An array of strings
 *
 */
function SSGetGroupNames()
	var data_file := SSGetGroupDataFile();
	var group_names := DFGetElemNames(data_file);
	
	return group_names;
endfunction

/*
 * SSGetGroupEngine(group_name)
 * 
 * Purpose
 * Retrieves the engine that the group will use.
 * 
 * Parameters
 * group_name:	Name of the group to get the engine type from.
 * 
 * Return Value
 * String
 *
 */
function SSGetGroupEngine(group_name)
	var group_elem := SSGetGroupDataElem(group_name);
	return group_elem.GetProp("Engine");
endfunction

/*
 * SSSetGroupEngine(group_name)
 * 
 * Purpose
 * Sets the engine that the group will use.
 * 
 * Parameters
 * group_name:	Name of the group to set the engine type for.
 * engine_name:	Name of the engine the group will use.
 *
 * Return Value
 * 1 on succcess
 *
 */
function SSSetGroupEngine(group_name, engine_name)
	var group_elem := SSGetGroupDataElem(group_name);
	return group_elem.SetProp("Engine", engine_name);
endfunction

/*
 * SSAddEntryToGroup(group_name, entry_name)
 * 
 * Purpose
 * Adds an entry name to the groups's elem.
 * 
 * Parameters
 * group_name:	The group the entry will be added to.
 * entry_name:	The name of the entry to add.
 *
 * Return Value
 * 1 on success
 *
 */
function SSAddEntryToGroup(group_name, entry_name)
	var entry_list := SSGetEntriesInGroup(group_name);
	
	if ( entry_list.Exists(entry_name) )
		return 0;
	else
		entry_list.Insert(entry_name, 1);
		var group_elem := SSGetGroupDataElem(group_name);
		return group_elem.SetProp("EntryList", entry_list);
	endif
endfunction

/*
 * SSRemoveEntryFromGroup(group_name, entry_name)
 * 
 * Purpose
 * Removes an entry name from the groups's elem.
 * 
 * Parameters
 * group_name:	The group the entry will be removed from.
 * entry_name:	The name of the entry to remove.
 *
 * Return Value
 * 1 on success
 *
 */
function SSRemoveEntryFromGroup(group_name, entry_name)
	var entry_list := SSGetEntriesInGroup(group_name);
			
	if ( !entry_list.Exists(entry_name) )
		return 0;
	else
		entry_list.Erase(entry_name);
		var group_elem := SSGetGroupDataElem(group_name);
		return group_elem.SetProp("EntryList", entry_list);
	endif
endfunction

/*
 * SSGetEntriesInGroup(group_name)
 *
 * Purpose
 * Retrieves the entries in a spawn group
 *
 * Parameters
 * group_name:	Name of the group to retrieve the entries from.
 * 
 * Return Value
 * Dictionary 
 * Keys are the entries - nothing else is used.
 * 
 */
function SSGetEntriesInGroup(group_name)
	var group_elem := SSGetGroupDataElem(group_name);
	var group_list := group_elem.GetProp("EntryList");
	
	if ( !group_list )
		group_list := dictionary;
	endif
	
	return group_list;
endfunction

