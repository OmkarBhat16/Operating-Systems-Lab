echo "Enter file name pattern : "
read pattern

echo $(ls *"$pattern"*)
