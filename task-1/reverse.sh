#!/bin/bash

strlen=${#1}

len=$((strlen-1))

while [ $len -ge 0 ]

do

	revstr=$revstr${1:$len:1}

	len=$((len-1))

done



echo "Original String: $1"

echo "Reversed String: $revstr"
