/* Warehouse.cpp
 * Authors: Adam Waggoner, Jaden Holladay
 */

#include "Warehouse.h"
#include "Shipment.h"
#include <map>
#include <iostream>
#include <stack>

namespace cs3505
{
  //Default constructor
  Warehouse::Warehouse(const std::string name)
  {
    this->Name = name;
  }

  void Warehouse::ReceiveShipment(const std::string upc, Shipment shipment)
  {

    Inventory::iterator item = _inventory.find(upc);

    // If we have added this product upc before we add it to the deque.
    // Otherwise create a new deque and add the shipment.
    if (item != _inventory.end())
    {
      item->second.push_back(shipment);
    }
    else
    {
      Shipments shipments;
      shipments.push_back (shipment);
      _inventory.insert(make_pair(upc, shipments));
    }
  }

  void Warehouse::RequestShipment(const std::string upc, const int quantity)
  {
    Inventory::iterator inventory_item = _inventory.find(upc);

    // Check that we were able to find the product, if not return early.
    if(inventory_item == _inventory.end())
    {
      return;
    }

    Shipments & product_shipments = inventory_item->second;

    // Create a stack for all the shipments we will need to remove from our inventory.
    int number_shipments_removed = 0;
    int amount = quantity;
    for(Shipments::iterator shipment = product_shipments.begin(); shipment != product_shipments.end(); shipment++)
    {
      if (amount != 0)
      {
        //if there is more than enough in the current shipment,
        //remove the remaining quantity and break out of this loop
        if(shipment->Quantity > amount)
        {
          shipment->Quantity -= amount;
          break;
        }

        number_shipments_removed++;
        amount -= shipment->Quantity;
      }
      else
      {
        break;
      }
    }

    if (number_shipments_removed > 0)
    {
      // Remove the shipments requested.
      product_shipments.erase(product_shipments.begin(), product_shipments.begin() + number_shipments_removed);

      if(product_shipments.size() == 0)
      {
        //If there are no more shipments of this item, remove it from the inventory
        _inventory.erase(inventory_item);
      }
    }
  }

/* Finds the shipments for a given product by upc.
 * Returns a deque or Shipments.
 */
  Inventory Warehouse::Get_Inventory() const
  {
    return _inventory;
  }

  //Called at the start of each new day. Expired shipments get removed from this warehouse
  void Warehouse::RemoveExpired(int date)
  {
    std::stack<Inventory::iterator> erase_stack_ments;

    //Check each different item type in the inventory
    for(Inventory::iterator inventory = _inventory.begin(); inventory != _inventory.end(); ++inventory)
    {
      //build a stack of expired shipments
      int number_shipments_expired = 0;

      Shipments & shipments = inventory->second;

      for (Shipments::iterator shipment = shipments.begin(); shipment != shipments.end(); ++shipment)
      {
        if (date >= shipment->Expiration)
        {
          //add the iterator at this position to stack of shipments to be destroyed
          number_shipments_expired++;
        }
        else
        {
          //since the newest shipments should be added last
          //if we've hit a non-expired shipment, we know there
          //won't be anymore
          break;
        }
      }

      if (number_shipments_expired > 0)
      {
        // Remove the expired shipments
        shipments.erase(shipments.begin(), shipments.begin() + number_shipments_expired);

        // If there is no more shipments of the product in the warehouse we can remove it entirely.
        if(shipments.size() == 0)
        {
          erase_stack_ments.push(inventory);
        }
      }
    }

    //If there are "shipments" in the inventory with no shipment objects, erase them.
    while(!erase_stack_ments.empty())
    {
      _inventory.erase(erase_stack_ments.top());
      erase_stack_ments.pop();
    }

  }
}
