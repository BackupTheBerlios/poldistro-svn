use uo;
use os;

include ":spawnsystem:include/groups";
include ":spawnsystem:include/realms";
include ":spawnsystem:include/regions";

/*
 * SSMoveRegionToNewRealm(region_name, realm_name)
 *
 * Purpose
 * Makes calls to regions.inc and realms.inc to move a spawn region from one realm to another.
 * No error checking is present!
 *
 * Parameters
 * region_name:	Name of the region to move
 * realm_name:	Name of the realm to move the region to
 *
 * Returns
 * 1 (No useful return value)
 *
 */
function SSMoveRegionToNewRealm(region_name, realm_name)
	Set_Critical(1);
	var cur_realm := SSGetRegionRealm(region_name);
	SSRemoveRegionFromRealm(cur_realm, region_name);
	SSAddRegionToRealm(realm_name, region_name);
	SSSetRegionRealm(region_name, realm_name);
	Set_Critical(0);
	
	return 1;
endfunction

/* 
 * SSFullRemoveRegion(region_name)
 *
 * Purpose
 * Calls SSRemoveRegionFromRealm() and SSRemoveRegion() to cleanly remove a region.
 * 
 * Parameters
 * region_name:	Name of the region to erase.
 *
 * Return Value
 * Returns 1
 *
 */
function SSFullRemoveRegion(region_name)
	var realm_name := SSGetRegionRealm(region_name);
	SSRemoveRegionFromRealm(realm_name, region_name);
	SSRemoveRegion(region_name);
	
	return 1;
endfunction
