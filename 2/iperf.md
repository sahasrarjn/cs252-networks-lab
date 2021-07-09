# IPERF measurements


## TCP

### `iperf3 -c iperf.biznetnetworks.com`

```
Connecting to host iperf.biznetnetworks.com, port 5201
[  6] local 192.168.1.101 port 61818 connected to 117.102.109.186 port 5201
[ ID] Interval           Transfer     Bandwidth
[  6]   0.00-1.00   sec  1.87 MBytes  15.6 Mbits/sec                  
[  6]   1.00-2.00   sec  3.83 MBytes  32.2 Mbits/sec                  
[  6]   2.00-3.00   sec  3.13 MBytes  26.2 Mbits/sec                  
[  6]   3.00-4.00   sec  2.17 MBytes  18.2 Mbits/sec                  
[  6]   4.00-5.00   sec  2.69 MBytes  22.6 Mbits/sec                  
[  6]   5.00-6.00   sec  3.03 MBytes  25.4 Mbits/sec                  
[  6]   6.00-7.00   sec  3.15 MBytes  26.4 Mbits/sec                  
[  6]   7.00-8.00   sec  1.88 MBytes  15.8 Mbits/sec                  
[  6]   8.00-9.00   sec  2.30 MBytes  19.3 Mbits/sec                  
[  6]   9.00-10.00  sec  2.31 MBytes  19.4 Mbits/sec                  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth
[  6]   0.00-10.00  sec  26.4 MBytes  22.1 Mbits/sec                  sender
[  6]   0.00-10.00  sec  25.8 MBytes  21.6 Mbits/sec                  receiver

iperf Done.
```



### `iperf -c iperf.scottlinux.com`

```
[  6] local 192.168.1.101 port 61831 connected to 45.33.39.39 port 5201
[ ID] Interval           Transfer     Bandwidth
[  6]   0.00-1.00   sec   143 KBytes  1.17 Mbits/sec                  
[  6]   1.00-2.00   sec   536 KBytes  4.39 Mbits/sec                  
[  6]   2.00-3.00   sec  1.45 MBytes  12.1 Mbits/sec                  
[  6]   3.00-4.00   sec  2.91 MBytes  24.5 Mbits/sec                  
[  6]   4.00-5.00   sec  4.88 MBytes  40.9 Mbits/sec                  
[  6]   5.00-6.00   sec  3.44 MBytes  28.9 Mbits/sec                  
[  6]   6.00-7.00   sec  3.14 MBytes  26.4 Mbits/sec                  
[  6]   7.00-8.00   sec  2.57 MBytes  21.6 Mbits/sec                  
[  6]   8.00-9.00   sec   824 KBytes  6.75 Mbits/sec                  
[  6]   9.00-10.00  sec  2.20 MBytes  18.5 Mbits/sec                  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth
[  6]   0.00-10.00  sec  22.1 MBytes  18.5 Mbits/sec                  sender
[  6]   0.00-10.00  sec  21.2 MBytes  17.8 Mbits/sec                  receiver

iperf Done.
```





## UDP

### iperf.scottlinux.com

#### 1M

```
sahasraranjan@Sahasra-MacBook-Pro apps % ./iperf3 -c iperf.scottlinux.com -u -b 1M
Connecting to host iperf.scottlinux.com, port 5201
[  6] local 192.168.1.101 port 63259 connected to 45.33.39.39 port 5201
[ ID] Interval           Transfer     Bandwidth       Total Datagrams
[  6]   0.00-1.00   sec   120 KBytes   980 Kbits/sec  15  
[  6]   1.00-2.00   sec   128 KBytes  1.05 Mbits/sec  16  
[  6]   2.00-3.00   sec   120 KBytes   984 Kbits/sec  15  
[  6]   3.00-4.00   sec   120 KBytes   983 Kbits/sec  15  
[  6]   4.00-5.00   sec   120 KBytes   983 Kbits/sec  15  
[  6]   5.00-6.00   sec   128 KBytes  1.05 Mbits/sec  16  
[  6]   6.00-7.00   sec   120 KBytes   983 Kbits/sec  15  
[  6]   7.00-8.00   sec   120 KBytes   983 Kbits/sec  15  
[  6]   8.00-9.00   sec   120 KBytes   982 Kbits/sec  15  
[  6]   9.00-10.00  sec   128 KBytes  1.05 Mbits/sec  16  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Jitter    Lost/Total Datagrams
[  6]   0.00-10.00  sec  1.20 MBytes  1.00 Mbits/sec  5503895.693 ms  0/153 (0%)  
[  6] Sent 153 datagrams

iperf Done.
```



