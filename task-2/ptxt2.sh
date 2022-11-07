if [ "$#" != 6 ]
then
    echo "Invalid argument"
    echo "usage bash $0 -n <number of text output> -t <output timeout> -- <text to output>"
    exit 1
fi

text="$6"

while getopts n:t: c
do
    case "$c" in
        n)
            NUMBEROFTEXTOUTPUT="$OPTARG"
        ;;
        t)
            OUTPUTTIMEOUT="$OPTARG"
        ;;
        \?)
            echo "Invalid argument"
            echo "usage bash $0 -n <number of text output> -t <output timeout> -- <text to output>"
            exit 1
        ;;
    esac
done

for i in `seq "$NUMBEROFTEXTOUTPUT"`
do
    echo "$text"
    sleep $OUTPUTTIMEOUT
done