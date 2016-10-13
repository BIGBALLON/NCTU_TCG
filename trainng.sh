#!/bin/sh

num=0
while true 
do
./play_game 100
let num=num+100
printf "%d\n" $num
done
