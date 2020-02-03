#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/times.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>

//Project 4: A Shell
//CSC 352
//By: Matthew Yungbluth
//A custom shell with fuctionality for UNIX commands, exit, cd directory, 
//UNIX command > file to write to a file, 
//and UNIX command >> file to append to a file

clock_t start_time;
clock_t end_time;
struct tms start_cpu;
struct tms end_cpu;
int clock_start = 0;

void clock_print() {
    end_time = times(&end_cpu);
    //prints time elapsed
    printf("User Time: %jd, System Time: %jd\n",
    (intmax_t)(end_cpu.tms_utime - start_cpu.tms_utime),
    (intmax_t)(end_cpu.tms_stime - start_cpu.tms_stime));
}

void command_loop() {
    //loop of to handle every input entered by user
    int buff = 200;
    char inputString[buff];
    while (1) {
        char *token;
        if (clock_start == 0) {
	    //grabs input from the user only if there is no clock running
            fgets(inputString, 200, stdin);
        }
        char *curPos;
        if ((curPos = strchr(inputString, '\n')) != NULL) {
	    //replaces the newline enetered by the user to an end of string char
            *curPos = '\0';
        }
        if (strcmp(inputString, "exit") == 0) {
            //#1
            exit(0);
        }
        char copy[buff];
        strcpy(copy, inputString);
        char *eachCommand[buff];
        token = strtok(copy, " ()<>|&;");
        int i = 0;
        while (token != NULL) {
	    //the input string is tokenized and then put into eachCommand
            eachCommand[i] = token;
            i++;
            token = strtok(NULL, " ()<>|&;");
        }
        int commandLength = i;
        if (strcmp(eachCommand[0], "cd") == 0) {
            //#2
            int errorTest = chdir(eachCommand[1]);
            if (errorTest != 0) {
                printf("Error with cd command, invalid directory\n");
            }
            if (clock_start == 1) {
                clock_start = 0;
                clock_print();
            }
        } else if (strcmp(eachCommand[0], "time") != 0) {
	    //I found putting the time command at the end worked best, so this
	    //is the section for everything else that isn't the time command
            int numArrows = 0;
            int i = 0;
            for (i = 0; i < sizeof(inputString); i++) {
		//loop to find # of > in the inputString, to decide between
		//numbers 3, 5, and 6 from the program requirements
                if (inputString[i] == '>') {
                    numArrows++;
                }
            }
	    //set the index after the commands to be NULL for use in execvp
            eachCommand[commandLength] = NULL;
            //#3
            if (fork() == 0) {
                FILE *f;
                if (numArrows == 1) {
                    f = freopen(eachCommand[commandLength-1], "w", stdout);
		    eachCommand[commandLength-1] = NULL;
                } else if (numArrows == 2) {
                    f = freopen(eachCommand[commandLength-1], "a", stdout);
		    eachCommand[commandLength-1] = NULL;
                }
                int error_test = execvp(eachCommand[0], eachCommand);
		if (error_test == -1) {
		    printf("Error with UNIX command");
		}
                fclose(f);
                if(clock_start == 1) {
                    clock_start = 0;
                    clock_print();
                }
            } else {
                int status;
                wait(&status);
                if (clock_start == 1) {
                    clock_start = 0;
                    clock_print();
                }
            }
        } else {
            //#4
            start_time = times(&start_cpu);
            clock_start = 1;
            int i = 0;
            for (i = 0; i < sizeof(inputString)-5; i++) {
		//changes the input string to get rid of time , and then loops
		//through again with new inputString and clock_start set to 1
                inputString[i] = inputString[i+5];
            }
        }
        token = inputString;
    }
}

int main() {
    command_loop();
    return 0;
}
