/*===============================================================
* Current Version
* ATTRIBUTES_EX.INC - v1.0
* Updated 9/20/2005 11:42AM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

include ":attributes:include/attributes";

/*
 * AF_SkillIDToAttributeName(skill_number)
 *
 * Purpose
 * Gets the name of the attribute that is associated with a skill number.
 * Skills.cfg -> Attributes.cfg
 *
 * Parameters
 * skill_number:	Skill ID to convert
 *
 * Return value
 * Returns a string.
 *
 */
function AF_IDToAttributeName(skill_number)
	var skills_cfg := ReadConfigFile(":*:skills");
	var cfg_elem := skills_cfg[skill_number];
	
	return elem.Name;
endfunction

/*
 * AF_AttributeNameToSkillID(skill_number)
 *
 * Purpose
 * Gets the skill number (ID) that an attribute name is associated with.
 * Attributes.cfg -> Skills.cfg
 *
 * Parameters
 * attribute_name:	Attribute name to convert.
 *
 * Return value
 * Returns an integer.
 *
 */
function AF_AttributeNameToSkillID(attribute_name)
	var cfg_elem := AF_GetAttributeElem(attribute_name);
	
	return cfg_elem.SkillId;
endfunction