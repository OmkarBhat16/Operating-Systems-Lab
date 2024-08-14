for file in *.txt
do
	if [ -f "$file" ]; then
	base="${file%.txt}"
	mv "$file" "$base.text"
	fi
done
