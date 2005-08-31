/*===============================================================
* Current Version
* NPC_COMMANDS.INC - v1.0
* Updated 8/31/2005 6:38AM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;
use os;

include "include/sysevent";
include ":ai_brain:include/eventid";

function AI_ClearThoughts(mobile, flags)
	var brain	:= flags & CLR_BRAIN;
	var nerve	:= flags & CLR_NERVE;
	var both	:= flags & CLR_BOTH;
	
	if ( both || brain )
		brain := mobile.process;
		brain.clear_event_queue();
	endif
	
	if ( both || nerve )
		nerve := GetProcess(GetPid());
		nerve.clear_event_queue();
	endif
endfunction

function AI_Move(mobile, object, to_from:=NEMOVE_TOWARD, speed:=NEMOVE_RUN, no_wake:=WAKEUP, loop:=0)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_MOVE;
	ev.+source	:= object;
	ev.+direction	:= to_from;
	ev.+speed	:= speed;
	ev.+WakeUp	:= no_wake;
	ev.+loop	:= loop;
	ev.+process	:= GetProcess(GetPid());
	
	SendEvent(mobile, ev);
endfunction

function AI_MoveXY(mobile, x, y, to_from:=NEMOVE_TOWARD, speed:=NEMOVE_RUN, no_wake:=WAKEUP, loop:=0)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_MOVE_XY;
	ev.+x		:= x;
	ev.+y		:= y;
	ev.+direction	:= to_from;
	ev.+speed	:= speed;
	ev.+WakeUp	:= no_wake;
	ev.+loop	:= loop;
	ev.+process	:= GetProcess(GetPid());
	
	SendEvent(mobile, ev);
endfunction

function AI_Wander(mobile, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_WANDER;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());
	
	SendEvent(mobile, ev);
endfunction

function AI_Turn(mobile, turn_to, direction:=NETURN_TOWARD, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_TURN;
	ev.+source	:= turn_to;
	ev.+direction	:= direction;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());
	
	SendEvent(mobile, ev);
endfunction

function AI_TurnXY(mobile, x, y, direction:=NETURN_TOWARD, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_TURN_XY;
	ev.+x		:= x;
	ev.+y		:= y;
	ev.+direction	:= direction;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());
	
	SendEvent(mobile, ev);
endfunction

function AI_SetOpponent(mobile, opponent, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_OPPONENT;
	ev.+source	:= opponent;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());
	
	SendEvent(mobile, ev);
endfunction

function AI_Warmode(mobile, mode:=1, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_WARMODE;
	ev.+value	:= mode;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());

	SendEvent(mobile, ev);
endfunction

function AI_Speak(mobile, text:="!?", text_type:=SPEAK_TEXTTYPE_DEFAULT, do_event:=SPEAK_DOEVENT_DISABLE, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_SPEAK;
	ev.+text	:= text;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());
	
	SendEvent(mobile, ev);
endfunction

function AI_StartNerve(mobile, nerve_name, script_name, data, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_STARTNERVE;
	ev.+name	:= nerve_name;
	ev.+script	:= script_name;
	ev.+data	:= data;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());
	
	SendEvent(mobile, ev);
endfunction

function AI_EndNerve(mobile, nerve_name, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_ENDNERVE;
	ev.+name	:= nerve_name;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());

	SendEvent(mobile, ev);
endfunction

function AI_WinFight(mobile, opponent, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_WINFIGHT;
	ev.+source	:= opponent;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());
	
	SendEvent(mobile, ev);
endfunction

function AI_Attack(mobile, opponent, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= SYSEVENT_ENGAGED;
	ev.+source	:= opponent;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());
	
	SendEvent(mobile, ev);
endfunction

function AI_Flee(mobile, opponent, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_FLEE;
	ev.+source	:= opponent;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());
	
	SendEvent(mobile, ev);
endfunction

function AI_FowardEvent(mobile, nerve_name, mask, data, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_FWDNERVE;
	ev.+NerveName	:= nerve_name;
	ev.+mask	:= mask;
	ev.+data	:= data;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());
	
	SendEvent(mobile, ev);
endfunction

function AI_Sleep(mobile)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_SLEEP;
	ev.+WakeUp	:= NOWAKE;
	ev.+process	:= GetProcess(GetPid());
	
	SendEvent(mobile, ev);
endfunction

function AI_WakeUp(mobile)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_WAKEUP;
	ev.+WakeUp	:= WAKEUP;
	ev.+process	:= GetProcess(GetPid());
	
	SendEvent(mobile, ev);
endfunction
