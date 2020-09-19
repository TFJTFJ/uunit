#include <uunit.h>

#include "getbaud.h"

class ExampleTest
	: public uUnit
{
public:
	ExampleTest()
	{
		uUNIT_TEST(ExampleTest::boundaryTests);
		uUNIT_TEST(ExampleTest::exceptionTests);
	}

	void boundaryTests()
	{
		uUNIT_ASSERT_EQUAL(B0, getBaud(0));
		uUNIT_ASSERT_EQUAL(B0, getBaud(1));
		uUNIT_ASSERT_EQUAL(B0, getBaud(49));

		uUNIT_ASSERT_EQUAL(B50, getBaud(50));
		uUNIT_ASSERT_EQUAL(B50, getBaud(51));
		uUNIT_ASSERT_EQUAL(B50, getBaud(74));

		uUNIT_ASSERT_EQUAL(B75, getBaud(75));
		uUNIT_ASSERT_EQUAL(B75, getBaud(76));
		uUNIT_ASSERT_EQUAL(B75, getBaud(109));

		uUNIT_ASSERT_EQUAL(B110, getBaud(110));
		uUNIT_ASSERT_EQUAL(B110, getBaud(111));
		uUNIT_ASSERT_EQUAL(B110, getBaud(133));

		uUNIT_ASSERT_EQUAL(B134, getBaud(134));
		uUNIT_ASSERT_EQUAL(B134, getBaud(135));
		uUNIT_ASSERT_EQUAL(B134, getBaud(149));

		uUNIT_ASSERT_EQUAL(B150, getBaud(150));
		uUNIT_ASSERT_EQUAL(B150, getBaud(151));
		uUNIT_ASSERT_EQUAL(B150, getBaud(199));

		uUNIT_ASSERT_EQUAL(B200, getBaud(200));
		uUNIT_ASSERT_EQUAL(B200, getBaud(201));
		uUNIT_ASSERT_EQUAL(B200, getBaud(299));

		uUNIT_ASSERT_EQUAL(B300, getBaud(300));
		uUNIT_ASSERT_EQUAL(B300, getBaud(301));
		uUNIT_ASSERT_EQUAL(B300, getBaud(599));

		uUNIT_ASSERT_EQUAL(B600, getBaud(600));
		uUNIT_ASSERT_EQUAL(B600, getBaud(601));
		uUNIT_ASSERT_EQUAL(B600, getBaud(1199));

		uUNIT_ASSERT_EQUAL(B1200, getBaud(1200));
		uUNIT_ASSERT_EQUAL(B1200, getBaud(1201));
		uUNIT_ASSERT_EQUAL(B1200, getBaud(1799));

		uUNIT_ASSERT_EQUAL(B1800, getBaud(1800));
		uUNIT_ASSERT_EQUAL(B1800, getBaud(1801));
		uUNIT_ASSERT_EQUAL(B1800, getBaud(2399));

		uUNIT_ASSERT_EQUAL(B2400, getBaud(2400));
		uUNIT_ASSERT_EQUAL(B2400, getBaud(2401));
		uUNIT_ASSERT_EQUAL(B2400, getBaud(4799));

		uUNIT_ASSERT_EQUAL(B4800, getBaud(4800));
		uUNIT_ASSERT_EQUAL(B4800, getBaud(4801));
		uUNIT_ASSERT_EQUAL(B4800, getBaud(9599));

		uUNIT_ASSERT_EQUAL(B9600, getBaud(9600));
		uUNIT_ASSERT_EQUAL(B9600, getBaud(9601));
		uUNIT_ASSERT_EQUAL(B9600, getBaud(19199));

		uUNIT_ASSERT_EQUAL(B19200, getBaud(19200));
		uUNIT_ASSERT_EQUAL(B19200, getBaud(19201));
		uUNIT_ASSERT_EQUAL(B19200, getBaud(38399));

		uUNIT_ASSERT_EQUAL(B38400, getBaud(38400));
		uUNIT_ASSERT_EQUAL(B38400, getBaud(38401));
		uUNIT_ASSERT_EQUAL(B38400, getBaud(57599));

		uUNIT_ASSERT_EQUAL(B57600, getBaud(57600));
		uUNIT_ASSERT_EQUAL(B57600, getBaud(57601));
		uUNIT_ASSERT_EQUAL(B57600, getBaud(115199));

		uUNIT_ASSERT_EQUAL(B115200, getBaud(115200));
		uUNIT_ASSERT_EQUAL(B115200, getBaud(115201));
		uUNIT_ASSERT_EQUAL(B115200, getBaud(230399));

		uUNIT_ASSERT_EQUAL(B230400, getBaud(230400));
		uUNIT_ASSERT_EQUAL(B230400, getBaud(230401));
	}

	void exceptionTests()
	{
		try
		{
			getBaud(-1);
			uUNIT_ASSERT(false); // exception should be thrown for invalid value
		}
		catch(const bad_speed& e)
		{
			// Excpected outcome
		}
		catch(...)
		{
			uUNIT_ASSERT(false); // Unknown exception were thrown
		}
	}
};

// Registers the fixture into the 'registry'
static ExampleTest test;
