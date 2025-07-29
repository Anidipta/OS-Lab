# Write a Shell Script that reads the user’s name and time from the system. Then, it should print a greeting on the terminal based on the time of the day along with the user’s name, current date & time, and also show the process ID of the terminal the user logged into.

echo "Enter your name:"
read name   
current_time=$(date +%T)
current_date=$(date +%Y-%m-%d)
pid=$$

echo "Hello $name!, the current time is $current_time and the current date is $current_date. Your terminal process ID is $pid."