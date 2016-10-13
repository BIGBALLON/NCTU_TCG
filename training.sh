#!/bin/sh

num=0
while true 
do
./play_game 5000
let num=num+5000
printf "times:%d\n" $num
done
