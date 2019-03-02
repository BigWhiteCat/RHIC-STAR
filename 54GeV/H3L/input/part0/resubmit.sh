#!/bin/bash

workdir="/star/u/pengliu/gpfs01/H3L/R17AuAu54GeV"
rootfiledir="${workdir}/output0"
cshfiledir="${workdir}/input/part0/runinfo/csh"
sessfiledir="${workdir}/input/part0"

id="5B2A1E53917ADA052C42EECB8611AFBF"

n=0
i=0
failedID=""

while [ $i -lt 10060 ]; do
	
	if [ ! -e ${rootfiledir}/${id}_$i.la.picodst.root ]; then
		echo "${id}_$i.la.picodst.root doesn't exist.............."

		failedID="${failedID}${i},"

		let "n+=1"
	fi
    
	let "i+=1"
done

echo "failed job ID:"
echo "${failedID%?}"

echo "Total number of files missing = $n"
if [ $n -gt 0 ]; then
	
	star-submit -r  ${failedID%?}  ${sessfiledir}/${id}.session.xml

fi

echo "Total number of files missing = $n"
