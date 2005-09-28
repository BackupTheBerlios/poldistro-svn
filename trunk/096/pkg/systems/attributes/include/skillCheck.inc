// $Id$

/*===============================================================
* Current Version
* SKILLCHECK.INC - v1.0
* Updated 9/24/2005 6:52PM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;
use os;
use util;
use cfgfile;

include ":attributes:attributes";
include ":attributes:settings";

const ADV_SKILL		:= 1;
const ADV_STATS		:= 2;
const ADV_ALL		:= ADV_SKILL+ADV_STATS; // 3
const ADV_DISABLE	:= 4; // 4 - because if flags is 0, we want the default to be ADV_ALL.

var g_skill_debug	:= 0;


/*
 * SkillCheck(mobile, attrib_name, difficulty, award_points, advance_flags)
 *
 * Purpose
 * Performs a skill check on an attribute and performs skill and stat advancements.
 * <= 0 means the skill check failed > 0 means it was successful.
 *
 * Parameters
 * mobile:		Mobile reference to do the skill check for.
 * attribute_name:	Name of the attribute to perform the check on.
 * award_points:	Determines the amount of (if any) skill gain.
 * advance_flags:	Controls the turning on/off of stat and skill advancements for the check.
 *
 * Return value
 * Returns > 0 if the skill check was successful
 *
 */
function SkillCheck(mobile, attrib_name, difficulty, award_points:=0, advance_flags:=ADV_ALL)
	if ( mobile.dead )
		SendSysMessage(mobile, "You can't use skills while dead.");
		return -100;
	elseif ( GetObjProperty(mobile, "DisableSkills") )
		SendSysMessage(mobile, "Your skills are disabled.");
		return -100;
	elseif ( GetObjProperty(mobile, "NoGains") )
		advance_flags := ADV_DISABLE;
	endif
	
	var advance_skill := advance_flags & ADV_SKILL;
	var advance_stats := advance_flags & ADV_STATS;
	
	// Global skill-debug ( for SkillDbgMsg() )
	g_skill_debug := (GetObjProperty(mobile,"SkillDebug") != error);
	
	return 1;
endfunction

function CheckSkillAdvance(mobile, attribute, award_points)
	if ( AP_CheckSkillCap(mobile, attribute) )
		return error{"errortext":="Skill cap for attribute '"+attribute+"' already reached."};
	elseif ( AP_CheckSkillCap(mobile) )
		return error{"errortext":="Total skill cap already reached."};
	endif
	
	var skill_amt := AP_GetTrueSkill(mobile, attribute);
	var free_gain := CDbl(AP_GetSettingsCfgElem("Skills").FreeGainUntil);
	if ( skill_amt < free_gain )
		//Increase 0.1 if < free gain
		AP_SetTrueSkill(mobile, attribute, skill_amt+0.1);
	endif
	
	
	return 1;
endfunction
	

/*
 * SkillDbgMsg(mobile, message)
 *
 * Purpose
 * Checks to see if it should send a skill debug message to a mobile.
 *
 * Parameters
 * mobile:	Mobile to send the messages to.
 * message:	Debug message.
 *
 * Return value
 * Returns 1
 *
 */
function SkillDbgMsg(mobile, message)
	if ( g_skill_debug )
		SendSysMessage(mobile, "Skill Debug: "+message);
	endif
	
	return 1;
endfunction


//Cdbl(Pow(2.0, Cint(basevalue/100))* 10.24);