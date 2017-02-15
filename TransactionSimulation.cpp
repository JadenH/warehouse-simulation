#include "Warehouse.h"
#include "Product.h"
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <set>

using namespace std;

typedef std::map<std::string, Warehouse> Warehouses;
typedef std::map<std::string, Product> Products;

void UnstockedProducts(Warehouses warehouses, Products products);

int main(int argc, char ** argv)
{
  int current_day = 0;

  Warehouses warehouses;
  Products products;

  ifstream in(argv[1]);
  while (true)
  {
    string line;
    std::getline(in, line);
    // If the read failed, we're probably at end of file
    //   (or else the disk went bad).  Exit the loop.
    if (in.fail())
      break;

    vector<string> words;
    boost::split(words, line, boost::is_any_of(" "));

    if (!line.find("Next day:"))
    {
      current_day++;
    }
    else if (!line.find("Warehouse"))
    {
      warehouses.insert(make_pair(words[2], Warehouse(words[2])));
    }
    else if (!line.find("FoodItem"))
    {
      // TODO: Fix Words[11] (Whitespaces) & get rest of the name.
      products.insert(make_pair(words[4], Product(words[4], atoi(words[7].c_str()), words[11])));
    }
    else if (!line.find("Request"))
    {
      std::map<std::string, Warehouse>::iterator it = warehouses.find(words[3]);
      if (it != warehouses.end())
      {
        it->second.RequestShipment(words[1], atoi(words[2].c_str()));
      }
    }
    else if (!line.find("Receive"))
    {
      std::map<std::string, Product>::iterator product = products.find(words[1]);
      std::map<std::string, Warehouse>::iterator warehouse = warehouses.find(words[3]);
      if (product != products.end() && warehouse != warehouses.end())
      {
        Shipment shipment(product->second.Lifespan + current_day, atoi(words[2].c_str()));
        warehouse->second.ReceiveShipment(words[1], shipment);
      }

    }
  }
  in.close();

  cout << current_day << endl;
  cout << "Report by Jaden Holladay & Adam Waggoner" << endl;
  UnstockedProducts(warehouses, products);

  // END CITED
  return 0;
}

void UnstockedProducts(Warehouses warehouses, Products products)
{
  set<string> upcs;
  for (Products::iterator product = products.begin(); product != products.end(); ++product)
  {
    upcs.insert(product->first);
  }

  for (Warehouses::iterator warehouse = warehouses.begin(); warehouse != warehouses.end(); ++warehouse)
  {
    Inventory inventory = warehouse->second.Get_Inventory();
    for (Inventory::iterator items = inventory.begin(); items != inventory.end(); items++)
    {
      set<string>::iterator item = upcs.find(items->first);
      if (item != upcs.end())
      {
        upcs.erase(item);
      }
    }

  }

  for (set<string>::iterator upc = upcs.begin(); upc != upcs.end(); ++upc)
  {
    Products::iterator product = products.find(*(upc));
    if (product != products.end())
    {
      cout << *(upc) + " " + product->second.Name << endl;
    }
  }
}
