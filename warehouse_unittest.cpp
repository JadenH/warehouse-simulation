/* warehouse_unittest.cpp
* Authors: Adam Waggoner, Jaden Holladay
*
* Tests the functionality of the warehouse class.
*/

// ##################### STEP 1 ##################
// Include the necessary header files for testing

#include "warehouse.h"
#include "gtest/gtest.h"

#include <iostream>

// ##################### STEP 2 ##################
// Implement all the tests!

// +++++++++++++++++++ Test Constructors ++++++++++++++++++++++++++

TEST(Test_Constructor, Properly_Assigns_Name) {
  warehouse some_warehouse("Utah");

  EXPECT_EQ("Utah", some_warehouse.Name);
}

// ##################### STEP 3 ##################
// Run all the defined tests by calling RUN_ALL_TESTS() in main().
// This is done for us by linking gtest_main.cc through our makefile.
