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

// Test adding a shipment to a warehouse inventory.
TEST(Test_Functionality, Add_Shipment) {
  Warehouse some_warehouse("Utah");
  Shipment s(5, 10);
  some_warehouse.ReceiveShipment("000000", s);

  Shipments shipments = some_warehouse.Get_Inventory().find("000000")->second;

  EXPECT_EQ(1, shipments.size());
  EXPECT_EQ(5, shipments.front().Expiration);
  EXPECT_EQ(10, shipments.front().Quantity);
}

// Check that requesting all the quanitity removes the product
// from the warehouse inventory.
TEST(Test_Functionality, Request_Shipment_Removed) {
  Warehouse some_warehouse("Utah");
  Shipment s(5, 10);
  some_warehouse.ReceiveShipment("000000", s);
  some_warehouse.RequestShipment("000000", 10);

  Inventory shipments = some_warehouse.Get_Inventory();

  EXPECT_EQ(0, shipments.size());
}

// Check that removing some quantity does not remove the entire shipment.
TEST(Test_Functionality, Request_Shipment) {
  Warehouse some_warehouse("Utah");
  Shipment s(5, 10);
  some_warehouse.ReceiveShipment("000000", s);
  some_warehouse.RequestShipment("000000", 5);

  Inventory shipments = some_warehouse.Get_Inventory();
  Shipments product_shipments = some_warehouse.Get_Inventory().find("000000")->second;

  EXPECT_EQ(1, shipments.size());
  EXPECT_EQ(5, product_shipments.front().Expiration);
  EXPECT_EQ(5, product_shipments.front().Quantity);
}

//Ensure that expired shipments are fully removed from an inventory
TEST(Test_Functionality, Expired_Removal)
{
	Warehouse test_warehouse("Mordor");
	Shipment s(5,10);

	test_warehouse.ReceiveShipment("0237", s);

	test_warehouse.RemoveExpired(100);

	EXPECT_EQ(0, test_warehouse.Get_Inventory().size());
}

//Ensure that expired shipments are fully removed from an inventory
TEST(Test_Functionality, Expired_Removal_2)
{
	Warehouse test_warehouse("Mordor");
	Shipment s(2,10);

	test_warehouse.ReceiveShipment("0237", s);
	s.Expiration = 6;
	s.Quantity = 2;
	test_warehouse.ReceiveShipment("0237", s);

	test_warehouse.RemoveExpired(3);

	EXPECT_EQ(1, test_warehouse.Get_Inventory().size());
	EXPECT_EQ(1, test_warehouse.Get_Inventory().find("0237")->second.size());
}

// ##################### STEP 3 ##################
// Run all the defined tests by calling RUN_ALL_TESTS() in main().
// This is done for us by linking gtest_main.cc through our makefile.
