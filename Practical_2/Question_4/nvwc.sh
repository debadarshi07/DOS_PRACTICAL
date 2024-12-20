FILENAME="dtcal"

if [[ ! -f $FILENAME ]]; then
    echo "File $FILENAME does not exist."
    exit 1
fi

LINE_COUNT=$(wc -l < "$FILENAME")
WORD_COUNT=$(wc -w < "$FILENAME")
CHAR_COUNT=$(wc -c < "$FILENAME")

echo "Filename: $FILENAME"
echo "Line count: $LINE_COUNT"
echo "Word count: $WORD_COUNT"
echo "Char count: $CHAR_COUNT"
