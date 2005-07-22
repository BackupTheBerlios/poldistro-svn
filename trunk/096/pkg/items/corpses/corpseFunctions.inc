
function Carve_Corpse(who, cadaver)
  Detach();
  if((!Accessible(who, cadaver)) or (!CheckLineOfSight(who, cadaver)))
    SendSysMessage(who, "You cannot use that.");
    return;
  endif
  if(Distance(who, cadaver) > 2)
    SendSysMessage(who, "You are not close enough.");
    return;
  endif
  var c_type := cadaver.corpsetype;
  if(GetObjProperty(cadaver, "cut") == "1")
    SendSysMessage( who, "You cannot get any more from this corpse." );
    foreach thing in EnumerateItemsInContainer(cadaver)
      MoveItemToLocation(thing, cadaver.x, cadaver.y, cadaver.z, MOVEITEM_FORCELOCATION);
    endforeach
    DestroyItem(cadaver);
  elseif((c_type == 400) || (c_type == 401))
    var beardlist := {0x203e, 0x203f, 0x2040, 0x2041, 0x204b, 0x204c, 0x204d };
    var hairlist  := {0x2044, 0x2045, 0x2046, 0x2047, 0x2048, 0x2049, 0x204a, 0x203b, 0x203c, 0x203d };
    foreach thing in EnumerateItemsInContainer(cadaver)
      if((thing.objtype in hairlist) or (thing.objtype in beardlist))
        DestroyItem(thing);
      else
        MoveItemToLocation(thing, cadaver.x, cadaver.y, cadaver.z, MOVEITEM_FORCELOCATION);
      endif
    endforeach
    var partsarray := {};
    var part;
    part := CreateItemAtLocation(cadaver.x-1, cadaver.y, cadaver.z, 0x1da0, 1, cadaver.realm);
    partsarray.append(part);
    SetObjProperty(part, "serial", GetObjProperty(cadaver, "serial"));
    var aname := cadaver.name;
    aname["A corpse of"] := "";
    part.name := "The head of " + aname;
    part := CreateItemAtLocation(cadaver.x-1, cadaver.y, cadaver.z, 0x1da1, 1, cadaver.realm);
    partsarray.append(part);
    part := CreateItemAtLocation(cadaver.x-1, cadaver.y+1, cadaver.z, 0x1da2, 1, cadaver.realm);
    partsarray.append(part);
    part := CreateItemAtLocation(cadaver.x+1, cadaver.y, cadaver.z, 0x1da3, 1, cadaver.realm);
    partsarray.append(part);
    part := CreateItemAtLocation(cadaver.x+1, cadaver.y+1, cadaver.z, 0x1da4, 1, cadaver.realm);
    partsarray.append(part);
    part := CreateItemAtLocation(cadaver.x, cadaver.y, cadaver.z, 0x1d9f, 1, cadaver.realm);
    partsarray.append(part);
    var blood := CreateItemAtLocation(cadaver.x, cadaver.y, cadaver.z, 0x122a, 1, cadaver.realm);
    blood.movable := 0;
    DestroyItem(cadaver);
    sleep(40);
    foreach thing in partsarray
      if(!thing.container)
        DestroyItem(thing);
      endif
    endforeach
    sleep(20);
    DestroyItem(blood);
  else
    if(c_type == 223)
      CreateItemInContainer(cadaver, 0x9f1, 2);
      SendSysMessage(who, "You place the items on the corpse.");
      var theblood := CreateItemAtLocation(cadaver.x, cadaver.y, cadaver.z, UOBJ_BLOOD, 1, cadaver.realm);
      sleep(30);
      DestroyItem(cadaver);
      sleep(30);
      DestroyItem(theblood);
      return;
    endif
    var conf := ReadConfigFile(":*:npcdesc");
    var tmplate := GetObjProperty(cadaver, "npctemplate");
    if(!tmplate)
      SendSysMessage(who, "You cut the corpse, but fail to find anything useful.", 3, 40);
      var theblood := CreateItemAtLocation(cadaver.x, cadaver.y, cadaver.z, UOBJ_BLOOD, 1, cadaver.realm);
      sleep(30);
      DestroyItem(cadaver);
      sleep(30);
      DestroyItem(theblood);
      return;
    else
      SetObjProperty(cadaver, "cut","1");
      var corpseitm := conf[tmplate]."corpseitm";
      var corpseamt := conf[tmplate]."corpseamt";
      print("I: " + corpseitm);
      print("A: " + corpseamt);
      if(!corpseitm)
        print("error");
        var theblood := CreateItemAtLocation(cadaver.x, cadaver.y, cadaver.z, UOBJ_BLOOD, 1, cadaver.realm);
        sleep(30);
        DestroyItem(cadaver);
        sleep(30);
        DestroyItem(theblood);
        return;
      endif
      var i := 1;
      corpseitm := SplitWords(corpseitm);
      corpseamt := SplitWords(corpseamt);
      foreach thing in corpseitm
        CreateItemInContainer(cadaver, thing, Cint(corpseamt[i]));
        i := i + 1;
      endforeach
      SendSysMessage(who, "You place the items on the corpse.");
      var theblood := CreateItemAtLocation(cadaver.x, cadaver.y, cadaver.z, UOBJ_BLOOD, 1, cadaver.realm);
      sleep(30);
      DestroyItem(cadaver);
      sleep(30);
      DestroyItem(theblood);
    endif
  endif
endfunction
