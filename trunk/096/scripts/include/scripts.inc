/* $Id$
 *
 * Purpose
 * Provide various functions for the script object.
 *
 */
use os;


/*
 * KillScript()
 *
 * Author: Folko
 *
 * Purpose
 * Kills the calling script.
 *
 * Parameters
 * No parameters
 *
 * Return value
 * This function will never return
 * 
 */
function KillScript()
	GetProcess(GetPID()).kill();

	return; // This doesn't actually happen
endfunction
