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

/*
 * CheckStatsForSkill(mobile, skill_name)
 *
 * Purpose
 * Performs a stat check on all stats that are listed within a skill's attributes.cfg elem.
 *
 * Parameters
 * mobile:	Mobile to do the stat checks on.
 * skill_name:	Skill to get the stat advance list from.
 *
 * Return value
 * Returns 1
 *
 */
function CheckStatsForSkill(mobile, skill_name)
	var settings := AP_GetSettingsCfgElem("Stats");
	
	var next_check := CInt(GetObjProperty(mobile, "#LastStatGain"))+CInt(settings.GainWait);
	if ( next_check > ReadGameClock() )
		SkillDbgMsg(mobile, "Stat advance-wait timer has not yet expired.");
		return 0;
	endif
	
	foreach stat_entry in (AP_GetSkillStats(skill_name))
		var stat_name := _stat_entry_iter;
		var check_chance := stat_entry[1];
		var stat_mult := CDbl(RandomDiceRoll(stat_entry[2]));
		
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

/*
 * CheckStatAdvancement(mobile, stat_name, stat_mult)
 *
 * Purpose
 * Does an advancement check on a stat.
 *
 * Parameters
 * mobile:	Mobile to do the stat advancement check on.
 * stat_name:	Name of the stat to do the advancement check on.
 * stat_mult:	Multiplier to effect the chance of a gain. 
 *		(rolled dice from an attributes.cfg StatCheck entry)
 *
 * Return value
 * Returns 1
 *
 */
function CheckStatAdvancement(mobile, stat_name, stat_mult)
	if ( AP_CheckStatCap(mobile, stat_name) )
		SkillDbgMsg(mobile, "Stat cap for stat '"+stat_name+"' reached. No advance." );
		return 0;
	elseif ( AP_CheckStatCap(mobile) )
		SkillDbgMsg(mobile, "Total stat cap reached. No advance." );
		return 0;
	endif
	
	var settings := AP_GetSettingsCfgElem("Stats");
	var stat_cap := AP_GetStatCap(stat_name);
	var stat_value := AP_GetTrueStat(mobile, stat_name);
	var stat_left := stat_cap - stat_value; // Points until it is capped
	stat_mult := stat_mult * CDbl(settings.GainSpeed);
	
	SkillDbgMsg(mobile, "Stat Cap: "+stat_cap);
	SkillDbgMsg(mobile, "Stat Current: "+stat_value);
	SkillDbgMsg(mobile, "Left to cap: "+stat_left+" ->"+stat_cap+"-"+stat_value);
	
	var chance := ((stat_left * stat_mult) / (stat_cap / 2));
	if ( chance < 1.0 )
		chance := 1.0;
	endif
	SkillDbgMsg(mobile, "Chance: "+chance);
	SkillDbgMsg(mobile, "---");
	var random := RandomFloat(100.0);
	SkillDbgMsg(mobile, "Check %age: "+random);
	
	if ( random < chance )
		var advance := CDbl(0.1 + (0.1 * CDbl(CInt(chance / 12.5))));
		if ( advance > stat_left )
			advance := stat_left;
		elseif ( advance < 0.1 )
			advance := 0.1;
		endif

		var temp := stat_value+advance;
		while ( CInt(temp*10.0) == CInt(GetAttributeBaseValue(mobile, stat_name)) )
			// Kludge for an old core precision bug.
			// Makes sure it always goes up atleast 0.1.
			temp := temp+0.1;
			sleepms(10);
		endwhile	

		SkillDbgMsg(mobile, "Passed. Advance "+stat_name+": " + CStr(advance));
		AP_SetTrueStat(mobile, stat_name, temp);
		SetObjProperty(mobile, "#LastStatGain", ReadGameClock());
		
		return 1;
	endif
	
	SkillDbgMsg(mobile, "Failed. No advance.");
	return 0;
endfunction

/*
 * CheckSkillAdvance(mobile, stat_name, stat_mult)
 *
 * Purpose
 * Does an advancement check on a stat.
 *
 * Parameters
 * mobile:	Mobile to do the skill advancement check on.
 * skill_name:	Name of the skill to check.
 * award_diff:	Difficulty to use for advancement award.
 * pass_chance:	Chance of getting a gain check.
 * 
 *
 * Return value
 * Returns 1
 *
 */
function CheckSkillAdvance(mobile, skill_name, award_diff, pass_chance)
	if ( AP_CheckSkillCap(mobile, skill_name) )
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
		SkillDbgMsg(mobile, "Passed advance check: +"+(pass_chance - adv_check)+"%");
	else
		SkillDbgMsg(mobile, "Did not pass skill advance check.");
		return 0;
	endif
	
	SkillDbgMsg(mobile, "Skill Cap: "+skill_cap+"%");
	SkillDbgMsg(mobile, "Left to cap: "+limit_left+" ->"+skill_cap+"-"+true_skill);
	SkillDbgMsg(mobile, "Multiplier: "+multiplier);
	
	var int_chance := AP_GetStat(mobile, "Intelligence") / 2.0;
	var task_chance := (100.0 - award_diff) / 2.0;
	var chance := CInt((int_chance + task_chance) * multiplier);

	SkillDbgMsg(mobile, "INT gives "+int_chance+"%");
	SkillDbgMsg(mobile, "Task gives "+task_chance+"%");
	SkillDbgMsg(mobile, "Multiplier on "+(int_chance+task_chance)+" gives "+chance);
	SkillDbgMsg(mobile, "---");
	
	var check_roll := RandomInt(100);
	SkillDbgMsg(mobile, "Check %age: "+check_roll);
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
		
		SkillDbgMsg(mobile, "Passed. Advance "+skill_name+": " + advance);
		
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