#### 2M

```
sahasraranjan@Sahasra-MacBook-Pro apps % ./iperf3 -c iperf.scottlinux.com -u -b 2M
Connecting to host iperf.scottlinux.com, port 5201
[  6] local 192.168.1.101 port 52163 connected to 45.33.39.39 port 5201
[ ID] Interval           Transfer     Bandwidth       Total Datagrams
[  6]   0.00-1.00   sec   232 KBytes  1.89 Mbits/sec  29  
[  6]   1.00-2.00   sec   248 KBytes  2.03 Mbits/sec  31  
[  6]   2.00-3.00   sec   240 KBytes  1.97 Mbits/sec  30  
[  6]   3.00-4.00   sec   248 KBytes  2.03 Mbits/sec  31  
[  6]   4.00-5.00   sec   240 KBytes  1.97 Mbits/sec  30  
[  6]   5.00-6.00   sec   248 KBytes  2.03 Mbits/sec  31  
[  6]   6.00-7.00   sec   240 KBytes  1.96 Mbits/sec  30  
[  6]   7.00-8.00   sec   248 KBytes  2.03 Mbits/sec  31  
[  6]   8.00-9.00   sec   240 KBytes  1.97 Mbits/sec  30  
[  6]   9.00-10.00  sec   248 KBytes  2.03 Mbits/sec  31  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Jitter    Lost/Total Datagrams
[  6]   0.00-10.00  sec  2.38 MBytes  1.99 Mbits/sec  346.473 ms  0/303 (0%)  
[  6] Sent 303 datagrams

iperf Done.
```



#### 4M

```
sahasraranjan@Sahasra-MacBook-Pro apps % ./iperf3 -c iperf.scottlinux.com -u -b 4M
Connecting to host iperf.scottlinux.com, port 5201
[  6] local 192.168.1.101 port 52838 connected to 45.33.39.39 port 5201
[ ID] Interval           Transfer     Bandwidth       Total Datagrams
[  6]   0.00-1.00   sec   448 KBytes  3.65 Mbits/sec  56  
[  6]   1.00-2.00   sec   496 KBytes  4.08 Mbits/sec  62  
[  6]   2.00-3.00   sec   488 KBytes  3.99 Mbits/sec  61  
[  6]   3.00-4.00   sec   488 KBytes  4.00 Mbits/sec  61  
[  6]   4.00-5.00   sec   488 KBytes  4.00 Mbits/sec  61  
[  6]   5.00-6.00   sec   488 KBytes  4.00 Mbits/sec  61  
[  6]   6.00-7.00   sec   488 KBytes  4.00 Mbits/sec  61  
[  6]   7.00-8.00   sec   488 KBytes  3.99 Mbits/sec  61  
[  6]   8.00-9.00   sec   488 KBytes  4.00 Mbits/sec  61  
[  6]   9.00-10.00  sec   488 KBytes  4.00 Mbits/sec  61  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Jitter    Lost/Total Datagrams
[  6]   0.00-10.00  sec  4.73 MBytes  3.97 Mbits/sec  1.514 ms  0/605 (0%)  
[  6] Sent 605 datagrams

iperf Done.
```



#### 8M

