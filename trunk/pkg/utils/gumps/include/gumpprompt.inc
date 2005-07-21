use uo;
use os;

include ":gumps:include/gumps";
include ":gumps:include/gumps_ex";

/* Version 1.0 - Austin
 *
 * GumpPrompt(mobile, text)
 *
 * Purpose
 * Template to create a simple prompt window.
 *
 * Parameters
 * mobile:	Mobile to send the gump to.
 * text:	Text to display on the prompt gump.
 * movable:	0 - Dialog will not be movable
 *		1 - Dialog will be movable.
 *
 * Return value
 * Returns 1 when the okay button has been clicked.
 *
 */
function GumpPrompt(mobile, text, movable:=0)
	var gump_prompt := GFCreateGump();
	if ( !movable )
		GFClosable(gump_prompt, 0);
	endif
	GFResizePic(gump_prompt, 180, 100, GFCfgConst("BackGrounds", "SILVERTRIM"), 300, 160);
	GFResizePic(gump_prompt, 195, 115, GFCfgConst("BackGrounds", "DARK_STONE"), 270, 130);
	GFAddButton(gump_prompt, 300, 220, 2128, 2129, GF_CLOSE_BTN, 1);
	
	var y_pos := 125;
	foreach line in (GFWordWrap(text, 260))
		GFTextLine(gump_prompt, 200, y_pos, 1153, line);
		y_pos := y_pos+20;
		sleepms(2);
	endforeach
	
	var prompt_input := GFSendGump(mobile, gump_prompt);
	return prompt_input[0];
endfunction
