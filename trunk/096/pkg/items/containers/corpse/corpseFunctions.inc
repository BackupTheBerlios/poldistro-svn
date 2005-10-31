/* $Id$
 *
 */
include ":blood:blood";


function Carve_Corpse(who, cadaver)

         Detach();
	if((!Accessible(who, cadaver)) or (!CheckLineOfSight(who, cadaver)))
		SendSysMessage(who, "You cannot use that.");
		return 0;
	endif
	if(Distance(who, cadaver) > 2)
		SendSysMessage(who, "You are not close enough.");
		return 0;
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
		var blood := MakeBleed(cadaver);
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
			var theblood := MakeBleed(cadaver);
			sleep(30);
			DestroyItem(cadaver);
			sleep(30);
			DestroyItem(theblood);
			return 0;
		endif
		var conf := ReadConfigFile(":*:npcdesc");
		var tmplate := GetObjProperty(cadaver, "npctemplate");
		if(!tmplate)
			SendSysMessage(who, "You cut the corpse, but fail to find anything useful.", 3, 40);
			var theblood := MakeBleed(cadaver);
			sleep(30);
			DestroyItem(cadaver);
			sleep(30);
			DestroyItem(theblood);
			return 0;
		else
			SetObjProperty(cadaver, "cut","1");
			var corpseitm := conf[tmplate]."corpseitm";
			var corpseamt := conf[tmplate]."corpseamt";
			print("I: " + corpseitm);
			print("A: " + corpseamt);
			if(!corpseitm)
				print("error");
				var theblood := MakeBleed(cadaver);
				sleep(30);
				DestroyItem(cadaver);
				sleep(30);
				DestroyItem(theblood);
				return 0;
			endif
			var i := 1;
			corpseitm := SplitWords(corpseitm);
			corpseamt := SplitWords(corpseamt);
			foreach thing in corpseitm
				CreateItemInContainer(cadaver, thing, Cint(corpseamt[i]));
				i := i + 1;
			endforeach
			SendSysMessage(who, "You place the items on the corpse.");
			// The do/dowhile loop used here, is done to ensure that the loop
			// runs at least once. do/dowhile runs as a Post-Condition loop,
			// checking AFTER the loop. A while/endwhile loop is known as a
			// Pre-Condition loop, checking before it runs the loop.
			var orig_facing := cadaver.facing;
			do
				cadaver.facing := RandomInt(7) + 1;
			dowhile( orig_facing == cadaver.facing );
			var theblood := MakeBleed(cadaver);
			sleep(30);
			DestroyItem(cadaver);
			sleep(30);
			DestroyItem(theblood);
		endif
	endif

	return 0;

endfunction