```
sahasraranjan@Sahasra-MacBook-Pro apps % ./iperf3 -c iperf.scottlinux.com -u -b 8M
Connecting to host iperf.scottlinux.com, port 5201
[  6] local 192.168.1.101 port 65043 connected to 45.33.39.39 port 5201
[ ID] Interval           Transfer     Bandwidth       Total Datagrams
[  6]   0.00-1.00   sec   896 KBytes  7.33 Mbits/sec  112  
[  6]   1.00-2.00   sec   976 KBytes  7.97 Mbits/sec  122  
[  6]   2.00-3.00   sec   976 KBytes  8.02 Mbits/sec  122  
[  6]   3.00-4.00   sec   976 KBytes  8.00 Mbits/sec  122  
[  6]   4.00-5.00   sec   976 KBytes  8.00 Mbits/sec  122  
[  6]   5.00-6.00   sec   976 KBytes  7.97 Mbits/sec  122  
[  6]   6.00-7.00   sec   976 KBytes  8.02 Mbits/sec  122  
[  6]   7.00-8.00   sec   976 KBytes  8.00 Mbits/sec  122  
[  6]   8.00-9.00   sec   976 KBytes  7.99 Mbits/sec  122  
[  6]   9.00-10.00  sec   976 KBytes  8.00 Mbits/sec  122  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Jitter    Lost/Total Datagrams
[  6]   0.00-10.00  sec  9.45 MBytes  7.93 Mbits/sec  1.791 ms  0/1210 (0%)  
[  6] Sent 1210 datagrams

iperf Done.
```



#### 16M

```
sahasraranjan@Sahasra-MacBook-Pro apps % ./iperf3 -c iperf.scottlinux.com -u -b 16M
Connecting to host iperf.scottlinux.com, port 5201
[  6] local 192.168.1.101 port 54045 connected to 45.33.39.39 port 5201
[ ID] Interval           Transfer     Bandwidth       Total Datagrams
[  6]   0.00-1.00   sec  1.73 MBytes  14.4 Mbits/sec  221  
[  6]   1.00-2.01   sec  1.91 MBytes  16.0 Mbits/sec  245  
[  6]   2.01-3.01   sec  1.91 MBytes  16.1 Mbits/sec  245  
[  6]   3.01-4.00   sec  1.90 MBytes  15.9 Mbits/sec  243  
[  6]   4.00-5.00   sec  1.91 MBytes  16.1 Mbits/sec  245  
[  6]   5.00-6.00   sec  1.90 MBytes  15.9 Mbits/sec  243  
[  6]   6.00-7.00   sec  1.91 MBytes  16.1 Mbits/sec  245  
[  6]   7.00-8.00   sec  1.91 MBytes  16.0 Mbits/sec  244  
[  6]   8.00-9.00   sec  1.91 MBytes  16.0 Mbits/sec  244  
[  6]   9.00-10.01  sec  1.91 MBytes  15.9 Mbits/sec  244  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Jitter    Lost/Total Datagrams
[  6]   0.00-10.01  sec  18.9 MBytes  15.8 Mbits/sec  2.283 ms  71/2419 (2.9%)  
[  6] Sent 2419 datagrams

iperf Done.
```



#### 32M

```
Connecting to host iperf.scottlinux.com, port 5201
[  6] local 192.168.1.101 port 54571 connected to 45.33.39.39 port 5201
[ ID] Interval           Transfer     Bandwidth       Total Datagrams
[  6]   0.00-1.01   sec  3.47 MBytes  28.9 Mbits/sec  444  
[  6]   1.01-2.01   sec  3.81 MBytes  32.0 Mbits/sec  488  
[  6]   2.01-3.01   sec  3.82 MBytes  32.0 Mbits/sec  489  
[  6]   3.01-4.01   sec  3.80 MBytes  31.9 Mbits/sec  486  
[  6]   4.01-5.00   sec  3.81 MBytes  32.0 Mbits/sec  488  
[  6]   5.00-6.00   sec  3.84 MBytes  32.2 Mbits/sec  491  
[  6]   6.00-7.00   sec  3.81 MBytes  32.0 Mbits/sec  488  
[  6]   7.00-8.00   sec  3.81 MBytes  32.0 Mbits/sec  488  
[  6]   8.00-9.01   sec  3.81 MBytes  31.8 Mbits/sec  488  
[  6]   9.01-10.01  sec  3.81 MBytes  32.0 Mbits/sec  488  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Jitter    Lost/Total Datagrams
[  6]   0.00-10.01  sec  37.8 MBytes  31.7 Mbits/sec  4.403 ms  10/4838 (0.21%)  
[  6] Sent 4838 datagrams

iperf Done.
```



#### 64M

