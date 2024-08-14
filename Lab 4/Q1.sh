ls 
echo "Enter name of file to duplicate : "
read filename

cp "$filename" $"./duplicate_${filename}"
ls
