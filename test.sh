#!/bin/bash

g++ -std=c++98 Unit_test/utility_test.cpp -o ft::utility
g++ -std=c++98 Unit_test/utility_test.cpp -D real -o std::utility

./ft::utility >> ft::utility.log
./std::utility >> std::utility.log

diff ft::utility.log std::utility.log > test.log
rm -rf ft::utility.log std::utility.log ft::utility std::utility

g++ -std=c++98 Unit_test/type_traits_test.cpp -o ft::type_traits
g++ -std=c++98 Unit_test/type_traits_test.cpp -D real -o std::type_traits

./ft::type_traits >> ft::type_traits.log
./std::type_traits >> std::type_traits.log

diff ft::type_traits.log std::type_traits.log > test.log
rm -rf ft::type_traits.log std::type_traits.log ft::type_traits std::type_traits

g++ -std=c++98 Unit_test/stack_test.cpp -o ft::stack
g++ -std=c++98 Unit_test/stack_test.cpp -D real -o std::stack

./ft::stack >> ft::stack.log
./std::stack >> std::stack.log

diff ft::stack.log std::stack.log > test.log
rm -rf ft::stack.log std::stack.log ft::stack std::stack

cat test.log
rm -rf test.log

