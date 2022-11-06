text="$6"
while getopts n:t: c
do
    case "$c" in
    t)
        sleep "$OPTARG"
        ;;
    n)
        for i in `seq "$OPTARG"`
		do
			echo "$text"
		done
        ;;
    \?)
        echo "Invalid argument"
		echo "usage bash $0 -n <number of text output> -t <output timeout> -- <text to output>"
		exit 1
        ;;
    esac
done
