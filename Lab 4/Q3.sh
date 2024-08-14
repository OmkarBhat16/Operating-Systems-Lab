function sort(){
	n=$#
	strings={$@}
	echo "strings is : $strings"
	for((i = 0; i < n ; i++)); do
		for((j = i+1; j < n ; j++)); do
			if [ strings[j] < strings[{j+1}] ]; then
				temp=strings[j]
				strings[j]=strings[{j+1}]
				strings[{j+1}]=$temp
			fi
		done
	done
	echo "Sorted array : $strings"
}

sort $@
