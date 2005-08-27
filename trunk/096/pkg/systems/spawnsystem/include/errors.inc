use uo;
use os;

CONST SPAWN_ERROR_DISABLE	:= 0;
CONST SPAWN_ERROR_PRINT		:= 1;
CONST SPAWN_ERROR_SYSLOG	:= 2;
CONST SPAWN_ERROR_BROADCAST	:= 4;

function SSErrorReport(error_text, err_report:=SPAWN_ERROR_DISABLE)
	var do_print := err_report & SPAWN_ERROR_PRINT;
	var do_syslog := err_report & SPAWN_ERROR_SYSLOG;
	var do_broadcast := err_report & SPAWN_ERROR_BROADCAST;
	
	if ( do_print )
		Print("Error - Spawn System ["+error_text+"]");
	endif
	
	if ( do_syslog )
		SysLog("Error - Spawn System ["+error_text+"]");
	endif
	
	if ( do_broadcast )
		foreach mobile in EnumerateOnlineCharacters()
			if ( mobile.cmdlevel )
				SendSysMessage(mobile, "Error - Spawn System ["+error_text+"]");
			endif
			sleepms(5);
		endforeach
	endif
	
	return 1;
endfunction
