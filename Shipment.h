#ifndef SHIPMENTH
#define SHIPMENTH

/* Shipment.h
 * Authors: Adam Waggoner, Jaden Holladay
 *
 * Represents a shipment of products with a lifetime and quantity
 */
namespace cs3505
{
  struct Shipment
  {
    //UTC timestamp of expiration
    int Expiration;
    int Quantity;

    Shipment(int expiration, int quantity)
    {
      Expiration = expiration;
      Quantity = quantity;
    }
  };
}


#endif
