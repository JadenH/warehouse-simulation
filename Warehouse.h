#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include <map>
#include <vector>
#include "Shipment.h"

/* Warehouse.h
* Authors: Adam Waggoner, Jaden Holladay
*
* Represents the collection of shipments within a warehouse
*/

typedef std::vector<Shipment> Shipments;
typedef std::map<std::string, Shipments> Inventory;

class Warehouse
{
	public:
		Warehouse(const std::string name);
		~Warehouse();

		void ReceiveShipment(const std::string upc, const Shipment & shipment);
		void RequestShipment(const std::string upc, const int quantity);

    Shipments Get_Inventory(const std::string upc) const;

		std::string Name;

	private:
		// Contains shipments indexed by their UPC, and in the order of their expiration dates
		Inventory _inventory;
    void RemoveExpired(Shipments & shipments);
};

#endif
