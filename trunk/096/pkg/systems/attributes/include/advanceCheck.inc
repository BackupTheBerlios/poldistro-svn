// $Id$

/*===============================================================
* Current Version
* ADVANCECHECK.INC - v1.0
* Updated 9/28/2005 8:29PM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;
use os;
use util;

//function CheckStatAdvancement(mobile, stat_name)
//	return 1;
//endfunction

function CheckSkillAdvance(mobile, skill_name, award_diff, pass_chance, pass_success)
	if ( pass_success < 0 )
		SkillDbgMsg(mobile, "No skill advancement - skill check was not successful.");
		return 0;
	elseif ( AP_CheckSkillCap(mobile, skill_name) )
		SkillDbgMsg(mobile, "Skill cap for attribute '"+skill_name+"' already reached.");
		return 0;
	elseif ( AP_CheckSkillCap(mobile) )
		SkillDbgMsg(mobile, "Total skill cap already reached.");
		return 0;
	endif
	
	var skill_cap := AP_GetSkillCap(skill_name);
	var true_skill := AP_GetTrueSkill(mobile, skill_name);
	var limit_left := CDbl(skill_cap - true_skill);
	var adv_check := RandomInt(100)+1;
	
	var settings := AP_GetSettingsCfgElem("Skills");
	var multiplier := CDbl(settings.GainSpeed);
			
	if ( true_skill < CDbl(settings.FreeGainUntil) )
		SkillDbgMsg(mobile, "Skill is < "+CDbl(settings.FreeGainUntil)+". Allowing for advancement");
	elseif ( true_skill+Cdbl(settings.TooEasy) > award_diff )
		// Was it too easy? If so, return.
		SkillDbgMsg(mobile, "No challenge. No advance. True skill ("+true_skill+"-20) > "+award_diff);
		return 0;
	elseif ( adv_check <= pass_chance )
		SkillDbgMsg(mobile, "Passed advance check: +"+CStr(pass_chance - adv_check)+"%");
	else
		SkillDbgMsg(mobile, "Did not pass skill advance check.");
		return 0;
	endif
	
	SkillDbgMsg(mobile, "Skill Cap: "+CStr(skill_cap)+"%");
	SkillDbgMsg(mobile, "Left to cap: "+CStr(limit_left)+" ->"+skill_cap+"-"+true_skill);
	SkillDbgMsg(mobile, "Multiplier: "+CStr(multiplier));
	
	var int_chance := AP_GetStat(mobile, "Intelligence") / 2.0;
	var task_chance := (100.0 - award_diff) / 2.0;
	var chance := CInt((int_chance + task_chance) * multiplier);

	SkillDbgMsg(mobile, "INT gives "+CStr(int_chance)+"%");
	SkillDbgMsg(mobile, "Task gives "+CStr(task_chance)+"%");
	SkillDbgMsg(mobile, "Multiplier on "+CStr(int_chance+task_chance)+" gives "+CStr(chance));
	SkillDbgMsg(mobile, "---");
	
	var check_roll := RandomInt(100);
	SkillDbgMsg(mobile, "Check %age: "+CStr(check_roll));
	if ( check_roll < chance )
		var advance := 0.1;
		if ( award_diff > true_skill )
			advance := CDbl(0.1 * (1.0 + CInt((award_diff - true_skill) / 5.0)));
		endif
		if ( advance > limit_left )
			advance := limit_left;
		elseif ( advance < 0.1 )
			advance := 0.1;
		endif
		
		SkillDbgMsg(mobile, "Passed. Advance "+skill_name+": " + CStr(advance));
		
		var temp := true_skill+advance;
		while ( CInt(temp*10.0) == CInt(GetAttributeBaseValue(mobile, skill_name)) )
			// Kludge for an old core precision bug.
			// Makes sure it always goes up atleast 0.1.
			temp := temp+0.1;
			sleepms(10);
		endwhile
		AP_SetTrueSkill(mobile, skill_name, temp);
		
		return 1;
	endif
	
	SkillDbgMsg(mobile, "Failed advancement check. No advance.");
	
	return 0;
endfunction

/*
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
	
	if(points != 0)
      		points  := points * ((1000-temp_chance) / 1000);
    	endif
    	
	return 1;
endfunction
*/