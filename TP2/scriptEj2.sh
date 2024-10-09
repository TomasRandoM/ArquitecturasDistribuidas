#!/bin/bash

for i in {1..8}
do
   mpirun -n $i --hostfile ips.txt /home/mpiuser/tomas_rando/main.out
done
