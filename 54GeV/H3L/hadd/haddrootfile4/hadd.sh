#! /bin/bash

#==========================================================
# Peng Liu(liupeng@sinap.ac.cn)
# 2017.04.18
# V1.0
# Do not change the current directory's structure!
# Please do not remove the author's information!
#=========================================================
currentdir2=$PWD

name[1]="la.histo"
name[2]="ala.histo"
name[3]="labg.histo"
name[4]="alabg.histo"
name[5]="la.picodst"
name[6]="ala.picodst"
name[7]="labg.picodst"
name[8]="alabg.picodst"

NUM=8

#====================Do not change the following code!!!!============================
for((j=1;j<=${NUM};j++))
do

	cd ${currentdir2}/temp/${name[$j]}/script/
	
	echo "--------------------------------------"
	echo "${name[$j]} start hadding!"

	hadd  ../output/${name[$j]}.root    output*.root

	echo "${name[$j]} finished hadding!"
	echo "--------------------------------------"

done

echo "======================END========================="
