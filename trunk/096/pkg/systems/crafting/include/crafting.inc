// //$Id$

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  name:    Main Crafting Backbone (include file)
//  version: 1.0b3
//  author:  MuadDib
//
//  Purpose: Functions for creating crafting menus, info menus, item creation, resource selection,
//           skill gain, etc.
//
//  Notes:   Acknowledgement to Valkyrie and Austin for coding ideas, based off a combination of a
//           work-in-progress of her's, and mine both
//
//  Changes: Sept 5, 2005 -- TruncatePlural() replaced. New function by Austin.
//                        -- Did some comment changes, removed unused variables and functions.
//                        -- Removed requirement for an altered gumpUtil.inc. Can use standard
//                           Distro version now.
//           Sept 6, 2005 -- Info Gump changed in respect with Parts for Assembly items. For items
//                           that use less than 5 parts, each item is listed seperately now. If
//                           it contains 5 or more parts, it gives the old HTML method giving them
//                           in a sentence form, for more custom and ingenious assembly items requiring
//                           much more to craft (ewwwwww).
//                        -- Material and Material Name areas both now use a HTML gump area for
//                           showing their text for Assembly. Less code and less bandwidth.
//                        -- Matierial and Material name for standard, and dual material, items are
//                           now handled via the HTML gump method as parts. MUCH less code and bw
//                           are the end result for this change also.
//                        -- Added function playCraftWork(). This function is used to display a craft
//                           skill's action animation, sound, the loops to do it in, and the delay
//                           between loops. Sound is required, loops defaults to 0 if none sent, and
//                           delay defaults to 2 seconds if none sent, Action defaults to 0 (none) if
//                           none sent. All delays are in seconds.
//           Sept 7, 2005 -- Optimized a TON of if/else and if/elseif statements by converting them
//                           to case() statements where possible in the main menu's code and the info
//                           screen code.
//                        -- Altered most buttons out of the 1000 and 8000 range due to possible
//                           objtype conflicts. Info buttons now use 61500 through 62000. Repair,
//                           smelt, maker's mark, and retain color all converted also for this bug.
//           Sept 8, 2005 -- Changed TruncatePlural() to return a struct{errortext} if it could
//                           not find a "name" or "desc" entry for an itemdesc.cfg entry.
//                        -- Changed DrawNewPage to skip items with invalid Objtype names given
//                           in the Menu file, and with invalid objtype returned from TruncatePlural().
//           Sep 14, 2005 -- Redid code to set Last Item cprop checks.
//
//
//  To-Do:   1.) Break this down even more. Such as "crafting_menu.inc", "crafting_skill.inc",
//               "crafting_util.inc", and so on.
//           2.) Centralize Crafting Package. Move the skills.cfg information BACK into the
//               central skills.cfg in /config. Directory layout as follows:
//               pkg -> Crafting -> Include
//                               -> Repair
//                               -> Util    -> textcmd/admin
//                   -> Skills   -> Alchemy     -> mortar
//                               -> Blacksmithy -> smithing
//                               -> Etc etc.    -> usescripts, etc etc.
//           3.) Finish up repair contracts and tool wear.
//           4.) Create some cusotmized crafting includes for inscription, etc that require it.
//           5.) Create textcmds for editing the Menu and item configs, to add new items ingame.
//           6.) Create MethodScript system for Toolwear!
//           7.) UPGRADE to use the new gumps package by Austin for the newest distro.
//           8.) UPGRADE all buttons (except ones to make the item, which uses the button's objtype)
//               to use the 0xF000 - 0xFFFF range. That range is CORE RESERVED for objtypes, thus,
//               should NEVER contain custom items added by shard admins. Therefore anything in that
//               range should not be craftable and thus, not in these menus.
//           9.) Remove all sound and animation function calls from crafting. Change it to use a
//               single function called as "playCraftWork(anim, sound, loop:=0;, delay:=0;)"
//
// Strings to find and fix under new attributes:
// AwardPoints(who, Cint(craft_config[objtype].skillID), 1);
// AwardPoints(who, skillid, 1);
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////
use polsys;
use datafile;

