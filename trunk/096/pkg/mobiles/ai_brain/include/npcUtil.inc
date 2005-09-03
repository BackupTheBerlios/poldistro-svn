/*===============================================================
* Current Version
* NPC_UTIL.INC - v1.0
* Updated 8/31/2005 4:23AM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

/*
 * NPC_ParseTemplateName(template_name)
 *
 * Purpose
 * Finds the appropriate npcdesc.cfg to load.
 * This enables npcs to be placed in packages and not just the ::npcdesc file.
 * ReadConfigFile(":*:npcdesc") does not work in this case because packaged npcs
 * have the package name at the begining of their .npctemplate member. Reading the
 * specific config file - helps to avoid possible elem name collisions.
 *
 * Parameters
 * template_name:	Name of the npc template to parse
 *
 * Return value
 * Returns struct .package .template
 *
 */
function NPC_ParseTemplateName(template_name)
	//Find positions of ":" characters
	var colon_a := Find(template_name, ":", 1);
	var colon_b := Find(template_name, ":", 2);

	var parsed := struct{"package", "template"};

	if ( !colon_a || !colon_b )
		//Not a complete package name - use default npcdesc.cfg
		parsed.package := "::";
		parsed.template := template_name;
	else
		parsed.package := template_name[colon_a, colon_b];
		parsed.template := template_name[colon_b+1, Len(template_name)];
	endif

	return parsed;
endfunction
