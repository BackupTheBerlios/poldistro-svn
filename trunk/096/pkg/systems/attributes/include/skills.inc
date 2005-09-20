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
 * AF_GetSkill(mobile, skill_name)
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
function AF_GetSkill(who, skill_name)
	return AF_GetTrueSkill(who, skill_name)+AF_GetSkillMod(who, skill_name);
endfunction

/*
 * AF_GetTrueSkill(mobile, skill_name)
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
function AF_GetTrueSkill(who, skill_name)
	return CDbl(GetAttributeBaseValue(who, skill_name)) / 10.0;
endfunction

/*
 * AF_GetSkillMod(mobile, skill_name)
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
function AF_GetSkillMod(who, skill_name)
	return CDbl(GetAttributeTemporaryMod(who, skill_name)) / 10.0;
endfunction

/*
 * AF_SetTrueSkill(mobile, skill_name, points)
 *
 * Purpose
 * Sets the value of the skill.
 * Example: AF_SetTrueSkill(mobile, "strength", 44.5)
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
function AF_SetTrueSkill(mobile, skill_name, points)
	SetAttributeBaseValue(mobile, skill_name, CInt(CDbl(points) * 10.0));
endfunction

/*
 * AF_SetSkillMod(mobile, skill_name, points)
 *
 * Purpose
 * Sets the modifier value for the skill.
 * Example: AF_SetSkillMod(mobile, "strength", -15.3)
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
function AF_SetSkillMod(mobile, skill_name, points)
	SetAttributeTemporaryMod(mobile, skill_name, CInt(CDbl(points) * 10.0));
endfunction
