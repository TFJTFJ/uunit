#include "getbaud.h"

speed_t getBaud(int speed)
{
	struct
	{
		int value;
		speed_t baud;
	}
	speeds[] =
		{
			{      0,      B0 },
			{     50,     B50 },
			{     75,     B75 },
			{    110,    B110 },
			{    134,    B134 },
			{    150,    B150 },
			{    200,    B200 },
			{    300,    B300 },
			{    600,    B600 },
			{   1200,   B1200 },
			{   1800,   B1800 },
			{   2400,   B2400 },
			{   4800,   B4800 },
			{   9600,   B9600 },
			{  19200,  B19200 },
			{  38400,  B38400 },
			{  57600,  B57600 },
			{ 115200, B115200 },
			{ 230400, B230400 },
		};

	if(speed < 0)
	{
		throw bad_speed();
	}

	for(const auto& s : speeds)
	{
		if(speed == s.value)
		{
			return s.baud;
		}

		if(speed < s.value)
		{
			return (*((&s)-1)).baud;
		}
	}

	return speeds[sizeof(speeds) / sizeof(*speeds) - 1].baud;
}
