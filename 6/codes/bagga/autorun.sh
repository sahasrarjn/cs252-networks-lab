#!/bin/bash
gcc client.c -o client
gcc server.c -o server
touch data.txt
touch send.txt
touch recv.txt
> data.txt
> recv.txt
> send.txt
tcpflow=(reno cubic)
delays=(10ms 50ms 100ms)
losses=(0.1% 0.5% 1%)
sudo tc qdisc add dev lo root netem delay 0ms
for i  in $(seq 0 1);do
	for j in $(seq 0 2);do 
		for l in $(seq 0 2);do
			sudo tc qdisc change dev lo root netem loss ${losses[l]} delay ${delays[j]}
			echo ${tcpflow[i]} ${delays[j]} ${losses[l]}  >> data.txt		
			for gg in $(seq 1 20);do
				temp1=$(($i+$j+$l*21+$gg*441+8000))
				> send.txt
				base64 /dev/urandom | head -c 5000000 > send.txt
				#temp1=8085
				echo $temp1
				./server ${tcpflow[i]} $temp1 & 
				#sleep 0.5 
				BACK_PID=$! &
				./client ${tcpflow[i]} $temp1 
				#BACK_PID=$!
				wait $BACK_PID

				#sleep 0.1
				# BACK_PID=$!
				# wait $BACK_PID
				#echo "sad"
				dflin=`diff send.txt recv.txt|wc -l`
				# rm send.txt
				# rm recv.txt
				#echo "diff:"
				>recv.txt
				#echo $dflin >> data.txt
					if [[ $dflin -eq 0 ]]; then
						#statements
						echo "No error in connection."
					else
						echo "There is error in connection. bahut badad ar e re reijoi cdj ois djsao dasoida"
						exit 1
					fi
			done;
		done;
	done;
done;
python3 gen.py