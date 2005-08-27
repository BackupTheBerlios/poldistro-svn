use uo;
use os;

include ":datafile:include/datafile";

/*
 * SSGetRegionDataFile()
 *
 * Purpose
 * Quickly pull up the datafile that stores region information.
 *
 * Parameters
 *
 * Return Value
 * Data file reference
 *
 */
function SSGetRegionDataFile()
	var data_file := DFOpenDataFile(":spawnsystem:Regions", DF_CREATE);
	return data_file;
endfunction

/*
 * SSGetRegionDataElem(elem_name)
 *
 * Purpose
 * Quickly retrieve a region elem for the spawner.
 *
 * Parameters
 * elem_name:	Name of the elem to retrieve
 *
 * Return Value
 * A datafile elem reference.
 *
 */
function SSGetRegionDataElem(elem_name)
	var data_file := SSGetRegionDataFile();
	var region_elem := DFFindElement(data_file, elem_name, DF_NO_CREATE);

	return region_elem;
endfunction

/*
 * SSAddRegion(region_name)
 *
 * Purpose
 * Adds a region name to the spawner's region list
 *
 * Parameters
 * region_name:	A string containing the name of the new region.
 * realm_name:	Optional parameter to set the region's realm on creation.
 *
 * Return Value
 * Returns 1 on success.
 *
 */
function SSAddRegion(region_name, realm_name:="")
	var data_file := SSGetRegionDataFile();
	var result := data_file.CreateElement(region_name);
	
	if ( realm_name && result )
		SSSetRegionRealm(region_name, realm_name);
	endif
	
	return result;
endfunction

/*
 * SSRemoveRegion(region_name)
 *
 * Purpose
 * Removes a region elem from the spawner's list
 *
 * Parameters
 * region_name:	A string containing the name of the region to remove.
 *
 * Return Value
 * Result of the elem deletion.
 *
 * Notes:
 *    See SSFullRemoveRegion() in commontasks.inc
 * 
 */
function SSRemoveRegion(region_name)
	var data_file := SSGetRegionDataFile();
	return data_file.DeleteElement(region_name);
endfunction

/*
 * SSGetRegionNames(region_name:="")
 *
 * Purpose
 * Retrieves a list of region names listed in the spawner.
 *
 * Parameters
 * realm_name:	Optional parameter to list regions that belong to a specific realm.
 *		- Note its better to get them from SSGetRegionsInRealm(realm_name) in realms.inc
 *
 * Return Value
 * An array of strings
 *
 */
function SSGetRegionNames(realm_name:="")
	var data_file := SSGetRegionDataFile();

	var region_names := array{};
	if ( !realm_name )
		region_names := DFGetElemNames(data_file);
	else
		foreach region_name in DFGetElemNames(data_file)
			if ( Lower(SSGetRegionRealm(region_name)) == Lower(realm_name) )
				region_names.append(region_name);
			endif
			sleepms(2);
		endforeach
	endif

	return region_names;
endfunction

/*
 * SSGetRegionRealm(region_name)
 *
 * Purpose
 * Get the name of the realm the region is set to.
 *
 * Parameters
 * region_name:	Name of the region to lookup.
 *
 * Return Value
 * A string containing the name of a realm
 *
 */
function SSGetRegionRealm(region_name)
	var region_elem := SSGetRegionDataElem(region_name);
	return region_elem.GetProp("Realm");
endfunction

/*
 * SSSetRegionRealm(region_name, realm_name)
 *
 * Purpose
 * Sets the realm the region belongs to. 
 * 
 * Parameters
 * region_name:	The name of the region to set.
 * realm_name:	The name of the realm the region belongs to.
 *
 * Return Value
 * 1 on success
 *
 */
function SSSetRegionRealm(region_name, realm_name)
	var region_elem := SSGetRegionDataElem(region_name);
	return region_elem.SetProp("Realm", realm_name);
endfunction

/*
 * SSGetRegionCoordinates(region_name)
 *
 * Purpose
 * Retrieves the coordinates for the region
 * 
 * Parameters
 * region_name:	Name of the region to retrieve the coordinates of.
 *
 * Return Value
 * Returns a structure containing .x1, .y1, .x2, .y2
 *
 */
function SSGetRegionCoordinates(region_name)
	var region_elem := SSGetRegionDataElem(region_name);
	return region_elem.GetProp("Coordinates");
endfunction

/*
 * SSGetRegionCoordinates(region_name, x1, y1, x2, y2)
 *
 * Purpose
 * Sets the coordinates for a region
 * 
 * Parameters
 * region_name:	Name of the region to set the coordinates on.
 * x1:		Top left X coordinate
 * y1:		Top left Y coordinate
 * x2:		Bottom right X coordinate
 * y2:		Bottom right Y coordinate
 *
 * Return Value
 * 1 on success
 *
 */
