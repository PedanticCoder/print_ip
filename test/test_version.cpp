/*!
 *    @file test_version.cpp
 *    @brief Проверка корректности номера версии патча проекта
 */

#define BOOST_TEST_MODULE print_ip_test_module

#include "lib.h"
#include "../print.h"

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <iostream>

BOOST_AUTO_TEST_SUITE(project_version_test_suite)

BOOST_AUTO_TEST_CASE(print_ip_test_version)
{
    BOOST_CHECK(version() > 0);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(print_ip_string_test_suite)

struct cout_redirect {
    cout_redirect(std::streambuf *new_buffer ) 
        : old(std::cout.rdbuf( new_buffer ))
    { }

    ~cout_redirect( ) {
        std::cout.rdbuf(old);
    }

private:
    std::streambuf *old;
};

BOOST_AUTO_TEST_CASE(print_ip_output_checking)
{
    boost::test_tools::output_test_stream output;
    {
        cout_redirect guard(output.rdbuf( ));

        char ip = -1;  
        print_ip(ip);
        BOOST_CHECK(output.is_equal("255\n"));

	short ip2 = 0;
	print_ip(ip2);
	BOOST_CHECK(output.is_equal("0.0\n"));

	int ip3 = 2130706433;
	print_ip(ip3);
	BOOST_CHECK(output.is_equal("127.0.0.1\n"));

	unsigned long long int ip4 = 8875824491850138409LL;
	print_ip(ip4);
	BOOST_CHECK(output.is_equal("123.45.67.89.101.112.131.41\n"));

	print_ip(std::string("127.0.0.1"));
	BOOST_CHECK(output.is_equal("127.0.0.1\n"));

	print_ip(std::vector<int>{192, 168, 20, 10});
	BOOST_CHECK(output.is_equal("192.168.20.10\n"));

	print_ip(std::list<int>{132, 54, 76, 23, 354});
	BOOST_CHECK(output.is_equal("132.54.76.23.354\n"));
    }
}

BOOST_AUTO_TEST_SUITE_END()











