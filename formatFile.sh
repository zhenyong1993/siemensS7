#!/bin/bash

#replace tab to 4 white space
sed -i 's/\t/    /g' *.cpp
sed -i 's/\t/    /g' *.c
sed -i 's/\t/    /g' *.h

#remove tailing white space
sed -i 's/\s*$//g' *.cpp
sed -i 's/\s*$//g' *.c
sed -i 's/\s*$//g' *.h
