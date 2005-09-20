function Go_AddPrivateLocation(who)

        SendSysMessage(who, "Click where you want the new personal Go Location to go to.");
        var targ := TargetCoordinates(who);

        if (!targ)
                SendSysMessage(who, "Cancelled");
                return;
        endif

        var name := RequestInput(who, who.backpack, "What do you want to call this go location?");

        if ( !name )
                SendSysMessage(who, "Cancelled");
                return;
        endif

        go_prop := go_elem.GetProp(who.acctname);
        if ( go_prop.exists(lower(name)) )
                SendSysMessage(who, "You already have a go location named ["+name+"]");
                return;
        endif

        Go_SetLocation(who.acctname, who, name, targ.realm, targ.x, targ.y, targ.z);

endfunction

function Go_AddPublicLocation(who)

        SendSysMessage(who, "Click where you want the new public Go Location to go to.");
        var targ := TargetCoordinates(who);

        if (!targ)
                SendSysMessage(who, "Cancelled");
                return;
        endif

        var name := RequestInput(who, who.backpack, "What do you want to call this go location?");

        if ( !name )
                SendSysMessage(who, "Cancelled");
                return;
        endif

        go_prop_base := go_elem.GetProp("base_Distro");
        if ( go_prop_base.exists(lower(name)) )
                SendSysMessage(who, "You already have a go location named ["+name+"]");
                return;
        endif

        Go_SetLocation("base_Distro", who, name, targ.realm, targ.x, targ.y, targ.z);

endfunction

function Go_CopyPublicLocation(who)

        var gump := Go_RetrieveGump("CopyIndex", "base_Distro");
        num_keys := go_keys_base.size();
        if  ( !gump )
                SendSysMessage(who, "Building go public copy gump...");
                gump := Go_PublicCopyGump();
                Go_SaveGump("CopyIndex", gump, "base_Distro");
        endif

        var input := GFSendGump(who, gump);
        input := input[0];

        if(input)
                var send_Location := 0;
                send_Location := go_prop_base[lower(go_keys_base[input])];
                if ( send_Location )
                        go_prop_base := go_elem.GetProp("base_Distro");
                        if ( go_prop.exists(lower(send_Location.Name)) )
                                SendSysMessage(who, "You already have a go location named ["+send_Location.Name+"]");
                                return;
                        endif
                        SendSysMessage(who, "Copying [" + send_Location.Name + "] to your personal menu.");
                        Go_SetLocation(who.acctname, who, send_Location.Name, send_Location.Realm, send_Location.X, send_Location.Y, send_Location.Z);
                        return;
                else
                        SendSysMessage(who, "Location [" + send_Location.Name + "] does not exist.");
                        Go_RefreshMyGumps(who);
                        return;
                endif
        else
                SendSysMessage(who, "Copying Cancelled");
                Go_RefreshMyGumps(who);
                return;
        endif

endfunction

function Go_CopyPrivateLocation(who)

        var gump := Go_RetrieveGump("CopyIndex", who.acctname);
        num_keys := go_keys.size();
        if  ( !gump )
                SendSysMessage(who, "Building go private copy gump...");
                gump := Go_PrivateCopyGump();
                Go_SaveGump("CopyIndex", gump, who.acctname);
        endif

        var input := GFSendGump(who, gump);
        input := input[0];

        if(input)
                var send_Location := 0;
                send_Location := go_prop[lower(go_keys[input])];
                if ( send_Location )
                        go_prop := go_elem.GetProp(who.acctname);
                        if ( go_prop_base.exists(lower(send_Location.Name)) )
                                SendSysMessage(who, "You already have a public go location named ["+send_Location.Name+"]");
                                return;
                        endif
                        SendSysMessage(who, "Copying [" + send_Location.Name + "] to the public menu.");
                        Go_SetLocation("base_Distro", who, send_Location.Name, send_Location.Realm, send_Location.X, send_Location.Y, send_Location.Z);
                        return;
                else
                        SendSysMessage(who, "Location [" + send_Location.Name + "] does not exist.");
                        Go_RefreshMyGumps(who);
                        return;
                endif
        else
                SendSysMessage(who, "Copying Cancelled");
                Go_RefreshMyGumps(who);
                return;
        endif

endfunction

