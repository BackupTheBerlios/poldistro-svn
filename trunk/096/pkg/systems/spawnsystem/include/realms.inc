use uo;
use os;

include ":datafile:include/datafile";

/*
 * SSGetRealmDataFile()
 * 
 * Purpose
 * Quickly pull up the datafile that stores realm information.
 *
 * Parameters
 *
 * Return Value
 * Data file reference
 *
 */
function SSGetRealmDataFile()
	var data_file := DFOpenDataFile(":spawnsystem:Realms", DF_CREATE);
	return data_file;
endfunction

/*
 * SSGetRealmDataElem(elem_name)
 * 
 * Purpose
 * Quickly retrieve a realm elem for the spawner.
 *
 * Parameters
 * elem_name:	Name of the elem to retrieve
 *
 * Return Value
 * A datafile elem reference.
 *
 */
function SSGetRealmDataElem(elem_name)
	var data_file := SSGetRealmDataFile();
	var realm_elem := DFFindElement(data_file, elem_name, DF_NO_CREATE);

	return realm_elem;
endfunction

/*
 * SSAddRealm(realm_name)
 * 
 * Purpose
 * Adds a realm name to the spawner's realm list
 *
 * Parameters
 * realm_name:	A string containing the name of the new realm.
 *
 * Return Value
 * Returns 1 on success.
 *
 */
function SSAddRealm(realm_name)
	var data_file := SSGetRealmDataFile();
	return data_file.CreateElement(realm_name);
endfunction

/*
 * SSRemoveRealm(realm_name)
 *
 * Purpose
 * Removes a realm elem from the spawner's list
 *
 * Parameters
 * realm_name:	A string containing the name of the realm to remove.
 *
 * Return Value
 * Result of the elem deletion.
 *
 */
function SSRemoveRealm(realm_name)
	var data_file := SSGetRealmDataFile();
	return data_file.DeleteElement(realm_name);
endfunction

/*
 * SSGetRealmNames()
 *
 * Purpose
 * Retrieves a list of realm names listed in the spawner.
 *
 * Parameters
 * 
 * Return Value
 * An array of strings
 *
 */
function SSGetRealmNames()
	var data_file := SSGetRealmDataFile();
	var realm_names := DFGetElemNames(data_file);
	
	return realm_names;
endfunction

/*
 * SSAddRegionToRealm(realm_name, region_name)
 * 
 * Purpose
 * Adds a region name to the realm's elem.
 * 
 * Parameters
 * realm_name:	The realm the region will be added to.
 * region_name:	The name of the region to add.
 *
 * Return Value
 * 1 on success
 *
 */
function SSAddRegionToRealm(realm_name, region_name)
	var realm_elem := SSGetRealmDataElem(realm_name);
	var region_list := SSGetRegionsInRealm(realm_name);
	
	if ( region_list.Exists(region_name) )
		return 0;
	else
		region_list.Insert(region_name, 1);
		return realm_elem.SetProp("Regions", region_list);
	endif
endfunction

/*
 * SSRemoveRegionFromRealm(realm_name, region_name)
 * 
 * Purpose
 * Removes a region name from the realm's elem.
 * 
 * Parameters
 * realm_name:	The realm the region will be removed from.
 * region_name:	The name of the region to remove.
 *
 * Return Value
 * Returns the modified region list.
 *
 * Notes:
 *    See SSFullRemoveRegion() in commontasks.inc
 *
 */
function SSRemoveRegionFromRealm(realm_name, region_name)
	var realm_elem := SSGetRealmDataElem(realm_name);
	var region_list := SSGetRegionsInRealm(realm_name);
	
	if ( !region_list.Exists(region_name) )
		return 0;
	else
		region_list.Erase(region_name);
		return realm_elem.SetProp("Regions", region_list);
	endif
endfunction

/*
 * SSGetRegionsInRealm(realm_name)
 * 
 * Purpose
 * Lists the spawn regions that exist within a realm.
 *
 * Parameters
 * realm_name:	Name of the realm to retrieve the list from.
 *
 * Return Value
 * Returns an array of spawn region names in the realm.
 *
 */
function SSGetRegionsInRealm(realm_name)
	var realm_elem := SSGetRealmDataElem(realm_name);
	var region_list := realm_elem.GetProp("Regions");
	if ( !region_list )
		region_list := dictionary;
	endif
	
	return region_list;
endfunction
