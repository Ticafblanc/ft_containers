/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 07:21:01 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/12/30 07:21:05 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/Unit_test.hpp"

int main(){
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    //Test ft::enable_if https://en.cppreference.com/w/cpp/types/enable_if

    std::cout << "####  Test >> ft::enable_if  ####" << std::endl;


    //Test ft::is_integral https://en.cppreference.com/w/cpp/types/is_integral

    std::cout << "####  Test >> ft::is_integral  ####" << std::endl;

    std::cout << std::boolalpha << ft::is_integral<float>::value << std::endl;
    std::cout << std::boolalpha << ft::is_integral<std::string>::value << std::endl;
    std::cout << std::boolalpha << ft::is_integral<double>::value << std::endl;
    std::cout << std::boolalpha << ft::is_integral<bool>::value << std::endl;
    std::cout << std::boolalpha << ft::is_integral<char>::value << std::endl;
    std::cout << std::boolalpha << ft::is_integral<short>::value << std::endl;
    std::cout << std::boolalpha << ft::is_integral<int>::value << std::endl;
    std::cout << std::boolalpha << ft::is_integral<long>::value << std::endl;
    std::cout << std::boolalpha << ft::is_integral<long long>::value << std::endl;
    std::cout << std::boolalpha << ft::is_integral<unsigned char>::value << std::endl;
    std::cout << std::boolalpha << ft::is_integral<unsigned short>::value << std::endl;
    std::cout << std::boolalpha << ft::is_integral<unsigned int>::value << std::endl;
    std::cout << std::boolalpha << ft::is_integral<unsigned long>::value << std::endl;
    std::cout << std::boolalpha << ft::is_integral<unsigned long long>::value << std::endl << std::endl;


    //Test ft::equal https://en.cppreference.com/w/cpp/algorithm/equal

    std::cout << "####  Test >> ft::is_integral  ####" << std::endl;

    std::string radar("radar");
    std::string hello("hello");

    std::cout << ((ft::equal(radar.begin(), radar.begin() + radar.size()/2, radar.rbegin())) ? "good" : "bad" ) << std::endl;
    std::cout << ((ft::equal(hello.begin(), hello.begin() + hello.size()/2, hello.rbegin())) ? "good" : "bad" ) << std::endl << std::endl;

    //Test ft::lexicographical_compare https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare

    std::cout << "####  Test >> ft::lexicographical_compare  ####" << std::endl;
    int let = 97;
    std::vector<char> va1;
    for(int i = 0; i < 6; ++i)
        va1.insert(va1.begin(), static_cast<char>(let++));
    std::vector<char> va2;
    for(int i = 0; i < 6; ++i)
        va2.insert(va2.begin(), static_cast<char>(let--));

    while (!ft::lexicographical_compare(va1.begin(), va1.end(),
                                         va2.begin(), va2.end()))
    {
        std::vector<char>::iterator itv = va1.begin();
        for (int i = 0; i < 6; ++i)
            std::cout << *(itv++) << ' ';
        std::cout << "< ";

        itv = va2.begin();
        for (int i = 0; i < 6; ++i)
            std::cout << *(itv++) << ' ';
        std::cout << '\n';

        std::sort(va1.begin(), va1.end());//MUTE TO CHECK
        std::sort(va2.begin(), va2.end());//MUTE TO CHECK

    }

    std::vector<char>::iterator itv = va1.begin();
    for (int i = 0; i < 6; ++i)
        std::cout << *(itv++) << ' ';
    std::cout << ">= ";

    itv = va2.begin();
    for (int i = 0; i < 6; ++i)
        std::cout << *(itv++) << ' ';
    std::cout << '\n' << std::endl;
    std::cout << "execution time : " << std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start).count() << "ms" << std::endl;
    return 0;
}