include "include/objtype";
include ":crafting:include/craftGumps";
include ":crafting:include/craftingSkill";
include ":gumps:include/gumps";
include ":gumps:include/gumps_ex";

var craft_skill;
var craftL    := 0;
var rcolor    := 1;
var makermark := 1;

// Function used to target material and check ability for crafting.
// Returns an array of ItemRef for the item and Objtype for the
// resourceList of the material, and the Points bonus the resource
// gives for using it. If chk is passed, it is used for the "cprop"
// to check the item for. This is used for example, for boards that
// was originally colored logs. The colored log objtype is stored
// in the cprop, and is used to get it's "ResourceList" reference.
function MaterialSelection(who, craft_skill, type, chk:=0)

  SendSysMessage(who, "Select the "+lower(type)+" you would like to work with.");
  var material := Target(who);
  if(!material)
    return 0;
  endif
  if(material.container.serial != who.backpack.serial)
    SendSysMessage(who, "That is not in your backpack.");
    return 0;
  endif
  if((!can_access(who, material)) || (!Accessible(who, material)) || (Distance(who, material) > 2)
       || (material.movable == 0) || (!ReserveItem(material)))
    SendSysMessage(who, "You cannot use that.");
    return 0;
  endif
  var materialobjtype := 0;
  if(chk)
    if(GetObjProperty(material, chk))
      materialobjtype := GetObjProperty(material, chk);
    else
      materialobjtype := material.objtype;
    endif
  else
    materialobjtype := material.objtype;
  endif
  if(!canUseMaterial(who, materialobjtype, craft_skill))
    SendSysMessage(who, "You are not skilled enough to make anything out of that.");
    return 0;
  endif
  var rtype := lower(resource_config[materialobjtype].Type);
  var materialchk := 0;
  if(rtype == type)
    materialchk := 1;
  endif
  if(materialchk == 0)
    SendSysMessage(who, "That's not the proper material.");
    return 0;
  endif
  if((material.objtype >= UOBJ_BOLT_START) && (material.objtype <= UOBJ_BOLT_END))
    var totalcloth := material.amount * 50;
    var cloth;
    if(DestroyItem(material))
      cloth := CreateItemInBackpack(who, 0x1767, totalcloth);
      if(!cloth)
        cloth := CreateItemAtLocation(who.x, who.y, who.z, 0x1767, totalcloth);
      endif
    endif
    material := cloth;
  endif

  var retarray := array;
  retarray.append(material);
  retarray.append(materialobjtype);
  retarray.append(resource_config[materialobjtype].Ptmod);
  return retarray;

endfunction

// Used to create the actual item, handle it's coloring and marking of
// exceptional naming of the item itself. Returns objref if success, 0 if fail.
// All asked for items in the function line are able to be sent no matter the skill
// the script is for with crafting. Use_onobjtype is there only for when you are
// working with let's say boards for example, where they will have a cprop contianing
// the objtype of the original logs they was made from. Else you simply pass
// use_on.objtype for that. This will keep the customizability open for adding in
// special resources for crafting here also.
function CreateCraftItem(who, craft_skill, use_on, use_onobjtype, objtype, amount, itemname, reqd)

 var theitem := CreateItemInBackpack(who, objtype, 1);
 var elem    := FindConfigElem(resource_config, use_onobjtype);
 if(theitem)
   var nme := (resource_config[use_onobjtype].Name) + " " + itemname;
   if(find(nme, "plain ", 1))
     nme[find(nme, "plain ", 1),6] := "";
   endif
   if((rcolor == 1) && (craft_config[objtype].retain == 1))
     if(resource_config[use_onobjtype].Color)
       theitem.color := resource_config[use_onobjtype].Color;
     else
       theitem.color := use_on.color;
     endif
   endif
   SetObjProperty(theitem, "material", use_onobjtype);
   if(!SubtractAmount(use_on, amount))
     SendSysMessage(who, "You don't have enough materials in your backpack!");
     DestroyItem(theitem);
     return -1;
   endif
   var myskill := CDbl(AP_GetSkill(who, craft_skill));
   var aidskill := CDbl(AP_GetSkill(who, craft_config[objtype].skillID));
   // This snags the Qualities of the resource to use on item creation.
   // Format in the cfg for Quality is <dmg mod> <ar mod> <hp mod>.
   // 0 for a mod means there isn't one. Space delimited in the cfg,
   // this allows us to simply use SplitWords on it to make the array
   // of each of the settings.
   var temp := GetConfigString(elem, "Quality");
   temp := SplitWords(temp);
   var power  := GetConfigString(elem, "Power");
   if( (TypeOf(power) != "String") )
     power := 0;
   endif
   var wpower := GetConfigString(elem, "WPower");
   if( (TypeOf(wpower) != "String") )
     wpower := 0;
   endif
   if((craft_config[objtype].Exceptional == 1) && (ExceptionalCraft(myskill, reqd, aidskill)))
