/*===============================================================
* Current Version
* SKILLS.INC - v1.0
* Updated 9/20/2005 2:20PM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;

/*
 * attributes_GetSkill(mobile, skill_name)
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
function attributes_GetSkill(who, skill_name)
	return attributes_GetTrueSkill(who, skill_name)+attributes_GetSkillMod(who, skill_name);
endfunction

/*
 * attributes_GetTrueSkill(mobile, skill_name)
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
function attributes_GetTrueSkill(who, skill_name)
	return CDbl(GetAttributeBaseValue(who, skill_name)) / 10.0;
endfunction

/*
 * attributes_GetSkillMod(mobile, skill_name)
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
function attributes_GetSkillMod(who, skill_name)
	return CDbl(GetAttributeTemporaryMod(who, skill_name)) / 10.0;
endfunction

/*
 * attributes_SetTrueSkill(mobile, skill_name, points)
 *
 * Purpose
 * Sets the value of the skill.
 * Example: attributes_SetTrueSkill(mobile, "strength", 44.5)
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
function attributes_SetTrueSkill(mobile, skill_name, points)
	SetAttributeBaseValue(mobile, skill_name, CInt(CDbl(points) * 10.0));
endfunction

/*
 * attributes_SetSkillMod(mobile, skill_name, points)
 *
 * Purpose
 * Sets the modifier value for the skill.
 * Example: attributes_SetSkillMod(mobile, "strength", -15.3)
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
function attributes_SetSkillMod(mobile, skill_name, points)
	SetAttributeTemporaryMod(mobile, skill_name, CInt(CDbl(points) * 10.0));
endfunction

/*
 * attributes_SetSkillScript(attribute_name)
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
function attributes_GetSkillScript(attribute_name)
	var cfg := attributes_GetAttributeCfgElem(attribute_name);
	return cfg.Script;
endfunction

/*
 * attributes_GetSkillStats(attribute_name)
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
function attributes_GetSkillStats(attribute_name)
	var cfg_elem := attributes_GetAttributeCfgElem(attribute_name);
	var stat_entries := GetConfigStringDictionary(cfg_elem, "StatCheck");
	foreach textline in (stat_entries)
		textline := SplitWords(textline);
		sleepms(2);
	endforeach
	
	return stat_entries;
endfunction
