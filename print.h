#ifndef PRINT_H
#define PRINT_H

/*!
 *    @file print.h
 *    @brief Библиотека с метафункциями для возможности печати условного ip-адреса,
 *            представленного различными типами  
 */

#include <iostream>
#include <vector>
#include <list>
#include <string>

/*!
 *    @brief Метафункция для печати ip-адреса, представленного целочисленным типом 
 * 
 *    @details Представление не зависит от знака типа. Выводится побайтово начиная
 *             со старшего с символом "." в качестве разделителя.
 *
 *    @param ip Константная ссылка на ip-адрес, представленный целочисленным типом 
 */
template<typename T>
std::enable_if_t<std::is_integral_v<T>, void>
print_ip(const T& ip)
{
    const unsigned char mask = 0xff;
    const unsigned char byte_size = 8;

    std::make_unsigned_t<T> u_ip  = ip;

    unsigned int bytes_moved = 0;
    while(bytes_moved < sizeof(T))
    {
        unsigned int bit_shift = (sizeof(T) - 1 - bytes_moved) * byte_size;
        unsigned int ip_part   = (u_ip >> bit_shift) & mask;

        if(bytes_moved) std::cout << ".";
        std::cout << ip_part;
	++bytes_moved;
    }
    std::cout << std::endl;
}

/*!
 *    @brief Метафункция для печати ip-адреса, представленного в виде контейнеров
 *           std::vector, std::list 
 * 
 *    @details Содержимое выводится поэлементно и разделяется символом "."
 *
 *    @param ip Константная ссылка на ip-адрес, представленный в виде контейнера
 *              std::vector или std::list
 */
template<typename T>
std::enable_if_t<
    std::is_same_v<T, std::vector<typename T::value_type>> ||
    std::is_same_v<T, std::list<typename T::value_type>>, void>
print_ip(const T& ip)
{
    for(auto it = ip.cbegin(); it!=ip.cend(); ++it) {
        if(it != ip.cbegin()) std::cout << ".";
        std::cout << *it;
    }
    std::cout << std::endl; 
}

/*!
 *    @brief Простая функция для печати ip-адреса, представленного строковым типом
 * 
 *    @param ip Константная ссылка на ip-адрес, представленный типом string 
 */
void print_ip(const std::string& ip)
{
    std::cout << ip << std::endl; 
}

#endif // PRINT_H

