#ifndef DATETIMEH
#define DATETIMEH

#include <string>

/* DateTime.h
* 
* Authors: Adam Waggoner and Jaden Holladay
* Contains functions to simplify working with dates using the ctime library
*/

class DateTime
{
	public:
		static int ConvertToUTC(const std::string date);
		static int DaysBetween(const int UTCValueA, const int UTCValueB);
		static int DaysBetween(const std::string a, const std::string b);
};

#endif