//     AwardPoints(who, craft_skill, 1);
     SetObjProperty(theitem, "Exceptional", 1);
     if( TypeOf(craft_config[objtype].skillID) == "String" )
//       AwardPoints(who, Cint(craft_config[objtype].skillID), 1);
     endif
     if((craft_config[objtype].Mark == 1))
       if((makermark == 1) && (myskill >= 100))
         nme := "an exceptional " + nme + " [Crafted by " + who.name + "]";
       else
         nme := "an exceptional " + nme;
       endif
     else
       nme := "an exceptional " + nme;
     endif
     if(theitem.isA(POLCLASS_WEAPON))
       theitem.dmg_mod := CInt(temp[1])+(RandomInt(4));
     elseif(theitem.isA(POLCLASS_ARMOR))
       theitem.ar_mod := CInt(temp[2])+(RandomInt(4));
     endif
     theitem.maxhp_mod := CInt(temp[3])+(RandomInt(11));
     theitem.hp := theitem.maxhp;
     SendSysMessage(who, "You create an exceptional quality item.");
   else
     var rint := randomint(AP_GetSkill(who, craft_skill));
     if(reqd >= 23)
       reqd := reqd - 20;
     else
       reqd := 3;
     endif
     if(rint < reqd)
       SendSysMessage(who, "You were barely able to make this item.  Its quality is below average.");
       if(theitem.isA(POLCLASS_WEAPON))
         theitem.dmg_mod := CInt(temp[1])-(RandomInt(2)+1);
       elseif(theitem.isA(POLCLASS_ARMOR))
         theitem.ar_mod := CInt(temp[2])-(RandomInt(2)+1);
       endif
       theitem.maxhp_mod := CInt(temp[3])-(RandomInt(10)+1);
       theitem.hp := theitem.maxhp;
     else
       SendSysMessage(who, "You create the item and put it in your backpack.");
       if(theitem.isA(POLCLASS_WEAPON))
         theitem.dmg_mod := CInt(temp[1]);
       elseif(theitem.isA(POLCLASS_ARMOR))
         theitem.ar_mod := CInt(temp[2]);
       endif
       theitem.maxhp_mod := CInt(temp[3]);
       theitem.hp := theitem.maxhp;
     endif
     var word := "";
     if((nme[1] == "a") || (nme[1] == "e") || (nme[1] == "i") || (nme[1] == "o") || (nme[1] == "u"))
       word := "an ";
     else
       word := "a ";
     endif
     nme := "" + word + nme;
     nme := nme - "plain ";
   endif
   SetName(theitem, nme);
   if(theitem.isA(POLCLASS_CONTAINER))
     SetObjProperty(theitem, "trappable", 1);
   elseif(theitem.isA(POLCLASS_ITEM))
     SetToolDurability(who, theitem, craft_skill);
   endif