```
sahasraranjan@Sahasra-MacBook-Pro apps % ./iperf3 -c iperf.scottlinux.com -u -b 64M
Connecting to host iperf.scottlinux.com, port 5201
[  6] local 192.168.1.101 port 52915 connected to 45.33.39.39 port 5201
[ ID] Interval           Transfer     Bandwidth       Total Datagrams
[  6]   0.00-1.01   sec  6.90 MBytes  57.6 Mbits/sec  883  
[  6]   1.01-2.01   sec  7.66 MBytes  64.3 Mbits/sec  981  
[  6]   2.01-3.00   sec  7.59 MBytes  63.7 Mbits/sec  972  
[  6]   3.00-4.00   sec  7.66 MBytes  64.6 Mbits/sec  981  
[  6]   4.00-5.00   sec  7.62 MBytes  63.7 Mbits/sec  976  
[  6]   5.00-6.00   sec  7.63 MBytes  64.0 Mbits/sec  977  
[  6]   6.00-7.00   sec  7.63 MBytes  64.1 Mbits/sec  977  
[  6]   7.00-8.00   sec  7.60 MBytes  64.0 Mbits/sec  973  
[  6]   8.00-9.00   sec  7.63 MBytes  64.0 Mbits/sec  977  
[  6]   9.00-10.00  sec  7.65 MBytes  63.9 Mbits/sec  981  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Jitter    Lost/Total Datagrams
[  6]   0.00-10.00  sec  75.6 MBytes  63.4 Mbits/sec  1.168 ms  6826/9645 (71%)  
[  6] Sent 9645 datagrams

iperf Done.
```



#### 128M

```
sahasraranjan@Sahasra-MacBook-Pro apps % ./iperf3 -c iperf.scottlinux.com -u -b 128M
Connecting to host iperf.scottlinux.com, port 5201
[  6] local 192.168.1.101 port 59708 connected to 45.33.39.39 port 5201
[ ID] Interval           Transfer     Bandwidth       Total Datagrams
[  6]   0.00-1.00   sec  13.8 MBytes   115 Mbits/sec  1764  
[  6]   1.00-2.00   sec  13.8 MBytes   116 Mbits/sec  1778  
[  6]   2.00-3.00   sec  16.7 MBytes   140 Mbits/sec  2139  
[  6]   3.00-4.00   sec  13.8 MBytes   116 Mbits/sec  1776  
[  6]   4.00-5.00   sec  16.7 MBytes   140 Mbits/sec  2138  
[  6]   5.00-6.00   sec  15.4 MBytes   128 Mbits/sec  1974  
[  6]   6.00-7.00   sec  16.2 MBytes   136 Mbits/sec  2081  
[  6]   7.00-8.00   sec  14.2 MBytes   119 Mbits/sec  1826  
[  6]   8.00-9.00   sec  13.8 MBytes   115 Mbits/sec  1766  
[  6]   9.00-10.00  sec  16.8 MBytes   141 Mbits/sec  2153  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Jitter    Lost/Total Datagrams
[  6]   0.00-10.00  sec   151 MBytes   127 Mbits/sec  469.606 ms  18046/18823 (96%)  
[  6] Sent 18823 datagrams

iperf Done.
```



#### 256M

```
Connecting to host iperf.scottlinux.com, port 5201
[  6] local 192.168.1.101 port 51463 connected to 45.33.39.39 port 5201
[ ID] Interval           Transfer     Bandwidth       Total Datagrams
[  6]   0.00-1.00   sec  28.7 MBytes   240 Mbits/sec  3679  
[  6]   1.00-2.00   sec  29.6 MBytes   248 Mbits/sec  3786  
[  6]   2.00-3.00   sec  30.6 MBytes   257 Mbits/sec  3917  
[  6]   3.00-4.00   sec  30.4 MBytes   255 Mbits/sec  3896  
[  6]   4.00-5.00   sec  32.6 MBytes   274 Mbits/sec  4176  
[  6]   5.00-6.00   sec  28.5 MBytes   238 Mbits/sec  3651  
[  6]   6.00-7.00   sec  32.4 MBytes   272 Mbits/sec  4152  
[  6]   7.00-8.00   sec  23.2 MBytes   194 Mbits/sec  2970  
[  6]   8.00-9.00   sec  35.9 MBytes   302 Mbits/sec  4598  
[  6]   9.00-10.00  sec  30.4 MBytes   255 Mbits/sec  3899  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Jitter    Lost/Total Datagrams
[  6]   0.00-10.00  sec   302 MBytes   254 Mbits/sec  285.509 ms  37857/38163 (99%)  
[  6] Sent 38163 datagrams

iperf Done.
```



