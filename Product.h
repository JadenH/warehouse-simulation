#ifndef PRODUCTH
#define PRODUCTH

#include <string>

/* product.h
* Authors: Adam Waggoner, Jaden Holladay
*
* Represents a food product with a UPC, _Name, and lifespan.
*/

struct Product
{
	std::string UPC;
	int Lifespan;
	std::string Name;

  int TotalRequested;
  
  Product(std::string upc, int lifespan, std::string name)
  {
    UPC = upc;
    Lifespan = lifespan;
    Name = name;
  }
};

#endif
