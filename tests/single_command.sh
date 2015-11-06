#!/bin/sh
#!/bin/bash

cd ..
make rshell
cd src
{
echo ls -a
sleep 1
echo echo hello world
sleep 1
echo mkdir test
sleep 1
echo ls
sleep 1
echo rmdir test
sleep 1
echo ls
sleep 1
echo exit
} | ./rshell
