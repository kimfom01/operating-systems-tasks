#!/bin/bash

case "$2" in

	"+")echo $(expr $1 + $3)

	;;

	"-")echo $(expr $1 - $3)

	;;

	"*")echo $(expr $1 * $3)

	;;

	"/")if [ $3 != 0 ]; then

		echo $(expr $1 / $3)

	    else

		echo "Error! Divide by zero"

	    fi

	;;

esac
