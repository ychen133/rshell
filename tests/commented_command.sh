#!/bin/bash
#!/bin/sh

cd ..
make rshell
cd src

test1="ls #-a"
test2="echo hi && #echo hello"
test3="echo hello sushi#man"
test4="ls -a && echo hello world; #exit"
{
echo $test1
sleep 2
echo $test2
sleep 2
echo $test3
sleep 2
echo $test4
sleep 2
echo exit
} | ./rshell
