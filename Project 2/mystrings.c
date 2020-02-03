#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//mystrings
//By: Matthew Yungbluth
//Class: CSC 352

int main(int argc, char *argv[]) {
    //argv[1] is the file name
    FILE *f = fopen(argv[1], "rb");
    char curByte[1];
    fseek(f, 0, SEEK_END);
    int lengthOfFile = ftell(f);
    fseek(f, -lengthOfFile, SEEK_CUR);
    char curString[lengthOfFile];
    int curStringIndex = 0;
    memset(curString, 0, lengthOfFile);
    //Clears the curString array
    for (int i = 0; i < lengthOfFile; i++) {
        //Goes through each byte of the file
        fread(curByte, 1, 1, f);
        if (curByte[0] >= 32 && curByte[0] <= 126) {
            //Adds the byte to the string if it is a valid character
            curString[curStringIndex] = curByte[0];
            curStringIndex += 1;
        } else {
            if (strlen(curString) >= 4){
                printf("%s\n", curString);
            }
            memset(curString, 0, lengthOfFile);
            curStringIndex = 0;
            //Clears and resets the curString array
        }
    }
    if (strlen(curString) >= 4) {
        //used if there is a string at the end of the file
        printf("%s\n", curString);
    }
    fclose(f);
}
