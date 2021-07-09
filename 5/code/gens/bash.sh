# cat $1 | grep 'throughput' | sed 's/Total channel throughput = //g' > temp.txt
cnt=$(wc -l temp.txt)
python3 gen.py $cnt < temp.txt | sed "s/\'//g" | sed "s/,//g"