#include "DateTime.h"
#include <time.h>

// Converts a string in the format of "YYYY/MM/DD" to an int UTC timestamp.
int DateTime::ConvertToUTC(const std::string date)
{
	//Convert the date string to a char*
	const char* dateC = date.c_str();

	//Create an empty tm object
	struct tm theTime = {0, 0, 0, 0, 0, 0, 0, 0, -1, 0, NULL};
	//Convert the data in "date" and store it in the tm struct
    strptime(dateC, "%Y/%m/%d", &theTime);
    //Convert the tm object to an int UTC timestamp
    return mktime(&theTime);
}

//Returns the number of days from A to B (floors to an int using int division)
int DateTime::DaysBetween(const int UTCValueA, const int UTCValueB)
{
	//86400 is the amount of time that elapsed in a day
	return (UTCValueB - UTCValueA) / 86400;
}

//Returns the number of days from date string A to B (floors to an int using int division)
int DateTime::DaysBetween(const std::string UTCValueA, const std::string UTCValueB)
{
	return DaysBetween( ConvertToUTC(UTCValueA), ConvertToUTC(UTCValueB) );
}