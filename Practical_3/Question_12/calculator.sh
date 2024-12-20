if [ $# -ne 3 ]; then
    echo "Invalid input. Enter input in the following format: op1 operator op2"
    exit 1
fi

op1=$1
operator=$2
op2=$3

if ! [[ "$op1" =~ ^-?[0-9]+$ ]] || ! [[ "$op2" =~ ^-?[0-9]+$ ]]; then
    echo "Invalid input. Both operands must be numbers."
    exit 1
fi

case $operator in
    "+") result=$((op1 + op2));;
    "-") result=$((op1 - op2));;
    "x") result=$((op1 * op2));;
    "/")
        if [ $op2 -eq 0 ]; then
            echo "Invalid input. Division by zero is not allowed."
            exit 1
        fi
        result=$((op1 / op2))
        ;;
    "%") result=$((op1 % op2));;
    "^") result=$((op1 ** op2));;
    *) echo "Invalid input. Enter input in the following format: op1 operator op2"
       exit 1
       ;;
esac

echo "$op1 $operator $op2 = $result"