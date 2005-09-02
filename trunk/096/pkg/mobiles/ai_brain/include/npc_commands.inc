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

/////////////////////////////////////////////////////////////////
// * Function List *
//
// AI_Attack()
// AI_ClearThoughts()
// AI_EndNerve()
// AI_Flee()
// AI_FowardEvent()
// AI_Move()
// AI_MoveXY()
// AI_SetOpponent()
// AI_Sleep()
// AI_Speak()
// AI_StartNerve()
// AI_Turn()
// AI_TurnXY()
// AI_WakeUp()
// AI_Wander()
// AI_Warmode()
// AI_WinFight()
//
/////////////////////////////////////////////////////////////////

/*
 * AI_Attack(mobile, opponent, no_wake)
 *
 * Purpose
 * Triggers the npc's combat script on opponent.
 *
 * Parameters
 * mobile:	The npc that will receive the command.
 * opponent:	What the npc's combat nerve will attack.
 * no_wake:	Optional wakeup flag:
 *		WAKEUP - Will stop the sleep script if it is running - Default.
 *		NOWAKE - Will not stop the sleep script if it is running.
 *
 * Return value
 * Result of SendEvent()
 *
 */
function AI_Attack(mobile, opponent, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= SYSEVENT_ENGAGED;
	ev.+source	:= opponent;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());

	return SendEvent(mobile, ev);
endfunction

/*
 * AI_ClearThoughts(mobile, flags)
 *
 * Purpose
 * Clears the event queue for the script calling it and or the brain.
 *
 * Parameters
 * mobile:	A reference to the npc.
 * flags:	CLR_* flag for what scripts should have their event queues cleared.
 *		CLR_BRAIN - Clears the brain's queue.
 *		CLR_NERVE - Clears the nerve's queue.
 *		CLR_BOTH  - Clears the queue for both.
 *
 * Return value
 * Always returns 1
 *
 */
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

	return 1;
endfunction

/*
 * AI_EndNerve(mobile, nerve_name, no_wake)
 *
 * Purpose
 * Used to tell the brain to stop a nerve script.
 *
 * Parameters
 * mobile:	The npc that will receive the command.
 * nerve_name:	String containing the name of the nerve (dictionary key).
 * no_wake:	Optional wakeup flag:
 *		WAKEUP - Will stop the sleep script if it is running - Default.
 *		NOWAKE - Will not stop the sleep script if it is running.
 *
 * Return value
 * Result of SendEvent()
 *
 */
function AI_EndNerve(mobile, nerve_name, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_ENDNERVE;
	ev.+name	:= nerve_name;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());

	return SendEvent(mobile, ev);
endfunction

/*
 * AI_Flee(mobile, opponent, no_wake)
 *
 * Purpose
 * Used to tell the brain to stop a nerve script.
 *
 * Parameters
 * mobile:	The npc that will receive the command.
 * opponent:	Opponent to flee from.
 * no_wake:	Optional wakeup flag:
 *		WAKEUP - Will stop the sleep script if it is running - Default.
 *		NOWAKE - Will not stop the sleep script if it is running.
 *
 * Return value
 * Result of SendEvent()
 *
 */
function AI_Flee(mobile, opponent, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_FLEE;
	ev.+source	:= opponent;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());

	return SendEvent(mobile, ev);
endfunction

/*
 * AI_ForwardEvent(mobile, nerve_name, mask, data, no_wake)
 *
 * Purpose
 * Used to send an event from one nerve to another.
 *
 * Parameters
 * mobile:	The npc that will receive the command.
 * nerve_name:	String containing the name of the nerve to forward the event to (dictionary key).
 * mask:	The type of event the nerve should handle the forward as. (example: SYSEVENT_LEFTAREA)
 * data:	Data that the nerve will receive.
 * no_wake:	Optional wakeup flag:
 *		WAKEUP - Will stop the sleep script if it is running - Default.
 *		NOWAKE - Will not stop the sleep script if it is running.
 *
 * Return value
 * Result of SendEvent()
 *
 */
function AI_FowardEvent(mobile, nerve_name, mask, data, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_FWDNERVE;
	ev.+NerveName	:= nerve_name;
	ev.+mask	:= mask;
	ev.+data	:= data;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());

	return SendEvent(mobile, ev);
endfunction

/*
 * AI_Move(mobile, opponent, to_from, speed, no_wake, loop)
 *
 * Purpose
 * Commands an npc to move toward / away from an item or mobile.
 *
 * Parameters
 * mobile:	The npc that will receive the command.
 * object:	Item or mobile the npc will move away from/toward.
 * to_from:	Direction the npc will go:
 *		NEMOVE_TOWARD - Will make the npc move toward the object - Default
 *		NEMOVE_AWAY   - Will make the npc move away from the object.
 * speed:	Speed the npc will move at:
 *		NEMOVE_RUN  - NPC will run
 *		NEMOVE_WALK - NPC will walk
 * no_wake:	Optional wakeup flag::
 *		WAKEUP - Will stop the sleep script if it is running - Default.
 *		NOWAKE - Will not stop the sleep script if it is running.
 * loop:	Number of steps for the npc to take toward/away from the object.
 *		Note: Loop can be interrupted and end prematurely!
 *
 * Return value
 * Result of SendEvent()
 *
 */
