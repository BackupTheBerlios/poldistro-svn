/*
 * $Id$
 *
 */

use os;
use cfgfile;

/*
 * ParseCommands(text, last_cmd)
 * 
 * Purpose:
 * Takes in spoken text and finds boat commands inside of it.
 * Returns valid commands in the order they were issued.
 *
 * Parameters:
 * text:	Text to parse for commands.
 *
 * Return Value:
 * Returns an array of strings.
 *
 */
function ParseCommands(text)
	var cmd_cfg := ReadConfigFile(":boat:config/commands");
	if ( cmd_cfg.errortext )
		SysLog("Error - Unable to open :boat:config/commands.cfg");
		return cmd_cfg;
	endif	
	
	var cmd_list := GetConfigStringArray(cmd_cfg["heirarchy"], "CMD");
	text := Lower(text);
		
	var match := 0, pos := 0;
	foreach cmd in ( cmd_list )
		pos := pos + 1;
		cmd := Lower(cmd);
		while ( text[cmd] )
			text[cmd] := "[["+CStr(pos)+"]] ";
			match := 1;
			sleepms(2);
		endwhile
		sleepms(2);
	endforeach
	if ( match == 0 )
		return 0;
	endif

	var cmd_order := array{};
	text := SplitWords(text);
	foreach cmd in ( text )
		if ( cmd["[["] && cmd["]]"] )
			cmd["[["] := "";
			cmd["]]"] := "";
			cmd := cmd_list[CInt(cmd)];
			cmd_order.Append(cmd);
		endif
		sleepms(2);
	endforeach
	text := "";

	return cmd_order;
endfunction