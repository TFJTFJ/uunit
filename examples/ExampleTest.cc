#include <uunit.h>

#include "getbaud.h"

class ExampleTest
	: public uUnit
{
public:
	ExampleTest()
	{
		uTEST(ExampleTest::boundaryTests);
		uTEST(ExampleTest::orderTests);
		U_TEST(ExampleTest::exceptionTests);
	}


	void orderTests()
	{
		U_ASSERT_LESS_THAN(B0, B50);
	}

	void boundaryTests()
	{
		uASSERT(B0, getBaud(0));
		U_ASSERT_EQ(B0, getBaud(1));
		U_ASSERT_EQ(B0, getBaud(49));

		U_ASSERT_EQ(B50, getBaud(50));
		U_ASSERT_EQ(B50, getBaud(51));
		U_ASSERT_EQ(B50, getBaud(74));

		U_ASSERT_EQ(B75, getBaud(75));
		U_ASSERT_EQ(B75, getBaud(76));
		U_ASSERT_EQ(B75, getBaud(109));

		U_ASSERT_EQ(B110, getBaud(110));
		U_ASSERT_EQ(B110, getBaud(111));
		U_ASSERT_EQ(B110, getBaud(133));

		U_ASSERT_EQ(B134, getBaud(134));
		U_ASSERT_EQ(B134, getBaud(135));
		U_ASSERT_EQ(B134, getBaud(149));

		U_ASSERT_EQ(B150, getBaud(150));
		U_ASSERT_EQ(B150, getBaud(151));
		U_ASSERT_EQ(B150, getBaud(199));

		U_ASSERT_EQ(B200, getBaud(200));
		U_ASSERT_EQ(B200, getBaud(201));
		U_ASSERT_EQ(B200, getBaud(299));

		U_ASSERT_EQ(B300, getBaud(300));
		U_ASSERT_EQ(B300, getBaud(301));
		U_ASSERT_EQ(B300, getBaud(599));

		U_ASSERT_EQ(B600, getBaud(600));
		U_ASSERT_EQ(B600, getBaud(601));
		U_ASSERT_EQ(B600, getBaud(1199));

		U_ASSERT_EQ(B1200, getBaud(1200));
		U_ASSERT_EQ(B1200, getBaud(1201));
		U_ASSERT_EQ(B1200, getBaud(1799));

		U_ASSERT_EQ(B1800, getBaud(1800));
		U_ASSERT_EQ(B1800, getBaud(1801));
		U_ASSERT_EQ(B1800, getBaud(2399));

		U_ASSERT_EQ(B2400, getBaud(2400));
		U_ASSERT_EQ(B2400, getBaud(2401));
		U_ASSERT_EQ(B2400, getBaud(4799));

		U_ASSERT_EQ(B4800, getBaud(4800));
		U_ASSERT_EQ(B4800, getBaud(4801));
		U_ASSERT_EQ(B4800, getBaud(9599));

		U_ASSERT_EQ(B9600, getBaud(9600));
		U_ASSERT_EQ(B9600, getBaud(9601));
		U_ASSERT_EQ(B9600, getBaud(19199));

		U_ASSERT_EQ(B19200, getBaud(19200));
		U_ASSERT_EQ(B19200, getBaud(19201));
		U_ASSERT_EQ(B19200, getBaud(38399));

		U_ASSERT_EQ(B38400, getBaud(38400));
		U_ASSERT_EQ(B38400, getBaud(38401));
		U_ASSERT_EQ(B38400, getBaud(57599));

		U_ASSERT_EQ(B57600, getBaud(57600));
		U_ASSERT_EQ(B57600, getBaud(57601));
		U_ASSERT_EQ(B57600, getBaud(115199));

		U_ASSERT_EQ(B115200, getBaud(115200));
		U_ASSERT_EQ(B115200, getBaud(115201));
		U_ASSERT_EQ(B115200, getBaud(230399));

		U_ASSERT_EQ(B230400, getBaud(230400));
		U_ASSERT_EQ(B230400, getBaud(230401));
	}

	void exceptionTests()
	{
		try
		{
			getBaud(-1);
			U_ASSERT(false); // exception should be thrown for invalid value
		}
		catch(const bad_speed& e)
		{
			// Expected outcome
		}
		catch(...)
		{
			U_ASSERT(false); // Unknown exception were thrown
		}
	}
};

// Registers the fixture into the 'registry'
static ExampleTest test;
