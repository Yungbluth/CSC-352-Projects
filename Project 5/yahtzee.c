#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//By: Matthew Yungbluth
//CSC 352
//Project 5, /dev/dic and Yahtzee
char* ONE = " ";
char* TWO = " ";
char* THREE = " ";
char* FOUR = " ";
char* FIVE = " ";
char* SIX = " ";
char* THREE_KIND = " ";
char* FOUR_KIND = " ";
char* SMALL = " ";
char* LARGE = " ";
char* FULL = " ";
char* YAH = " ";
char* CHANCE = " ";
int TOTAL = 0;
int UPPER_TOTAL = 0;
int UPPER_FLAG = 0;
int ROUND_NUM = 1;

void round() {
    //One full round of yahtzee, calls itself until ROUND_NUM becomes 13
    FILE * dice_driver;
    dice_driver = fopen("/dev/dice", "r");
    int response[5];
    int * dice = (int *)malloc(5*sizeof(int));
    char roller[5];
    //Roller is temp rolls given by driver, changed to int and given to dice
    fread(roller, 1, 5, dice_driver);
    int i;
    for (i = 0; i < 5; i++) {
        dice[i] = (int)roller[i];
    }
    int rolls = 1;
    printf("Your roll:\n\n");
        for (i = 0; i < 5; i++) {
            printf("%d ", dice[i]);
        }
        for (i = 0; i < 5; i++) {
            response[i] = -1;
        }
        char input[40];
    while (rolls < 3) {
        //Only allows 2 rerolls, 3 rolls in total
        printf("\n\nWhich dice to reroll? ");
        fgets(input, 40, stdin);
        char* response_array = strtok(input, "\n");
        response_array = strtok(input, " ");
        i = 0;
        if (response_array == NULL) {
            //shouldn't hit this
            break;
        }
        int flag = 0;
        while (response_array != NULL) {
            if (atoi(response_array) == 0) {
                flag = 1;
                //break and go on with program when user finalizes rolls with entering 0
                break;}
            response[i] = atoi(response_array);
            response_array = strtok(NULL, " ");
            i++;
        }
        if (flag) break; 
	    char roll[5];
	    fread(roll, 1, 5, dice_driver);
        for (i = 0; i < 5; i ++) {
            //gets another random number for each requested
	        dice[response[i] - 1] = (int)roll[i];
        }
        printf("Your roll:\n\n");
        for (i = 0; i < 5; i++) {
            printf("%d ", dice[i]);
        }
        for (i = 0; i < 5; i++) {
            response[i] = -1;
            //resets the response, so it doesn't carry over for next reroll
        }
        rolls++;
    }
    char selection[2];
    int inputFlagOne = 0;
    //inputFlag to make sure user enters either a 1 or a 2
    while (!inputFlagOne){
        printf("\n\nPlace dice into:\n1) Upper Section\n2) Lower Section\n\nSelection? ");
        fgets(selection, 2, stdin);
        if (selection[0] == '1') {
            if (strcmp(ONE, " ") != 0 && strcmp(TWO, " ") != 0 && strcmp(THREE, " ") != 0 && strcmp(FOUR, " ") != 0 && strcmp(FIVE, " ") != 0 && strcmp(SIX, " ") != 0) {
                printf("\nAll upper section already assigned, please try again\n");
            } else {
                inputFlagOne = 1;
            }
        }
        if (selection[0] == '2') {
            if (strcmp(THREE_KIND, " ") != 0 && strcmp(FOUR_KIND, " ") != 0 && strcmp(SMALL, " ") != 0 && strcmp(LARGE, " ") != 0 && strcmp(FULL, " ") != 0 && strcmp(YAH, " ") != 0 && strcmp(CHANCE, " ") != 0) {
                printf("\nAll lower section already assigned, please try again\n");
            } else {
                inputFlagOne = 1;
            }
        }
    }
    int toAdd = 0;
    char category;
    char selectionTwo[2];
    if (selection[0] == '1') {
        int switchFlag = 0;
        //switch flag to make sure user enters a valid input
        //By default all categories are " ", they are then assigned a number when the user selects them
        //therefore if the category " " it is open to be selected
        while (!switchFlag) {
            printf("\n\nPlace dice into:\n1) Ones\n2) Twos\n3) Threes\n4) Fours\n5) Fives\n6) Sixes\n\nSelection? ");
            int ch = getchar();
            while (ch != '\n' && ch != EOF);
            fgets(selectionTwo, 2, stdin);
            switch(selectionTwo[0]) {
                //simple addition for all upper section, added to toAdd
                case '1': 
                    if (ONE == " ") {
                        category = '1';
                        for (i = 0; i < 5; i++) {
                            if (dice[i] == 1) {
                                toAdd += 1;
                            }
                        }
                        switchFlag = 1;
                    } else {
                        printf("\nOne previously assigned, try again\n");
                    }
                    break;
                case '2':
                    if (TWO == " ") {
                        category = '2';
                        for (i = 0; i < 5; i++) {
                            if (dice[i] == 2) {
                                toAdd += 2;
                            }
                        }
                        switchFlag = 1;
                    } else {
                        printf("\nTwo previously assigned, try again\n");
                    }
                    break;
                case '3':
                    if (THREE == " ") {
                        category = '3';
                        for (i = 0; i < 5; i++) {
                            if (dice[i] == 3) {
                                toAdd += 3;
                            }
                        }
                        switchFlag = 1;
                    } else {
                        printf("\nThree previously assigned, try again\n");
                    }
                    break;
                case '4':
                    if (FOUR == " ") {
                        category = '4';
                        for (i = 0; i < 5; i++) {
                            if (dice[i] == 4) {
                                toAdd += 4;
                            }
                        }
                        switchFlag = 1;
                    } else {
                        printf("\nFour previously assigned, try again\n");
                    }
                    break;
                case '5': 
                    if (FIVE == " ") {
                        category = '5';
                        for (i = 0; i < 5; i++) {
                            if (dice[i] == 5) {
                                toAdd += 5;
                            }
                        }
                        switchFlag = 1;
                    } else {
                        printf("\nFive previously assigned, try again\n");
                    }
                    break;
                case '6': 
                    if (SIX == " ") {
                        category = '6';
                        for (i = 0; i < 5; i++) {
                            if (dice[i] == 6) {
                                toAdd += 6;
                            }
                        }
                        switchFlag = 1;
                    } else {
                        printf("\nSix previously assigned, try again\n");
                    }
                    break;
                default: printf("Error in selection, %c", selection[0]);
            }
        }
        sum_of_scores(toAdd, category);
    } else if (selection[0] == '2') {
        //Lower section a bit more complex than upper section
        int switchFlag = 0;
        while (!switchFlag) {
        printf("\n\nPlace dice into:\n1) Three of a Kind\n2) Four of a Kind\n3) Full House\n4) Small Straight\n5) Large Straight\n6) Yahtzee\n7) Chance\n\nSelection? ");
        int ch = getchar();
        while (ch != '\n' && ch != EOF);
        fgets(selectionTwo, 2, stdin);
        switch (selectionTwo[0]) {
            case '1':
                //7, three of a kind
                if (THREE_KIND == " ") {
                    for (i = 0; i < 3; i++) {
                        int j;
                        int counter = 0;
                        for (j = 0; j < 5; j++) {
                            if (dice[i] == dice[j]) {
                                counter += 1;
                            }
                        }
                        int total_dice = 0;
                        if (counter >= 3) {
                            //if user does have a three of a kind:
                            for (j = 0; j < 5; j++) {
                                total_dice += dice[j];
                            }
                        }
                        toAdd += total_dice;
                    }
                    category = '7';
                    switchFlag = 1;
                } else {
                    printf("\nThree of a kind previously assigned, try again\n");
                }
                break;
            case '2':
                //8, four of a kind
                if (FOUR_KIND == " ") {
                    for (i = 0; i < 2; i++) {
                        int j;
                        int counter = 0;
                        for (j = 0; j < 5; j++) {
                            if (dice[i] == dice[j]) {
                                counter += 1;
                            }
                        }
                        int total_dice = 0;
                        if (counter >= 4) {
                            //if user does have a four of a kind
                            for (j = 0; j < 5; j++) {
                                total_dice += dice[j];
                            }
                        }
                        toAdd += total_dice;
                    }
                    category = '8';
                    switchFlag = 1;
                } else {
                    printf("\nFour of a kind previous assigned, try again\n");
                }
                break;
            case '3':
                //F, full house
                if (FULL == " ") {
                    int twoFlag = 0;
                    int threeFlag = 0;
                    for (i = 0; i < 4; i++) {
                        int j;
                        int count = 0;
                        for (j = 0; j < 5; j++) {
                            if (dice[i] == dice[j]) {
                                count += 1;
                            }
                        }
                        if (count == 3) {
                            threeFlag = 1;
                        } else if (count == 2) {
                            twoFlag = 1;
                        }
                    }
                    if (twoFlag && threeFlag) {
                        //if user has both a pair and a three of a kind (full house):
                        toAdd += 25;
                    }
                    switchFlag = 1;
                    category = 'F';
                } else {
                    printf("\nFull house previously assigned, try again\n");
                }
                break;
            case '4':
                //S, small straight 4 in a row
                if (SMALL == " ") {
                    //straight is found by finding the two lowest numbers, and checking both to see
                    //if either of them have a number that is +1, +2, and +3 of it, making a straight
                    int straight = 0;
                    int lowRange[2] = {7, 7};
                    for (i = 0; i < 5; i++) {
                        //lowRangeOne or lowRangeTwo will be the lowest number of small straight
                        if (dice[i] < lowRange[0]) {
                            lowRange[0] = dice[i];
                        }
                        if (dice[i] < lowRange[1] && dice[i] > lowRange[0]) {
                            lowRange[1] = dice[i];
                        }
                    }
                    int j;
                    for (i = 0; i < 2; i++) {
                        //two times for both low ranges
                        int oneFlag = 0;
                        int twoFlag = 0;
                        int threeFlag = 0;
                        for (j = 0; j < 5; j++) {
                            if (dice[j] == lowRange[i] + 1) {
                                oneFlag = 1;
                            } else if (dice[j] == lowRange[i] + 2) {
                                twoFlag = 1;
                            } else if (dice[j] == lowRange[i] + 3) {
                                threeFlag = 1;
                            }
                        }
                        if (oneFlag && twoFlag && threeFlag) {
                            straight = 1;
                        }
                    }
                    if (straight) {
                        //if user does have a straight
                        toAdd += 30;
                    }
                    switchFlag = 1;
                    category = 'S';
                } else {
                    printf("\nSmall straight previously assigned, try again\n");
                }
                break;
            case '5':
                //L, large straight 5 in a row
                if (LARGE == " ") {
                    //large straight is easier to find because only have 1 lowest number,
                    //found similarly to low straight
                    int lowRange = 7;
                    int oneFlag = 0;
                    int twoFlag = 0;
                    int threeFlag = 0;
                    int fourFlag = 0;
                    for (i = 0; i < 5; i++) {
                        if (dice[i] < lowRange) {
                            lowRange = dice[i];
                        }
                    }
                    int j;
                    for (j = 0; j < 5; j++) {
                        if (dice[j] == lowRange + 1) {
                            oneFlag = 1;
                        } else if (dice[j] == lowRange + 2) {
                            twoFlag = 1;
                        } else if (dice[j] == lowRange + 3) {
                            threeFlag = 1;
                        } else if (dice[j] == lowRange + 4) {
                            fourFlag = 1;
                        }
                    }
                    if (oneFlag && twoFlag && threeFlag && fourFlag) {
                        //if user has a large straight:
                        toAdd += 40;
                    }
                    switchFlag = 1;
                    category = 'L';
                } else {
                    printf("\nLarge straight previously assigned, try again\n");
                }
                break;
            case '6':
                //Y, yahtzee
                if (YAH == " ") {
                    //easy to find, get value of first dice and make sure all other dice are equal
                    int num = dice[0];
                    int counter = 0;
                    for (i = 0; i < 5; i++) {
                        if (num == dice[i]) {
                            counter += 1;
                        }
                    }
                    if (counter == 5) {
                        //If user does have a yahtzee
                        toAdd += 50;
                    }
                    switchFlag = 1;
                    category = 'Y';
                } else {
                    printf("\nYahtzee previously assigned, try again\n");
                }
                break;
            case '7':
                //C, chance
                if (CHANCE == " ") {
                    int totalSum = 0;
                    for (i = 0; i < 5; i++) {
                        totalSum += dice[i];
                    }
                    toAdd += totalSum;
                    switchFlag = 1;
                    category = 'C';
                } else {
                    printf("\nChance previously assigned, try again\n");
                }
                break;
            default: printf("Error in selection");
        }
    }
    sum_of_scores(toAdd, category);
}
}

