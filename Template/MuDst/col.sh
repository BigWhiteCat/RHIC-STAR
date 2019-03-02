#!/bin/bash


col -b < Main.C  > main.C
mv main.C Main.C 

col -b < StRoot/MyMaker/MyMaker.h > StRoot/MyMaker/MyMaker.hpp
mv StRoot/MyMaker/MyMaker.hpp StRoot/MyMaker/MyMaker.h

col -b < StRoot/MyMaker/MyMaker.cxx > StRoot/MyMaker/MyMaker.cpp
mv StRoot/MyMaker/MyMaker.cpp StRoot/MyMaker/MyMaker.cxx 
