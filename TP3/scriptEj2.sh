#!/bin/bash

for i in {1..108}
do
   mpirun --oversubscribe -n $i --hostfile ips.txt /home/mpiuser/tomas_rando/main1.out --mca btl_tcp_if_include 10.65.1.107/24
done