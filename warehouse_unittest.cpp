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
  some_warehouse.ReceiveShipment("000000", s);

  std::deque<Shipment> shipments = some_warehouse.Get_Inventory("000000");

  EXPECT_EQ(1, shipments.size());
  EXPECT_EQ(5, shipments.front().Expiration);
  EXPECT_EQ(10, shipments.front().Quantity);
}

// +++++++++++++++++++ Test DateTime +++++++++++++++++++

/* NOTES ON time.h
*
* Uses the local time zone of the machine running the code.
* this shouldn't be a problem since we're not worried
* about hours or minutes.
*
* Need to fully initialize a struct tm to be empty before
* converting into it.
*/

#include "DateTime.cpp"

// Converts a datetime to a UTC time code
TEST(Test_DateTime, Convert_UTC)
{
	int utcTime = DateTime::ConvertToUTC("1996/12/11");

  EXPECT_EQ(850287600, utcTime);
}

//Assert that the timestamps for two different dates are 1 day apart from eachother when converted to utc
TEST(Test_DateTime, UTC_Date_Difference)
{
	std::string dateA = "1996/12/11";
	std::string dateB = "1996/12/12";

	int utcTimeA = DateTime::ConvertToUTC(dateA);
	int utcTimeB = DateTime::ConvertToUTC(dateB);

  //Ensure that the length of time between the two dates is
  //86400 (the length of one day)
  EXPECT_EQ(utcTimeB - utcTimeA, 86400);
  EXPECT_EQ(DateTime::DaysBetween(dateA,dateB), 1);
  EXPECT_EQ(DateTime::DaysBetween(utcTimeA, utcTimeB), 1);
}

// Tests the DateTime implementation on a pretty big range of dates (my lifetime so far!)
// Demonstrates that the DateTime functions correctly account for leap years
TEST(Test_DateTime, UTC_Big_Date_Difference)
{
	std::string dateA = "1996/12/11";
	std::string dateB = "2017/02/14";

  EXPECT_EQ(DateTime::DaysBetween(dateA,dateB), 7370);
}

// ##################### STEP 3 ##################
// Run all the defined tests by calling RUN_ALL_TESTS() in main().
// This is done for us by linking gtest_main.cc through our makefile.
