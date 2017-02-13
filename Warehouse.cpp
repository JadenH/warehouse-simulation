/* Warehouse.cpp
* Authors: Adam Waggoner, Jaden Holladay
*/

#include "Warehouse.h"
#include "Shipment.h"
#include <map>

//Default constructor
Warehouse::Warehouse(const std::string name)
{
	this->Name = name;
	_inventory = new std::map<int, std::deque<Shipment>* >();
}

//Copy constructor
Warehouse::Warehouse(const Warehouse & rhs)
{
	//TODO: Implement this
}

//Destructor
Warehouse::~Warehouse()
{
	delete _inventory;
}

void Warehouse::ReceiveShipment(const int upc, const Shipment & shipment)
{
  std::map<int, std::deque<Shipment>* >::iterator it = _inventory->find(upc);

  // If we have added this product upc before we add it to the deque.
  // Otherwise create a new deque and add the shipment.
  if (it != _inventory->end())
  {
    it->second->push_back(shipment);
  }
  else
  {
    std::deque<Shipment>* Shipments = new std::deque<Shipment>();
    Shipments->push_back (shipment);
    _inventory->insert(make_pair(upc, Shipments));
  }
}

void Warehouse::RequestShipment(const int upc, const int quantity)
{
  std::map<int, std::deque<Shipment>* >::iterator it = _inventory->find(upc);
  if (it != _inventory->end())
  {
    RemoveExpired(upc);
    //TODO: Check if expired & remove up to quantity amount.
  }
}

/* Finds the shipments for a given product by upc.
 * Returns a deque or Shipments.
 */
std::deque<Shipment> Warehouse::Get_Inventory(const int upc)
{
  std::map<int, std::deque<Shipment>* >::iterator it = _inventory->find(upc);
  if (it != _inventory->end())
  {
    // Return the dereferenced deque of shipments.
    return *(it->second);
  }
}

// Do we want to have this? Not sure yet...
// bool Warehouse::ContainsProduct(const int upc)
// {
//   std::map<int, std::deque<Shipment>* >::iterator it = _inventory->find(upc);
//   return it != _inventory->end();
// }

void Warehouse::RemoveExpired(int upc)
{
	//TODO: Implement this
}
