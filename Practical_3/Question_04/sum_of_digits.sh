echo "Enter a five-digit number: "
read number

if [[ ! $number =~ ^[0-9]{5}$ ]]; then
    echo "Error: Please enter a valid five-digit number."
    exit 1
fi

sum=0

for (( i=0; i<${#number}; i++ )); do
    digit=${number:i:1}
    sum=$((sum + digit))
done

echo "The sum of the digits is: $sum"