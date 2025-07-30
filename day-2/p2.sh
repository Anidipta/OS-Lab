# Write a shell script that accepts two directories namely OS1 and OS2 as arguments and deletes those files in OS2 which are identical to their names in OS1.

dir1="$1"
dir2="$2"

if [ ! -d "$dir1" ] || [ ! -d "$dir2" ]; then
    echo "ERROR: Not Found."
    exit 1
fi

for file in "$dir1"/*; do
    fname=$(basename "$file")
    target="$dir2/$fname"
    if [ -e "$target" ]; then
        echo "Deleting $target"
        rm "$target"
    fi
done

:<<'MULTILINE_COMMENT'
OUTPUT 1:
$ ./day-2/p2.sh day-2/OS1 day-2/OS2
Deleting day-2/OS2/b.txt

OUTPUT 2:
$ ./day-2/p2.sh day-2/OS1 day-2/OS2
ERROR: Not Found.
MULTILINE_COMMENT