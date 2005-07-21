Gumps by Melanius and Austin
__________________________________________________________
1. About
2. Installation
3. documentation




About:
----------------------------
This is a new gump system to replace the old one. 
In this new system, gumps are handled in a more object 
oriented manner, and are no longer dealt with globally. 
The code is more optimized so the gumps will not take as 
many cycles to be generated. 

It was also setup so the function prototypes are similar 
to the old one for faster migration times.

Included is a text command, called previewgump.src that 
shows how a gump can be assembled. It shows various tricks 
and techniques that can be used to put one together.

Also, the long list of graphical constants in the gumps.inc
were removed and placed in a config file. See GumpCfgInfo()
in gumps_ex.inc for more information.




Installation:
----------------------------
Extract into x:\xPOLx\pkg\gumps\

You will need to update the code to any scripts that used 
the old gump system. For compatibility though, the old gumps 
include is included with this.

include ":gumps:includes/gumps";
gumps.inc will contain the functions necessary for creating 
a gump. 

include ":gumps:includes/gumps_ex";
gumps_ex.inc contains helper functions, such as determining 
the width of text, aligning text and cleanly extracting the 
data from text inputs. 

To use the old gump include, use
include ":gumps:includes/old/old-gumps";




documentation:
----------------------------
Function List:
	GFAddButton(byref gump, x, y, off_id, on_id, btn_type:=GF_PAGE_BTN, btn_value:=0)
	GFAddHTMLLocalized(byref gump, x, y, width, height, cliloc, background, scrollbar, hue := 0)
	GFCheckBox(byref gump, x, y, unc_id, che_id, status:=0, btn_value:=0)
	GFCreateGump(x:=0, y:=0, width:=0, height:=0)
	GFDisposable(byref gump, bool)
	GFExtractData(input, data_id)
	GFGumpPic(byref gump, x, y, gump_id, hue := 0)
	GFHTMLArea(byref gump, x, y, width, height, text, background:=0, scrollbar:=0)
	GFMovable(byref gump, bool)
	GFPage(byref gump, page)
	GFRadioButton(byref gump, x, y, unp_id, pres_id, status:=0, btn_value:=0)
	GFResizePic(byref gump, x, y, gump_id, width:=0, height:=0)
	GFSendGump(who, byref gump)
	GFSetRadioGroup(byref gump, group_id)
	GFTextCrop(byref gump, x, y, width, height, hue:=0, text:="")
	GFTextEntry(byref gump, x, y, width, height, txt_color, ini_text:="")
	GFTextLine(byref gump, x, y, hue:=0, text:="")
	GFTilePic(byref gump, x, y, tile_id, hue := 0)

Internal/Private Function List:
	o XGFError(text)

Global Variables:
	(Constants for the GFAddButton() function)
	const GF_PAGE_BTN	:= 0x0;
	const GF_CLOSE_BTN	:= 0x1;
	const GF_DUMMY_BTN	:= 0x2;



__________________________________________________________
For licensing information, please see license.txt in the 
docs directory.
