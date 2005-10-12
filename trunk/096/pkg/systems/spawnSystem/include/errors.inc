use uo;
use os;

CONST SPAWN_ERROR_DISABLE	:= 0;
CONST SPAWN_ERROR_PRINT		:= 1;
CONST SPAWN_ERROR_SYSLOG	:= 2;
CONST SPAWN_ERROR_BROADCAST	:= 4;

function SS_ErrorReport(error_text, err_report:=SPAWN_ERROR_DISABLE)
		if ( err_report & SPAWN_ERROR_PRINT )
		Print(""+error_text);
	endif
	
	if ( err_report & SPAWN_ERROR_SYSLOG )
		SysLog(""+error_text);
	endif
	
	if ( err_report & SPAWN_ERROR_BROADCAST )
		foreach mobile in EnumerateOnlineCharacters()
			if ( mobile.cmdlevel )
				SendSysMessage(mobile, ""+error_text);
			endif
			sleepms(5);
		endforeach
	endif
	
	return 1;
endfunction
