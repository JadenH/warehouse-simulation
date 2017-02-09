#ifndef WarehouseH
#define WarehouseH

#include <string>
#include <map>
#include <deque>
#include "Shipment.h"

/* Warehouse.h
* Authors: Adam Waggoner, Jaden Holladay
*
* Represents the collection of shipments within a Warehouse
*/

class Warehouse
{
	public:
		Warehouse(const std::string name);
		Warehouse(const Warehouse & rhs);
		~Warehouse();

		void RecieveShipment(const Shipment s);
		void RequestShipment(const Shipment s);
		void RemoveExpired();		

		std::string Name;

	private:
		// Contains shipments indexed by their UPC, and in the order of their expiration dates
		std::map<int, std::deque<Shipment>* >* _Inventory; 
};

#endif