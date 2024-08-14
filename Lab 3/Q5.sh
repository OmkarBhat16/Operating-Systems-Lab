echo "Enter file extension : "
read ext

mkdir ${ext}

for file in *.$ext; do
	mv $file ./$ext
done
