////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  name:    repair.inc
//  version: 2.0
//  author:  MuadDib
//
//  Purpose: Contains all the central Repair functions involving repairing items, using repair
//           deeds, etc.
//
//  Changes: Sept 14, 2005 - Updated repair_item() for swing counter (new crafting ready)
//                         - Added CreateRepairDeed() Function with support for the following skills:
//                           Smithy, Bowcraft, Carpenter, Tailor (new crafting ready)
//                         - Moved repair_this() function to the include (new crafting ready)
//                         - Moved s_weapon_armor() to the include (new crafting ready)
//                         - Moved resmelt() to include (New crafting ready)
//
////////////////////////////////////////////////////////////////////////////////////////////////////

include ":attributes:attributes";

function repair_item(character, what, skillid )
  var maxhp;
  maxhp := what.maxhp;
  maxhp := cint(maxhp * what.quality);
  var thehp := what.hp;
  var damaged := maxhp - thehp;
  var hisskill := GetEffectiveSkill(character, skillid);
  var damageamount := 0.0;
  damageamount := (125 -  hisskill)/3000.0;
  if(what.hp == what.maxhp)
    SendSysMessage(character, "That item is not damaged.");
    return;
  endif
  if((what.hp <= 0) || (what.quality <= 0.1) || (!what.quality))
    SendSysMessage(character, "The brittle material breaks when you handle it");
    DestroyItem(what);
    return;
  endif
  if(what.quality <= damageamount)
    SendSysMessage(character, "The brittle material breaks when you handle it");
    DestroyItem(what);
    return;
  endif
  what.quality := what.quality - damageamount;
  if((what.hp <= 0) || (what.quality <= 0.1) || (!what.quality))
    SendSysMessage(character, "The brittle material breaks when you handle it");
    DestroyItem(what);
    return;
  endif
  if (CheckSkill(character, skillid, cint(damaged / 3), 0))
    var repaired_amount := cint( ((randomint(hisskill) + 1))/2);
    if (damaged == 1)
      repaired_amount := 1;
    endif
    if (thehp + repaired_amount > what.maxhp)
      what.hp := what.maxhp;
      EraseObjProperty(what, "swings");
      SendSysMessage(character, "You  repair the item completely");
    else
      what.hp := thehp + repaired_amount;
      SendSysMessage(character, "You successfully repair some of the damage");
    endif
    if ((what.hp <= 0) || (what.quality <= 0.1) || (!what.quality))
      SendSysMessage(character, "The brittle material breaks when you handle it");
      DestroyItem(what);
      return;
    endif
  else
    var damage_amount := randomint(10);
    if (thehp <= damage_amount)
      DestroyItem(what);
      SendSysMessage(character, "You fail and destroy the item");
    endif
    thehp := thehp - damage_amount;
    what.hp := thehp;
    if(randomint(2) == 1)
      what.quality := what.quality - (damaged/100);
    endif
    if(thehp <= 0)
      DestroyItem(what);
      SendSysMessage(character, "You fail and destroy the item");
    else
      SendSysMessage(character, "You fail and damage the item");
    endif
    if ((what.hp <= 0) || (what.quality <= 0.1) || (!what.quality))
      SendSysMessage(character, "The brittle material breaks when you handle it");
      DestroyItem(what);
      return;
    endif
  endif
endfunction

function CreateRepairDeed(who, scroll, skillid)

  var type, title, color;
  case(CInt(skillid))
     7: type := "Blacksmith"; color := CInt(2107);
     8: type := "Bowyer"; color := CInt(2116);
    11: type := "Carpenter"; color := CInt(2113);
    34: type := "Tailor"; color := CInt(2128);
  endcase
  var ramt := GetEffectiveSkill(who, skillid);
  if(ramt < 50)
    SendSysMessage(who, "You must be at least apprentice level to create a repair service contract.");
    return;
  endif
  if(ramt < 60 )
    title := "A repair service contract from an Apprentice " + type;
  elseif(ramt < 70 )
    title := "A repair service contract from a Journeyman " + type;
  elseif(ramt < 80 )
    title := "A repair service contract from an Expert " + type;
  elseif(ramt < 90 )
    title := "A repair service contract from an Adept " + type;
  elseif(ramt < 100 )
    title := "A repair service contract from a Master " + type;
  elseif(ramt < 110 )
    title := "A repair service contract from a Grandmaster " + type;
  elseif(ramt < 120 )
    title := "A repair service contract from an Elder " + type;
  elseif(ramt < 130 )
    title := "A repair service contract from a Legendary " + type;
  endif
  type := lower(type);
  var ret := GetItemDescriptor(0xee09);
  ret.Color := color;
  ret.CProps.insert("type", type);
  ret.CProps.insert("skillid", skillid);
  ret.CProps.insert("ramt", ramt);
  var theitem := CreateItemInBackpack(who, ret, 1);
  if(theitem)
    SubtractAmount(scroll, 1);
  endif
  SetName(theitem, title);
  return;

endfunction

