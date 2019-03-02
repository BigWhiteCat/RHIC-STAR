#!/bin/bash


col -b < Main.C  > main.C
mv main.C Main.C 

col -b < StRoot/StMyMaker/StMyMaker.h > StRoot/StMyMaker/StMyMaker.hpp
mv StRoot/StMyMaker/StMyMaker.hpp StRoot/StMyMaker/StMyMaker.h

col -b < StRoot/StMyMaker/StMyMaker.cxx > StRoot/StMyMaker/StMyMaker.cpp
mv StRoot/StMyMaker/StMyMaker.cpp StRoot/StMyMaker/StMyMaker.cxx 
