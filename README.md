Author: Yu-Che Cheng
Partner: William Gu
User: ychen133 & wgu005
SID: 861142301
Class: CS-100-001
Lab: 023
HW#1: rshell

Summary:
In this programming assignment, I learned to use 3 important functions:
fork(), wait(), and execvp(). These commands allows me to run bash commands
inside a C++ program. Even though execvp() alone, given the right arguments
and usage, can carry out a bash command on its own, it needs the other 2 functions
to handle multiple commands. The task of this assignment was to create our own
shell that prompts the user for a line of bash commands, executes it, and 
continues doing so until told to stop with the command "exit". 

The shell we are tasked with making must be able to handle connectors ;, &&, 
and || so it can run multiple commands put on a single line of input. Each 
connectors specefies the order of execution for the 2 commands it takes in
differently. To achieve this, we must use execvp() to be able to run single
commands; but, execvp() stops the program (much like return) when executed
correctly so fork must be used to run multiple instances of execvp() at a time
so that the program don't stop after executing a single command. To specify 
behaviors that waits for the result of the child process and then acts accordingly 
we use call wait(), usually like this: wait(&status), in order to wait for the 
first process of the fork(), which is the child, to finish then we move on to its
second process, the parent.

After we have the mentioned process wrapped in a function, call it myPrompt(),
we can have another function, call it myFork(), to call the first function 
within a fork. myPrompt() will be called in the child process and the parent 
process will wait for it to finish, check what happens, and choose whether
to fork a new process to prompt the user for another input or to simply stop 
in the case of an "exit" command is inputted. If the child succeeds, the parent 
should call myFork() to prompt user again.

In development of this program, we came across some bugs that needed fixing.
One of the first bug encountered was with && connector. While testing, I
discovered that the exit() call doesn't end the if statement/ stop the entire
fork but rather simply exit the branch, either it be child or parent. So 
this causes the && to continue the command after it even when the command before
fails. This was resolved by using an if statement that checks whether the 
child branch exited itself or not.n the parent branch. So basically the design
went like so: if the child succeeds, the parent doesn't exit. But if child
fails, the parent exits and stops reading.

Another bug found relates to the comment function of rshell. When # is found,
the program uses substr() to obtain an argument that came before #. The 
substring is then put into the string token to be process by the program. So
when the program reads "#echo" it turns it into "", an empty string with size
of zero. This caused a problem with the if statement that detects the ;  
connector which calls string::at(string::size() - 1) to access the last 
char in the string. So if the string is "", it tries to access index of -1,
whihc is an out-of-bounds error. This is resolved by adding another condition
in the if statement that checks to see if token's size is greater than 0.

The comment detection part also had another bug. When # is detected, it will
leave the execution of what ever is left in stringList to a piece of code outside
the while() loop used for reading input. By default, it would return 0, if 
execvp() runs. Thus, I had to change my return when "exit" is detected to 1.
Now # can be properly ignored. While debugging this, I noticed that a lot of 
my bugs were the result of my comment detection code's being to complicated 
and messy. So I smoothed it out by simply using the string::substr(). 
The execution, pushing to stringList, etc. will all be handled by the rest of the 
code just like any other token. This however wil not deal with inputs such as
"echo hi # echo nope". An input like this will still echo "nope". So I changed 
the comment detection code again. The code retains its substr() for getting
anything before the #. But now it loads contents of stringList into myCmd[]
and executes if stringList.size() is not 0. NULL is added after stringList's
contents have been loaded into myCmd. This tell program to where to stop
reading. Now the comment part of the code works correctly.       
