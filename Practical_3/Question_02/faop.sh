perform_operation() {
    case $op in
        1) result=$(echo "$num1 + $num2" | bc -l);;
        2) result=$(echo "$num1 - $num2" | bc -l);;
        3) result=$(echo "$num1 * $num2" | bc -l);;
        4)
            if [ $(echo "$num2 == 0" | bc -l) -eq 1 ]; then
                echo "Error: Division by zero is not allowed."
                exit 1
            fi
            result=$(echo "$num1 / $num2" | bc -l);;
        *) echo "Invalid operation selected."; exit 1;;
    esac
    echo "Result: $result"
}

read -p "Enter the first number: " num1
read -p "Enter the second number: " num2

echo "Select an operation to perform:"
echo "1) Addition"
echo "2) Subtraction"
echo "3) Multiplication"
echo "4) Division"
read -p "Enter your choice (1-4): " op

perform_operation