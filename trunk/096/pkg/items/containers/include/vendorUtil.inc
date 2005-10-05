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

include ":containers:storageAreas";

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
function CPV_DeleteContainers(npc)
	var container_id := CP_GetMobileContainerID(npc);	
	CP_RemoveStorageAreaContainer(container_id, "Merchat - ForSale");
	CP_RemoveStorageAreaContainer(container_id, "Merchat - Buying");
	CP_RemoveStorageAreaContainer(container_id, "Merchat - ShoppingCart");
	CP_RemoveStorageAreaContainer(container_id, "Merchat - Holding");
endfunction

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
function CPV_GetForSaleContainer(npc)
	return CP_GetStorageContainerForMobile(npc, "Merchat - ForSale", CP_CREATE);
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
function CPV_GetBuyingContainer(npc)
	return CP_GetStorageContainerForMobile(npc, "Merchat - Buying", CP_CREATE);
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
function CPV_GetShoppingCartContainer(npc)
	return CP_GetStorageContainerForMobile(npc, "Merchat - ShoppingCart", CP_CREATE);
endfunction

/*
 * CPV_ShoppingCartContainer(npc)
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
function CPV_GetHoldingContainer(npc)
	return CP_GetStorageContainerForMobile(npc, "Merchat - Holding", CP_CREATE);
endfunction