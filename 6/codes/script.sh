#! /bin/bash

# This is automation script for the assignemnt. This start the sender and receiver and terminates them 
# after the tranfer is complete. All the standard errors are handeled to avoid any failure while automation.
# Stores all the throughput values in a file for 20 runs and then compute mean and stddev of the values

# Usage: ./script.sh 



# Delay and Loss values
declare -a delays
delays=( 10ms 50ms 100ms )
declare -a losses
losses=( 0.1% 0.5% 1% )


for f in recv thput
do
	# clear files ($f.txt)
	echo -n "" > $f.txt
done

# generate send.txt of size 5MB
yes | head -c 5MB > send.txt


# compile both the files
gcc -o sender sender.c
gcc -o receiver receiver.c

# Set MTU value for 'lo' loopback interface
sudo ifconfig lo mtu 1500 

# For loops to experiment for each loss, delay, tcp_type. each for 20 runs
for (( i = 0; i < 3; i++ )); do
	# Delay value
	delay=${delays[i]}
	echo Delay: $delay

	for (( j = 0; j < 3; j++ )); do
		# Loss value
		loss=${losses[j]}
		echo Loss: $loss
		
		# Uncomment the first line if running this command for the first time. Use "add" if first time else "change"
		# sudo tc qdisc add dev lo root netem loss $loss delay $delay 
		sudo tc qdisc change dev lo root netem loss $loss delay $delay

		for (( k = 0; k < 2; k++ )); do
			isReno=$k
			# TCP type = {reno|cubic} 
			if (( $isReno==1 ))
			then
				echo "Reno"
				tcp="reno"
			else
				echo "Cubic"
				tcp="cubic"
			fi

			echo -n "" > thput.txt # clear thput.txt

			for (( run = 0; run < 20; run++ )); do
				# 20 runs for each loss,dalay,tcp values
				
				if [[ $(lsof -t -i:5432) ]] 
				then
					# Error handling: Stop all the process running on the port 5432 
					kill -9 $(lsof -t -i:5432)
				fi
				
				# Start receiver side and append the througput values to file thput.txt
				./receiver $tcp >> thput.txt &
				P1=$! # PID of receiver

				# Error handling: If receiver (server) is running then only start sender (client) else wait for 1s then start sender (client)
				if [[ $(lsof -t -i:5432) ]] 
				then
					# Start sender side
					./sender $tcp & P2=$!
				else
					# Wait for 1s then start sender side
					sleep 1
					./sender $tcp & P2=$!
				fi
					
				# Wait for sender and receiver to terminate
				wait $P2 $P1 

				f1='send.txt'
				f2='recv.txt'
				# Compare both the files if all the data is transfered
				if ! diff -q $f1 $f2 > /dev/null
				then
				  echo "The files are different"
				fi

			done
				# Compute mean (thput values in the thput.txt file) using the AWK comment 
				mean=$(awk '{for(i=1;i<=NF;i++) {sum[i] += $i; sumsq[i] += ($i)^2}} 
						END {for (i=1;i<=NF;i++) {
						printf "%f", sum[i]/NR}
						}' thput.txt)

				# Compute stddev (thput values in the thput.txt file) using the AWK comment 
				stddev=$(awk '{for(i=1;i<=NF;i++) {sum[i] += $i; sumsq[i] += ($i)^2}} 
						END {for (i=1;i<=NF;i++) {
						printf "%f", sqrt((sumsq[i]-sum[i]^2/NR)/NR)}
						}' thput.txt)

				# Print the mean and stddev values
				echo Mean: $mean
				echo Stddev: $stddev
		done
	done
done
