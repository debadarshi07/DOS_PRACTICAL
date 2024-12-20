echo "Enter internal marks: "
read marks
echo "Enter attendance percentage: "
read attendance

if ! [[ $marks =~ ^[0-9]+$ && $attendance =~ ^[0-9]+$ ]]; then
    echo "Error: Please enter valid numeric values for marks and attendance."
    exit 1
fi

if (( marks >= 20 && attendance >= 75 )); then
    echo "Allowed for Semester"
else
    echo "Not allowed"
fi