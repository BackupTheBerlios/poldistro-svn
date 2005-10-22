Currently POL Gump Designer (PGD), gets your UO installation directory by reading the
registry entry.

You can manually specify the directory in which your mul files are stored by
creating a PGumpDesigner.exe.config

and adding the content:

<?xml version="1.0" encoding="utf-8" ?>
<configuration>
   <PathToGumpsMul>C:\\Path\to\your\gumps.mul</PathToGumpsMul>
   <PathToFontsMul>C:\\Path\to\your\fonts.mul</PathToFontsMul>
</configuration>

by replacing the paths with ones you like.
