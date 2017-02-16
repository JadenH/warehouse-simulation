/* Warehouse.cpp
* Authors: Adam Waggoner, Jaden Holladay
*/

#include "Warehouse.h"
#include "Shipment.h"
#include <map>
#include <iostream>
#include <stack>

//Default constructor
Warehouse::Warehouse(const std::string name)
{
	this->Name = name;
}

//Destructor
Warehouse::~Warehouse()
{
}

void Warehouse::ReceiveShipment(const std::string upc, const Shipment & shipment)
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
  Inventory::iterator it = _inventory.find(upc);
  if (it != _inventory.end())
  {
    // TODO: Need to figure out how to do this properly.
    // RemoveExpired(*(it->second));
    //TODO: Check if expired & remove up to quantity amount.
  }
}

/* Finds the shipments for a given product by upc.
 * Returns a deque or Shipments.
 */
Inventory Warehouse::Get_Inventory() const
{
  return _inventory;
}

// Do we want to have this? Not sure yet...
// bool Warehouse::ContainsProduct(const std::string upc)
// {
//   std::map<int, std::deque<Shipment>* >::iterator it = _inventory.find(upc);
//   return it != _inventory.end();
// }

//Called at the start of each new day. Expired shipments get removed from this warehouse
void Warehouse::RemoveExpired(int date)
{
  //Check each different item type in the inventory
  for(Inventory::iterator itr = _inventory.begin(); itr != _inventory.end(); ++itr)
  {
    //build a stack of expired shipments
    std::stack<Shipments::iterator> destroy_stack;

    Shipments & shipments = itr->second;

    for (Shipments::iterator it = shipments.begin(); it != shipments.end(); ++it)
    {
      if (it->Expiration < date)
      {
        //add the iterator at this position to stack of shipments to be destroyed
        destroy_stack.push(it);
      }
      else
      {
        //since the newest shipments should be added last
        //if we've hit a non-expired shipment, we know there
        //won't be anymore
        break;
      }
    }

    //erase all of the expired shipments
    while(!destroy_stack.empty())
    {
      shipments.erase(destroy_stack.top());
      destroy_stack.pop();
    }
  }
}