//   if((power) && (theitem.isa(POLCLASS_ARMOR)))
//     SetObjProperty(theitem, "power", power);
//     theitem.equipscript := "equiparmor";
//     theitem.unequipscript := "unequiparmor";
//   elseif((wpower == "SILVER") && theitem.isA(POLCLASS_WEAPON))
//     SetObjProperty(theitem, "SilverHit", 1);
//   elseif(wpower && theitem.isA(POLCLASS_WEAPON))
//     SetObjProperty(theitem, "wpower", power);
//     theitem.equipscript := "equipweapon";
//     theitem.unequipscript := "unequipweapon";
//   endif
 else
   SendSysMessage(who, "You don't have enough room in your backpack!");
   return 0;
 endif

 return theitem;

endfunction

// This function is used to create items that are marked "assemble" in the
// crafting configs. Reads a prop from the cfg entry for a list of parts and
// their amounts then checks the player's backpack for the items and works it.
function CreateAssembly(who, tool, objtype, amt)

  var skill := craft_config[objtype].skill, theitem;
  var mainSkill := CInt(AP_GetSkill(who, craft_skill));
  var modpts := 0;
  if(mainSkill >= skill)
    modpts := (mainSkill - (skill - 10));
  endif
  var diff := Cint(craft_config[objtype].difficulty);
  var pts  := Cint(craft_config[objtype].points);
  pts := pts + modpts;
  var counter := 0, chk := 0;
  // Get a list of the parts from the cfg entry. Format from config is listed in cfg
  // header. Objtypes first, then amount for each objtype, in the same respective order.
  // To match them together, we divid the length of the array by 2 then use that.
  // Example : mod := len(array)/2;
  // Example2: objtype := array[x]; amt := array[x+mod];
  var partslist := SplitWords(craft_config[objtype].parts);
  if(!partslist or partslist.errortext)
    SendSysMessage(who, "This item does not require parts to be made! Contact a GM.");
    return;
  endif
  var mod := len(partslist)/2;
  var partcounter, partarray, checker;
  var x := who.x, y := who.y;

  while(counter < amt)
    if((who.x != x) || (who.y != y))
      break;
    endif
    if(chk == 1)
      break;
    endif
    partarray := {};
    checker := 0;
    chk := 0;
    // We use the Enumerate in a variable like this so as to work with it
    // as an array. This way no need to enumerate every for/endfor cycle.
    var blist := EnumerateItemsInContainer(who.backpack);
    for i := 1 to mod
      partcounter := 0;
      foreach thing in blist
        // If thing.objtype is the same as the objtype in the part list array position....
        if(CInt(thing.objtype) == CInt(partslist[i]))
          // If the amount is less than the counter for this item type, append it to the
          // array for deletion later.
          if(partcounter < CInt(partslist[i+mod]))
            if(ReserveItem(thing))
              partarray.append(thing);
              partcounter := partcounter + 1;
            endif
          endif
        endif
      endforeach
      // We add 2 to the checker var here once all required peices are added. We use
      // this later to divide by 2. If divided by 2, it equals the mod variable, we know
      // all the required peices are in their backpack. That works, because it is the same
      // method for the partslist array which is an amount entry for each objtype entry.
      // Sure, we could use 1, then divide the mod by 2 also for this to work. But I was
      // in one of my moods ;)
      if(partcounter == CInt(partslist[i+mod]))
        checker := checker + 2;
      endif
    endfor
    if((checker /2) != mod)
      SendSysMessage(who, "You do not have the required materials to make that.");
      return;
    else
      sleep(2);
      if(CraftCheckSkill(who, mainSkill, diff, pts))
        PlaySoundEffect(who, 0x23e);
        sleep(2);
        foreach thing in partarray
          if(!DestroyItem(thing))
            SendSysMessage(who, "You do not have the ready materials to make that.");
            return;
          endif
        endforeach
        theitem := CreateItemInBackpack(who, objtype, 1);
        if(!theitem)
          SendSysMessage(who, "You don't have enough room in your backpack!");
          return 0;
        endif
        CheckToolWear (who, tool, mainSkill);
        theitem.movable := 1;
        SendSysMessage(who, "You create the item and put it in your backpack.");
      endif
    endif
    if(theitem.isA(POLCLASS_CONTAINER))
      SetObjProperty(theitem, "trappable", 1);
    endif
    counter := counter + 1;
  endwhile

