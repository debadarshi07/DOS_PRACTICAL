echo "Enter Ramesh's basic salary: "
read basic_salary

dearness_allowance=$(echo "0.4 * $basic_salary" | bc)
house_rent_allowance=$(echo "0.2 * $basic_salary" | bc)

gross_salary=$(echo "$basic_salary + $dearness_allowance + $house_rent_allowance" | bc)

echo "Ramesh's gross salary is: $gross_salary"