function Go_SetLocation(gump_Type, who, name, realm, x, y, z)

        if( !realm )
          realm := who.realm;
        endif

        z := GetMapInfo(x, y, realm).z;

        var temp := dictionary;
        temp.+Name := lower(name);
        temp.+Realm := realm;
        temp.+X := x;
        temp.+Y := y;
        temp.+Z := z;
        case(gump_Type)
          "base_Distro": go_prop_base[lower(name)] := temp;
                         go_elem.SetProp(gump_Type, go_prop_base);
          default: go_prop[lower(name)] := temp;
                   go_elem.SetProp(gump_Type, go_prop);
        endcase
        Go_RefreshMyGumps(who);

endfunction

function Go_PublicCopyGump()

        var gump := GFCreateGump();
        GFResizePic(gump, 0, 0, BKGND_SILVERTRIM, 400, 520);
        GFResizePic(gump, 15, 15, BKGND_DARK_STONE, 370, 35);
        GFHTMLArea(gump,  15, 20, 370, 20, "<basefont color=#7FFFD4><center>Go To Locations (Public)</center>");
        GFResizePic(gump, 15, 55, BKGND_DARK_STONE, 370, 410);
        GFHTMLArea(gump,  25, 60, 150, 20, "<basefont color=#7FFFD4>Name");
        GFHTMLArea(gump, 175, 60, 150, 20, "<basefont color=#7FFFD4>Realm");
        GFHTMLArea(gump, 295, 60, 150, 20, "<basefont color=#7FFFD4>Copy");
        GFResizePic(gump, 15, 470, BKGND_DARK_STONE, 370, 35);


        GFPage(gump, 1);

        var y_loc := 85;
        var page_num := 1;
        var counter := 1;
        var line_num := 0;

        go_keys_base.sort();
        foreach place in ( go_keys_base )
                GFTextLine(gump,  25, y_loc, 2100, go_prop_base[place].Name);
                GFTextLine(gump, 175, y_loc, 2100, go_prop_base[place].Realm);
                GFAddButton(gump, 300, y_loc+3, 2117, 2118, GF_CLOSE_BTN, counter);

                counter := counter + 1;
                line_num := line_num+1;
                y_loc := y_loc + 20;
                if ( line_num >= 18 && line_num < num_keys )
                        GFAddButton(gump, 370, 435, 2706, 2707, GF_PAGE_BTN, page_num+1);
                        page_num := page_num + 1;
                        GFPage(gump, page_num);
                        GFAddButton(gump, 370,  85, 2704, 2705, GF_PAGE_BTN, page_num-1);
                        y_loc := 85;
                        line_num := 0;
                endif
                sleepms(2);
        endforeach

        return gump;

endfunction

function Go_PrivateCopyGump()

        var gump := GFCreateGump();
        GFResizePic(gump, 0, 0, BKGND_SILVERTRIM, 400, 520);
        GFResizePic(gump, 15, 15, BKGND_DARK_STONE, 370, 35);
        GFHTMLArea(gump,  15, 20, 370, 20, "<basefont color=#7FFFD4><center>Go To Locations (Private)</center>");
        GFResizePic(gump, 15, 55, BKGND_DARK_STONE, 370, 410);
        GFHTMLArea(gump,  25, 60, 150, 20, "<basefont color=#7FFFD4>Name");
        GFHTMLArea(gump, 175, 60, 150, 20, "<basefont color=#7FFFD4>Realm");
        GFHTMLArea(gump, 295, 60, 150, 20, "<basefont color=#7FFFD4>Copy");
        GFResizePic(gump, 15, 470, BKGND_DARK_STONE, 370, 35);


        GFPage(gump, 1);

        var y_loc := 85;
        var page_num := 1;
        var counter := 1;
        var line_num := 0;

        go_keys.sort();
        foreach place in ( go_keys )
                GFTextLine(gump,  25, y_loc, 2100, go_prop[place].Name);
                GFTextLine(gump, 175, y_loc, 2100, go_prop[place].Realm);
                GFAddButton(gump, 300, y_loc+3, 2117, 2118, GF_CLOSE_BTN, counter);

                counter := counter + 1;
                line_num := line_num+1;
                y_loc := y_loc + 20;
                if ( line_num >= 18 && line_num < num_keys )
                        GFAddButton(gump, 370, 435, 2706, 2707, GF_PAGE_BTN, page_num+1);
                        page_num := page_num + 1;
                        GFPage(gump, page_num);
                        GFAddButton(gump, 370,  85, 2704, 2705, GF_PAGE_BTN, page_num-1);
                        y_loc := 85;
                        line_num := 0;
                endif
                sleepms(2);
        endforeach

        return gump;

endfunction