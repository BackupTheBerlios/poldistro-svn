use uo;
use util;
use cfgfile;

const MIN_COLOR := 2;
const MAX_COLOR := 1001;

function CanDye(item)
	var config := ReadConfigFile(":*:itemdesc");
	config := config[item.objtype];
	
	if ( config.CanDye )
		return 1;
	elseif ( config.dyeable )
		return 1;
	endif
endfunction

function ValidDyeColor(mobile, color)
	if ( mobile.cmdlevel )
		return 1;
	elseif ( (color >= MIN_COLOR) && (color <= MAX_COLOR) )
		return 1;
	else
		return 0;
	endif
endfunction

function RandomDyeColor(item)
	var color := RandomInt(MAX_COLOR - MIN_COLOR);
	color := color+MIN_COLOR;
	item.color := color;
endfunction