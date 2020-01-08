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
#include <tuple>

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

/*!
 *	@brief Частичные специализации метафункции, проверяющей одинаковы ли типы, содержащиеся в кортеже
 *	@param T - первый параметр метафункции, содержащий определенный тип элемента кортежа
 *	@param Args... - набор параметров, содержащих остальные типы элементов кортежа
 */ 
template<typename T, typename... Args>
struct areSameTupleTypes { };

template<typename T>
struct areSameTupleTypes<T> : std::true_type {};

template<typename T, typename U, typename... Args>
struct areSameTupleTypes<T, U, Args...>
{
	static const bool value = areSameTupleTypes<U, Args...>::value && std::is_same_v<T, U>;
};

template<size_t cur_idx, size_t tuple_size, typename... Args>
struct printHelper
{
    void operator()(const std::tuple<Args...>& ip_parts)
    {
        if (cur_idx != 0) std::cout << ".";
        
        std::cout << std::get<cur_idx>(ip_parts);
        printHelper<cur_idx + 1, tuple_size, Args...>{}(ip_parts);
    }
};

template<size_t tuple_size, typename... Args>
struct printHelper<tuple_size, tuple_size, Args...>
{
    void operator()(const std::tuple<Args...>& ip_parts)
    {
        std::cout << std::endl;
    }
};

template<typename... Args>
std::enable_if_t<
	areSameTupleTypes<Args...>::value,
	void>
print_ip(const std::tuple<Args...>& ip)
{
	printHelper<
	0,
	std::tuple_size_v<std::remove_reference_t<decltype(ip)>>,
	Args...> {} (ip);	 
}

#endif // PRINT_H

