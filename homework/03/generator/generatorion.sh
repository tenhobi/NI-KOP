#!/usr/bin/env bash

### parameter -W ... weight
#for i in {1..10}
#do
#  VALUE=$((i * 100))
#  ./generator/kg2 -n 15 -N 200 -W $VALUE -C 500 > weight_$VALUE.txt
#done

### parameter -C ... cost
#for i in {1..10}
#do
#  VALUE=$((i * 100))
#  ./generator/kg2 -n 15 -N 200 -W 500 -C $VALUE > cost_$VALUE.txt
#done

### parameter -m ... bag capacity : sum weight ration
#for i in {1..10}
#do
#  VALUE=$(echo "$i * 0.1" | bc)
#  ./generator/kg2 -n 15 -N 200 -W 500 -C 500 -m $VALUE > capsumw_$VALUE.txt
#done

### parameter -c ... correlation with weight
#for k in {uni,corr,strong}
#do
#  for i in {1..10}
#  do
#    VALUE=$((i * 100))
#    ./generator/kg2 -n 15 -N 200 -W $VALUE -C 500 -c $k > xxx_${k}_$VALUE.txt
#  done
#done

### parameter -k ... exponent of granularity
#for w in {bal,light,heavy}
#do
#  for k in -5 -2 -1 -0.7 -0.5 -0.2 0 0.2 0.5 0.7 1 2 5
#  do
#    ./generator/kg2 -n 15 -N 200 -W 500 -C 500 -w $w -k $k > yyy_${w}_$k.txt
#  done
#done

## heuristic: parameter -m ... bag capacity : sum weight ration
#for i in {1..10}
#do
#  VALUE=$(echo "$i * 0.1" | bc)
#  ./generator/kg2 -n 15 -N 200 -W 500 -C 500 -m $VALUE > capsumw_$VALUE.txt
#done

### heuristic: parameter -k ... exponent of granularity
#for w in {bal,light,heavy}
#do
#  for k in -5 -2 -1 -0.7 -0.5 -0.2 0 0.2 0.5 0.7 1 2 5
#  do
#    ./generator/kg2 -n 15 -N 200 -W 500 -C 500 -w $w -k $k > zzz_${w}_$k.txt
#  done
#done
