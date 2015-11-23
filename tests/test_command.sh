#!/bin/bash
#!/bin/sh

cd ..
make rshell
cd src

test1="test -e /.."
test2="[ -e /..]"
test3="test /.."


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
sleep 2
} | ./rshell
