//$Id$

/*===============================================================
* Current Version
* ZULUBOOKS.INC - v1.0
* Updated 9/29/2005 4:00PM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use os;
use cfgfile;

/* SysBook_GetZuluBooksCfgFile()
 * 
 * Purpose
 * Loads zulubooks.cfg
 *
 * Parameters
 *
 * Return value
 * Config file
 *
 */
function SysBook_GetZuluBooksCfgFile()
	var cfg_file := ReadConfigFile(":sysbooks:config/zulubooks");
	if ( cfg_file.errortext )
		SysLog("Error::SysBook_GetZuluBooksCfgFile() - Unable to open zulubooks.cfg ->"+cfg_file.errortext);
	endif

	return cfg_file;
endfunction

/*
 * SysBook_GetZuluCfgElem(elem_name, cfg_file)
 *
 * Purpose
 * Retrieves a config elem for a book in zulubooks.cfg
 *
 * Parameters
 * elem_name:		Name of the book elem to retrieve.
 * cfg_file:		Optional parameter - reference to a config already read in.
 *
 * Return value
 * Returns a config file elem.
 *
 */
function SysBook_GetZuluCfgElem(elem_name, byref cfg_file:=0)
	if ( !cfg_file )
		cfg_file := SysBook_GetZuluBooksCfgFile();
	endif
	
	var cfg_elem := cfg_file[elem_name];
	if ( cfg_elem.errortext )
		SysLog("Error::SysBook_GetZuluCfgElem() - unable to find cfg elem ["+elem_name+"] ->"+cfg_elem.errortext);
	endif
	
	return cfg_elem;
endfunction
