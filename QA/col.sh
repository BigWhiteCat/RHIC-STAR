#!/bin/bash


col -b < Main.C  > main.C
mv main.C Main.C

col -b < StRoot/StV0Maker/StV0Maker.h > StRoot/StV0Maker/StV0Maker.hpp
mv StRoot/StV0Maker/StV0Maker.hpp StRoot/StV0Maker/StV0Maker.h

col -b < StRoot/StV0Maker/StV0Maker.cxx > StRoot/StV0Maker/StV0Maker.cpp
mv StRoot/StV0Maker/StV0Maker.cpp StRoot/StV0Maker/StV0Maker.cxx

col -b < StRoot/StV0Maker/StDcaService.h > StRoot/StV0Maker/StDcaService.hpp
mv StRoot/StV0Maker/StDcaService.hpp StRoot/StV0Maker/StDcaService.h

col -b < StRoot/StV0Maker/StDcaService.cxx > StRoot/StV0Maker/StDcaService.cpp
mv StRoot/StV0Maker/StDcaService.cpp StRoot/StV0Maker/StDcaService.cxx

col -b < StRoot/StV0Maker/StV0Dst.h > StRoot/StV0Maker/StV0Dst.hpp
mv StRoot/StV0Maker/StV0Dst.hpp StRoot/StV0Maker/StV0Dst.h

col -b < StRoot/StV0Maker/StV0Type.h > StRoot/StV0Maker/StV0Type.hpp
mv StRoot/StV0Maker/StV0Type.hpp StRoot/StV0Maker/StV0Type.h
