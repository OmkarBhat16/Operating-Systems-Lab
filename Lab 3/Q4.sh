echo "Enter basic amount : "
read basic

echo "Enter TA amount : "
read TA

res=$(echo "$basic * 1.1 + $TA" | bc -l)
echo "Gross Salary is : $res"

