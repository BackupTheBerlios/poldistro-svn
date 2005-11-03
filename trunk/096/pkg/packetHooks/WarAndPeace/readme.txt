===================================
  War Request Packet Hook
  Written By MuadDib
===================================

  1) Requirements
  2) How to Install
  3) Thanks To...

===================================
    Requirements
===================================
  To use these scripts, you will need the following:
    A working and installed copy of POL v.096 or newer

===================================
    How To Install
===================================
  1) Extract the zip to somewhere in your pkg directory in POL
  2) Making sure pkg.cfg has Enabled set to 1.
  3) Compile the package with eCompile.
  4) Start POL and begin using it.

===================================
    Notes
===================================
  1) If you want to block entering war mode in certain areas, or
     if any circumstances exist, simply modify the ProcessWarMode(who)
     function. If it returns 0, it will block entering war mode. If
     it returns 1, it will allow it. 

	For Example. In the ProcessWarMode(who) function, you can check
        X and Y, to see if they are in a certain area (box), and if so,
        return 0, and they will not be able to enter mode.

===================================
    Thanks To...
===================================
  Thanks to the POL dev team for continually developing the best 
    Ultima Online server emulator around.
