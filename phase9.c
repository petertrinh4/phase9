
//Header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Macros for code readability
#define ZERO 0
#define ONE 1
#define TWO 2
#define FOURTEEN 14
#define NAME 20
#define PLAY 1
#define LEAD 2
#define EXIT 3
#define FALSE 0
#define TRUE 1
#define HAND 10
#define DECK 108
#define FOUR 4
#define EIGHT 8
#define TWELVE 12
#define WILD 13
#define SKIP 14

//Function prototypes
void welcomeScreen();
void playGame();
int displayMenu();
void displayLeaderboard();
void initializeDeck(int deck[DECK]);
void shuffleDeck(int deck[DECK]);
void displayDeck(int deck[DECK]);
void dealHand(int deck[DECK], int* deckIdx, int playerHand[HAND]);
void displayPlayerHand(char player[NAME], int playerHand[HAND]);
int dealDiscard(int deck[DECK], int* deckIdx);
void displayDiscard(int discard);
int comp(const void* a, const void* b);

//Main function
int main() {
    welcomeScreen(); //Write the function declaration or prototype for function welcomeScreen
    srand((unsigned int)time(NULL));
    playGame(); //Write the function declaration or prototype for function playGame
    return 0; //Returns zero to indicate successful operation of the program
}

//Welcome screen function
void welcomeScreen() {
    printf("XXXX    X  X      X      XXXX   XXXX    XXXX \n"); //Print the name of the game and the instructions as shown
    printf("X   X   X  X     X X    XX      X      X    X\n");
    printf("XXXX    XXXX    XX XX    XX     XXX     XXXX \n");
    printf("X       X  X    X   X      XX   X         X  \n");
    printf("X       X  X   X     X   XXXX   XXXX     X   \n");
    printf("\n");
    printf("=====>   PHASE 9 PHASES   <=====\n\n");
    printf("1. 2 sets of 3\n");
    printf("2. 1 set of 3 + 1 run of 4\n");
    printf("3. 1 set of 4 + 1 run of 4\n");
    printf("4. 1 run of 7\n");
    printf("5. 1 run of 8\n");
    printf("6. 1 run of 9\n");
    printf("7. 2 sets of 4\n");
    printf("8. 1 set of 5 + 1 set of 2\n");
    printf("9. 1 set of 5 + 1 set of 3\n");
}

//Play game function
void playGame() {
    char one[NAME]; //Stores player one's name
    char two[NAME]; //Stores player two's name
    int oneHand[HAND];
    int twoHand[HAND];
    int turn = ZERO;
    int deck[DECK];
    int deckIdx = ZERO;
    int currentPlayer = ONE;
    int choice = ZERO;
    choice = displayMenu();

    while(choice != EXIT) {
    if(choice == PLAY) {
        printf("\nPlayer One, enter your name: "); //Print statement to prompt player one to enter their name
        scanf("%s", one); //Scan statement to store player one’s name in variable one
        printf("Player Two, enter your name: "); //Print statement to prompt player two to enter their name
        scanf("%s", two); //Scan statement to store player two’s name in variable two
        printf("\n%s and %s let's play Phase 9!\n", one, two); //Print statement using the entered player names to play phase 9
        initializeDeck(deck);
        printf("\nUnshuffled deck of cards:\n");
        displayDeck(deck);
        printf("\n"); //Separates the deck of cards
        shuffleDeck(deck);
        printf("Shuffled deck of cards:\n");
        displayDeck(deck);
        dealHand(deck, &deckIdx, oneHand);
        qsort(oneHand, HAND, sizeof(oneHand[ZERO]), comp);
        dealHand(deck, &deckIdx, twoHand);
        qsort(twoHand, HAND, sizeof(twoHand[ZERO]), comp);
        int discard = dealDiscard(deck, &deckIdx);
        
        while(turn < TWO) {
        if(currentPlayer == ONE) {
            displayPlayerHand(one, oneHand);
            displayDiscard(discard);
            currentPlayer = TWO;
        }
        else if(currentPlayer == TWO) {
            displayPlayerHand(two, twoHand);
            displayDiscard(discard);
            currentPlayer = ONE;
        }
        turn++;
        }
    }
    else if(choice == LEAD) {
        displayLeaderboard();
    }
    else {
        printf("\nThank you for playing Phase 9!\n");
        exit(ZERO);
    }
    choice = displayMenu();
    deckIdx = ZERO;
    turn = ZERO;
    }
}