function AI_Move(mobile, object, to_from:=NEMOVE_TOWARD, speed:=NEMOVE_RUN, no_wake:=WAKEUP, loop:=0)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_MOVE;
	ev.+source	:= object;
	ev.+direction	:= to_from;
	ev.+speed	:= speed;
	ev.+WakeUp	:= no_wake;
	ev.+loop	:= loop;
	ev.+process	:= GetProcess(GetPid());

	return SendEvent(mobile, ev);
endfunction

/*
 * AI_MoveXY(mobile, x, y, to_from, speed, no_wake, loop)
 *
 * Purpose
 * Commands an npc to move toward or away from an XY coordinate.
 *
 * Parameters
 * mobile:	The npc that will receive the command.
 * x:		X coordinate to move away from/toward
 * y:		Y coordinate to move away from/toward
 * to_from:	Direction the npc will go:
 *		NEMOVE_TOWARD - Will make the npc move toward the object - Default
 *		NEMOVE_AWAY   - Will make the npc move away from the object.
 * speed:	Speed the npc will move at:
 *		NEMOVE_RUN  - NPC will run
 *		NEMOVE_WALK - NPC will walk
 * no_wake:	Optional wakeup flag::
 *		WAKEUP - Will stop the sleep script if it is running - Default.
 *		NOWAKE - Will not stop the sleep script if it is running.
 * loop:	Number of steps for the npc to take toward/away from the object.
 *		Note: Loop can be interrupted and end prematurely!
 *
 * Return value
 * Result of SendEvent()
 *
 */
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

	return SendEvent(mobile, ev);
endfunction

/*
 * AI_SetOpponent(mobile, opponent, no_wake)
 *
 * Purpose
 * Places the npc into war mode and sets an opponent.
 *
 * Parameters
 * mobile:	The npc that will receive the command.
 * opponent:	Mobile reference that will be considered an opponent.
 * no_wake:	Optional wakeup flag:
 *		WAKEUP - Will stop the sleep script if it is running - Default.
 *		NOWAKE - Will not stop the sleep script if it is running.
 *
 * Return value
 * Result of SendEvent()
 *
 */
function AI_SetOpponent(mobile, opponent, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_OPPONENT;
	ev.+source	:= opponent;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());

	return SendEvent(mobile, ev);
endfunction

/*
 * AI_Sleep(mobile)
 *
 * Purpose
 * Instructs the npc to go into sleep mode - shuts down all nerves.
 *
 * Parameters
 * mobile:	The npc that will receive the command.
 *
 * Return value
 * Result of SendEvent()
 *
 */
function AI_Sleep(mobile)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_SLEEP;
	ev.+WakeUp	:= NOWAKE;
	ev.+process	:= GetProcess(GetPid());

	return SendEvent(mobile, ev);
endfunction

/*
 * AI_Speak(mobile, text, text_type, do_event, no_wake)
 *
 * Purpose
 * Commands the NPC to speak.
 *
 * Parameters
 * mobile:	The npc that will receive the command.
 * text:	The text the npc will speak.
 * text_type:	text_type for npc.em :
 *		SPEAK_TEXTTYPE_DEFAULT - Default
 *		SPEAK_TEXTTYPE_WHISPER
 *		SPEAK_TEXTTYPE_YELL
 * do_event:	Flags for sending a system event for speech to surrounding npcs.
 *		SPEAK_DOEVENT_DISABLE - Default
 *		SPEAK_DOEVENT_ENABLE
 * no_wake:	Optional wakeup flag:
 *		WAKEUP - Will stop the sleep script if it is running - Default.
 *		NOWAKE - Will not stop the sleep script if it is running.
 *
 * Return value
 * Result of SendEvent()
 *
 */
function AI_Speak(mobile, text, text_type:=SPEAK_TEXTTYPE_DEFAULT, do_event:=SPEAK_DOEVENT_DISABLE, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_SPEAK;
	ev.+text	:= text;
	ev.+texttype	:= text_type;
	ev.+doevent	:= do_event;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());

	return SendEvent(mobile, ev);
endfunction

/*
 * AI_StartNerve(mobile, nerve_name, script_name, data, no_wake)
 *
 * Purpose
 * Used to start a custom nerve up from within a nerve.
 *
 * Parameters
 * mobile:	The npc that will receive the command.
 * nerve_name:	String containing the name of the nerve (dictionary key).
 * script_name:	Path of the script to start.
 * data:	Data to be sent to the nerve once it starts.
 * no_wake:	Optional wakeup flag:
 *		WAKEUP - Will stop the sleep script if it is running - Default.
 *		NOWAKE - Will not stop the sleep script if it is running.
 *
 * Return value
 * Result of SendEvent()
 *
 */
