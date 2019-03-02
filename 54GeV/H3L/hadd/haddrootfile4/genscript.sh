#! /bin/bash

#==========================================================
# Peng Liu(liupeng@sinap.ac.cn)
# 2017.04.18
# V1.0
# This script should work together with sample.sh
# Do not change the current directory's structure!
# Please do not remove the author's information!
#=========================================================

directory="\/star\/u\/pengliu\/gpfs01\/H3L\/R17AuAu54GeV\/output*\/"
currentdir="\/star\/u\/pengliu\/gpfs01\/H3L\/R17AuAu54GeV\/hadd\/haddrootfile4\/"
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
for((i=1;i<=${NUM};i++))
do
	cd ${currentdir2}
	rm -rf ./temp/${name[$i]}
    cp -r ./sample  ./temp/${name[$i]}
	cd ./temp/${name[$i]}

    cp -r ./src ./script

	sed -e "14s/\/directoryofrootfile\//$directory/g" -e "15,16s/nameofrootfile/${name[$i]}/g" ./sample.sh  >./script/${name[$i]}.sh
	chmod u+x ./script/${name[$i]}.sh
	sed -i "3s/\/directory_job\//${currentdir}temp\/${name[$i]}\//g" ./submit/submit.con
	sed -i -e "3s/\/directory_job\//${currentdir}temp\/${name[$i]}\//g" -e "4s/scriptname_job/${name[$i]}.sh/g" ./submit/run.csh

	sed -i "3s/\/directory_job\//${currentdir}temp\/${name[$i]}\//g" ./submit/submit2.con
	sed -i -e "3s/\/directory_job\//${currentdir}temp\/${name[$i]}\//g" ./submit/run2.csh

done
echo "=================================================="
echo "Finished the generation of script!"
echo "=================================================="

for((j=1;j<=${NUM};j++))
do

	cd ${currentdir2}/temp/${name[$j]}/submit/
	
	echo "--------------------------------------"
	echo "${name[$j]}.sh start submitting!"

	(nohup ./run.csh > ./log/nohup.out)>& ./log/nohup.err &

	echo "${name[$j]}.sh finished submitting!"
	echo "--------------------------------------"

done

echo "======================END========================="
