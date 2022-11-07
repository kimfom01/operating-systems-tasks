#!/bin/bash
if [ "$#" != 6 ]
then
    echo "Invalid argument"
    echo "usage bash $0 -n <number of text output> -t <output timeout> -- <text to output>"
    exit 1
fi

text="$6"

while [ -n "$1" ]
do
    case "$1" in
        -n)
            NUMBEROFTEXTOUTPUT="$2"
            shift 2
        ;;
        -t)
            OUTPUTTIMEOUT="$2"
            shift 2
        ;;
        --)
            break
        ;;
    esac
done

for i in `seq "$OUTPUTTIMEOUT"`
do
    for i in `seq "$NUMBEROFTEXTOUTPUT"`
    do
        echo "$text"
    done
    sleep $OUTPUTTIMEOUT
done