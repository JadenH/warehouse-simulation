#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include <map>
#include <deque>
#include "shipment.h"

/* warehouse.h
* Authors: Adam Waggoner, Jaden Holladay
*
* Represents the collection of shipments within a warehouse
*/

class warehouse
{
	public:
		warehouse(const std::string name);
		warehouse(const warehouse & rhs);
		~warehouse();

		void RecieveShipment(const Shipment s);
		void RequestShipment(const Shipment s);
		void RemoveExpired();

		std::string Name;

	private:
		// Contains shipments indexed by their UPC, and in the order of their expiration dates
		std::map<int, std::deque<Shipment>* >* _Inventory;
};

#endif
