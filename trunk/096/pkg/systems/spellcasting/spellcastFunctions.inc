
function mobspellcast(me, circle)
  var diff, points, umana;
  // replace case with cfg pulls
  case(circle)
    1:   diff := 10;     points :=  20;    umana :=   4;
    2:   diff := 20;     points :=  40;    umana :=   6;
    3:   diff := 30;     points :=  80;    umana :=   9;
    4:   diff := 50;     points := 100;    umana :=  11;
    5:   diff := 60;     points := 130;    umana :=  14;
    6:   diff := 70;     points := 160;    umana :=  20;
    7:   diff := 85;     points := 190;    umana :=  40;
    8:   diff := 95;     points := 210;    umana :=  50;
  endcase
  if(umana > GetMana(me))
    return 0;
  endif
  if(CheckHands(me))
    if(CheckSkill(me, SKILLID_MAGERY, (diff - 10), points))
      SetMana(me, GetMana(me)-umana);
      return 1;
    else
      return 0;
    endif
  endif
endfunction

function CheckHands(who)
  var hand1 := (GetEquipmentByLayer(who, 1));
  var hand2 := (GetEquipmentByLayer(who, 2));
  if(hand1)
    if(hand1.graphic != 0x0efa)
      SendSysMessage(who,"You can't cast spells with things in your hands.", 3, 40);
      return 0;
    endif
  endif
  if(hand2)
    if(hand2.graphic != 0x0efa)
      SendSysMessage(who,"You can't cast spells with things in your hands.", 3, 40);
      return 0;
    endif
  endif
  return 1;
endfunction


// Function getPointValue, to vary the value of the spellcasting by how
// challenging it is to the caster
// I'm not convinced all of it is necessary, but it was in the old system, so here it is.
function getPointValue(caster, points, diff, skill)
  skill := GetEffectiveSkill(caster, skill);
  if (skill > (diff - 20))
    if ((skill - diff) <= 5)
      return points;
    elseif ((skill - diff) <= 10)
      return (points * 3 / 4);
    elseif ((skill - diff) <= 15)
      return (points / 2);
    elseif ((skill - diff) <= 20)
      return (points / 4);
    else
      return 0;
    endif
  endif
endfunction

function HasRegs( byref caster, byref thecfg, byref spellid )
  var theSpell := FindConfigElem(thecfg, spellid);
  var regsArray := GetConfigStringArray(theSpell, "Reagent");
  foreach reg in regsArray
    reg := GetObjtypeByName(reg);
    if (!FindSubstance(caster.backpack, reg, 1))
      return 0;
    endif
  endforeach
  return 1;
endfunction

