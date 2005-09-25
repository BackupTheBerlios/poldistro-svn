/*===============================================================
* Current Version
* SKILLS.INC - v1.0
* Updated 9/24/2005 6:52PM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;

/*
 * AP_GetSkill(mobile, skill_name)
 *
 * Purpose
 * Retrieves the base value of the skill plus its mod value.
 *
 * Parameters
 * mobile:	Mobile reference to retrieve the points from.
 * skill_name:	Name of the skill to retrieve the points for.
 *
 * Return value
 * Returns an integer.
 *
 */
function AP_GetSkill(who, skill_name)
	return AP_GetTrueSkill(who, skill_name)+AP_GetSkillMod(who, skill_name);
endfunction

/*
 * AP_GetTrueSkill(mobile, skill_name)
 *
 * Purpose
 * Retrieves the base value of the skill and turns it into a usable number.
 *
 * Parameters
 * mobile:	Mobile reference to retrieve the points from.
 * skill_name:	Name of the skill to retrieve the points for.
 *
 * Return value
 * Returns a double.
 *
 */
function AP_GetTrueSkill(who, skill_name)
	return CDbl(GetAttributeBaseValue(who, skill_name)) / 10.0;
endfunction

/*
 * AP_GetSkillMod(mobile, skill_name)
 *
 * Purpose
 * Retrieves the base value of the skill mod and turns it into a usable number.
 *
 * Parameters
 * mobile:	Mobile reference to retrieve the points from.
 * skill_name:	Name of the skill to retrieve the modifier points for.
 *
 * Return value
 * Returns a double.
 *
 */
function AP_GetSkillMod(who, skill_name)
	return CDbl(GetAttributeTemporaryMod(who, skill_name)) / 10.0;
endfunction

/*
 * AP_SetTrueSkill(mobile, skill_name, points)
 *
 * Purpose
 * Sets the value of the skill.
 * Example: AP_SetTrueSkill(mobile, "strength", 44.5)
 *
 * Parameters
 * mobile:	Mobile reference to set the points on.
 * skill_name:	Name of the skill to set the points on.
 * points:	Number of points to set the skill at.
 *
 * Return value
 * Returns a double.
 *
 */
function AP_SetTrueSkill(mobile, skill_name, points)
	SetAttributeBaseValue(mobile, skill_name, CInt(CDbl(points) * 10.0));
endfunction

/*
 * AP_SetSkillMod(mobile, skill_name, points)
 *
 * Purpose
 * Sets the modifier value for the skill.
 * Example: AP_SetSkillMod(mobile, "strength", -15.3)
 *
 * Parameters
 * mobile:	Mobile reference to set the modifier points on.
 * skill_name:	Name of the skill to set the modifier points on.
 * points:	Number of points to set the modifier skill at.
 *
 * Return value
 * Returns a double.
 *
 */
function AP_SetSkillMod(mobile, skill_name, points)
	SetAttributeTemporaryMod(mobile, skill_name, CInt(CDbl(points) * 10.0));
endfunction

/*
 * AP_SetSkillScript(attribute_name)
 *
 * Purpose
 * Gets the script that a skill uses.
 *
 * Parameters
 * attribute_name:	Name of the attribute to get the script for.
 *
 * Return value
 * Returns a string.
 *
 */
function AP_GetSkillScript(attribute_name)
	var cfg := AP_GetAttributeCfgElem(attribute_name);
	return cfg.Script;
endfunction

/*
 * AP_GetSkillStats(attribute_name)
 *
 * Purpose
 * Retrieves a dictionary from the attribute's config elem
 * Key is the stat name, inside is an array containing the settings for it.
 * dict["StatName"] => array{gain chance, award points dice}
 *
 * Parameters
 * attribute_name:	Name of the skill to retrieve stat settings for.
 *
 * Return value
 * Returns a dictionary.
 *
 */
function AP_GetSkillStats(attribute_name)
	var cfg_elem := AP_GetAttributeCfgElem(attribute_name);
	var stat_entries := GetConfigStringDictionary(cfg_elem, "StatCheck");
	foreach textline in (stat_entries)
		textline := SplitWords(textline);
		sleepms(2);
	endforeach
	
	return stat_entries;
endfunction

/*
 * AP_CheckSkillCap(mobile, skill_name)
 *
 * Purpose
 * Checks if a skill is greater than or equal to its maximum value in settings.cfg
 * If no skill_name is passed, it will check the totals.
 *
 * Parameters
 * mobile:		Mobile to check the skills on
 * stat_name:	Optional parameter - name of the skill to check.
 *
 * Return value
 * Returns 1 if skill(s) >= to the cap
 *
 */
function AP_CheckSkillCap(mobile, skill_name:="")
	var cfg_elem := AP_GetSettingsCfgElem("Skills");
	
	if ( skill_name )
		var cap := GetConfigReal(cfg_elem, skill_name);
		return ( AP_GetTrueSkill(mobile, skill_name) >= cap );
	else
		var total := 0.0;
		foreach attribute_name in ( AP_ListAttributesByType("Skill") )
			total := total + AP_GetTrueSkill(mobile, attribute_name);
			sleepms(2);
		endforeach
		
		return ( total >= GetConfigReal(cfg_elem, "TotalCap") );
	endif
endfunction
