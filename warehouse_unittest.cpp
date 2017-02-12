/* warehouse_unittest.cpp
* Authors: Adam Waggoner, Jaden Holladay
*
* Tests the functionality of the warehouse class.
*/

// ##################### STEP 1 ##################
// Include the necessary header files for testing

#include "Warehouse.h"
#include "Shipment.h"
#include "gtest/gtest.h"

#include <iostream>

// ##################### STEP 2 ##################
// Implement all the tests!

// +++++++++++++++++++ Test Constructors ++++++++++++++++++++++++++

TEST(Test_Constructor, Properly_Assigns_Name) {
  Warehouse some_warehouse("Utah");

  EXPECT_EQ("Utah", some_warehouse.Name);
}

// +++++++++++++++++++ Test Functionality ++++++++++++++++++++++++++

TEST(Test_Constructor, Add_Shipment) {
  Warehouse some_warehouse("Utah");
  Shipment s(5, 10);
  some_warehouse.ReceiveShipment(000000, s);

  std::deque<Shipment> shipments = some_warehouse.Get_Inventory(000000);

  EXPECT_EQ(1, shipments.size());
  EXPECT_EQ(5, shipments.front().Expiration);
  EXPECT_EQ(10, shipments.front().Quantity);
}

// ##################### STEP 3 ##################
// Run all the defined tests by calling RUN_ALL_TESTS() in main().
// This is done for us by linking gtest_main.cc through our makefile.
