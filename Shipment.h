#ifndef SHIPMENTH
#define SHIPMENTH

/* Shipment.h
* Authors: Adam Waggoner, Jaden Holladay
*
* Represents a shipment of products with a lifetime and quantity
*/

struct Shipment
{
	//UTC timestamp of expiration
	int Expiration;
	int Quantity;
};

#endif