function repair_this(who, skillid := 7)
  SendSysMessage(who, "Select item to repair.");
  var use_on := Target(who);
  if(!can_access(who, use_on))
    return;
  endif
  if(use_on.movable == 0)
    SendSysMessage(who, "You cannot repair that.");
    return;
  endif
  if((!Accessible(who, use_on)) or (Distance(who, use_on) > 2))
    SendSysMessage(who, "You cannot reach that.");
    return;
  endif
  if(CInt(use_on.objtype) == CInt(0xe34))
    case(CInt(skillid))
       7: CreateRepairDeed(who, use_on, skillid);
       8: CreateRepairDeed(who, use_on, skillid);
      11: CreateRepairDeed(who, use_on, skillid);
      34: CreateRepairDeed(who, use_on, skillid);
    endcase
    return;
  endif
  var forge := 0;
  case(CInt(skillid))
     7: forge := 1;
  endcase
  if(!forge)
    if(is_weapon_armor(use_on.objtype))
      repair_item( who, use_on, skillid);
    else
      SendSysMessage(who, "You cannot repair that.");
    endif
  else
    if(is_weapon_armor(use_on.objtype))
      var near_items := ListItemsNearLocation(who.x, who.y, who.z,3);
      foreach item in near_items
        if ((item.objtype == UOBJ_ANVIL1) || (item.objtype == UOBJ_ANVIL2))
          repair_item( who, use_on, skillid);
          return;
        endif
      endforeach
      SendSysMessage( who, "You must be near an anvil to repair items!" );
      return;
    else
      SendSysMessage(who, "You cannot repair that");
    endif
  endif
  return;
endfunction

function is_weapon_armor(what)
  var combatcfg := ReadConfigFile(":combat:itemdesc");
  var elem := FindConfigElem(combatcfg, what);
  var repairable := GetConfigInt(elem, "repairable");
  if (repairable == 1)
    return 1;
  else
    return 0;
  endif
endfunction

function resmelt(who)

  var near_items := ListItemsNearLocation(who.x, who.y, who.z, 3);
  var forge_near := 0;
  foreach forge in near_items
    if((forge.objtype == 0xfb1) || ((forge.objtype >= 0x197a) && (forge.objtype <= 0x19a9)))
      forge_near := 1;
      break;
    endif
  endforeach
  if(forge_near == 0)
    SendSysMessage(who, "You must be near a forge.");
    return;
  endif
  SendSysMessage(who, "Select the item you wish to melt.");
  var use_on := Target(who, TGTOPT_CHECK_LOS);
  if(!use_on or !can_access(who, use_on))
    return;
  endif
  if(use_on.container.serial != who.backpack.serial)
    SendSysMessage(who, "That is not in your backpack.");
    return;
  endif
  if(!Accessible(who, use_on) || !ReserveItem( use_on ))
    SendSysMessage(who, "You cannot use that.");
    return;
  endif
  if(use_on.movable == 0)
    SendSysMessage(who, "You cannot use that while it is locked down.");
    return;
  endif
  if(use_on in ListEquippedItems(who))
    SendSysMessage(who, "You cannot use that.");
    return;
  endif
  var cfgarray := GetConfigStringKeys(rlist_cfg);
  if(use_on.isA(POLCLASS_CONTAINER))
    var contitems := EnumerateItemsInContainer(use_on);
    var skill, amt, ingot;
    foreach thing in contitems
      if(craftcfg[thing.objtype])
        skill := craftcfg[thing.objtype].skill;
        amt := CInt(craftcfg[thing.objtype].material);
        if((!skill) || (!amt))
          return;
        endif
        skill := CInt(skill/2);
        if(skill < 5)
          skill := 5;
        endif
        amt := CInt((amt * GetEffectiveSkill(who,SKILLID_BLACKSMITHY) * 75 ) / 10000);
        if(amt < 1)
          amt := 1;
        endif
        ingot := -1;
        var mattype := CInt(GetObjProperty(use_on, "material"));
        if(mattype >= 0)
          if(mattype != error)
            ingot := mattype;
          endif
        endif
        if(ingot == -1)
          foreach entry in cfgarray
            if(lower(rlist_cfg[entry].Type) == "metal")
              if(CInt(rlist_cfg[entry].Color) == CInt(thing.color))
                ingot := entry;
              endif
            endif
          endforeach
        endif
        if(ingot == -1)
          SendSysMessage(who, "You have no idea how to smelt this strange ore!");
          return;
        endif
        PlaySoundEffect(who, 0x2c);
        sleep(1);
        PlaySoundEffect(who, 0x22);
        if(DestroyItem(thing))
          if(CheckSkill(who, SKILLID_BLACKSMITHY, skill, 10))
            CreateItemInContainer(who.backpack, ingot, amt);
          else
            SendSysMessage(who, "You destroy the item.");
          endif
        endif
      endif
      sleep(1);
   endforeach
  else
    if(!craftcfg[use_on.objtype])
      return;
    endif
    var ingot := -1;
    var skill := craftcfg[use_on.objtype].skill;
    var amt := CInt(craftcfg[use_on.objtype].material);
    if((!skill) || (!amt))
      return;
    endif
    skill := CInt(skill/2);
    if(skill < 5)
      skill := 5;
    endif
    amt := CInt((amt * GetEffectiveSkill(who,SKILLID_BLACKSMITHY) * 75 ) / 10000);
    if(amt < 1)
      amt := 1;
    endif
    var mattype := CInt(GetObjProperty(use_on, "material"));
    if(mattype >= 0)
      if(mattype != error)
        ingot := mattype;
      endif
    endif
    if(ingot == -1)
      foreach entry in cfgarray
        if(lower(rlist_cfg[entry].Type) == "metal")
          if(CInt(rlist_cfg[entry].Color) == CInt(use_on.color))
            ingot := entry;
          endif
        endif
      endforeach
    endif
    if(ingot == -1)
      SendSysMessage(who, "You have no idea how to smelt this strange ore!");
      return;
    endif
    PlaySoundEffect(who, 0x2c);
    sleep(1);
    PlaySoundEffect(who, 0x22);
    if(DestroyItem(use_on))
      if(CheckSkill(who, SKILLID_BLACKSMITHY, skill, 10))
        CreateItemInContainer(who.backpack, ingot, amt);
      else
        SendSysMessage(who, "You destroy the item.");
      endif
    endif
  endif

endfunction