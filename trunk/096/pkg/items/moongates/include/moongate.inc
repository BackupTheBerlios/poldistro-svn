/*
 * $Id$
 *
 */

use uo;
use os;
use cfgfile;

include ":datafile:datafile";

// Constats for the moongate gump.
const MG_CANCEL_BTN	:= 0x0;
const MG_OKAY_BTN	:= 0x1;
const MG_LOCATION_START := 0xA00;


/*
 * MG_GetRealmDataFile()
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
function MG_GetDataFile()
	var data_file := DFOpenDataFile(":moongates:gateinfo", DF_CREATE);
	return data_file;
endfunction

/*
 * MG_GetRealmDataElem(elem_name)
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
function MG_GetDataElem(elem_name)
	var data_file := MG_GetDataFile();
	var realm_elem := DFFindElement(data_file, elem_name, DF_CREATE);

	return realm_elem;
endfunction