//Display menu function
int displayMenu() {
    int choice = ZERO;
    int valid = FALSE;
    while(!valid) {
    printf("\nSelect a menu option:\n");
    printf("1. Play Phase 9\n");
    printf("2. View Leaderboard\n");
    printf("3. Exit Game\n");
    scanf("%d", &choice);
    if(choice != PLAY && choice != LEAD && choice != EXIT) {
        valid = FALSE;
    }
    else {
        valid = TRUE;
    }
}
return choice;
}

//Initialize deck function
void initializeDeck(int deck[DECK]) {
int idx = ZERO; //Idx used to count cards in array 'deck'
for(int a = ZERO; a < EIGHT; a++) {
    for(int b = ONE; b <= TWELVE; b++) { //Adds in cards 1-12 w/ total of 96 cards
    deck[idx] = b;
    idx++;
    }
}
for(int c = ZERO; c < EIGHT; c++) { //Adds in 8 wild cards
    deck[idx] = WILD;
    idx++;
}
for(int d = ZERO; d < FOUR; d++) { //Adds 4 skip cards
    deck[idx] = SKIP;
    idx++;
}
}

//Shuffle deck function (Durstenfeld shuffle algorithm)
void shuffleDeck(int deck[DECK]) {
    for(int a = ZERO; a < DECK; a++) {
        int b = rand() % DECK;
        int card = deck[a];
        deck[a] = deck[b];
        deck[b] = card;
    }
}

//Display deck function
void displayDeck(int deck[DECK]) {
    for(int a = ZERO; a < DECK; a++) {
        printf("%d ", deck[a]);
    }
    printf("\n");
}

//Deal hand function
void dealHand(int deck[DECK], int *deckIdx, int playerHand[HAND]) {
    for(int a = ZERO; a < HAND; a++) {
        playerHand[a] = deck[*deckIdx];
        (*deckIdx)++;
    }
}

//Display player hand function
void displayPlayerHand(char player[NAME], int playerHand[HAND]) {
    printf("\n%s's hand:\n\n", player);
    printf("+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+\n");
    printf("|       |       |       |       |       |       |       |       |       |       |\n");
    printf("|");
    for(int a = ZERO; a < HAND; a++) {
        if(playerHand[a] == WILD) {
            printf("   W   |");
        }
        else if(playerHand[a] == SKIP) {
            printf("   S   |");
        }
        else {
            printf("  %3d  |", playerHand[a]);
        }
    }
    printf("\n|       |       |       |       |       |       |       |       |       |       |\n");
    printf("+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+\n");
}

//Deal discard function
int dealDiscard(int deck[DECK], int *deckIdx) {
    int discard = deck[*deckIdx];
    (*deckIdx)++;
    return discard;
}

//Display discard function
void displayDiscard(int discard) {
    printf("\nDiscard pile:\n\n");
    printf("+-------+\n");
    printf("|       |\n");
    printf("| %3d   |\n", discard);
    printf("|       |\n");
    printf("+-------+\n");
}

//Display leaderboard function
void displayLeaderboard() {
    printf("---------------------------------------\n");
    printf("           Phase 9 Leaderboard         \n");
    printf("---------------------------------------\n");
    printf("   Position      Player      Wins      \n");
    printf("   --------      ------      ----      \n");
    printf("       1          Peter       47       \n");
    printf("       2          Jackson     36       \n");
    printf("       3          Cindy       32       \n");
    printf("       4          Jake        28       \n");
    printf("       5          Lisa        25       \n");
    printf("       6          Tyler       17       \n");
    printf("       7          Manny       16       \n");
}

//Shuffle card function
int comp(const void *a, const void *b) {
return (*(int *)a - *(int *)b);
}
