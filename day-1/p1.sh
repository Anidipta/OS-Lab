# Write a Shell Script which accepts two numbers (the first argument is the starting number; the second argument is the ending number) in the command line as arguments. Then display all the ODD numbers, all the EVEN numbers, and all the PRIME numbers within the range.

echo "Enter two numbers:"
read x y

echo "Even numbers between $x and $y are:"
for (( i=x; i<=y; i++ ))
do
  if (( i % 2 == 0 ))
  then
    echo $i
  fi
done

echo "Odd numbers between $x and $y are:"
for (( i=x; i<=y; i++ ))
do
  if (( i % 2 != 0 ))
  then
    echo $i
  fi
done

echo "Prime numbers between $x and $y are:"
for (( i=x; i<=y; i++ ))
do
  if (( i < 2 ))
  then
    continue
  fi
  is_prime=1
  for (( j=2; j*j<=i; j++ ))
  do
    if (( i % j == 0 ))
    then
      is_prime=0
      break
    fi
  done
  if (( is_prime == 1 ))
  then
    echo $i
  fi
done