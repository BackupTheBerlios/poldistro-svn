use uo;
use os;
use util;
use cfgfile;

include ":attributes:attributes";
include "include/client";

const MAX_RANGE	:= 16;

function SpellDebug(who, text)
	if ( who.cmdlevel )
		SendSysMessage(who, text, SSM_INFO_DEBUG);
	endif
endfunction

function UseMana(who, amount)
	if ( GetManaPoints(who) >= amount )
		SetManaPoints(who, GetManaPoints(who)-amount);
		return 1;
	else
		return 0;
	endif
endfunction

function Reflection(who, targ, spell_strength, info)
	// Lower targ's defense
	// Apply some of spell_strength to target if reflected.
	// Lower spell_strength by how much was not reflected.
	// Start the spell again and point it at who from targ.
	
endfunction

function SpellTarget(byref who, byref npctarget:=0, prompt := "Select a target.", ops:=TGTOPT_CHECK_LOS+TGTOPT_NEUTRAL)
	var x := who.x;
	var y := who.y;
	who.hidden := 0;
	
	if ( npctarget )
		return npctarget;
	elseif ( who.npctemplate )
		return;
	endif
	
	SendSysMessage(who, prompt);
	
	var targ := Target(who, ops);
	if ( Distance(who, targ) > MAX_RANGE )
		SendSysMessage(who, "That is too far away.");
		return 0;
	elseif ( who.x == x && who.y == y )
		return targ;
	else
		SendSysMessage(who, "You break your concentration.");
		return 0;
	endif
endfunction

function SpellTargetCoordinates(byref who, byref npctarget:=0, prompt := "Select a target.", range := MAX_RANGE)
	var x := who.x;
	var y := who.y;
	who.hidden := 0;
	
	if ( npctarget )
		return npctarget;
	elseif ( who.npctemplate )
		return;
	endif
	
	SendSysMessage(who, prompt);
	var targ := TargetCoordinates(who);
	if ( !targ )
		SendSysMessage(who, "Cancelled.");
		return 0;
	elseif ( CoordDistance(who.x, who.y, targ.x, targ.y) > range )
		SendSysMessage(who, "That is too far away.");
		return 0;
	elseif ( who.x == x && who.y == y )
		return targ;
	else
		SendSysMessage(who, "You lose concentration.");
		return 0;
	endif
endfunction

function GetSpellPoints(mage, targ, points)
	var mage_skill := GetSkill(mage, "Magery");
	var defense := GetSkill(targ, "Magic_Resistance");

	// Failed MR check results in only half your resistance being used!
	if ( SkillCheck(targ, "Magic_Resistance", -1) < 0 )
		defense := CInt(defense / 2);
	endif

	// Old formulas
	// CInt(points * (mage_skill - defense) / 100);
	// CInt(points * ((mage_skill * 1.3) - defense) / ( mage_skill * 1.3 ))
	var effect_level := CInt(points * (mage_skill-defense) / mage_skill );
	return effect_level;
endfunction

function GetSpellWords(spell_name)
	var cfg := ReadConfigFile(":magic:configs/spell_info");
	if ( cfg.errortext )
		return "Error - GetSpellWords(). Unable to open :magic:configs/spell_info.cfg ->"+cfg.errortext;
	endif
	
	cfg := cfg[spell_name];
	if ( cfg.errortext )
		return "Error - GetSpellWords(). Unable to find elem ["+spell_name+"] ->"+cfg.errortext;
	endif
	
	return cfg.SpellWords;
endfunction

function ReleaseScript(pid)
	var process := GetProcess(pid);
	process.SendEvent("done");
endfunction
