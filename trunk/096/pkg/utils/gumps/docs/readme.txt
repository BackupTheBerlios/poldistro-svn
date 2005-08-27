Gumps by Melanius and Austin
__________________________________________________________
About:

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
__________________________________________________________

Installation:
Extract into x:\xPOLx\pkg\gumps\

You will need to update the code to any scripts that used 
the old gump system. For compatibility though, the old gumps 
include is included with this.

include ":gumps:include/gumps";
gumps.inc will contain the functions necessary for creating 
a gump. 

include ":gumps:include/gumps_ex";
gumps_ex.inc contains helper functions, such as determining 
the width of text, aligning text and cleanly extracting the 
data from text inputs. 

To use the old gump include, use
include ":gumps:include/old/old-gumps";
__________________________________________________________
For licensing information, please see license.txt in the 
docs directory.
