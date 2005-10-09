/* 
 * $Id$
 * 
 * Uhh what the fuck is this anyway?
 *
 */
 
use uo;
use os;

include ":gumps:gumps";

const MAXIMUM_LOSS := 0.20; //20% loss for 20 shortterm murders or more

function ResNow(mobile)
	var gump := GFCreateGump();
	GFClosable(gump, 0);
	GFGumpPic(gump, 300, 230, 2070);
	GFAddButton(gump, 330, 305, 2073, 2072, GF_CLOSE_BTN, 10);
	GFAddButton(gump, 400, 305, 2076, 2075, GF_CLOSE_BTN, 11);
	GFTextLine(gump, 332, 264, 40, "Resurrect Now?");
	
	var input := GFSendGump(mobile, gump);
	input := input[0];
	input := input-10;
	
	if ( !input )
		return 0;
	else
		return 1;
	endif
endfunction

function MurdererStatLoss(who)
	var shortc := GetObjProperty(who,"shortmurders");
	if( !shortc )
		return 0;
	endif
	
	if( shortc > 4 )
		var multiplier := CInt(shortc)/100.0;
		if(multiplier > MAXIMUM_LOSS)
			multiplier := MAXIMUM_LOSS;
		endif
		
		multiplier := 1.0 - multiplier;
		
		var str := GetStrength(who);
		var dex := GetDexterity(who);
		var inte := GetIntelligence(who);
	
		str := CInt(str * multiplier);
		dex := CInt(dex * multiplier);
		inte := CInt(inte * multiplier);
	
		SetBaseStrength(who,str);
		SetBaseDexterity(who,dex);
		SetBaseIntelligence(who,inte);
		SetHp(who, who.maxhp);
		SetStamina(who, who.maxstamina);
		SetMana(who, who.maxmana);
		
		var skillarray := GetObjProperty(who, "SkillArray");
		var newval, final;
		foreach entry in skillarray
			if((GetTrueEffectiveSkill(who, entry)	) > 0.0)
				newval:= (GetTrueEffectiveSkill(who, entry)	);
				final:=(newval * multiplier);
				SetBaseSkillBaseValue(who, entry, CInt(final * 10));
			endif
		endforeach
		SendSysMessage(who,"Thy body pays the price for thy sins.");
	endif
endfunction