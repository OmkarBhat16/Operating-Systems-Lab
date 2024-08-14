ls
echo "Enter names of files to delete (seperate with space) : "
read -a files
#echo ${files[@]}

for file in ${files[*]}; do
#	echo $file
	echo "Do you want to delete $file : y/N"
	read resp
	
	if [ "$resp" = 'y' ]; then
		rm $file
	else
		echo "$file skipped"
	fi	
done
