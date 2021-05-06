f1='send.txt'
f2='recv.txt'
if ! diff -q $f1 $f2 > /dev/null
then
  echo "The files are different"
fi