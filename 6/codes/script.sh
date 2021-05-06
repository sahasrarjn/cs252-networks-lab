#! /bin/bash

# send.txt of size 5MB, already in the directory
for f in recv mean std thput
do
	# clear f.txt
	echo -n "" > f.txt
done

yes | head -c 5MB >send.txt

declare -a delays
delays=( 10ms 50ms 100ms )

declare -a losses
losses=( 0.1% 0.5% 1% )

# compile
gcc -o sender sender.c
gcc -o receiver receiver.c

#sudo ifconfig lo mtu 1500 # which loopback interface

for (( i = 0; i < 3; i++ )); do
	delay=${delays[i]}
	echo "=============== Delay: "$delay "=============="
	#### Run .... add ..... $delay if giving errors (i.e. running this command for the first time)
#	sudo tc qdisc change dev lo root netem delay $delay
	for (( j = 0; j < 3; j++ )); do
		loss=${losses[i]}
		echo "=============== Loss: "$loss "==============="
	#### Run .... add ..... $delay if giving errors (i.e. running this command for the first time)
#		sudo tc qdisc change dev lo root netem loss $loss
		for (( k = 0; k < 2; k++ )); do
			isReno=$k
			if (( $isReno==1 ))
			then
				echo "======== Reno ========"
			else
				echo "======== Cubic ========"
			fi

			echo -n "" > thput.txt # clear thput

			for (( run = 1; run < 20; run++ )); do
				echo $run
				./receiver $isReno &
				P1=$!
				./sender 0.0.0.0 $isReno >> thput.txt & P2=$!
				# thput=$(./sender 0.0.0.0 $isReno | tail -1 & P2=$!) 
				wait $P2 # Wait for sender to stop
				sleep 0.6
				kill -9 $P1 # Stop receiver

				# echo Thput: $thput
				echo $thput >> thput.txt

				f1='send.txt'
				f2='recv.txt'
				wc -l $f1
				wc -l $f2
				if ! diff -q $f1 $f2 > /dev/null
				then
				  echo "The files are different"
				fi

			done
				mean=$(awk '{for(i=1;i<=NF;i++) {sum[i] += $i; sumsq[i] += ($i)^2}} 
						END {for (i=1;i<=NF;i++) {
						printf "%f", sum[i]/NR}
						}' thput.txt)

				stddev=$(awk '{for(i=1;i<=NF;i++) {sum[i] += $i; sumsq[i] += ($i)^2}} 
						END {for (i=1;i<=NF;i++) {
						printf "%f", sqrt((sumsq[i]-sum[i]^2/NR)/NR)}
						}' thput.txt)

			    # echo Delay=$delay, Loss=$loss
				echo Mean Thput: $mean
				echo Std Dev of Thput: $stddev
				echo .........................
		done
	done
done
