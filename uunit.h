// -*- c++ -*-
// This is the header-only implementation of the uUnit unit-test framework.
// Copyright 2020 Bent Bisballe Nyeng (deva@aasimon.org)
// This file released under the CC0-1.0 license. See CC0-1.0 file for details.
#pragma once

#include <cstddef>
#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

class uUnit
{
public:
	uUnit()
	{
		if(uUnit::suite_list == nullptr)
		{
			uUnit::suite_list = this;
			return;
		}

		auto unit = uUnit::suite_list;
		while(unit->next_unit)
		{
			unit = unit->next_unit;
		}
		unit->next_unit = this;
	}

	virtual ~uUnit() = default;

	//! Overload to prepare stuff for each of the tests.
	virtual void setup() {}

	//! Overload to tear down stuff for each of the tests.
	virtual void teardown() {}

	struct test_result
	{
		std::string func;
		std::string file;
		std::size_t line;
		std::string msg;
		int id;
	};

	//! Run test
	//! \param test_suite the name of a test suite or null for all.
	//! \param test_name the name of a test name inside a test suite. Only valid
	//!  if test_suite is non-null. nullptr for all tests.
	static int runTests(std::ofstream& out)
	{
		std::size_t test_num{0};
		std::size_t failed{0};

		std::list<test_result> failed_tests;
		std::list<test_result> successful_tests;

		for(auto suite = uUnit::suite_list; suite; suite = suite->next_unit)
		{
			for(auto test : suite->tests)
			{
				++test_num;
				try
				{
					suite->setup();
					test.first();
					suite->teardown();
				}
				catch(test_result& result)
				{
					std::cout << "F";
					fflush(stdout);
					result.id = test_num;
					result.func = test.second;
					failed_tests.push_back(result);
					++failed;
					continue;
				}
				catch(...)
				{
					break; // Uncaught exception. Do not proceed with this test.
				}
				std::cout << ".";
				fflush(stdout);
				test_result result{test.second};
				result.id = test_num;
				successful_tests.push_back(result);
			}
		}

		out << "<?xml version=\"1.0\" encoding='ISO-8859-1' standalone='yes' ?>" <<
			std::endl;
		out << "<TestRun>" << std::endl;
		out << "	<FailedTests>" << std::endl;
		for(auto test : failed_tests)
		{
			out << "		<FailedTest id=\"" << test.id << "\">" << std::endl;
			out << "			<Name>" << sanitize(test.func) << "</Name>" << std::endl;
			out << "			<FailureType>Assertion</FailureType>" << std::endl;
			out << "			<Location>" << std::endl;
			out << "				<File>" << sanitize(test.file) << "</File>" << std::endl;
			out << "				<Line>" << test.line << "</Line>" << std::endl;
			out << "			</Location>" << std::endl;
			out << "			<Message>" << sanitize(test.msg) << "</Message>" <<
				std::endl;
			out << "		</FailedTest>" << std::endl;
		}
		out << "	</FailedTests>" << std::endl;
		out << "	<SuccessfulTests>" << std::endl;
		for(auto test : successful_tests)
		{
			out << "		<Test id=\"" << test.id << "\">" << std::endl;
			out << "			<Name>" << sanitize(test.func) << "</Name>" << std::endl;
			out << "		</Test>" << std::endl;

		}
		out << "	</SuccessfulTests>" << std::endl;
		out << "	<Statistics>" << std::endl;
		out << "		<Tests>" << (successful_tests.size() + failed_tests.size()) <<
			"</Tests>" << std::endl;
		out << "		<FailuresTotal>" << failed_tests.size() << "</FailuresTotal>" <<
			std::endl;
		out << "		<Errors>0</Errors>" << std::endl;
		out << "		<Failures>" << failed_tests.size() << "</Failures>" <<
			std::endl;
		out << "	</Statistics>" << std::endl;
		out << "</TestRun>" << std::endl;

		return failed == 0 ? 0 : 1;
	}

protected:
	template<typename O, typename F>
	void registerTest(O* obj, const F& fn, const char* name)
	{
		tests.emplace_back(std::make_pair(std::bind(fn, obj), name));
	}
	#define U_TEST(func)	  \
		registerTest(this, &func, #func)

	void u_assert(bool value, const char* expr,
	              const char* file, std::size_t line)
	{
		if(!value)
		{
			std::stringstream ss;
			ss << "assertion failed" << std::endl <<
				"- Expression: " << expr << "" << std::endl;
			throw test_result{"", file, line, ss.str()};
		}
	}
	//! Convenience macro to pass along filename and linenumber
	#define U_ASSERT(value)	  \
		u_assert(value, #value, __FILE__, __LINE__)

	void assert_equal(double expected, double value,
	                  const char* file, std::size_t line)
	{
		if(std::fabs(expected - value) > 0.0000001)
		{
			std::stringstream ss;
			ss << "equality assertion failed" << std::endl <<
				"- Expected: " << expected << "" << std::endl <<
				"- Actual  : " << value << "" << std::endl;
			throw test_result{"", file, line, ss.str()};
		}
	}
	template<typename T>
	void assert_equal(T expected, T value,
	                  const char* file, std::size_t line)
	{
		if(expected != value)
		{
			std::stringstream ss;
			ss << "equality assertion failed" << std::endl <<
				"- Expected: " << expected << "" << std::endl <<
				"- Actual  : " << value << "" << std::endl;
			throw test_result{"", file, line, ss.str()};
		}
	}
	template<typename T>
	void assert_less_than(T op1, T op2,
		const char* file, std::size_t line)
	{
		if (op1 >= op2)
		{
			std::stringstream ss;
			ss << "less-than assertion failed" << std::endl <<
				"- Expected: " << op1 << sanitize(" < ") << op2 << std::endl <<
				"- Actual  : " << op1 << sanitize(" >= ") << op2 << std::endl;
			throw test_result{ "", file, line, ss.str() };
		}
	}


	//! Convenience macro to pass along filename and linenumber
	#define U_ASSERT_EQ(expected, value) \
		assert_equal(expected, value, __FILE__, __LINE__)


	//! Convenience macro for less-than assertion
	#define U_ASSERT_LESS_THAN(op1, op2) \
		assert_less_than(op1, op2, __FILE__, __LINE__)

private:
	static std::string sanitize(const std::string& input)
	{
		std::string output;
		for(auto c : input)
		{
			switch(c)
			{
			case '"':
				output += "&quot;";
				break;
			case '&':
				output += "&amp;";
				break;
			case '<':
				output += "&lt;";
				break;
			case '>':
				output += "&gt;";
				break;
			default:
				output += c;
				break;
			}
		}
		return output;
	}

	static uUnit* suite_list;
	uUnit* next_unit{nullptr};
	std::vector<std::pair<std::function<void()>, const char*>> tests;
};

#ifdef uUNIT_MAIN
uUnit* uUnit::suite_list{nullptr};
#endif
