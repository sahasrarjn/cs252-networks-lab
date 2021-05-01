############### Generate binary file of size 5M ###########
# if [[ "$OSTYPE" == "linux-gnu"* ]]; then
#         isMac=0
# elif [[ "$OSTYPE" == "darwin"* ]]; then
#         isMac=1
# fi

# if [["$isMac" == "1"]]; then
# 	dd if=/dev/zero of=send.txt bs=1m count=5
# else
# 	dd if=/dev/zero of=send.txt  bs=5M  count=1
# fi
############################################################
touch send.txt recv.txt
rm mean.txt stddev.txt
touch mean.txt stddev.txt

yes > send.txt & PID=$!; sleep 0.0002; pkill $PID

declare -a delays
delays=( 10ms 50ms 100ms )

declare -a losses
losses=( 0.1 0.5 1 )

# compile
# gcc -o sender sender.c
# gcc -o receiver receiver.c

for (( i = 0; i < 3; i++ )); do
	delay=delays[i]
	for (( j = 0; j < 3; j++ )); do
		loss=losses[i]
		for (( k = 0; k < 2; k++ )); do
			isReno=$k
			for (( run = 0; run < 20; run++ )); do

				# ./receiver $isReno &
				cat > temp2 &
				P1=$!

				# ./sender 0.0.0.0 $isReno & # ectract sender time from here
				cat temp & 
				P2=$!

				wait $P2 # Wait for sender to stop

				pkill $P1 # Stop receiver

				f1='send.txt'
				f2='recv.txt'
				f1='receiver.c'
				f2='huh.c'
				if diff -q $f1 $f2 > /dev/null
				then
				  echo "The files are equal"
				else
				  echo "The files are different or inaccessible"
				fi

				filesize=$(wc -c recv.txt | tr -d -c 0-9)

			done
			
		done
	done
done
