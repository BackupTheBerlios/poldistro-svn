@echo off
REM $Id: realmgen.bat,v 1.1 2004/03/16 14:05:46 folko Exp $

uoconvert multis
move multis.cfg config

uoconvert tiles
move tiles.cfg config

uoconvert landtiles
move landtiles.cfg config

uoconvert map     realm=britannia mapid=0 usedif=1 width=6144 height=4096
uoconvert statics realm=britannia
uoconvert maptile realm=britannia


