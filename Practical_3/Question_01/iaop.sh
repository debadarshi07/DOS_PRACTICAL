perform_arithmetic() {
    case $operation in
        1)  result=$((num1 + num2))
            echo "Result of addition: $result" ;;
        2)  result=$((num1 - num2))
            echo "Result of subtraction: $result" ;;
        3)  result=$((num1 * num2))
            echo "Result of multiplication: $result" ;;
        4)  if [ $num2 -eq 0 ]; then
                echo "Error: Division by zero is not allowed!"
            else
                result=$((num1 / num2))
                echo "Result of division: $result"
            fi;;
        *)  echo "Invalid operation selected!" ;;
    esac
}

echo "Enter the first number:"
read num1
echo "Enter the second number:"
read num2
if ! [[ "$num1" =~ ^-?[0-9]+$ ]] || ! [[ "$num2" =~ ^-?[0-9]+$ ]]; then
    echo "Error: Please enter valid integers."
    exit 1
fi

echo "Select the operation you want to perform:"
echo "1. Addition (+)"
echo "2. Subtraction (-)"
echo "3. Multiplication (*)"
echo "4. Division (/)"
read operation
perform_arithmetic