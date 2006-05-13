[ - What is this? -]
A party system hook for use until the core supports it. Every effort has been made to make it as OSI-like as possible. It uses the client's party scroll gump, handles chat and private messaging and sends stats updates to other party members allowing you to see their stamina and mana.


[ - Installation - ]
In the 096 distro the BF packet is hooked by the BFCommanad package, so if you're not using the 096 distro, you must add this to uopacket.cfg:
Packet 0xBF
{
  Length variable
  SubCommandOffset 4
  SubCommandLength 1
}

If you already have code that checks if looting another player's corpse is legal, then add the code that checks party information from corpseOnRemove to yours. If you don't have any code to check the legality, and you want it, find where the corpse item is defined and add this line somewhere in the definition of the item:
OnRemoveScript :partySystem:corpseOnRemove

This will call corpseOnRemove when an item is removed from the corpse. Basically you can loot a corpse if it's:
your own corpse
your agressor's corpse (someone who attacks you and you kill them)
a criminal/murderer's
fellow/rival guild member 

If you become a criminal, the flag is set for 2 minutes or whatever default time is defined in repsys.cfg.


NOTE: If you are NOT using the 096 distro, and you are still using the old attributes.inc file, you'll have to update a few functions in doPartySystem.src before it will compile. First, change the attributes include line to this:
include "include/attributes"; // for getting player stats

And then change these lines:
        // Set the length and everything in the packet past name
        packet.SetInt16( OFFSET_SEND_STATUS_LENGTH, 66 );
        packet.SetInt16( OFFSET_SEND_STATUS_CURRENT_HEALTH, GetHp( char ) );
        packet.SetInt16( OFFSET_SEND_STATUS_MAX_HEALTH, GetMaxHp( char ) );
        packet.SetInt8( OFFSET_SEND_STATUS_NAME_CHANGE, 0 );
        packet.SetInt8( OFFSET_SEND_STATUS_VALID, 1 );
        packet.SetInt8( OFFSET_SEND_STATUS_SEX, char.gender );
        packet.SetInt16( OFFSET_SEND_STATUS_STR, GetStrength( char ) );
        packet.SetInt16( OFFSET_SEND_STATUS_DEX, GetDexterity( char ) );
        packet.SetInt16( OFFSET_SEND_STATUS_INT, GetIntelligence( char ) );
        packet.SetInt16( OFFSET_SEND_STATUS_CURRENT_STAMINA, GetStamina( char ) );
        packet.SetInt16( OFFSET_SEND_STATUS_MAX_STAMINA, GetMaxStamina( char ) );
        packet.SetInt16( OFFSET_SEND_STATUS_CURRENT_MANA, GetMana( char ) );
        packet.SetInt16( OFFSET_SEND_STATUS_MAX_MANA, GetMaxMana( char ) );


You also might want to take a look around config.inc and change settings to suit your needs.


[ - Considerations - ]
A big thank you to Max Scherr for his help on the forums (and help with German). Also, thanks to Kinetix, who doesn't know he helped me by posting code on Folko's old forums. And a massive thanks to the POL devs and various other POL supporters who keep these things alive!
Thanks also to Aeros for testing and posting his problems on the forums


[ - Possible bugs - ]
Party chat and private party messages have no font or color because they're sent as unicode and I can't find a list of fonts or colors for unicode
The onCorpseRemove script is somewhat untested


[ - TODO - ]
Documentation for all files and functions (right now everything is mostly in the code)
In corpseOnRemove.src I couldn't find a way to determine agressors. I tried reportalbles but it always came up blank...


[ - Contact - ]
Please send me any comments, questions or BUGS.

E-mail: tekproxy@gmail.com
AIM: tekproxy