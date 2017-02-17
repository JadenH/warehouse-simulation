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
namespace cs3505
{
  typedef std::vector<Shipment> Shipments;
  typedef std::map<std::string, Shipments> Inventory;

  class Warehouse
  {
    public:
      Warehouse(const std::string name);

      void ReceiveShipment(const std::string upc, Shipment shipment);
      void RequestShipment(const std::string upc, const int quantity);
      void RemoveExpired(int date);

      Inventory Get_Inventory() const;

      std::string Name;

    private:
      // Contains shipments indexed by their UPC, and in the order of their expiration dates
      Inventory _inventory;
  };
}
#endif
