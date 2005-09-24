/*===============================================================
* Current Version
* SKILLCHECK.INC - v1.0
* Updated 9/24/2005 12:34AM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;
use os;
use util;
use cfgfile;

include ":attributes:include/attributes";

const ADV_SKILL		:= 1;
const ADV_STATS		:= 2;
const ADV_ALL		:= ADV_SKILL+ADV_STATS; // 3
//Set to 4 because if it was 0, it would default to ADV_ALL.
const ADV_DISABLE	:= 4;

var g_skill_debug	:= 0;

function SkillCheck(mobile, attrib_name, difficulty, award_points:=0, advance_flags:=ADV_ALL)
	if ( mobile.dead )
		SendSysMessageEX(mobile, "You can't use skills while dead.");
		return -100;
	elseif ( GetObjProperty(mobile, "DisableSkills") )
		SendSysMessageEX(mobile, "Your skills are disabled.");
		return -100;
	elseif ( GetObjProperty(mobile, "NoGains") )
		advance := ADV_DISABLE;
	endif
	
	var advance_skill := advance & ADV_SKILL;
	var advance_stats := advance & ADV_STATS;
	
	// Global skill-debug ( for SkillDbgMsg() )
	g_debug := (GetObjProperty(mobile,"SkillDebug") != error);
	
endfunction

