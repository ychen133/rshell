#!/bin/bash
#!/bin/sh

cd ..
make rshell
cd src

test1="exit"
test2="ls && exit"
test3="ls; echo exiting; exit#yolo"

{
echo $test1
sleep 2
} | ./rshell

{
echo $test2
sleep 2
} | ./rshell

{
echo $test3
} | ./rshell
