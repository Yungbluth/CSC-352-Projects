#include <stdio.h>
//Blackjack
//By: Matthew Yungbluth
//Class: CSC 352
int dealerPrint(int dealerFirst, int dealerSecond, int dealerShow) {
    if (!dealerShow) {
        printf("The dealer:\n? + %d", dealerSecond);
    } else {
        printf("\nThe dealer:\n%d + %d = %d", dealerFirst, dealerSecond, (dealerFirst + dealerSecond));
        if ((dealerFirst + dealerSecond) > 21) {
            printf(" BUSTED!\n\n Dealer busted. You win!");
        }
    }
    return dealerFirst;
}

int playerPrint(int playerFirst, int playerSecond) {
    int hit = 0;
    char input[5];
    printf("\n\nYou:\n%d + %d = %d\n\n", playerFirst, playerSecond, (playerFirst+playerSecond));
    if (playerFirst + playerSecond > 21) {
        printf("BUSTED!\n\nYou busted. Dealer wins.");
        return hit;
    }
    printf("Would you like to \"hit\" or \"stand\"? ");
    scanf("%s",input);
    if (input[0] == 'h') {
        hit = 1;
        int total = playerFirst + playerSecond;
        playerFirst = total;
    }
    return hit;
}

int main() {
    //4 of 2,3,4,5,6,7,8,9,10, jack, queen, king, ace
    int cards[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};
    srand((unsigned int)time(NULL));
    int dealerFirst = cards[(rand() % 14)];
    int dealerSecond = cards[(rand() % 14)];
    int playerFirst = cards[(rand() % 14)];
    int playerSecond = cards[(rand() % 14)];
    int dealer[2];
    int player[3];
    int hit = 1;
    while (hit) {
        //Each hit from player goes through this loop
        dealerPrint(dealerFirst, dealerSecond, 0);
        hit = playerPrint(playerFirst, playerSecond);
        if (playerFirst + playerSecond > 21 && playerSecond == 11) {
            playerSecond = 1;
        }
        int total = playerFirst + playerSecond;
        playerFirst = total;
        playerSecond = cards[(rand() % 14)];

    }
    //Player is done hitting
    if (playerFirst < 21) {
        while (dealerFirst < 17){
            if (dealerFirst + dealerSecond > 21 && dealerSecond == 11) {
                dealerSecond = 1;
            }
            dealerPrint(dealerFirst, dealerSecond, 1);
            int total = dealerFirst + dealerSecond;
            dealerFirst = total;
            dealerSecond = cards[(rand() % 14)];
        }
        if (dealerFirst <= 21 && dealerFirst < playerFirst) {
            printf("\nYou win!");
        } else if (dealerFirst <= 21 && dealerFirst > playerFirst) {
            printf("\nDealer wins.");
        } else if (dealerFirst == playerFirst) {
            printf("\nYou tie!");
        }
    }
    
    return 0;
}
