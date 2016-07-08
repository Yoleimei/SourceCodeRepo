# find -type d | while read file; do ./touch.sh $file; done
touch $1/readme.md
echo $1
