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
	this->_Inventory = new std::map<int, std::deque<Shipment>* >();
}

//Copy constructor
Warehouse::Warehouse(const Warehouse & rhs)
{
	//TODO: Implement this
}

//Destructor
Warehouse::~Warehouse()
{
	delete(this->_Inventory);
}

void Warehouse::RecieveShipment(Shipment s)
{
	//TODO: Implement this
}

void Warehouse::RequestShipment(Shipment s)
{
	//TODO: Implement this
}

void Warehouse::RemoveExpired()
{
	//TODO: Implement this
}

