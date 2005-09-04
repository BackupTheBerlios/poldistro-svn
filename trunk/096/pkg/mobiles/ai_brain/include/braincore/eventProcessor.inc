/*===============================================================
* Current Version
* EVENTPROCESSOR.INC - v1.0
* Updated 9/1/2005 6:20AM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

function ProcessEvent(byref ev)
	var old_priority := set_priority(25);
	
	case( ev.type )
		//
		// *Check movement first, since its the event that seems to be sent most often.
		//
		
		// Move NPC
		// .source	: From/To whom/what?
		// .speed	: Walk/Run
		// .direction	: Away/Towards
		// .loop	: Number of times to attempt to loop the movement.
		NPCEVENT_MOVE:
			Movement(ev);
			break;
			
		// Instructs the npc to walk toward an XY coordinate.
		// .x and .y	: From/To  coordinates
		// .speed	: Walk/Run
		// .direction	: Away/Towards
		// .loop	: Number of times to attempt to loop the movement.
		NPCEVENT_MOVE_XY:
			MovementXY(ev);
			break;
			
		// Wander somewhere
		// .loop	: Number of times to attept to wander.
		NPCEVENT_WANDER:
	   		MovementWander(ev);
	   		break;
			
		// Triggered when a mobile enter's the npcs 'area size'.
		// .source	: What entered the area
		SYSEVENT_ENTEREDAREA:
			if ( g_settings.exists("enter_react_script") )
				var process := 0; //GetNerve("EnterReaction");
				if ( !process )
					//StartNerve("EnterReaction", g_settings["enter_react_script"], {me, ev, settings});
				else
					process.SendEvent(ev);
				endif
			endif
			break;
			
		//
		// * Check System Events that the core sends.
		//
			
		// Triggered when a mobile leaves the npc's 'area size'.
		// .source	: What left the area
		SYSEVENT_LEFTAREA:
			if ( g_settings.exists("leave_react_script") )
				var process := 0; //GetNerve("LeaveReaction");
				if ( !process )
					//StartNerve("LeaveReaction", g_settings["leave_react_script"], {me, ev, settings});
				else
					process.SendEvent(ev);
				endif
			endif
			break;
			
		// Sent when something targets the npc to begin combat or
		// when something has damaged the npc.
		// .source	: What caused the damage or engaged the npc
		// For SYSEVENT_DAMAGED
		// .damaged	: Integer amount of damage.
		SYSEVENT_ENGAGED:
		SYSEVENT_DAMAGED:
			if ( g_settings.exists("combat_script") )
				if ( (ev.source).ISA(POLCLASS_MOBILE) )
					var process := 0; //GetNerve("Combat");
					if ( !process )
						//StartNerve("Combat", g_settings["combat_script"], {me, ev, settings});
					else
						process.SendEvent(ev);
					endif
				endif
			endif
			break;
			
		// Instructs the npc to run its disengage nerve.
		// When something attacking it goes out of warmode, this is run.
		// .source	: What was targetting this npc but has now left combat mode.
		SYSEVENT_DISENGAGED:
			if ( g_settings.exists("disengage_script") )
				var process := 0; //GetNerve("Disengage");
				if ( !process )
					//StartNerve("Disengage", g_settings["disengage_script"], {me, ev, settings});
				else
					process.SendEvent(ev);
				endif
			endif
			break;
			
		// When speech is made by a player, this nerve is used.
		// Note: The NPC function Say() doesnt yet pass around the speech event.
		// .source	: Where the speech originated.
		// .text	: The actual speech
		// .uc_text	: a "Unicode array" of 2-byte "Big Endian" integers.
		// .langcode	: a 3-character, uppercase language code.
		// .texttype	: "yell", "whisper", "emote", "default".
		SYSEVENT_SPEECH:
			if( g_settings.exists("listen_script") )
				var process := 0; //GetNerve("Speech");
				if ( !process )
					//StartNerve("Speech", g_settings["listen_script"], {me, ev, settings});
				else
					process.SendEvent(ev);
				endif
			endif
			break;
			
		// Instructs the npc to run its double click script.
		// Run when the npc is double clicked by a player.
		// .source	: What sent the double click
		SYSEVENT_DOUBLECLICKED:
			if ( g_settings.exists("dbl_click_script") )
				if ( Distance(ev.source, npc) <= g_settings["dbl_click_range"] )
					var process := 0; //GetNerve("DblClick");
					if ( !process )
						//StartNerve("DblClick", g_settings["dbl_click_script"], {npc, ev, settings});
					else
						process.SendEvent(ev);
					endif
				endif
			endif
			break;
			
		// The NPC is a merchant, and has sold or purchased something.
		// Both sold and bought events are sent to this same nerve.
		// The best thing to do is fork it into two functions inside the
		// nerve script to handle each event type.
		// MERCHANT_SOLD means the merchant sold an item to the player.
		// MERCHANT_BOUGHT means the merchatn bought something from the player.
		//
		// .source	: Who the merchant is selling to/buying from.
		// .amount	: Gold amount for the sale/purchase.
		SYSEVENT_MERCHANT_SOLD:
		SYSEVENT_MERCHANT_BOUGHT:
			if ( g_settings.exists("merchant_script") )
				var process := 0; //GetNerve("Merchant");
				if ( !process )
					//StartNerve("Merchant", g_settings["merchant_script"], {npc, ev, settings});
				else
					process.SendEvent(ev);
				endif
			endif
			break;
			
		// Someone has dragged an item onto the npc.
		// .source	: What dragged the item over the npc.
		// .item	: The item being given to the npc.
		SYSEVENT_ITEM_GIVEN:
			if ( g_settings.exists("give_item_script") )
				var process := 0; //GetNerve("GiveItem");
				if ( !process )
					//StartNerve("GiveItem", g_settings["give_item_script"], {npc, ev, settings});
				else
					process.SendEvent(ev);
				endif
			endif
			break;
			
		//
		// * Check custom events
		//
				
		// Instructs the npc to run its flee script.
		// .source	: What to flee from.
		NPCEVENT_FLEE:
			if ( g_settings.exists("flee_script") )
				var process := 0; //GetNerve("Flee");
				if ( !process )
					//StartNerve("Flee", g_settings["flee_script"], {npc, ev, settings});
				else
					process.SendEvent(ev);
				endif
			endif
			break;
			
		//A nerve has instructed the brain to kill another nerve or its self.
		// .name	: Nerve name
		NPCEVENT_ENDNERVE:
			//KillNerve(ev.name);
			break;
			
		//A nerve has instructed the brain to start another nerve.
		// .name	: Nerve name
		// .script	: Nerve script
		// .data	: array of goodies
		NPCEVENT_STARTNERVE:
			//StartNerve(ev.name, ev.script, ev.data);
			break;
			
		// Set a new opponent!
		// NOTE: Auto-sets Warmode=1!
		// .source	: Opponent (mobile)
		NPCEVENT_OPPONENT:
			SetOpponent(ev.source);
			break;
			
		// Say something
		// .text	: Speech content
		// .texttype	: Speech type ("default", "whisper", yell")
		// .doevent	: Sends SYSEVENT_SPEECH to surrounding npcs
		NPCEVENT_SPEAK:
			Say(ev.text, ev.texttype, ev.doevent);
			break;
			
		// Turn toward something
		// .source	: Target (anything)
		// .direction	: NETURN_TOWARD or NETURN_AWAY
		NPCEVENT_TURN:
			case (ev.direction)
				NETURN_TOWARD:
					TurnToward(ev.source);
				NETURN_AWAY:
					TurnAwayFrom(ev.source);
			endcase
			break;
			
		// Face towards or away from XY coordinates.
		// .x and .y replace .source for TURN_XY
		// .direction	: NETURN_TOWARD or NETURN_AWAY
		NPCEVENT_TURN_XY:
			case (ev.direction)
				NETURN_TOWARD:
					TurnTowardLocation(ev.x, ev.y);
				NETURN_AWAY:
					TurnAwayFromLocation(ev.x, ev.y);
			endcase
			break;
			
		// Set WarMode state
		// NOTE: Auto-clears Opponent if turned off!
		// .value : 0=Off. 1=On.
		NPCEVENT_WARMODE:
			SetWarmode( ev.value );
			break;
	   		
	   	// Force the npc to go into its sleep mode.
	   	// If the next event in the queue tells it to wake up,
	   	// this command will be useless.
	   	NPCEVENT_SLEEP:
	   		//idle_ticks := g_settings["idle_ticks"]+1;
	   		break;
	   		
	   	// Force the npc out of sleep mode.
	   	NPCEVENT_WAKEUP:
	   		//sleep_mode := 0;
	   		//idle_ticks := 0;
	   		break;
	   		
	   	// Forward an event from one nerve to another.
	   	// .NerveName	: The name of the nerve to forward the event to.
	   	// .mask	: Type of event for the nerve to receive.
	   	// .data	: Data to forward to the nerve.
	   	NPCEVENT_FWDNERVE:
	   		var process := 0; //GetNerve(ev.NerveName);
			if ( process )
				process.SendEvent(ev);
			endif
			break;
			
		// If the event .type is unknown, send it to the
		// npc's "virtual" nerve if it has one.
	   	default:
	   		if ( g_settings.exists("virtual_nerve") )
	   			var process := 0; //GetNerve("Virtual");
				if ( !process )
					//StartNerve("Virtual", g_g_settings["virtual_nerve"], {npc, ev, settings});
				else
					process.SendEvent(ev);
				endif
			endif
			break;
	   endcase

	   // If the event has a .process member, reply to it by sending
	   // an event with .type being the NPCEVENT_DONE constant
	   // and telling it what event it sent that has finished
	   // being processed.
	   if ( ev.process )
	   	(ev.process).SendEvent(struct{"type":=NPCEVENT_DONE, "source":=ev.type});
	   endif
	   
	   set_priority(old_priority);
endfunction