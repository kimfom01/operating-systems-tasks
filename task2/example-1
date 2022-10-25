#!/bin/bash
while [ -n "$1" ]
do
	case "$1" in
	-a)
		echo "a = $2"
		shift 2
		;;
	-b)
		echo "b = $2"
		shift 2
		;;
	--)
		shift
		break
		;;
	*)
		echo "Invalid argument"
		echo "usage $0 -a <text> -b <text> -- <text>"
		exit 1
		;;
	esac
done

echo $1
