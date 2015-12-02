#!/bin/bash

trap "rm $submissionFile 2> log.txt; rm $outputFile 2> log.txt; rm $resultFile 2> log.txt;" SIGHUP SIGINT SIGTERM SIGKILL

submissionFile=$1

currentDir=${PWD##*/}

#make sure current working directory is codeChecker
if [ ! "$currentDir" = "codeChecker" ]
then
	cd codeChecker
	newDir=${PWD##*/}

	if [ ! "$newDir" = "codeChecker" ]
	then
		echo "Unable to change directory" > log.txt
		exit -1
	fi
fi


if [ ! -e $submissionFile ]
then
	echo $submissionFile
	echo "No file submitted" > log.txt
	exit -1
fi

#setup c++ file
cp templateCode.cpp submission.cpp
cat $submissionFile >> submission.cpp
rm $submissionFile 2> log.txt
submissionFile=submission.cpp

#compile submission
g++ -std=c++0x $submissionFile

outputFile=a.out

if [ ! -e $outputFile ]
then
	echo "Compile Errors Found"
	rm $submissionFile 2> log.txt
	rm $outputFile 2> log.txt
	exit -1
fi

resultFile=result.txt
if [ ! -e $resultFile ]
then
	touch $resultFile
fi

#check submission code
./$outputFile

cat $resultFile

#clean up
rm $submissionFile 2> log.txt
rm $resultFile 2> log.txt
rm $outputFile 2> log.txt

exit 0
