#!/bin/bash
g++ Unit_test/utility_test.cpp -o ft::utility
g++ Unit_test/utility_test.cpp -D real -o std::utility


./ft::utility >> ft::utility.log
./std::utility >> std::utility.log

diff ft::utility.log std::utility.log >> test.log
rm -rf ft::utility.log std::utility.log ft::utility std::utility

g++ Unit_test/algorithm_test.cpp -o ft::algorithm
g++ Unit_test/algorithm.cpp -D real -o std::algorithm

./ft::algorithm >> ft::algorithm.log
./std::algorithm >> std::algorithm.log

diff ft::algorithm.log std::algorithm.log >> test.log
rm -rf ft::algorithm.log std::algorithm.log ft::algorithm std::algorithm

cat test.log
rm -rf test.log

