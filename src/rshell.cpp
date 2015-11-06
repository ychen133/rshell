#include<iostream>
#include<sstream>
#include<cstring>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<sys/types.h>
#include<sys/wait.h>
#include<vector>
using namespace std;

int myShell()
{	
	//prompt the user for a line of input
	cout << "$ ";
	string input;
        getline(cin, input);
	//use stringstream to break inputted line as
	//multiple strings and put into token	
        stringstream ss(input);
	string token;
	//token is read and processed by the code
	//to determine what to do with it.
	//If a connector is not found in token, it is put
	//into stringList. 
	vector<string> stringList;
	//When a connector is found, empty contents of stringList
	//into myCmd as c-strings. myCmd will now hold the arguments
	//for  a single command stored in myCmd as const char* 
	//so we can use them in execvp() which takes const char*.
	const char* myCmd[50]; 
	//found is used to detect # for comments	
	size_t found;	
	
	//while loop reads a string into token one at a time
	while(ss >> token)
	{	
		//When # is found, it ignores whatever comes after
		//it and returns 1 to indicate the program to ask
		//the user for another input
		found = token.find("#");
		if(found != string::npos)
		{
			token = token.substr(0, found);
			//cout << "Comment token: " << token << endl;
			if(token.size() != 0)
			{
				stringList.push_back(token);
			}
			
			for(int a = 0; a < stringList.size(); a++)
			{
				myCmd[a] = stringList.at(a).c_str();	
			}
			myCmd[stringList.size()] = (const char*)NULL;
			if(stringList.size() != 0)
			{
				execvp(myCmd[0], (char* const*)myCmd);	
			}
			//return 1;
		}
		//if token found is "exit", return 1, ending the code
		//and telling the program to stop prompting the user
		else if(token == "exit")
		{
			//return 0;
			return 1;
		}
		//if token string is not empty (to avoid out of bounds
		//error), check the last char of it to look for the ; 
		//connector. If found, take out the semicolon, empty 
		//stringList into myCmd and execute. Afterwards, clear 
		//stringList and adding arguments to stringList. Both
		//branches of the fork: child and parent, are always
		//executed.
		else if(token.size() > 0 && token.at(token.length() - 1) == ';')
		{
			token.erase(token.end() - 1);
			stringList.push_back(token);
			for(int a = 0; a < stringList.size(); a++)
			{
				//testing output code below
				//cout << a << ":" << stringList.at(a) << endl;
				myCmd[a] = stringList.at(a).c_str();
			}
			
			//Puts NULL at end of array to stop reading
			myCmd[stringList.size()] = (const char*)NULL;
			//start fork process for ; here
			pid_t pid;
			int status;
			pid = fork();
			if(pid < 0)
			{
				perror("fork failed");
				exit(12);
			}
			else if(pid == 0)
			{
				execvp(myCmd[0], (char* const*)myCmd);
			}
			else if(pid > 0)
			{ 
				wait(&status);
				stringList.clear();
			}
		}
		//If the && token is found, execute what is read in so far 
		//reading what is in stringList, putting them into myCmd,
		//and execute the process in child. If child fails, exit
		//the child process and don't initiaite the parent process.
		//If child succeeds, continue to parent process.
		else if(token == "&&")
		{
			for(int a = 0; a < stringList.size(); a++)
			{	
				//cout << a << ":" << stringList.at(a) << endl;
				myCmd[a] = stringList.at(a).c_str();	
			}
			myCmd[stringList.size()] = (const char*)NULL;
			//fork process for && here
			pid_t pid;
			int status;
			pid = fork();
			if(pid < 0)
			{
				perror("fork failed");
				exit(12);
			}
			else if(pid == 0)	//child process
			{
				execvp(myCmd[0], (char* const*)myCmd);
				//if fork fails, exit child process
				perror("child error");
				sleep(1);
				exit(12);	
			}
			else if(pid > 0)	//parent process
			{
				wait(&status);	//wait for child to finish
				if(!WIFEXITED(status) || WEXITSTATUS(status) != 0)
				{
					exit(12);	
				}
				stringList.clear();	
			}	
		}
		//If || connector is found, do the usual load arguments
		//from stringList to myCmd, add NULL at the end, and
		//execute. No fork process used here because only 
		//continues when the first command succeeds. If execvp()
		//works, the program stops automatically. If fails, it 
		//continues reading.
		else if(token == "||")
		{
			for(int a = 0; a < stringList.size(); a++)
			{
				//cout << a << ":" << stringList.at(a) << endl;
				myCmd[a] = stringList.at(a).c_str();
			}
			myCmd[stringList.size()] = (const char*)NULL;
			//fork process for || here
			execvp(myCmd[0], (char* const*)myCmd);
			perror("error");
			stringList.clear();
		}
		//here is where token is continuously pushed into the token
		//until a connector, comment, or exit is detected.
		else
		{
			if(token.size() != 0)
			{
				stringList.push_back(token);
			}
		}
	}	                         	

	//loop for putting args into myCmd when connectors are not foundi.
	//Thw while loop naturally stops if there are no more strings to 
	//read from. So this code here executes whatever is left inside
	//stringList.
	for(int a = 0; a < stringList.size(); a++)
	{
		myCmd[a] = stringList.at(a).c_str();
	}
	myCmd[stringList.size()] = NULL;
	//printing loop for testing
	//cout << "Printing last part" << endl;
	//for(int j = 0; myCmd[j] != NULL; j++)
	//{
	//	cout << j << ":" << myCmd[j] << endl;
	//}
	
	//if nothing in stringList, don't try to execute
	if(stringList.size() != 0)
	{
		execvp((const char*)myCmd[0], (char* const*)myCmd);
	}
	
}

//This function repeats the myShell() using fork() because myShell()
//ends itself whenever execvp() runs correctly, so there must be 
//always a parent process with a myShell() waiting to prompt the user
//unless the child process returns a 0.
int shellFork()
{
	pid_t pid;
	int status;
	pid = fork();

	//checks if fork() works
	if(pid < 0)
	{
		perror("fork failed");
		exit(1);
	}
	//child process that prompts the user first
	//and sees if conditions are met to continue
	//prompting the user.
	else if(pid == 0)
	{
		//if returns 0, exit
		if(myShell() == 1)
		{
			exit(1);
		}
	}
	//Parent process that only executes if child process
	//did not exit. If so, it exits as well, ending the 
	//recurring fork call.
	else if(pid > 0)
	{
		wait(&status);	//wait for child to finish
		//check if child exited or not. If so, exit(1).
		if(!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		{
			exit(1);
		}
		//if child did not exit, use recurrence to
		//continue prompting the user.
		shellFork();
	}
	return 0;
}


int main()
{
	shellFork();
	return 0;
}

