use uo;
use util;
use math;
include "include/attributes";

function DealDamage(defender, attacker, rawdamage)
  rawdamage := rawdamage + RandomInt( (GetEffectiveSkill(attacker, 1) ) / 20);
  ApplyRawDamage(defender, rawdamage);
endfunction