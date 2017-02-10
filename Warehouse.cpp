/* warehouse.cpp
* Authors: Adam Waggoner, Jaden Holladay
*/

#include "warehouse.h"
#include "shipment.h"
#include <map>

//Default constructor
warehouse::warehouse(const std::string name)
{
	this->Name = name;
	this->_Inventory = new std::map<int, std::deque<Shipment>* >();
}

//Copy constructor
warehouse::warehouse(const warehouse & rhs)
{
	//TODO: Implement this
}

//Destructor
warehouse::~warehouse()
{
	delete(this->_Inventory);
}

void warehouse::RecieveShipment(Shipment s)
{
	//TODO: Implement this
}

void warehouse::RequestShipment(Shipment s)
{
	//TODO: Implement this
}

void warehouse::RemoveExpired()
{
	//TODO: Implement this
}
