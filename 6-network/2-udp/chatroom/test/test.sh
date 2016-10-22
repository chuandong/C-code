#!/bin/bash 

i=0

while [ $i -lt 1000 ] 
do
	./test_talk 192.168.10.10 &
	((i++))
done