#### 512M

```
sahasraranjan@Sahasra-MacBook-Pro apps % ./iperf3 -c iperf.scottlinux.com -u -b 512M
Connecting to host iperf.scottlinux.com, port 5201
[  6] local 192.168.1.101 port 55046 connected to 45.33.39.39 port 5201
[ ID] Interval           Transfer     Bandwidth       Total Datagrams
[  6]   0.00-1.00   sec  55.7 MBytes   467 Mbits/sec  7133  
[  6]   1.00-2.00   sec  54.9 MBytes   459 Mbits/sec  7031  
[  6]   2.00-3.00   sec  61.2 MBytes   514 Mbits/sec  7841  
[  6]   3.00-4.00   sec  67.1 MBytes   562 Mbits/sec  8585  
[  6]   4.00-5.00   sec  61.2 MBytes   514 Mbits/sec  7839  
[  6]   5.00-6.00   sec  60.7 MBytes   509 Mbits/sec  7773  
[  6]   6.00-7.00   sec  43.0 MBytes   360 Mbits/sec  5503  
[  6]   7.00-8.00   sec  79.2 MBytes   664 Mbits/sec  10133  
[  6]   8.00-9.00   sec  65.8 MBytes   555 Mbits/sec  8427  
[  6]   9.00-10.00  sec  50.2 MBytes   421 Mbits/sec  6425  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Jitter    Lost/Total Datagrams
[  6]   0.00-10.00  sec   599 MBytes   502 Mbits/sec  300919930.215 ms  59157/59248 (1e+02%)  
[  6] Sent 59248 datagrams

iperf Done.
```



#### 1024M

```
Connecting to host iperf.scottlinux.com, port 5201
[  6] local 192.168.1.101 port 54506 connected to 45.33.39.39 port 5201
[ ID] Interval           Transfer     Bandwidth       Total Datagrams
[  6]   0.00-1.00   sec   113 MBytes   950 Mbits/sec  14510  
[  6]   1.00-2.00   sec   122 MBytes  1.02 Gbits/sec  15554  
[  6]   2.00-3.00   sec   122 MBytes  1.02 Gbits/sec  15635  
[  6]   3.00-4.00   sec   122 MBytes  1.02 Gbits/sec  15622  
[  6]   4.00-5.00   sec   122 MBytes  1.02 Gbits/sec  15648  
[  6]   5.00-6.00   sec   122 MBytes  1.03 Gbits/sec  15622  
[  6]   6.00-7.00   sec   122 MBytes  1.02 Gbits/sec  15627  
[  6]   7.00-8.00   sec   122 MBytes  1.02 Gbits/sec  15615  
[  6]   8.00-9.00   sec   122 MBytes  1.02 Gbits/sec  15639  
[  6]   9.00-10.00  sec   120 MBytes  1.01 Gbits/sec  15387  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Jitter    Lost/Total Datagrams
[  6]   0.00-10.00  sec  1.18 GBytes  1.01 Gbits/sec  96.536 ms  154018/154644 (1e+02%)  
[  6] Sent 154644 datagrams

iperf Done.
```



#### 2048M

