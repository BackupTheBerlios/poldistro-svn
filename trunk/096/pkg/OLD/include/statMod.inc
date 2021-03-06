use uo;
use util;

include ":attributes:attributes";

function GetModAmount(magery)
  var mod_amount := CInt(RandomInt(3) +(magery/10));
  if(mod_amount > 10)
    mod_amount := 10;
  endif
  return mod_amount;
endfunction

function GetModDuration(magery)
  var duration := CInt(60 +((magery / 30) * 60));
  return(duration);
endfunction

function CanMod(who, stat)
  var mod;
  case(stat)
    "str": mod := "#ss";
    "dex": mod := "#dd";
    "int": mod := "#ii";
    "p"  : mod := "#pp";
    "ar" : mod := "#ar";
  endcase
  if(GetObjProperty(who, mod))
    return 0;
  else
    return 1;
  endif
endfunction

function DoTempMod(who, stat, amt, duration)
  var mod;
  case(stat)
    "str":  mod := "#ss";  AP_SetStatMod(who, "Strength", AP_GetStatMod(who, "Strength") + amt);
    "dex":  mod := "#dd";  AP_SetStatMod(who, "Dexterity", AP_GetStatMod(who, "Dexterity") + amt);
    "int":  mod := "#ii";  AP_SetStatMod(who, "Intelligence", AP_GetStatMod(who, "Intelligence") + amt);
    "ar" :  mod := "#ar";  who.ar_mod           := who.ar_mod + amt;
	"p"  :  mod := "#pp";  who.setParalyzed(1);
  endcase
  SetObjProperty(who,mod,1);
  var parms := {};
  parms[2] := who;
  parms[1] := stat;
  parms[3] := amt;
  parms[4] := duration;
  parms[5] := who.serial;
  start_script("::/misc/unmod", parms);
endfunction