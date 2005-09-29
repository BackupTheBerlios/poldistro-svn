// $Id$

/*===============================================================
* Current Version
* STATCHECK.INC - v1.0
* Updated 9/28/2005 3:48PM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

function CheckStatAdvancement(mobile, stat_name)
	// Get the stat and work out the advancement chance (biased against max stat)
	var stat_value := CDbl(GetTrueStat(mobile, stat_name));
	var stat_cap := 6000.0;
	if ( !mobile.npctemplate )
		stat_cap := CDbl(GetStatCap(mobile, stat_name));
		if ( stat_value >= stat_cap )
			SkillDbgMsg(mobile, "stat_cap reached. No advance." );
			return 0;
		endif
	endif

	var stat_start := 0.0;
	if ( !mobile.npctemplate )
		stat_start := CDbl(GetStatStart(mobile, stat_name));
	endif
	var stat_diff := CDbl(stat_cap - stat_start);
	var stat_left := CDbl(stat_cap - stat_value);

	SkillDbgMsg(mobile, "Stat Start: "+CStr(stat_start));
	SkillDbgMsg(mobile, "Stat Cap: "+CStr(stat_cap));
	SkillDbgMsg(mobile, "Stat Diff: "+CStr(stat_diff));
	SkillDbgMsg(mobile, "---");
	SkillDbgMsg(mobile, "Stat Current: "+CStr(stat_value));
	SkillDbgMsg(mobile, "Left to cap: "+CStr(stat_left)+" ->"+stat_cap+"-"+stat_value);

	var chance := CDbl(stat_left * stat_mult / stat_diff);
	if ( chance < 1.0 )
		chance := 1.0;
	endif

	SkillDbgMsg(mobile, "Chance: "+CStr(chance));
	SkillDbgMsg(mobile, "---");

	var random := CDbl(RandomFloat(100.0));
	SkillDbgMsg(mobile, "Check %age: "+CStr(random));
	if ( random < chance )
		var advance := CDbl(0.1 + (0.1 * CDbl(CInt(chance / 12.5))));
		if ( advance > stat_left )
			advance := stat_left;
		elseif ( advance < 0.1 )
			advance := 0.1;
		endif

		var temp := stat_value+advance;
		while ( CInt(temp*10.0) == CInt(GetRawStat(mobile, stat_name)) )
			//Makes sure you always go up atleast .1
			temp := temp+0.1;
			sleepms(10);
		endwhile

		SkillDbgMsg(mobile, "Passed. Advance "+stat_name+": " + CStr(advance));
		SendSysMessageEX(mobile, "You gain a little " + stat_name + " from your actions.", SSM_HELPFUL);
		SetTrueStat(mobile, stat_name, temp);

		SetObjProperty(mobile, "#LastStatGain", ReadGameClock());
		return 1;
	endif
	SkillDbgMsg(mobile, "Failed. No advance.");
	return 0;
endfunction