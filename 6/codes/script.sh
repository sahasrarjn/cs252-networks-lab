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

sudo ifconfig lo mtu 1500 # which loopback interface

for (( i = 0; i < 3; i++ )); do
	delay=${delays[i]}
	echo Delay: $delay
	for (( j = 0; j < 3; j++ )); do
		loss=${losses[j]}
		echo Loss: $loss
	#### Run .... add ..... $delay if giving errors (i.e. running this command for the first time)
		sudo tc qdisc change dev lo root netem loss $loss delay $delay
		for (( k = 1; k < 2; k++ )); do
			isReno=$k
			if (( $isReno==1 ))
			then
				echo "Reno"
				tcp="reno"
			else
				echo "Cubic"
				tcp="cubic"
			fi

			echo -n "" > thput.txt # clear thput

			for (( run = 1; run < 20; run++ )); do
				if [[ $(lsof -t -i:5432) ]] 
				then
					kill -9 $(lsof -t -i:5432)
				fi
				# echo $run
				./receiver $tcp >> thput.txt &
				P1=$!

				if [[ $(lsof -t -i:5432) ]] 
				then
					./sender $tcp & P2=$!
				else
					sleep 1
					./sender $tcp & P2=$!
				fi
				
				wait $P2 $P1 # Wait for sender to stop
				

				f1='send.txt'
				f2='recv.txt'
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
				echo Mean: $mean
				echo Stddev: $stddev
		done
	done
done
