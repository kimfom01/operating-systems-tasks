#!/bin/bash
text="$6"
while [ -n "$1" ]
do
	
	case "$1" in
	-n)
		for i in `seq "$2"`
		do
			echo "$text"
		done
		shift 2
		;;
	-t)
		sleep "$2"
		;;
	--)
		shift
		break
		;;
	*)
		echo "Invalid argument"
		echo "usage $0 -n <number of text output> -t <output timeout> -- <text to output>"
		exit 1
		;;
	esac
done

echo $1
