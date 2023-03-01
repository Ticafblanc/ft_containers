/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:47:59 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/02/28 20:48:01 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/Unit_test.hpp"

int main(){

    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    for(int i = 0; i < 100; i++) {
        std::cout<<"Test utility start" << std::endl;
        utility_test();
        std::cout<<"Test type_trait start" << std::endl;
        type_traits();
        std::cout<<"Test stack start" << std::endl;
        stack_test();
        std::cout<<"Test vector start" << std::endl;
        vector_test();
        std::cout<<"Test map start" << std::endl;
        map_test();
        std::cout<<"Test set start" << std::endl;
        set_test();

    }
    std::cout << "execution time : " << std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start).count() << "ms" << std::endl;
}
