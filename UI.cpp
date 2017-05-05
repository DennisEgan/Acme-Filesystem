#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

#define EXITTYPE "^D"
bool doNotExit=true;

// This function parses through the user input, which has already been checked to make sure run has been entered first before continuing
void parse(char *input, char **argv)
{
    // Stay in loop until iteration reaches the end character
    while (*input != '\0') {

        // Replace all spaces with 0s
        while (*input == ' ' || *input == '\t' || *input == '\n')
            *input++ = '\0';
        // Save the location for the argument
        *argv++ = input;

        // Keep looping until the end to make sure every character was read
        while (*input != '\0' && *input != ' ' && 
               *input != '\t' && *input != '\n') 
            input++;
    }

    // Place an end character for the end of the argument
    *argv = '\0';
}

void directory() {
    cout << "\tATOS-FS Directory Listing\n";
    cout << "\tFILENAME\t\tSIZE (blks)\n";
    cout << "\t"/*filename*/ "\t\n"/*size_of_file*/;
    cout << "\tFREESPACE 0 blks\n";    
}

void createFile(char **argv) {
    
}

void typeFile(char **argv) {
    
}

// This function is responsible for executing the commands given through the user input. It creates a child process to handle the system calls while the main program runs
void execute(char **argv)
{
    pid_t pid;
    int status;

    // Creates a child process
    if ((pid = fork()) < 0) {
        exit(1);
    }

    // The child process will be responsible for executing the command
    else if (pid == 0) {
        if (execvp(*argv, argv) < 0) {
            exit(1);
        }
    }

    // Parent waits for child to finish
    else {
        while (wait(&status) != pid);
    }
}

int main()
{
    string input; 
    char *in;
    char *argv[64];

    // Loop until the user inputs 'exit'
    while (1) {
        printf("$$ ");

        // Read in user input as a string to search for 'run'
        getline(cin, input);
	
	    // Check to see if there was no input
        while (input.empty()) {
	    printf("$$ ");
            getline(cin, input);
        }

        // Convert to char * by dynamically allocating memory
        in = (char *)malloc(input.size()+1);
        memcpy(in, input.c_str(), input.size()+1);

        // Begin the parsing function to break down input
        parse(in, argv);

        // Exit if user input is 'exit'
        if (strcmp(argv[0], "EXIT") == 0)
            exit(0);

        // If user input valid, will execute system calls
        else if (strcmp(argv[0], "CREATE") == 0) {

        // Deletes 'run' from the array and shifts all elements to the left
//	    memmove(argv-1, argv, (sizeof(char)*(62)));
            createFile(argv);
        }
	else if (strcmp(argv[0], "TYPE") == 0)
	    typeFile(argv);
	else if (strcmp(argv[0], "DIR") == 0)
	    directory();
    }

    // Release memory
//    free(in);
//
//    return 0;
}
