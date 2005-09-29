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

function CheckStatsForSkill(mobile, skill_name)
	var settings := AP_GetSettingsCfgElem("Stats");
	
	var next_check := CInt(GetObjProperty(mobile, "#LastStatGain"))+CInt(settings.GainWait);
	if ( next_check > ReadGameClock() )
		SkillDbgMsg(mobile, "Stat advance-wait timer has not yet expired.");
		return 0;
	endif
	
	var stat_mult := settings.GainSpeed;
	foreach stat_entry in (AP_GetSkillStats(skill_name))
		var stat_name := _stat_entry_iter;
		var check_chance := stat_entry[1];
		var stat_mult := RandomDiceRoll(stat_entry[2]);
		
		var roll := RandomInt(100)+1;
		
		if ( roll <= check_chance )
			SkillDbgMsg(mobile, "("+roll+" < "+check_chance+"%) Checking stat "+stat_name);
			CheckStatAdvancement(mobile, stat_name, stat_mult);
		else
			SkillDbgMsg(mobile, "("+roll+" > "+check_chance+"%) skipping stat check for "+stat_name);
		endif
		sleepms(10);
	endforeach
	
	return 1;
endfunction


function CheckStatAdvancement(mobile, stat_name, stat_mult)
		
endfunction

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
	elseif (  DifficultyTooEasy(true_skill, award_diff) )
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
