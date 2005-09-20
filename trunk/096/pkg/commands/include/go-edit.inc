function Go_EditPublicLocation(who)

        var gump := Go_PublicEditGump();
        num_keys := go_keys_base.size();

        var input := GFSendGump(who, gump);
        input := input[0];

        if(input)
                var send_Location := go_prop_base[lower(go_keys_base[input])];
                if ( send_Location )
                        var edit_gump := Go_EditPublicLocationGump(send_Location);
                        var edit_input := GFSendGump(who, edit_gump);

                        if ( edit_input[edit_update] )
                                edit_name := GFExtractData(edit_input, edit_name);
                                x_pos := CInt(GFExtractData(edit_input, x_pos));
                                y_pos := CInt(GFExtractData(edit_input, y_pos));
                                z_pos := CInt(GFExtractData(edit_input, z_pos));

                                if ( !edit_name )
                                        SendSysMessage(who, "Cancelled - No name entered");
                                        return;
                                elseif ( lower(edit_name) != send_Location.Name )
                                        if ( go_prop_base.exists( Lower(edit_name) ) )
                                                SendSysMessage(who, "Cancelled - location already exists with the name ["+edit_name+"]");
                                                return;
                                        endif
                                endif

                                var original_Realm := send_Location.Realm;
                                go_prop_base.erase(lower(send_Location.Name));
                                go_elem.SetProp("base_Distro", go_prop_base);
                                Go_SetLocation("base_Distro", who, edit_name, original_Realm, x_pos, y_pos, z_pos);
                                SendSysMessage(who, "Updated ["+edit_name+"]");
                                Go_RefreshMyGumps(who);
                        elseif ( edit_input[edit_delete] )
                                SendSysMessage(who, "Deleted [" + send_Location.Name + "]");
                                go_prop_base.erase(lower(send_Location.Name));
                                go_elem.SetProp("base_Distro", go_prop_base);
                                Go_RefreshMyGumps(who);
                        else
                                SendSysMessage(who, "Cancelled");
                        endif
                else
                        SendSysMessage(who, "Location [" + send_Location.Name + "] does not exist.");
                        return;
                endif
        else
                SendSysMessage(who, "Editing Cancelled");
                return;
        endif

endfunction

function Go_EditPrivateLocation(who)

        var gump := Go_PrivateEditGump();
        num_keys := go_keys.size();

        var input := GFSendGump(who, gump);
        input := input[0];

        if(input)
                var send_Location := go_prop[lower(go_keys[input])];
                if ( send_Location )
                        var edit_gump := Go_EditPrivateLocationGump(send_Location);
                        var edit_input := GFSendGump(who, edit_gump);

                        if ( edit_input[edit_update] )
                                edit_name := GFExtractData(edit_input, edit_name);
                                x_pos := CInt(GFExtractData(edit_input, x_pos));
                                y_pos := CInt(GFExtractData(edit_input, y_pos));
                                z_pos := CInt(GFExtractData(edit_input, z_pos));

                                if ( !edit_name )
                                        SendSysMessage(who, "Cancelled - No name entered");
                                        return;
                                elseif ( lower(edit_name) != send_Location.Name )
                                        if ( go_prop_base.exists( Lower(edit_name) ) )
                                                SendSysMessage(who, "Cancelled - location already exists with the name ["+edit_name+"]");
                                                return;
                                        endif
                                endif

                                var original_Realm := send_Location.Realm;
                                go_prop.erase(lower(send_Location.Name));
                                go_elem.SetProp(who.acctname, go_prop);
                                Go_SetLocation(who.acctname, who, edit_name, original_Realm, x_pos, y_pos, z_pos);
                                SendSysMessage(who, "Updated ["+edit_name+"]");
                                Go_RefreshMyGumps(who);
                        elseif ( edit_input[edit_delete] )
                                SendSysMessage(who, "Deleted [" + send_Location.Name + "]");
                                go_prop.erase(lower(send_Location.Name));
                                go_elem.SetProp(who.acctname, go_prop);
                                Go_RefreshMyGumps(who);
                        else
                                SendSysMessage(who, "Cancelled");
                        endif
                else
                        SendSysMessage(who, "Location [" + send_Location.Name + "] does not exist.");
                        return;
                endif
        else
                SendSysMessage(who, "Editing Cancelled");
                return;
        endif

endfunction

function Go_PublicEditGump()

        var gump := GFCreateGump();
        GFResizePic(gump, 0, 0, BKGND_SILVERTRIM, 400, 520);
        GFResizePic(gump, 15, 15, BKGND_DARK_STONE, 370, 35);
        GFHTMLArea(gump,  15, 20, 370, 20, "<basefont color=#7FFFD4><center>Go To Locations (Public)</center>");
        GFResizePic(gump, 15, 55, BKGND_DARK_STONE, 370, 410);
        GFHTMLArea(gump,  25, 60, 150, 20, "<basefont color=#7FFFD4>Name");
        GFHTMLArea(gump, 175, 60, 150, 20, "<basefont color=#7FFFD4>Realm");
        GFHTMLArea(gump, 295, 60, 150, 20, "<basefont color=#7FFFD4>Edit");
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

