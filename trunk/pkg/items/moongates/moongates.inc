use uo;
use os;

function CreateMoongates()
  var moongates := {
	{4467,	1283,	5, "Moonglow", "britannia"},		// moonglow
    {1336,	1997,	5, "Britain", "britannia"},		// britain
    {1499,	3771,	5, "Jhelom", "britannia"},		// jehlom
	{771,	753,	5, "Yew", "britannia"},		    // yew
    {2701,	693,	5, "Minoc", "britannia"},		// minoc
    {1828,	2948, -20, "Trinsic", "britannia"},	    // trinsic
    {643,	2067,	5, "Skara", "britannia"},		// skara
    {3564,	2140,  34, "Magincia", "britannia"}, 	    // magincia
    
	{4467,	1283,	5, "Moonglow", "britannia_alt"},		// moonglow
    {1336,	1997,	5, "Britain", "britannia_alt"},		// britain
    {1499,	3771,	5, "Jhelom", "britannia_alt"},		// jehlom
	{771,	753,	5, "Yew", "britannia_alt"},		    // yew
    {2701,	693,	5, "Minoc", "britannia_alt"},		// minoc
    {1828,	2948, -20, "Trinsic", "britannia_alt"},	    // trinsic
    {643,	2067,	5, "Skara", "britannia_alt"},		// skara
    {3564,	2140,  34, "Magincia", "britannia_alt"} 	    // magincia    
  };
  var moongate;
  syslog( "Creating moongates." );
  foreach gate in moongates
    foreach thing in ListItemsNearLocation(gate[1], gate[2], gate[3], 0, gate[5]);
      if(thing.objtype != 0x887b)
        DestroyItem(thing);
      endif
    endforeach
	moongate := CreateItemAtLocation( gate[1], gate[2], gate[3], "systemmoongate", 1, gate[5] );
    SetObjProperty(moongate, "City", gate[4]);
    moongate.facing := 29;
    moongate.decayAt := 0;
    moongate.movable := 0;
  endforeach
endfunction
