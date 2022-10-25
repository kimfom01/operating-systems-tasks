#!/bin/bash

if [ ! -f "$1" ]
then
	touch "$1"
fi

if [ ! -z "$2" ] 
then 
    chmod "$2" "$1"
fi

