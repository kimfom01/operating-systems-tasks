arr=("$@")
# arr=(3 5 4 6 8 3)

size=${#arr[@]}

for (( i=0; i<size-1; i++ ))
do
    for (( j=0; j<size-i-1; j++ ))
    do
        if (( arr[j] > arr[j+1] ))
        then
            temp=${arr[j]}
            arr[j]=${arr[j+1]}
            arr[j+1]=$temp
        fi
    done
done

for i in ${!arr[@]}
do
    echo ${arr[$i]}
done