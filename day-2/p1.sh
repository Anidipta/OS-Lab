# Write a shell command that accepts a filename as argument and displays the last modification time, if the file exists and a suitable message if it does not.

filename="$1"

if [ -f "$filename" ]; then
    echo "Last modification time of $filename:"
    stat -c %y "$filename"
else
    echo "File '$filename' does not exist."
fi

: <<'MULTILINE_COMMENT'
OUTPUT 1:
$ ./day-2/p1.sh day-2/OS1/a.txt
File 'day-2/OS1/a.txt' does not exist.

OUTPUT 2:
$ ./day-2/p1.sh day-2/OS1/b.txt
Last modification time of day-2/OS1/b.txt:
2025-07-30 19:30:35.198397500 +0530
MULTILINE_COMMENT