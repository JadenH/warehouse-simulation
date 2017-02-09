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
	int UPC;
	int Lifespan;
	std::string Name;
};

#endif