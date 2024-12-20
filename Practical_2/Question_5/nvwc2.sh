if [ "$#" -ne 1 ]; then
    echo "Usage: $0 filename"
    exit 1
fi

FILE="$1"

if [ ! -f "$FILE" ]; then
    echo "File not found!"
    exit 1
fi

LINECOUNT=$(wc -l < "$FILE")
WORDCOUNT=$(wc -w < "$FILE")
CHARCOUNT=$(wc -c < "$FILE")

echo "$FILE $LINECOUNT $WORDCOUNT $CHARCOUNT"