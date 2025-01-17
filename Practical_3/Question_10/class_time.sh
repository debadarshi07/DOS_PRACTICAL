echo "Enter a day:"
read day

day=$(echo $day | tr '[:upper:]' '[:lower:]')

case $day in
    monday) echo "DOS class is at 9:00 AM in Room 101";;
    tuesday) echo "DOS class is at 11:00 AM in Room 102";;
    wednesday) echo "DOS class is at 2:00 PM in Room 103";;
    thursday) echo "DOS class is at 10:00 AM in Room 104";;
    friday) echo "DOS class is at 1:00 PM in Room 105";;
    saturday) echo "DOS class is at 3:00 PM in Room 106";;
    sunday) echo "Holiday";;
    *) echo "No class on $day";;
esac