void sum_of_scores(int toAdd, char category) {
    //changes category to equal toAdd, and then prints off the new totals to screen
    switch(category) {
        case '1':
            if (strcmp(ONE, " ") == 0) {
                char buffer[100];
                sprintf(buffer, "%d", toAdd);
                ONE = buffer;
                TOTAL += toAdd;
                UPPER_TOTAL += toAdd;
            }
            break;
        case '2':
            if (strcmp(TWO, " ") == 0) {
                char buffer[100];
                sprintf(buffer, "%d", toAdd);
                TWO = buffer;
                TOTAL += toAdd;
                UPPER_TOTAL += toAdd;
            }
            break;
        case '3':
            if (strcmp(THREE, " ") == 0) {
                char buffer[100];
                sprintf(buffer, "%d", toAdd);
                THREE = buffer;
                TOTAL += toAdd;
                UPPER_TOTAL += toAdd;
            }
            break;
        case '4':
            if (strcmp(FOUR, " ") == 0) {
                char buffer[100];
                sprintf(buffer, "%d", toAdd);
                FOUR = buffer;
                TOTAL += toAdd;
                UPPER_TOTAL += toAdd;
            }
            break;
        case '5':
            if (strcmp(FIVE, " ") == 0) {
                char buffer[100];
                sprintf(buffer, "%d", toAdd);
                FIVE = buffer;
                TOTAL += toAdd;
                UPPER_TOTAL += toAdd;
            }
            break;
        case '6':
            if (strcmp(SIX, " ") == 0) {
                char buffer[100];
                sprintf(buffer, "%d", toAdd);
                SIX = buffer;
                TOTAL += toAdd;
                UPPER_TOTAL += toAdd;
            }
            break;
        case '7':
            if (strcmp(THREE_KIND, " ") == 0) {
                char buffer[100];
                sprintf(buffer, "%d", toAdd);
                THREE_KIND = buffer;
                TOTAL += toAdd;
            }
            break;
        case '8':
            if (strcmp(FOUR_KIND, " ") == 0) {
                char buffer[100];
                sprintf(buffer, "%d", toAdd);
                FOUR_KIND = buffer;
                TOTAL += toAdd;
            }
            break;
        case 'F':
            if (strcmp(FULL, " ") == 0) {
                char buffer[100];
                sprintf(buffer, "%d", toAdd);
                FULL = buffer;
                TOTAL += toAdd;
            }
            break;
        case 'S':
            if (strcmp(SMALL, " ") == 0) {
                char buffer[100];
                sprintf(buffer, "%d", toAdd);
                SMALL = buffer;
                TOTAL += toAdd;
            }
            break;
        case 'L':
            if (strcmp(LARGE, " ") == 0) {
                char buffer[100];
                sprintf(buffer, "%d", toAdd);
                LARGE = buffer;
                TOTAL += toAdd;
            }
            break;
        case 'Y':
            if (strcmp(YAH, " ") == 0) {
                char buffer[100];
                sprintf(buffer, "%d", toAdd);
                YAH = buffer;
                TOTAL += toAdd;
            }
            break;
        case 'C':
            if (strcmp(CHANCE," ") == 0) {
                char buffer[100];
                sprintf(buffer, "%d", toAdd);
                CHANCE = buffer;
                TOTAL += toAdd;
            }
            break;
        default: printf("something went wrong D:");
    }
    printf("\n\nYour score so far is: %d", TOTAL);
    int upper = 0;
    if (UPPER_TOTAL >= 63) {
        upper = 35;
        if (!UPPER_FLAG) {
            TOTAL += 35;
        }
        UPPER_FLAG = 1;
    }
    printf("\n\nOnes: %s\tFours: %s\nTwos: %s\tFives: %s\nThrees: %s\tSixes: %s\nUpper Section Bonus: %d\n", ONE, TWO, THREE, FOUR, FIVE, SIX, upper);
    printf("Three of a kind: %s\tFour of a kind: %s\nSmall Straight: %s\tLarge Straight: %s\nFull House: %s\tYahtzee: %s\nChance: %s\n", THREE_KIND, FOUR_KIND, SMALL, LARGE, FULL, YAH, CHANCE);
    if (ROUND_NUM < 13) {
        //Don't continue after 13 rounds
        ROUND_NUM++;
        int ch = getchar();
        while (ch != '\n' && ch != EOF);
        round();
    } else {
        printf("Game is Over!\nFinal Score: %d", TOTAL);
    }
}
int main() {
    round();
}
