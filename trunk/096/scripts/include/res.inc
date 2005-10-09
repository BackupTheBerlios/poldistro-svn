use uo;

include ":gumps:gumps";

function ResNow(mobile)
	var gump := GFCreateGump();
	GFClosable(gump, 0);
	GFGumpPic(gump, 300, 230, 2070);
	GFAddButton(gump, 330, 305, 2073, 2072, GF_CLOSE_BTN, 10);
	GFAddButton(gump, 400, 305, 2076, 2075, GF_CLOSE_BTN, 11);
	GFTextLine(gump, 332, 264, 40, "Resurrect Now?");
	
	var input := GFSendGump(mobile, gump);
	input := input[0];
	input := input-10;
	
	if ( !input )
		return 0;
	else
		return 1;
	endif
endfunction
