use uo;
use os;

include ":gumps:include/gumps";
include ":gumps:include/gumps_ex";

/* Version 1.0 - Austin
 *
 * RequestGump(mobile, question, option, pre_val, cancel_btn)
 *
 * Purpose
 * Template to create a single field input gump.
 *
 * Parameters
 * mobile:	Mobile to send the gump to.
 * question:	Primary text field, instructing the mobile on what to enter.
 * option:	Optional text placed directly above the text entry area.
 * pre_val:	The text to display in the text entry field.
 * cancel_btn:	0 - No cancel button will be shown
 * 		1 - A cancel button will be shown.
 *
 * Return value
 * Returns 'error' if the cancel button is clicked.
 * Returns 0 or the text that was entered.
 *
 */
function RequestGump(mobile, question, option := "", pre_val := "", cancel_btn:=0)
	//Mobile = Character input gump is sent to.
	//Question = Question to ask.
	//Option = Optional text to put under the question.
	//Preval = What you want them to see in the text area when it comes up.
	
	if ( !pre_val || pre_val == error )
		pre_val := "";
	endif
	
	var r_gump := GFCreateGump();
	GFClosable(r_gump, 0);
	GFResizePic(r_gump, 0, 0, GFCfgConst("BackGrounds", "SILVERTRIM"), 400, 205);
	GFResizePic(r_gump, 15, 15, GFCfgConst("BackGrounds", "DARK_STONE"), 370, 175);
	
	var y_pos := 20;
	foreach line in (GFWordWrap(question, 370))
		GFTextLine(r_gump, 20, y_pos, 1153, line);
		y_pos := y_pos+20;
		sleepms(2);
	endforeach
	
	y_pos := 75;
	foreach line in (GFWordWrap(option, 370))
		GFTextLine(r_gump, 20, y_pos, 1153, line);
		y_pos := y_pos+20;
		sleepms(2);
	endforeach
	
	GFResizePic(r_gump, 20, 100, GFCfgConst("BackGrounds", "GOLDTRIM"), 360, 30);
	var r_txt := GFTextEntry(r_gump, 30, 105, 335, 25, 1153, pre_val);
	
	if ( cancel_btn )
		GFAddButton(r_gump, 90, 160, 2128, 2129, GF_CLOSE_BTN, 100);
		GFAddButton(r_gump, 240, 160, 2119, 2120, GF_CLOSE_BTN, 200);
	else
		GFAddButton(r_gump, 180, 160, 2128, 2129, GF_CLOSE_BTN, 100);
	endif
	
	var input := GFSendGump(mobile, r_gump);
	var text_area := GFExtractData(input, r_txt);
	
	if ( input[200] )
		return error;
	elseif ( !text_area || text_area == error )
		return 0;
	else
		return text_area;
	endif
endfunction