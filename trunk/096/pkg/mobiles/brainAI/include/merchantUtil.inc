// $Id$

/*===============================================================
* Current Version
* MERCHANTUTIL.INC - v1.0
* Updated 10/2/2005 8:39PM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;


/*
 * NPC_MerchantForSaleContainer(npc)
 *
 * Purpose
 *
 * Parameters
 * npc:	
 *
 * Return value
 * Returns a container
 *
 */
function NPC_MerchantForSaleContainer(npc)
	var forsale_pack := CInt(GetObjProperty(npc, "ForSaleContainer"));
	forsale_pack := SystemFindObjectBySerial(forsale_pack);
	
	if ( !forsale_pack )
		forsale_pack := CreateItemInBackPack(npc, "backpack", 1);
		SetName(forsale_pack, "Items Being Sold");
		SetObjProperty(npc, "ForSaleContainer", forsale_pack.serial);
	endif
	
	return forsale_pack;
endfunction

/*
 * NPC_MerchantBuyingContainer(npc)
 *
 * Purpose
 *
 * Parameters
 * npc:	
 *
 * Return value
 * Returns a container
 *
 */
function NPC_MerchantBuyingContainer(npc)
	var buying_pack := CInt(GetObjProperty(npc, "BuyingContainer"));
	buying_pack := SystemFindObjectBySerial(buying_pack);
	
	if ( !buying_pack )
		buying_pack := CreateItemInBackPack(npc, "backpack", 1);
		SetName(buying_pack, "Items Ill Buy");
		SetObjProperty(npc, "BuyingContainer", buying_pack.serial);
	endif
	
	return buying_pack;
endfunction

/*
 * NPC_MerchantShoppingCartContainer(npc)
 *
 * Purpose
 *
 * Parameters
 * npc:	
 *
 * Return value
 * Returns a container
 *
 */
function NPC_MerchantShoppingCartContainer(npc)
	var shopcart_pack := CInt(GetObjProperty(npc, "ShopCartContainer"));
	shopcart_pack := SystemFindObjectBySerial(shopcart_pack);
	
	if ( !shopcart_pack )
		shopcart_pack := CreateItemInBackPack(npc, "backpack", 1);
		SetName(shopcart_pack, "Shopping Cart");
		SetObjProperty(npc, "ShopCartContainer", shopcart_pack.serial);
	endif
	
	return shopcart_pack;
endfunction