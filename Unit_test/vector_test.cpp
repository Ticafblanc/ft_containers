/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Unit_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 07:21:01 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/12/30 07:21:05 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Unit_test.hpp"
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <iterator>
#include "../stack.tpp"

int main(){
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    ft::vector<int>         s;
//    std::cout << s.capacity() << std::endl;
//    s.reserve(50);
//    std::cout << s.capacity() <<std::endl;

//    ft::vector<int>            aft(std::allocator<int>);
//    size_t st = 98;
//    int    i = 1;
//    std::vector<int>            s1(st,i);
//    std::cout << s1.size() << " " << s1.capacity() <<std::endl;
//    s1 = s;
//    /*s1.push_back(3);*/
//    std::cout << s1.size() << " " << s1.capacity() << std::endl;


//
//    i = 2;
//    std::vector<int>            s2(s,i);
//    std::vector<int>::iterator Is2 = s2.begin();
//    std::vector<int>::iterator Its2 = s2.end();
//    for(; Is1 != Its1; ++Is1)
//        std::cout << *Is1 << std::endl;
//    s2.insert(s2.begin(),Is1, Its1);
//    for(; Is2 != Its2; ++Is2)
//        std::cout << "2:"<< *Is2 << std::endl;
//    for(; Is1 != Its1; ++Is1)
//        std::cout << "1:"<< *Is1 << std::endl;
//    s1.insert(s1.begin(),s2.begin(), s2.begin() + 10);
//
//    std::cout << s1.size() <<" "<< s2.size()<<std::endl;
//    std::cout << s1.capacity() <<" "<< s2.capacity()<<std::endl;
//    s1.assign(20, 34);
//    s1.resize(30);
//    std::vector<int>::iterator Is1 = s1.begin();
//    std::vector<int>::iterator Its1 = s1.end();
//    std::cout << s1.size() <<" "<< s2.size()<<std::endl;
//    std::cout << s1.capacity() <<" "<< s2.capacity()<<std::endl;
//    for(; Is1 != Its1; ++Is1)
//        std::cout << "1:"<< *Is1 << std::endl;


//    ft::vector<int>            stft2(s, i);
//    ft::vector<int>            stft3(34, 45);



//    ft::vector<int>::iterator it = stft2.begin();
//    ft::vector<int>::iterator it2 = stft2.end();
//    ft::vector<int>           itconst(s);
//    ft::vector<int>             itcons(It, Id);
//    ft::vector<int>             copyconstruct(itconst);
//    stft = itconst;
    //std::cout <<"befor  "<< stft2.size() << "\n" << stft2.capacity()<< std::endl;
//    stft2.assign(34, 45);
    //__COUT__<< "\nsize = " <<  stft2.size() << "\ncapacity = " << stft2.capacity()  __CENDL__
    //std::cout <<"afer"<< stft2.size()<< "\n" << stft2.capacity()<<std::endl;
//    ft.assign(9, 90);
//    ft2.assign(fit, fit2);
//    ft.assign(s, c);
//
//    //ft::vector<int>::iterator ite = i.end();
//    ft::vector<int>            fi(200,45);
//    ft::vector<int>::iterator fit = fi.begin();
//    std::cout << i.max_size() << std::endl;
//    std::cout << fi.max_size() << std::endl;

//    std::istream_iterator<std::vector<int>, std::vector<int>::difference_type> in();
//    in = i.begin();

//    ft::vector<char>            ft_void;
//    std::vector<char>           std_void;
//    ft::vector<int>             ft_alloc(std::allocator<int>);
//    std::vector<int>            std_alloc(std::allocator<int>);
//    ft::vector<int>          ft_count(s, c);
//    std::cout << *(ft_count.end() - 1) << std::endl;
//    std::cout << "execution time : " << std::chrono::duration_cast<std::chrono::milliseconds>(
//            std::chrono::system_clock::now() - start).count() << "ms" << std::endl;
//    std::chrono::system_clock::time_point starts = std::chrono::system_clock::now();
//    std::cout << std::endl;
//    std::vector<int>         std_count(s, c);
//    std::cout << (std_count.size()) << std::endl;
//    std::cout << "execution time : " << std::chrono::duration_cast<std::chrono::milliseconds>(
//            std::chrono::system_clock::now() - starts).count() << "ms" << std::endl;
//
//    int i1 = 200;
//    int i2= 45;
//    ft::vector<int>             ft_integrl(200, 45);
//    std::vector<int>             std_integral(200, 45);
//    ft::vector<int>             ft_integralv(i1, i2);
//    std::vector<int>             std_integralv(i1, i2);
//    std::vector<int>            ft_input = std::vector<int >(it, it + 200);
   // ft::vector<int>             std_input = ft::vector<int>(it, it + 200);


	std::cout << std::endl;
    std::cout << "execution time : " << std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start).count() << "ms" << std::endl;
    return 0;
}