function AI_StartNerve(mobile, nerve_name, script_name, data, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_STARTNERVE;
	ev.+name	:= nerve_name;
	ev.+script	:= script_name;
	ev.+data	:= data;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());

	return SendEvent(mobile, ev);
endfunction

/*
 * AI_Turn(mobile, turn_to, direction, no_wake)
 *
 * Purpose
 * Commands the NPC to face away from / toward an object.
 *
 * Parameters
 * mobile:	The npc that will receive the command.
 * turn_to:	item or moble reference to turn away from / toward.
 * direction:	Direction the npc will face:
 *		NETURN_TOWARD - Will make the npc turn toward the object - Default.
 		NETURN_AWAY   - Will make the npc turn away from the object.
 * no_wake:	Optional wakeup flag:
 *		WAKEUP - Will stop the sleep script if it is running - Default.
 *		NOWAKE - Will not stop the sleep script if it is running.
 *
 * Return value
 * Result of SendEvent()
 *
 */
function AI_Turn(mobile, turn_to, direction:=NETURN_TOWARD, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_TURN;
	ev.+source	:= turn_to;
	ev.+direction	:= direction;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());

	return SendEvent(mobile, ev);
endfunction

/*
 * AI_TurnXY(mobile, x, y, direction, no_wake)
 *
 * Purpose
 * Commands the NPC to face away from / toward a coordinate.
 *
 * Parameters
 * mobile:	The npc that will receive the command.
 * x:		X coordinate to turn away from / toward.
 * y:		Y coordinate to turn away from / toward.
 * direction:	Direction the npc will face:
 *		NETURN_TOWARD - Will make the npc turn toward the object - Default.
 		NETURN_AWAY   - Will make the npc turn away from the object.
 * no_wake:	Optional wakeup flag:
 *		WAKEUP - Will stop the sleep script if it is running - Default.
 *		NOWAKE - Will not stop the sleep script if it is running.
 *
 * Return value
 * Result of SendEvent()
 *
 */
function AI_TurnXY(mobile, x, y, direction:=NETURN_TOWARD, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_TURN_XY;
	ev.+x		:= x;
	ev.+y		:= y;
	ev.+direction	:= direction;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());

	return SendEvent(mobile, ev);
endfunction

/*
 * AI_WakeUp(mobile)
 *
 * Purpose
 * Sends an event to the npc causing its sleep script to end.
 *
 * Parameters
 * mobile:	The npc that will receive the command.
 *
 * Return value
 * Result of SendEvent()
 *
 */
function AI_WakeUp(mobile)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_WAKEUP;
	ev.+WakeUp	:= WAKEUP;
	ev.+process	:= GetProcess(GetPid());

	return SendEvent(mobile, ev);
endfunction

/*
 * AI_Wander(mobile, opponent, no_wake)
 *
 * Purpose
 * Commands the NPC to wander one step in a random direction.
 *
 * Parameters
 * mobile:	The npc that will receive the command.
 * no_wake:	Optional wakeup flag:
 *		WAKEUP - Will stop the sleep script if it is running - Default.
 *		NOWAKE - Will not stop the sleep script if it is running.
 * loop:	Number of times to attempt to wander.
 *		Note: Loop can be interrupted and end prematurely!
 *
 * Return value
 * Result of SendEvent()
 *
 */
function AI_Wander(mobile, no_wake:=WAKEUP, loop:=0)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_WANDER;
	ev.+WakeUp	:= no_wake;
	ev.+loop	:= CInt(loop);
	ev.+process	:= GetProcess(GetPid());

	return SendEvent(mobile, ev);
endfunction

/*
 * AI_WarMode(mobile, mode, no_wake)
 *
 * Purpose
 * Toggles warmode on the npc. Setting to 0 also clears the opponent.
 *
 * Parameters
 * mobile:	The npc that will receive the command.
 * mode:	0 - Takes the NPC out of warmode and clears the opponent - Default.
 *		1 - Places the npc into warmode.
 * no_wake:	Optional wakeup flag:
 *		WAKEUP - Will stop the sleep script if it is running - Default.
 *		NOWAKE - Will not stop the sleep script if it is running.
 *
 * Return value
 * Result of SendEvent()
 *
 */
function AI_WarMode(mobile, mode:=0, no_wake:=WAKEUP)
	var ev		:= struct;
	ev.+type	:= NPCEVENT_WARMODE;
	ev.+value	:= mode;
	ev.+WakeUp	:= no_wake;
	ev.+process	:= GetProcess(GetPid());

	return SendEvent(mobile, ev);
endfunction
