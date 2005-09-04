/*===============================================================
* Current Version
* EVENTID.INC - v1.0
* Updated 8/31/2005 5:50AM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

//
// * Custom brain AI event IDs
//
const NPCEVENT_MOVE				:= 0xA00003;	// Has NEMOVE_* helper constants
const NPCEVENT_OPPONENT				:= 0xA00004;	// Set New Opponent (.source)
const NPCEVENT_SPEAK				:= 0xA00005;	// Speak (.text)
const NPCEVENT_TURN				:= 0xA00006;	// Turn towards or away from an object
const NPCEVENT_WARMODE				:= 0xA00007;	// Set WarMode state (.value=0|1)
const NPCEVENT_ATTACK				:= 0xA0000A;	// Tell the npc to attack something
const NPCEVENT_MOVE_XY				:= 0xA0000B;	// Tell the NPC to move to coordinates
const NPCEVENT_TURN_XY				:= 0xA0000C;	// Tell the NPC to turn towards coordinates
const NPCEVENT_WANDER				:= 0xA0000D;	// Tell the npc to wander

const NPCEVENT_ENDNERVE				:= 0xA0000F;	// Tell the brain to stop a nerve.
const NPCEVENT_STARTNERVE			:= 0xA00010;	// Tell the brain to start a nerve.
const NPCEVENT_DONE				:= 0xA00011;	// Brain tells a nerve that its instruction is done.

const NPCEVENT_SLEEP				:= 0xA00012;	// Tell the brain to go to sleep.
const NPCEVENT_WAKEUP				:= 0xA00013;	// Tell the brain to wake up.

const NPCEVENT_FWDNERVE				:= 0xA00014;	// Tell the brain to forward an event to a nerve.

//
// * NPCEVENT_MOVE helper constants (.source = object)
//
const NEMOVE_WALK				:= 1;	// .speed (default)
const NEMOVE_RUN				:= 2;	// .speed
const NEMOVE_TOWARD 				:= 1;	// .direction (default)
const NEMOVE_AWAY				:= 2;	// .direction

//
// * NE_TURN helper constants
//
const NETURN_TOWARD				:= 1;
const NETURN_AWAY				:= 2;

//
// * AWAKEN CONSTANTS
// 
const WAKEUP					:= 0;
const NOWAKE					:= 1;

//
// * CLEAR THOUGHT CONSTANTS
//
const CLR_BRAIN					:= 1;
const CLR_NERVE					:= 2;
const CLR_BOTH					:= 3;

//
//* NPC.EM constants (only brain can access npc.em)
//
// Constants for texttype flags in the AI_Speak() function
const SPEAK_TEXTTYPE_DEFAULT			:= "default";
const SPEAK_TEXTTYPE_WHISPER			:= "whisper";
const SPEAK_TEXTTYPE_YELL			:= "yell";

// Constants for doevent flag in AI_Speak() function
const SPEAK_DOEVENT_DISABLE			:= 0x0;
const SPEAK_DOEVENT_ENABLE			:= 0x1;
