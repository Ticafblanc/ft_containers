#!/bin/bash

make

./Bin/ft_stl>> ft_stl.log
./Bin/stl >> stl.log

diff ft_stl.log stl.log > test.log
rm -rf ft_stl.log stl.log

cat test.log
rm -rf test.log