/* $Id$
 *
 * Purpose
 *
 * Function List
 * CP_GetStorageContainerForMobile(container_id, storage_area_name:=0)
 * CP_GetStorageAreaContainer(mobile, storage_area_name:=0, create:=CP_NOCREATE)
 * CP_GetStorageAreaContainer(container_id, storage_area_name:=0)
 * CP_RegisterStorageArea(storage_area_name)
 * CP_RemoveStorageAreaContainer(container_id, storage_area_name)
 * CP_StorageDebugMsg(text)
 *
 * Internal Function List
 */
use uo;
use os;
use polsys;

// * Global Variables *
const CP_NOCREATE	:= 0x0;
const CP_CREATE		:= 0x1;

const CP_DEFAULT_AREA	:= "World Bank";
const CP_DEFAULT_PREFIX	:= "[Root Container] ";

/* 
 * Set the 'box_type' variable to the object name of the container type
 * you want to be used for bank box. 
 * Example: "pouch" "metalchest" "barrel"
 *
 * This is ONLY used when a new root container is created. It can be changed on
 * the fly inside of a script for when you want to use specific container
 * types for special storage areas. 
 *
 * Ideally, you should make an object type with the name 'BankBox' to better
 * control the number of items that can be put in the storage container.
 */
var container_type	:= "BankBox";

// Toggles the bank related debug messages on and off.
var STORAGE_DEBUG	:= 1;


/*
 * GetStorageContainerForMobile(mobile, storage_area_name, create)
 *
 * Purpose
 *
 * Parameters
 * mobile:		Owner of the container that will be retrieved (uses .serial of it)
 * storage_area_name:	Name of the storage area to retrieve the container from.
 * create:		Controls if the container will be created if it does not already exist.
 *
 * Return Value
 * A container object
 *
 */
function CP_GetStorageContainerForMobile(mobile, storage_area_name:=0, create:=CP_NOCREATE)
	if ( (!storage_area_name) || (storage_area_name == error) )
		storage_area_name := CP_DEFAULT_AREA;
	endif
	
	var root_container := CP_GetStorageAreaContainer(Hex(mobile.serial), storage_area_name);
	if ( !root_container && create )
		root_container := CP_CreateStorageAreaContainer(Hex(mobile.serial), storage_area_name);
	endif
	
	return root_container;
endfunction


/*
 * CP_GetStorageAreaContainer(container_name, storage_area_name)
 *
 * Purpose
 * Retrieves a root container that matches the id sent.
 *
 * Parameters
 * container_id:	Name of the root container to retrieve.
 * storage_area_name:	Name of the storage area to retrieve the container from.
 *
 * Return value
 * A container object
 *
 */
function CP_GetStorageAreaContainer(container_id, storage_area_name:=0)
	if ( (!storage_area_name) || (storage_area_name == error) )
		storage_area_name := CP_DEFAULT_AREA;
	endif
	var storage_area := FindStorageArea(storage_area_name);
	
	var container_name := CP_DEFAULT_PREFIX + container_id;
	var root_container := FindRootItemInStorageArea(storage_area, container_name);
	if ( !root_container )
		//Old distro (pre 096) root container names.
		container_name := "Bankbox of "+container_name;
		root_container := FindRootItemInStorageArea(storage_area, container_name);
		//Set the name to the new style
		container_name["Bankbox of "] := "";
		container_name := "[Root Container] "+Hex(CInt(container_name));
	endif
	
	return root_container;
endfunction


/*
 * CP_CreateStorageAreaContainer(container_id, storage_area_name)
 *
 * Purpose
 * Creates a root container in a storage area.
 *
 * Parameters
 * container_id:	Name of the container to create.
 * storage_area_name:	Name of the storage area to create the container in.
 *
 * Return value
 * A container object
 *
 */
function CP_CreateStorageAreaContainer(container_id, storage_area_name:=0)
	if ( (!storage_area_name) || (storage_area_name == error) )
		storage_area_name := CP_DEFAULT_AREA;
	endif
	
	var storage_area := FindStorageArea(storage_area_name);
	if ( !storage_area )
		// The storage area does not exist - so create it.
		CreateStorageArea(storage_area_name);
		storage_area := FindStorageArea(storage_area_name);
		CP_RegisterStorageArea(storage_area_name);
	endif
	
	var container_name := CP_DEFAULT_PREFIX + container_id;
	
	var result := CreateRootItemInStorageArea(storage_area, container_name, container_type);
	if ( result.errortext )
		return result;
	endif
		
	return FindRootItemInStorageArea(storage_area_name, container_name);
endfunction


/*
 * CP_RemoveStorageAreaContainer(container_id, storage_area_name)
 *
 * Purpose
 * Removes a root container from a storage area.
 * Also deletes all of its contents.
 *
 * Parameters
 * container_id:	Name of the container to remove.
 * storage_area_name:	Name of the storage area to remove the container from.
 *
 * Return value
 * Returns the result of the deletion.
 *
 */
function CP_RemoveStorageAreaContainer(container_id, storage_area_name:=0)
	if ( (!storage_area_name) || (storage_area_name == error) )
		storage_area_name := CP_DEFAULT_AREA;
	endif

	var storage_area := FindStorageArea(storage_area_name);
	var container_name := CP_DEFAULT_PREFIX + container_id;

	CP_StorageDebugMsg("Removed root container. Storage area: ["+storage_area_name+"] ID: ["+container_id+"]");

	return DestroyRootItemInStorageArea(storage_area, container_name);
endfunction


/*
 * CP_RegisterStorageArea(storage_area_name)
 *
 * Purpose
 * Tracks the names of storage areas that have been created.
 *
 * Parameters
 * storage_area_name:	Name of the storage area to add.
 *
 * Return value
 * Returns 1
 *
 */
function CP_RegisterStorageArea(storage_area_name)
	if ( (!storage_area_name) || (storage_area_name == error) )
		return error{"errortext":="Not a valid storage area name"};
	endif

	set_critical(1);
	var all_areas := GetGlobalProperty("StorageAreaNames");
	if ( !all_areas.Exists(storage_area_name) )
		CP_StorageDebugMsg("Registering storage area ["+storage_area_name+"]");
		all_areas.Insert(storage_area_name, 0);
		SetGlobalProperty("StorageAreaNames", all_areas);
	endif
	set_critical(0);
	
	return 1;
endfunction


/*
 * CP_StorageDebugMsg(text)
 *
 * Purpose
 *
 * Parameters
 *
 * Return value
 *
 */
function CP_StorageDebugMsg(text)
	if ( STORAGE_DEBUG )
		SysLog(text);
	endif
	
	return 1;
endfunction
