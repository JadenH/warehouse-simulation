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

//Forward declarations
void UnstockedProducts(Warehouses warehouses, Products products);
void WellStockedProducts(Warehouses warehouses, Products products);

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

      for(Warehouses::iterator itr = warehouses.begin(); itr != warehouses.end(); itr++)
      {
      	itr->second.RemoveExpired(current_day);
      }
    }
    else if (!line.find("Warehouse"))
    {
      warehouses.insert(make_pair(words[2], Warehouse(words[2])));
    }
    else if (!line.find("FoodItem"))
    {
      // TODO: Fix Words[11] (Whitespaces) & get rest of the name.
      //Get the start position of the name of the fooditem
      int name_pos = line.find(words[11]);
      products.insert(make_pair(words[4], Product(words[4], atoi(words[7].c_str()), line.substr(name_pos))));
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

  cout << "Current day: " << current_day << endl;
  cout << "Report by Jaden Holladay & Adam Waggoner" << endl;
  cout << endl; //Print a single blank line after the title
  UnstockedProducts(warehouses, products);
  cout << endl;
  WellStockedProducts(warehouses, products);
  cout << endl;
  // END CITED
  return 0;
}

//Find all unstocked products and print their upcs and names
void UnstockedProducts(Warehouses warehouses, Products products)
{
  cout << "Unstocked Products:" << endl;

	//Create a set of all the upcs in the product table 		
  set<string> upcs;
  for (Products::iterator product = products.begin(); product != products.end(); ++product)
  {
    upcs.insert(product->first);
  }

  //Iterate through each warehouse, and iterate through their inventories.
  for (Warehouses::iterator warehouse = warehouses.begin(); warehouse != warehouses.end(); ++warehouse)
  {
    Inventory inventory = warehouse->second.Get_Inventory();
    for (Inventory::iterator items = inventory.begin(); items != inventory.end(); items++)
    {
      set<string>::iterator item = upcs.find(items->first);

      //If we find certain upc, we just remove it from our set of upcs
      if (item != upcs.end())
      {
        upcs.erase(item);
      }
    }

  }

  //Print all of the names
  for (set<string>::iterator upc = upcs.begin(); upc != upcs.end(); ++upc)
  {
    Products::iterator product = products.find(*(upc));
    if (product != products.end())
    {
      cout << *(upc) + " " + product->second.Name << endl;
    }
  }
}

//Find all unstocked products and print their upcs and names
void WellStockedProducts(Warehouses warehouses, Products products)
{
  cout << "Well Stocked Products:" << endl;
  //Maps each upc to an int count of how many of these products exist
  map<string, int> upcs;

  //Set that will contain upcs of all well stocked items
  set<string> wellstocked;
  
  for (Products::iterator product = products.begin(); product != products.end(); ++product)
  {
    upcs.insert(make_pair(product->first,0));
  }

  //Iterate through each warehouse, and iterate through their inventories.
  for (Warehouses::iterator itr= warehouses.begin(); itr!= warehouses.end(); itr++)
  {
  	//Gets the inventory from the current warehouse
    Inventory inventory = itr->second.Get_Inventory();

    //iterate over each collection of shipments
    for (Inventory::iterator jtr = inventory.begin(); jtr != inventory.end(); jtr++)
    {
      map<string,int>::iterator item = upcs.find(jtr->first);

      //If we find certain upc, increment its count in the map
      if (item != upcs.end())
      {
        upcs.find(item->first)->second++;
      }
    }

  }

  //Print all of the names
  for (map<string, int>::iterator upc = upcs.begin(); upc != upcs.end(); ++upc)
  {
    Products::iterator product = products.find(upc->first);

    //if this product is well stocked
    if (product != products.end() && upcs.find(upc->first)->second >= 2)
    {
      cout << upc->first << " " << product->second.Name << endl;
    }
  }

}