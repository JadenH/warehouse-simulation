#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include <map>
#include <deque>
#include "Shipment.h"

/* Warehouse.h
* Authors: Adam Waggoner, Jaden Holladay
*
* Represents the collection of shipments within a warehouse
*/

class Warehouse
{
	public:
		Warehouse(const std::string name);
		Warehouse(const Warehouse & rhs);
		~Warehouse();

		void ReceiveShipment(const int upc, const Shipment & shipment);
		void RequestShipment(const int upc, const int quantity);

    std::deque<Shipment> Get_Inventory(const int upc);

		std::string Name;

	private:
		// Contains shipments indexed by their UPC, and in the order of their expiration dates
		std::map<int, std::deque<Shipment>* >* _inventory;
    void RemoveExpired(int upc);
};

#endif
