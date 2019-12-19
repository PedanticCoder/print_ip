cmake_minimum_required(VERSION 3.2)

configure_file(version.h.in ${PROJECT_SOURCE_DIR}/test/version.h)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_version test_version.cpp)

add_library(print_ip_lib lib.cpp)

set_target_properties(test_version PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(test_version 
	print_ip_lib
)

target_link_libraries(test_version
    ${Boost_LIBRARIES}
    print_ip_lib
)

enable_testing()

add_test(print_ip_tests test_version)
