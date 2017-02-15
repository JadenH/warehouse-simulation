/* Warehouse.cpp
* Authors: Adam Waggoner, Jaden Holladay
*/

#include "Warehouse.h"
#include "Shipment.h"
#include <map>
#include <iostream>

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
Shipments Warehouse::Get_Inventory(const std::string upc) const
{
  Inventory::const_iterator it = _inventory.find(upc);
  if (it != _inventory.end())
  {
    return it->second;
  }
}

// Do we want to have this? Not sure yet...
// bool Warehouse::ContainsProduct(const std::string upc)
// {
//   std::map<int, std::deque<Shipment>* >::iterator it = _inventory.find(upc);
//   return it != _inventory.end();
// }

void Warehouse::RemoveExpired(Shipments & shipments)
{
  for (Shipments::iterator it = shipments.begin(); it != shipments.end(); ++it)
  {
    if (it->Expiration > 0)
    {
      //TODO: Delete this thing.
    }
  }
}
