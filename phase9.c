
//Header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

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
#define LINE 100
#define FIELDS 3
#define DATA 45
#define DISCARD 1
#define DRAW 2
#define THREE 3
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define NINE 9
#define TEN 10
#define ELEVEN 11

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
void displaySingle(int discard);
int comp(const void* a, const void* b);
void readLeaderboardFile();
int playerOption(char player[NAME]);
int draw(int deck[DECK], int* deckIdx);
int discardCard(char player[NAME], char playerHand[HAND], int pickUp);
void updateHand(char player[NAME], char playerHand[HAND], int discardIdx, int* discard, int newCard);
char* trim(char* str);

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
    int discardOrDraw = ZERO; //Stores player's choice to pick up discard/draw from deck
    int pickUp = ZERO; //Stores the player's picked up card value(1-14)
    int playerDiscard = ZERO;

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
        //displayDeck(deck);
        printf("\n"); //Separates the deck of cards
        shuffleDeck(deck);
        printf("Shuffled deck of cards:\n");
        //displayDeck(deck);
        dealHand(deck, &deckIdx, oneHand);
        qsort(oneHand, HAND, sizeof(oneHand[ZERO]), comp); //Sort player 1's hand
        dealHand(deck, &deckIdx, twoHand);
        qsort(twoHand, HAND, sizeof(twoHand[ZERO]), comp); //Sort player 2's hand
        int discard = dealDiscard(deck, &deckIdx);
        
        while(turn < TWO) {
        if(currentPlayer == ONE) {
            displayPlayerHand(one, oneHand);
            displaySingle(discard);
            discardOrDraw = playerOption(one); 
            if(discardOrDraw == DISCARD) {
                printf("\nPlayer picked up the discard\n");
                pickUp = discard;
                printf("\nNew card\n");
                displaySingle(pickUp);
            }
            else if(discardOrDraw == DRAW) {
                printf("Player drew from the deck");
                pickUp = draw(deck, &deckIdx);
                printf("\nNew card\n");
                displaySingle(pickUp);
            }
            playerDiscard = discardCard(one, oneHand, pickUp);
            updateHand(one, oneHand, playerDiscard, &discard, pickUp);
            currentPlayer = TWO;
        }
        else if(currentPlayer == TWO) {
            displayPlayerHand(two, twoHand);
            displaySingle(discard);
            discardOrDraw = playerOption(two);
            if(discardOrDraw == DISCARD) {
                printf("\nPlayer picked up the discard\n");
                pickUp = discard;
                printf("\nNew card\n");
                displaySingle(pickUp);
            }
            else if(discardOrDraw == DRAW) {
                printf("Player drew from the deck");
                pickUp = draw(deck, &deckIdx);
                printf("\nNew card\n");
                displaySingle(pickUp);
            }
            playerDiscard = discardCard(two, twoHand, pickUp);
            updateHand(two, twoHand, playerDiscard, &discard, pickUp);
            currentPlayer = ONE;
        }
        turn++;
        }
    }
    else if(choice == LEAD) {
        readLeaderboardFile();
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

//Display single function
void displaySingle(int discard) {
    printf("\n+-------+\n");
    printf("|       |\n");

    if (discard == WILD) {
        printf("|  W    |\n"); // Display 'W' for WILD
    } 
    else if (discard == SKIP) {
        printf("|  S    |\n"); // Display 'S' for SKIP
    } 
    else {
        printf("|%3d    |\n", discard); // Display actual value
    }

    printf("|       |\n");
    printf("+-------+\n");
}

//Reads from leaderboard txt file
void readLeaderboardFile() {
    char line[LINE];
    int fieldIdx = ZERO;
    char* data[DATA];
    FILE* fp = fopen("leaderboard.txt", "r");
    printf("X      XXXX      X      XXXX    XXXX   XXXX    XXXX    XXXX      X      XXXX    XXXX\n"); //Prints the leaderboard header
    printf("X      X        X X     X   X   X      X   X   X   X   X  X     X X     X   X   X   X\n");
    printf("X      XXXX    XX XX    X   X   XXXX   XXXX    XXXX    X  X    XX XX    XXXX    X   X\n");
    printf("X      X       X   X    X   X   X      X  X    X   X   X  X    X   X    X  X    X   X\n");
    printf("XXXX   XXXX   X     X   XXXX    XXXX   X   X   XXXX    XXXX   X     X   X   X   XXXX\n");

    if(fp == NULL) {
        perror("Error opening file");
        return;
    }
    while(fgets != NULL) {
        fgets(line, LINE, fp);
        char* field = strtok(line, ",");
        field = trim(field);
        while(field != NULL) {
            data[fieldIdx] = malloc(strlen(field + 1));
            strcpy(data[fieldIdx], field);
            field = strtok(NULL, ",");
            field = trim(field);
            fieldIdx++;
        }
    }
    fclose(fp);
    for(int i = ZERO; i < DATA; i += FIELDS) {
        printf(data[i+1]);
    }
}

//
int playerOption(char player[NAME]){
}

//
int draw(int deck[DECK], int* deckIdx){
}

//
int discardCard(char player[NAME], char playerHand[HAND], int pickUp) {
}

//
void updateHand(char player[NAME], char playerHand[HAND], int discardIdx, int* discard, int newCard) {
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

//
char* trim(char* str) {
    if(str == NULL || *str == '\0') { //Checks if the string is empty
        return str;
    }
    char* start = str; //Trims leading white space
    while(isspace((unsigned char) * start)) {
        start++;
    }
    char* end = str + strlen(str) - 1; //Trims trailing white space
    while(end > start && isspace((unsigned char) * end)) {
        end--;
    }
    end[1] = '\0'; //Adds the null terminator
    return start; //Returns the updated string
}
