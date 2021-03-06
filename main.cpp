#include "print.h"

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <tuple>

/*!
 *    @file main.cpp
 *    @brief Точка старта программы    
 *
 *    @mainpage Условие
 *
 * Реализовать функцию печати условного ip-адреса.
 * Адрес может быть представлен в виде произвольного целочисленного типа. Представление не зависит от
 * знака типа. Выводить побайтово начиная со старшего с символом . в качестве разделителя.
 * Адрес может быть представлен в виде строки. Выводится как есть.
 * Адрес может быть представлен в виде контейнеров std::list, std::vector. Выводится содержимое
 * контейнера поэлементно и разделяется . (одним символом точка).
 */

int main()
{
    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(long(8875824491850138409));
    print_ip(std::string("127.0.0.1"));
    print_ip(std::vector<int>{192, 168, 20, 10});
    print_ip(std::list<int>{132, 54, 76, 23, 354});
    print_ip(std::make_tuple(192, 168, 33, 45));
    
    return 0;
}