```
sahasraranjan@Sahasra-MacBook-Pro apps % ./iperf3 -c iperf.scottlinux.com -u -b 2048M
Connecting to host iperf.scottlinux.com, port 5201
[  6] local 192.168.1.101 port 54948 connected to 45.33.39.39 port 5201
[ ID] Interval           Transfer     Bandwidth       Total Datagrams
[  6]   0.00-1.00   sec   236 MBytes  1.97 Gbits/sec  30144  
[  6]   1.00-2.00   sec   240 MBytes  2.02 Gbits/sec  30775  
[  6]   2.00-3.00   sec   243 MBytes  2.04 Gbits/sec  31120  
[  6]   3.00-4.00   sec   246 MBytes  2.07 Gbits/sec  31472  
[  6]   4.00-5.00   sec   244 MBytes  2.04 Gbits/sec  31191  
[  6]   5.00-6.01   sec   242 MBytes  2.03 Gbits/sec  31003  
[  6]   6.01-7.00   sec   246 MBytes  2.07 Gbits/sec  31501  
[  6]   7.00-8.00   sec   244 MBytes  2.05 Gbits/sec  31229  
[  6]   8.00-9.00   sec   244 MBytes  2.04 Gbits/sec  31218  
[  6]   9.00-10.00  sec   245 MBytes  2.06 Gbits/sec  31357  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Jitter    Lost/Total Datagrams
[  6]   0.00-10.00  sec  2.37 GBytes  2.04 Gbits/sec  6679689.929 ms  273180/273330 (1e+02%)  
[  6] Sent 273330 datagrams

iperf Done.
```



#### 4096M

```
sahasraranjan@Sahasra-MacBook-Pro apps % ./iperf3 -c iperf.scottlinux.com -u -b 4096M
Connecting to host iperf.scottlinux.com, port 5201
[  6] local 192.168.1.101 port 55191 connected to 45.33.39.39 port 5201
[ ID] Interval           Transfer     Bandwidth       Total Datagrams
[  6]   0.00-1.00   sec   388 MBytes  3.25 Gbits/sec  49664  
[  6]   1.00-2.00   sec   570 MBytes  4.78 Gbits/sec  72916  
[  6]   2.00-3.00   sec   487 MBytes  4.09 Gbits/sec  62359  
[  6]   3.00-4.00   sec   487 MBytes  4.09 Gbits/sec  62365  
[  6]   4.00-5.00   sec   495 MBytes  4.15 Gbits/sec  63351  
[  6]   5.00-6.00   sec   484 MBytes  4.06 Gbits/sec  61942  
[  6]   6.00-7.00   sec   468 MBytes  3.92 Gbits/sec  59888  
[  6]   7.00-8.00   sec   521 MBytes  4.37 Gbits/sec  66716  
[  6]   8.00-9.00   sec   477 MBytes  4.00 Gbits/sec  61023  
[  6]   9.00-10.00  sec   505 MBytes  4.24 Gbits/sec  64633  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Jitter    Lost/Total Datagrams
[  6]   0.00-10.00  sec  4.77 GBytes  4.10 Gbits/sec  321678.496 ms  602885/603082 (1e+02%)  
[  6] Sent 603082 datagrams

iperf Done.
```



#### 8192M (Here we got throughput less than the specified UDP rate)

```
sahasraranjan@Sahasra-MacBook-Pro apps % ./iperf3 -c iperf.scottlinux.com -u -b 8192M
Connecting to host iperf.scottlinux.com, port 5201
[  6] local 192.168.1.101 port 55616 connected to 45.33.39.39 port 5201
[ ID] Interval           Transfer     Bandwidth       Total Datagrams
[  6]   0.00-1.00   sec   467 MBytes  3.91 Gbits/sec  59736  
[  6]   1.00-2.00   sec   638 MBytes  5.35 Gbits/sec  81648  
[  6]   2.00-3.00   sec   676 MBytes  5.67 Gbits/sec  86526  
[  6]   3.00-4.00   sec   645 MBytes  5.41 Gbits/sec  82542  
[  6]   4.00-5.00   sec   655 MBytes  5.49 Gbits/sec  83824  
[  6]   5.00-6.00   sec   686 MBytes  5.75 Gbits/sec  87760  
[  6]   6.00-7.00   sec   668 MBytes  5.60 Gbits/sec  85463  
[  6]   7.00-8.00   sec   685 MBytes  5.74 Gbits/sec  87623  
[  6]   8.00-9.00   sec   695 MBytes  5.83 Gbits/sec  88952  
[  6]   9.00-10.00  sec   695 MBytes  5.83 Gbits/sec  88910  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Jitter    Lost/Total Datagrams
[  6]   0.00-10.00  sec  6.36 GBytes  5.46 Gbits/sec  10472026883.641 ms  776924/776960 (1e+02%)  
[  6] Sent 776960 datagrams

iperf Done.
```

