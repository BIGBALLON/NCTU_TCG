#!/bin/sh

num=0
while true 
do
./play_game 500
let num=num+500
printf "times:%d\n" $num
done
