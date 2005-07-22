/* $Id: config.inc,v 1.1 2004/03/16 14:05:46 folko Exp $
 *
 * Purpose
 * Provide various functions and constants for the shard's behaviour.
 *
 */
use cfgfile;

include "include/exception";

const SHARD_CFG     := ":config:config/shardconfig";
const CONFIG_ELEM   := "Main";

enum CFG_ENTRIES
    SHARD_NAME      := "ShardName",
    SHARD_TIMEZONE  := "TimeZone",

    LINGER_STAFF    := "StaffLingerTime",
    LINGER_PLAYER   := "PlayerLingerTime",
    
    REGEN_HITS      := "HitsRegenRate",
    REGEN_MANA      := "ManaRegenRate",
    REGEN_STAM      := "StamRegenRate",
    
    SAVE_TIME       := "SaveTime",
    SAVE_ANNOUNCE   := "SaveAnnounce"
endenum


/*
 * QueryConfigString(what)
 *
 * Author: Folko
 *
 * Purpose
 * Returns a config string from the shard's main config file.
 *
 * Parameters
 * what:    The name of the config elem to return
 *
 * Return value
 * The config file's value for the desired elem.
 * 
 */
function QueryConfigString(what)
    return(GetConfigString(FindConfigElem(ReadConfigFile(SHARD_CFG), CONFIG_ELEM), what));
endfunction


/*
 * QueryConfigInt(what)
 *
 * Author: Folko
 *
 * Purpose
 * Returns a config integer from the shard's main config file.
 *
 * Parameters
 * what:    The name of the config elem to return
 *
 * Return value
 * The config file's value for the desired elem.
 * 
 */
function QueryConfigInt(what)
    return(GetConfigInt(FindConfigElem(ReadConfigFile(SHARD_CFG), CONFIG_ELEM), what));
endfunction


/*
 * GetShardName()
 *
 * Author: Folko
 *
 * Purpose
 * Returns the shard's name as specified in the config file.
 *
 * Parameters
 * No parameters.
 *
 * Return value
 * The shard's name.
 * 
 */
function GetShardName()
    return(QueryConfigString(SHARD_NAME));
endfunction


/*
 * GetStaffLingerTime()
 *
 * Author: Folko
 *
 * Purpose
 * Returns the linger time for staff in seconds.
 *
 * Parameters
 * No parameters.
 *
 * Return value
 * The staff linger time in seconds.
 * 
 */
function GetStaffLingerTime()
    return(QueryConfigInt(LINGER_STAFF));
endfunction


/*
 * GetPlayerLingerTime()
 *
 * Author: Folko
 *
 * Purpose
 * Returns the linger time for players in seconds.
 *
 * Parameters
 * No parameters.
 *
 * Return value
 * The player linger time in seconds.
 * 
 */
function GetPlayerLingerTime()
    return(QueryConfigInt(LINGER_PLAYER));
endfunction


/*
 * GetTimeZone()
 *
 * Author: Folko
 *
 * Purpose
 * Returns the timezone offset from the GMT time.
 *
 * Parameters
 * No parameters.
 *
 * Return value
 * The offset from GMT
 * 
 */
function GetTimeZone()
    return(QueryConfigInt(SHARD_TIMEZONE));
endfunction


/*
 * GetDefaultRegenRate(stat)
 *
 * Author: Folko
 *
 * Purpose
 * Returns the default regen rate of a stat
 *
 * Parameters
 * stat:    The stat to query
 *
 * Return value
 * The default stat regen rate
 * 
 */
function GetDefaultRegenRate(stat)
    if(stat != REGEN_HITS && stat != REGEN_MANA && stat != REGEN_STAM)
        return(Exception("config::GetDefaultRegenRate: Invalid stat '" + CStr(stat) + "'."));
    endif
    return(QueryConfigInt(stat));
endfunction


/*
 * GetSaveTime()
 *
 * Author: Folko
 *
 * Purpose
 * Returns the time between saves in minutes
 *
 * Parameters
 * No parameters
 *
 * Return value
 * The time between saves in minutes
 * 
 */
function GetSaveTime()
    return(QueryConfigInt(SAVE_TIME));
endfunction


/*
 * GetSaveAnnounceTime()
 *
 * Author: Folko
 *
 * Purpose
 * Returns the time of the save announcement before a save in minutes
 *
 * Parameters
 * No parameters
 *
 * Return value
 * The offset of the save time and announce time
 * 
 */
function GetSaveAnnounceTime()
    return(QueryConfigInt(SAVE_ANNOUNCE));
endfunction
