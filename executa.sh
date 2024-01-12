#!/bin/bash
reset
gcc rbc.cpp -o rbc -lm

./rbc iris.data > relatorio.txt

rm rbc
