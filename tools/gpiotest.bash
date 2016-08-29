#!/bin/bash
source gpio

gpio mode 0 out
gpio mode 2 out

gpio mode 3 in
gpio mode 5 in
gpio mode 6 in

gpio write 0 1
sleep .5
gpio write 0 0
sleep .5

gpio write 2 1
sleep .5
gpio write 2 0
sleep .5

gpio write 0 1
sleep .5
gpio write 0 0
sleep .5

gpio write 2 1
sleep .5
gpio write 2 0
sleep .5

gpio write 0 1
gpio write 2 1
sleep .5
gpio write 0 0
gpio write 2 0
sleep .5

gpio write 0 1
gpio write 2 1
sleep .5
gpio write 0 0
gpio write 2 0
sleep .5

gpio write 0 1
sleep .5
gpio write 0 0
gpio write 2 1
sleep .5
gpio write 2 0
sleep .5

gpio write 0 1
sleep .5
gpio write 0 0
sleep .5

gpio write 2 1
sleep .5
gpio write 2 0
sleep .5

gpio write 0 1
sleep .5
gpio write 0 0
sleep .5

gpio write 2 1
sleep .5
gpio write 2 0
sleep .5

gpio write 0 1
gpio write 2 1
sleep .5
gpio write 0 0
gpio write 2 0
sleep .5

gpio write 0 1
gpio write 2 1
sleep .5
gpio write 0 0
gpio write 2 0
sleep .5

gpio write 0 1
sleep .5
gpio write 0 0
gpio write 2 1
sleep .5
gpio write 2 0
sleep .5
