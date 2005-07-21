
function is_fish(theobj)
  if((theobj >= UOBJ_FISH_START) && (theobj <= UOBJ_FISH_END) )
    return 1;
  elseif ((theobj >= UOBJ_SFISH_START) && (theobj <= UOBJ_SFISH_END))
    return 1;
  else
    return 0;
  endif
endfunction

function CarveFish(who, blade, use_on)
  if((!Accessible(who, use_on)) or (!CheckLineOfSight(who, use_on)) or (dist(who, use_on) > 2))
    SendSysMessage(who, "You cannot use that.");
    return;
  endif
  if((!ReserveItem(use_on)) || (use_on.movable == 0))
    SendSysMessage(who, "You cannot use that.");
    return;
  endif
  var num_steaks := (4 * use_on.amount);
  PlaySoundEffect(who, SFX_57);
  if(DestroyItem(use_on))
    CreateItemInBackpack(who, UOBJ_FISHSTEAK, num_steaks);
    SendSysMessage(who, "You carve the fish steaks and put them in your backpack.");
  endif
  sleep(1);
endfunction

