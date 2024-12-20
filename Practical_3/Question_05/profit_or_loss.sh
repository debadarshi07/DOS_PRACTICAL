echo "Enter the cost price of the item: "
read cost_price
echo "Enter the selling price of the item: "
read selling_price

if (( $(echo "$selling_price > $cost_price" | bc -l) )); then
    profit=$(echo "$selling_price - $cost_price" | bc)
    echo "The seller made a profit of: $profit"
elif (( $(echo "$selling_price < $cost_price" | bc -l) )); then
    loss=$(echo "$cost_price - $selling_price" | bc)
    echo "The seller incurred a loss of: $loss"
else
    echo "No profit, no loss."
fi