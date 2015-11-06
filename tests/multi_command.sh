#!/bin/bash
#!/bin/sh

string1= echo test1; ls -a; echo Welcome!
string2= echo test2; mkdir test; ls; rmdir test; ls 
string3= echo test3; ls -a; echo hello && mkdir test2 && rmdir test2 || echo world

cd ..
make rshell
cd src

{
echo $string1
sleep 1
echo $string2
sleep 1
echo $string3
sleep 1
echo exit
} | ./rshell
