if [ $# -ne 3 ]; then
    echo "Error: Please provide exactly three numbers as arguments."
    exit 1
fi

num1=$1
num2=$2
num3=$3

if ! [[ $num1 =~ ^-?[0-9]+(\.[0-9]+)?$ && $num2 =~ ^-?[0-9]+(\.[0-9]+)?$ && $num3 =~ ^-?[0-9]+(\.[0-9]+)?$ ]]; then
    echo "Error: All arguments must be numeric."
    exit 1
fi

if (( $(echo "$num1 <= $num2" | bc -l) && $(echo "$num1 <= $num3" | bc -l) )); then
    smallest=$num1
elif (( $(echo "$num2 <= $num1" | bc -l) && $(echo "$num2 <= $num3" | bc -l) )); then
    smallest=$num2
else
    smallest=$num3
fi

echo "The smallest number is: $smallest"