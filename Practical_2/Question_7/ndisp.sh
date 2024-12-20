if [ "$#" -ne 3 ]; then
    echo "Usage: $0 n m filename"
    exit 1
fi
n=$1
m=$2
filename=$3
if [ ! -f "$filename" ]; then
    echo "File not found!"
    exit 1
fi
echo "First $n lines:"
head -n "$n" "$filename"
echo "Last $m lines:"
tail -n "$m" "$filename"