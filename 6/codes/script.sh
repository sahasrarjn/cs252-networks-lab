#! /bin/bash
## Give sudo permissions `sudo ./script.sh`

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

sudo ifconfig lo mtu 1500 # which loopback interface

for (( i = 0; i < 3; i++ )); do
	delay=${delays[i]}
	echo "=============== Delay: "$delay "=============="
	#### Run .... add ..... $delay if giving errors (i.e. running this command for the first time)
	sudo tc qdisc change dev lo root netem delay $delay
	for (( j = 0; j < 3; j++ )); do
		loss=${losses[i]}
		echo "=============== Loss: "$loss "==============="
	#### Run .... add ..... $delay if giving errors (i.e. running this command for the first time)
		sudo tc qdisc change dev lo root netem loss $loss
		for (( k = 0; k < 2; k++ )); do
			isReno=$k
			if (( $isReno==1 ))
			then
				echo "======== Reno ========"
			else
				echo "======== Cubic ========"
			fi

			echo -n "" > thput.txt # clear thput

			for (( run = 1; run < 21; run++ )); do
				echo $run
				./receiver $isReno &
				P1=$!
				./sender 0.0.0.0 $isReno & # ectract sender time from here
				thput=$(cat temp | tail -1 & P2=$!) 
				wait $P2 # Wait for sender to stop
				echo $P1
				kill -9 $P1 # Stop receiver

				f1='send.txt'
				f2='recv.txt'
				if ! diff -q $f1 $f2 > /dev/null
				then
				  echo "Error: The files are different or inaccessible"
				fi

				echo $thput >> thput.txt
			done
				mean=$(awk '{for(i=1;i<=NF;i++) {sum[i] += $i; sumsq[i] += ($i)^2}} 
						END {for (i=1;i<=NF;i++) {
						printf "%f", sum[i]/NR}
						}' thput.txt)

				stddev=$(awk '{for(i=1;i<=NF;i++) {sum[i] += $i; sumsq[i] += ($i)^2}} 
						END {for (i=1;i<=NF;i++) {
						printf "%f", sqrt((sumsq[i]-sum[i]^2/NR)/NR)}
						}' thput.txt)

			    echo Delay =$delay, Loss=$loss
				echo Mean Thput: $mean
				echo Std Dev of Thput: $stddev
				echo .........................
		done
	done
done