function Go_PrivateEditGump()

        var gump := GFCreateGump();
        GFResizePic(gump, 0, 0, BKGND_SILVERTRIM, 400, 520);
        GFResizePic(gump, 15, 15, BKGND_DARK_STONE, 370, 35);
        GFHTMLArea(gump,  15, 20, 370, 20, "<basefont color=#7FFFD4><center>Go To Locations (Private)</center>");
        GFResizePic(gump, 15, 55, BKGND_DARK_STONE, 370, 410);
        GFHTMLArea(gump,  25, 60, 150, 20, "<basefont color=#7FFFD4>Name");
        GFHTMLArea(gump, 175, 60, 150, 20, "<basefont color=#7FFFD4>Realm");
        GFHTMLArea(gump, 295, 60, 150, 20, "<basefont color=#7FFFD4>Edit");
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

function Go_EditPublicLocationGump(send_Location)

        var gump := GFCreateGump();
        GFResizePic(gump, 0, 0, BKGND_SILVERTRIM, 400, 520);
        GFResizePic(gump, 15, 15, BKGND_DARK_STONE, 370, 35);
        GFHTMLArea(gump,  15, 20, 370, 20, "<basefont color=#7FFFD4><center>Go To Locations (Public)</center>");
        GFResizePic(gump, 15, 55, BKGND_DARK_STONE, 370, 410);
        GFResizePic(gump, 15, 470, BKGND_DARK_STONE, 370, 35);
        edit_update := GFAddButton(gump, 25, 477, 4008, 4010, GF_CLOSE_BTN, UPDATE_BUTTON);
        GFHTMLArea(gump,  57, 480, 40, 20, "<basefont color=#7FFFD4>Update");
        edit_delete := GFAddButton(gump, 100, 477, 4005, 4007, GF_CLOSE_BTN, DELETE_BUTTON);
        GFHTMLArea(gump,  132, 480, 40, 20, "<basefont color=#7FFFD4>Delete");

        GFTextLine(gump, 20, 120, 2100, "Name");
        GFResizePic(gump, 120, 117, 2620, 180, 30);
        edit_name := GFTextEntry(gump, 130, 122, 160, 25, 2100, send_Location.Name);

        GFTextLine(gump, 20, 143, 2100, "X Coordinate");
        GFResizePic(gump, 120, 140, 2620, 100, 30);
        x_pos := GFTextEntry(gump, 130, 145, 80, 25, 2100, send_Location.X);

        GFTextLine(gump, 20, 166, 2100, "Y Coordinate");
        GFResizePic(gump, 120, 163, 2620, 100, 30);
        y_pos := GFTextEntry(gump, 130, 168, 80, 25, 2100, send_Location.Y);

        GFTextLine(gump, 20, 189, 2100, "Z Coordinate");
        GFResizePic(gump, 120, 186, 2620, 100, 30);
        z_pos := GFTextEntry(gump, 130, 191, 80, 25, 2100, send_Location.Z);

        return gump;

endfunction

function Go_EditPrivateLocationGump(send_Location)

        var gump := GFCreateGump();
        GFResizePic(gump, 0, 0, BKGND_SILVERTRIM, 400, 520);
        GFResizePic(gump, 15, 15, BKGND_DARK_STONE, 370, 35);
        GFHTMLArea(gump,  15, 20, 370, 20, "<basefont color=#7FFFD4><center>Go To Locations (Private)</center>");
        GFResizePic(gump, 15, 55, BKGND_DARK_STONE, 370, 410);
        GFResizePic(gump, 15, 470, BKGND_DARK_STONE, 370, 35);
        edit_update := GFAddButton(gump, 25, 477, 4008, 4010, GF_CLOSE_BTN, UPDATE_BUTTON);
        GFHTMLArea(gump,  57, 480, 40, 20, "<basefont color=#7FFFD4>Update");
        edit_delete := GFAddButton(gump, 100, 477, 4005, 4007, GF_CLOSE_BTN, DELETE_BUTTON);
        GFHTMLArea(gump,  132, 480, 40, 20, "<basefont color=#7FFFD4>Delete");

        GFTextLine(gump, 20, 120, 2100, "Name");
        GFResizePic(gump, 120, 117, 2620, 180, 30);
        edit_name := GFTextEntry(gump, 130, 122, 160, 25, 2100, send_Location.Name);

        GFTextLine(gump, 20, 143, 2100, "X Coordinate");
        GFResizePic(gump, 120, 140, 2620, 100, 30);
        x_pos := GFTextEntry(gump, 130, 145, 80, 25, 2100, send_Location.X);

        GFTextLine(gump, 20, 166, 2100, "Y Coordinate");
        GFResizePic(gump, 120, 163, 2620, 100, 30);
        y_pos := GFTextEntry(gump, 130, 168, 80, 25, 2100, send_Location.Y);

        GFTextLine(gump, 20, 189, 2100, "Z Coordinate");
        GFResizePic(gump, 120, 186, 2620, 100, 30);
        z_pos := GFTextEntry(gump, 130, 191, 80, 25, 2100, send_Location.Z);

        return gump;

endfunction