endfunction

//
//  TruncatePlural()
//
//  * Returns the name for the item of the objtype passed.
//
function TruncatePlural(obj_type, add_S := 0)
        obj_type := CInt(obj_type);

        var config := ReadConfigFile(":*:itemdesc");
        config := config[obj_type];

        var name;
        if (config.desc)
                name := config.desc;
        elseif (config.name)
                name := config.name;
        else
                return error{"errortext":="Invalid Objtype : " + hex(obj_type) + "."};
        endif

        if ( !name["%"] )
                if ( add_S == 0 )
                        return name;
                endif
                if ( name[len(name)] in {"s"} )
                        return name;
                elseif ( name[len(name)] in {"h","j","x","z"} )
                        return name + "es";
                endif
                return name + "s";
        endif

        // Will deal with:
        //
        //      Bread Stick%s
        //      Bread Loa%ves/f%
        //      Lump%s% of Coal
        //      Loa%ves/f% of Bread
        //
        var first := find(name, "%", 1);
        var slash := find(name, "/", first);
        var second := find(name, "%", first + 1);
        if ( slash && !second )
                // Force-append a % if a '/' exists!
                name := name + "%";
                second := len(name);
        elseif ( !slash )
                slash := second;
        endif

        // wwwww%xx[/yy]%[zzzzz]
        // 12345678     9 01234
        // 12345678 901 2 34567

        var s_plur := name[first+1, slash-(first+1)];
        var s_sing := "";
        if ( slash != first )
                s_sing := name[slash+1, second-(slash+1)];
        endif

        var s_first := name[1, first-1];
        var s_middle := s_plur;
        var s_last := "";
        if ( len(name) > second )
                s_last := name[second+1, len(name)-second];
        endif

        if ( add_S == 0 )
                s_middle := s_sing;
        endif

        if ( !s_first )
                s_first := "";
        endif
        if ( !s_middle )
                s_middle := "";
        endif
        if ( !s_last )
                s_last := "";
        endif
        return s_first + s_middle + s_last;

endfunction


// Used to check the skill of the character vs the
// the skill of the resource_config (resources config) to
// see if they can work with the material.
function canUseMaterial(who, use_on, craft_skill)

  if( AP_GetSkill(who, craft_skill) >= resource_config[use_on].Skill )
    return 1;
  else
    return 0;
  endif

endfunction

// This function is used for those who have items from objtype 0 to 16383 the same
// as the items in the tiledata. It will convert the objtype to the correct Cliloc
// ID for it's name. Can be used in menu scripts such as crafting, etc. Just remember
// to pass the objtype as CInt(objtype) so it converts the hex to Integer.
// NOTE: Clilocs was implemented in uh, client 3.x+ I believe.
// 1020000 - First tiledata name entry
// 1036383 - Last tiledata name entry
// **** OLD AND OBSOLETE. NO LONGER USING CLILOCS IN THIS CRAFTING. LEFT
// **** IN FOR REFERENCE AND KNOWLEDGE
function ClilocObjtype(objtype)

  return -1;
  if((objtype >= 0) && (objtype <= 16383) && objtype != error)
    return CInt(objtype)+1020000;
  else
    return -1;
  endif

endfunction


// This function is used to display a craft skill's action,
// sound, the loops to do it in, and the delay between loops.
// Sound is required, loops defaults to 0 if none sent, and delay
// defaults to 2 seconds if none sent, Action defaults to 0
// (none) if none sent. Who is who the info is to be sent to.
// All delays are in seconds.
function playCraftWork(who, craftSound, loops:=0, delay:=2, craftAction:=0)


  if(loops)
    for i := 1 to loops
      if(craftAction)
        PerformAction( who, craftAction );
      endif
      PlaySoundEffect(who, craftSound);
      sleep(delay);
    endfor
  else
    PlaySoundEffect(who, craftSound);
    sleep(delay);
  endif

  return;

endfunction