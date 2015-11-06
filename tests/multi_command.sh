#!/bin/bash
#!/bin/sh

cd .. 
make rshell
cd src
string1= ls -a; echo Welcome!
string2= mkdir test; ls; rmdir test; ls 
{
echo $string1
sleep 1
echo $string2
sleep 1
echo exit
} | ./rshell
