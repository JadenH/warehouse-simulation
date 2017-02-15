#include "Warehouse.h"
#include "Product.h"
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;

int main(int argc, char ** argv)
{
  int current_day = 0;
  std::map<std::string, Warehouse> Warehouses;
  std::map<std::string, Product> Products;

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
      Warehouses.insert(make_pair(words[2], Warehouse(words[2])));
    }
    else if (!line.find("FoodItem"))
    {
      Products.insert(make_pair(words[4], Product(words[4], atoi(words[7].c_str()), std::string(""))));
    }
    else if (!line.find("Request"))
    {
      std::map<std::string, Warehouse>::iterator it = Warehouses.find(words[3]);
      if (it != Warehouses.end())
      {
        it->second.RequestShipment(words[1], atoi(words[2].c_str()));
      }
    }
    else if (!line.find("Receive"))
    {
      std::map<std::string, Product>::iterator product = Products.find(words[3]);
      std::map<std::string, Warehouse>::iterator warehouse = Warehouses.find(words[3]);
      if (product != Products.end() && warehouse != Warehouses.end())
      {
        Shipment shipment(product->second.Lifespan + current_day, atoi(words[2].c_str()));
        warehouse->second.ReceiveShipment(words[1], shipment);
      }

    }
  }
  in.close();

  cout << current_day << endl;
  cout "Report by Jaden Holladay & Adam Waggoner" << endl;
  
  // END CITED
  return 0;
}