function SSSetRegionCoordinates(region_name, x1, y1, x2, y2)
	var region_elem := SSGetRegionDataElem(region_name);
	
	var coords := struct{"x1":=x1, "y1":=y1, "x2":=x2, "y2":=y2};
		
	return region_elem.SetProp("Coordinates", coords);
endfunction

/*
 * SSGetGroupsInRegion(region_name)
 *
 * Purpose
 * Retrieves the groups and their settings in a spawn region
 *
 * Parameters
 * region_name:	Name of the region to retrieve the groups from.
 * 
 * Return Value
 * Dictionary 
 * -keys are the group name, with a struct inside for settings.
 * 
 */
function SSGetGroupsInRegion(region_name)
	var region_elem := SSGetRegionDataElem(region_name);
	var group_list := region_elem.GetProp("Groups");
	if ( !group_list )
		group_list := dictionary;
	endif
	
	return group_list;
endfunction

/* 
 * SSGetGroupInRegion(region_name, group_name)
 * Retrieves a specific spawn group and its settings from a region
 *
 * Parameters
 * region_name:	Name of the region the spawn group is in.
 * group_name:	Name of the region to retrieve.
 *
 * Return Value
 * Struct 
 *
 */
 function SSGetGroupInRegion(region_name, group_name)
 	var group_list := SSGetGroupsInRegion(region_name);
 	return group_list[group_name];
 endfunction

/*
 * SSAddGroupToRegion(region_name, group_name, max_amt, spawn_wait, enabled)
 *
 * Purpose
 * Adds a spawn group to a spawn region
 * 
 * Parameters
 * region_name:	Name of the region to add the group to.
 * group_name:	Name of the group to add to the region.
 * max_amt:	Max amount of objects (mobiles/items) the group should make.
 * spawn_wait:	Amount of time between each spawn cycle for this group.
 * enabled:	0 | 1
 * 
 * Return Value
 * 1 on success
 *
 * Notes:
 * 	This function can also be used to update a spawn group's settings in a region.
 *
 */
function SSAddGroupToRegion(region_name, group_name, max_amt, spawn_wait, enabled)
	var settings := struct;
	settings.+max_amt := max_amt;
	settings.+spawn_wait := spawn_wait;
	settings.+enabled := enabled;
	
	var group_list := SSGetGroupsInRegion(region_name);
	group_list.Insert(group_name, settings);
	
	var region_elem := SSGetRegionDataElem(region_name);
	return region_elem.SetProp("Groups", group_list);
endfunction

/*
 * SSRemoveGroupFromRegion(region_name, group_name)
 *
 * Purpose
 * Removes a spawn group from a spawn region
 * 
 * Parameters
 * region_name:	Name of the region to remove from the group.
 * group_name:	Name of the group to remove from the region.
 * 
 * Return Value
 * 1 on success
 *
 */
function SSRemoveGroupFromRegion(region_name, group_name)
	var group_list := SSGetGroupsInRegion(region_name);
	group_list.Erase(group_name);
	
	var region_elem := SSGetRegionDataElem(region_name);
	region_elem.EraseProp("Spawns-"+group_name); //Clears the spawns list too
	return region_elem.SetProp("Groups", group_list);
endfunction

/*
 * SSAddSpawnToRegion(region_name, group_name, serial)
 *
 * Purpose
 * Used to track what has been spawned in a region's group list. 
 *
 * Parameters
 * region_name:	Name of the region the object was created in.
 * group_name:	Name of the group the object is listed in.
 * object:	A reference to the object that was created.
 *
 * Return Value
 * 1 on success
 *
 */
function SSAddSpawnToRegion(region_name, group_name, object)
	var spawn_list := SSGetSpawnsInRegionGroup(region_name, group_name);
	
	var spawn_info := struct;
	spawn_info.+time := polcore().systime;
	spawn_info.+orig_coords := struct{"x":=object.x, "y":=object.y};
	
	spawn_list[object.serial] := spawn_info;
	
	var region_elem := SSGetRegionDataElem(region_name);
	region_elem.SetProp("Spawns-"+group_name, spawn_list);
endfunction

/*
 * SSGetSpawnsInRegion(region_name, group_name)
 *
 * Purpose
 * Returns a list of objects that have been spawned in a region's group.
 *
 * Parameters
 * region_name:	Name of the region the group is in.
 * group_name:	Name of the group to get the spawn list of.
 *
 * Return Value
 * Dictionary
 *
 */
function SSGetSpawnsInRegionGroup(region_name, group_name)
	var region_elem := SSGetRegionDataElem(region_name);
	var spawns := region_elem.GetProp("Spawns-"+group_name);
	if ( !spawns )
		spawns := dictionary;
	endif
	
	return spawns;
endfunction
