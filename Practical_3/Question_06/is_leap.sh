if [ $# -eq 0 ]; then
    year=$(date +%Y)
else
    year=$1
fi

if ! [[ $year =~ ^[0-9]{4}$ ]]; then
    echo "Error: Please enter a valid year."
    exit 1
fi

if (( (year % 4 == 0 && year % 100 != 0) || year % 400 == 0 )); then
    echo "$year is a leap year."
else
    echo "$year is not a leap year."
fi