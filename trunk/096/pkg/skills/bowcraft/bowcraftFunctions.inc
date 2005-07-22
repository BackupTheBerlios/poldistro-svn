
function CarveLogs(who, blade, logs)
  if(logs.movable == 0)
    SendSysMessage(who, "You cannot use those logs.");
    return;
  endif
  if((!Accessible(who, logs)) or (!CheckLineOfSight(who, logs)) or (dist(who, logs) > 2))
    SendSysMessage(who, "You cannot use that.");
    return;
  endif
  if(!logs.container)
    if(Distance(who, logs) > 2)
      SendSysMessage(who, "That is too far away.");
      return;
    endif
  endif
  var creatable := CreatableObjects(who, blade, logs);
  var selection := SelectMenuItem2(who, "BowcraftCarving");
  if(!selection)
    return;
  endif
  var what := selection.objtype;
  if(!Accessible(who, logs))
    SendSysMessage(who, "I can't access the logs to make that.");
    return;
  endif
  var objectconfig := FindConfigElem(bowcraftconfigfile, what);
  if(!objectconfig)
    return;
  endif
  var material := CInt(GetConfigString(objectconfig, "Material"));
  if(material > logs.amount)
    SendSysMessage(who, "You don't have enough logs to make that.");
    return;
  endif
  var difficulty := GetConfigInt(objectconfig, "Difficulty");
  var pointvalue := GetConfigInt(objectconfig, "PointValue");
  var bow := 0;
  Detach();
  PlaySoundEffect(who, 0x5a);
  PerformAction(who, 0x021);
  sleep(2);
  PlaySoundEffect(who, 0x5a);
  PerformAction(who, 0x021);
  sleep(2);
  PlaySoundEffect(who, 0x5a);
  PerformAction(who, 0x021);
  sleep(2);
  PlaySoundEffect(who, 0x5a);
  PerformAction(who, 0x021);
  sleep(2);
  if(CheckSkill(who, SKILLID_BOWCRAFT, difficulty, pointvalue))
    if(what == UOBJ_SHAFTS)
      var amt := logs.amount;
      if(DestroyItem(logs))
        CreateItemInBackpack(who, what, amt);
        CheckToolWear (who, blade, SKILLID_BOWCRAFT);
        SendSysMessage(who, "You create some shafts and place them in your pack." );
      endif
    elseif (what == UOBJ_BOW)
      if(SubtractAmount(logs, material))
        bow := CreateItemInBackpack(who, what);
        CheckToolWear (who, blade, SKILLID_BOWCRAFT);
        SendSysMessage(who, "You create a bow and place it in your pack.");
        SetName(bow, "a bow");
      endif
    elseif (what == UOBJ_XBOW)
      if(SubtractAmount(logs, material))
        bow := CreateItemInBackpack(who, what);
        CheckToolWear (who, blade, SKILLID_BOWCRAFT);
        SendSysMessage(who, "You create a crossbow and place it in your pack.");
        SetName(bow, "a crossbow");
      endif
    elseif (what == UOBJ_HEAVY_XBOW)
      if(SubtractAmount(logs, material))
        bow := CreateItemInBackpack(who, what);
        CheckToolWear (who, blade, SKILLID_BOWCRAFT);
        SendSysMessage(who, "You create a heavy crossbow and place it in your pack.");
        SetName(bow, "a heavy crossbow");
      endif
    else
      SendSysMessage(who, "I don't know how to make that.");
      return;
    endif
    if((RandomInt(CInt(GetEffectiveSkill(who,SKILLID_BOWCRAFT)) + 1) > (difficulty + 20)) && (bow != 0))
      setquality(who, bow);
//      var skill := GetEffectiveSkill(who, SKILLID_BOWCRAFT);
//      ExceptionalFameMod(who, skill, difficulty, pointvalue);
    endif
  else
    SubtractAmount(logs, (RandomInt(5) + 1));
    SendSysMessage(who, "You destroy some logs.");
  endif
endfunction

function setquality(who, bow)
  var tname := TruncateArticle(bow.name);
  if(CInt(GetEffectiveSkill(who, SKILLID_BOWCRAFT)) >= 99)
    bow.name := "an exceptional " + tname + " [crafted by " + who.name + "]";
  else
    bow.name := "an exceptional " + tname;
  endif
  bow.quality := bow.quality + 0.2;
  bow.hp := bow.maxhp;
  SendSysMessage(who, "You created an exceptional item.");
endfunction

function CreatableObjects( who, blade, logs )
  var objtypes := GetMenuObjTypes( "BowcraftCarving" );
  objtypes := ApplyConstraint( objtypes, bowcraftconfigfile, "material", GetAmount(logs) );
  return objtypes;
endfunction

