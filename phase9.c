
#include <stdio.h> //Header files
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define ZERO 0 //Macros for code readability
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
#define THIRTEEN 13

struct Player {
    int playerNum;
    char playerName[NAME];
    int playerHand[TEN];
    int currentPhase;
    int wins;
};

void welcomeScreen(); //Function prototypes
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
int discardCard(char player[NAME], int playerHand[HAND], int pickUp);
void updateHand(char player[NAME], int playerHand[HAND], int discardIdx, int* discard, int newCard);
char* trim(char* str);
int checkPhase(struct Player player);
int countRuns(int playerHand[HAND], int size, int runSize);
int countSets(int playerHand[HAND], int size, int setSize);
void updatePhase(struct Player* player);
void displayPhase(int currentPhase);

int main() { //Main function
    welcomeScreen(); //Write the function declaration or prototype for function welcomeScreen
    srand((unsigned int)time(NULL));
    playGame(); //Write the function declaration or prototype for function playGame
    return ZERO; //Returns zero to indicate successful operation of the program
}

void welcomeScreen() { //Welcome screen function
    printf("\n");
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

void playGame() { //Play game function
    struct Player one; //Stores player one's name
    struct Player two; //Stores player two's name
    //int oneHand[HAND];
    //int twoHand[HAND];
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
            scanf("%s", one.playerName); //Scan statement to store player one’s name in variable one
            one.playerNum = ONE;
            one.currentPhase = ONE;
            one.wins = ZERO;
            printf("Player Two, enter your name: "); //Print statement to prompt player two to enter their name
            scanf("%s", two.playerName); //Scan statement to store player two’s name in variable two
            two.playerNum = TWO;
            two.currentPhase = ONE;
            two.wins = ZERO;
            printf("\n%s and %s let's play Phase 9!", one.playerName, two.playerName); //Print statement using the entered player names to play phase 9
            initializeDeck(deck);
            printf("\n"); //Separates the deck of cards
            shuffleDeck(deck);
            dealHand(deck, &deckIdx, one.playerHand);
            qsort(one.playerHand, HAND, sizeof(one.playerHand[ZERO]), comp); //Sort player 1's hand
            dealHand(deck, &deckIdx, two.playerHand);
            qsort(two.playerHand, HAND, sizeof(two.playerHand[ZERO]), comp); //Sort player 2's hand
            int discard = dealDiscard(deck, &deckIdx);
            
            while(turn < FOUR) {
                if(currentPlayer == one.playerNum) {
                    displayPhase(one.currentPhase);
                    displayPlayerHand(one.playerName, one.playerHand);
                    printf("\nDiscard pile");
                    displaySingle(discard);
                    discardOrDraw = playerOption(one.playerName); 
                    if(discardOrDraw == DISCARD) {
                        printf("%s picked up the discard\n", one.playerName);
                        pickUp = discard;
                        printf("\nNew card");
                        displaySingle(pickUp);
                    }
                    else if(discardOrDraw == DRAW) {
                        printf("%s drew from the deck", one.playerName);
                        pickUp = draw(deck, &deckIdx);
                        printf("\n\nNew card");
                        displaySingle(pickUp);
                    }
                    playerDiscard = discardCard(one.playerName, one.playerHand, pickUp);
                    updateHand(one.playerName, one.playerHand, playerDiscard, &discard, pickUp);
                    if(checkPhase(one) == TRUE) {
                        printf("\n%s completed their phase!\n", one.playerName);
                        updatePhase(&one);
                    }
                    else {
                        printf("\n%s did not complete their phase\n", one.playerName);
                    }
                    currentPlayer = two.playerNum;
                }
                else if(currentPlayer == two.playerNum) {
                    displayPhase(two.currentPhase);
                    displayPlayerHand(two.playerName, two.playerHand);
                    printf("\nDiscard pile");
                    displaySingle(discard);
                    discardOrDraw = playerOption(two.playerName);

                    if(discardOrDraw == DISCARD) {
                        printf("%s picked up the discard\n", two.playerName);
                        pickUp = discard;
                        printf("\nNew card");
                        displaySingle(pickUp);
                    }
                    else if(discardOrDraw == DRAW) {
                        printf("%s drew from the deck", two.playerName);
                        pickUp = draw(deck, &deckIdx);
                        printf("\n\nNew card");
                        displaySingle(pickUp);
                    }
                    playerDiscard = discardCard(two.playerName, two.playerHand, pickUp);
                    updateHand(two.playerName, two.playerHand, playerDiscard, &discard, pickUp);
                    if(checkPhase(two) == TRUE) {
                        printf("\n%s completed their phase!\n", two.playerName);
                        updatePhase(&two);
                    }
                    else {
                        printf("\n%s did not complete the phase\n", two.playerName);
                    }
                    currentPlayer = one.playerNum;
                }
                turn++;
            }
        }
        else if(choice == LEAD) {
            readLeaderboardFile();
        }
        else {
            exit(ZERO);
        }
        choice = displayMenu();
        deckIdx = ZERO;
        turn = ZERO;
    }
}

int displayMenu() { //Display menu function
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

void initializeDeck(int deck[DECK]) { //Initialize deck function
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

void shuffleDeck(int deck[DECK]) { //Shuffle deck function (Durstenfeld shuffle algorithm)
    for(int a = ZERO; a < DECK; a++) {
        int b = rand() % DECK;
        int card = deck[a];
        deck[a] = deck[b];
        deck[b] = card;
    }
}

void displayDeck(int deck[DECK]) { //Display deck function
    for(int a = ZERO; a < DECK; a++) {
        printf("%d ", deck[a]);
    }
    printf("\n");
}

void dealHand(int deck[DECK], int *deckIdx, int playerHand[HAND]) { //Deal hand function
    for(int a = ZERO; a < HAND; a++) {
        playerHand[a] = deck[*deckIdx];
        (*deckIdx)++;
    }
}

void displayPlayerHand(char player[NAME], int playerHand[HAND]) { //Display player hand function
    printf("\n%s's hand:\n", player);
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

int dealDiscard(int deck[DECK], int *deckIdx) { //Deal discard function
    int discard = deck[*deckIdx];
    (*deckIdx)++;
    return discard;
}

void displaySingle(int discard) { //Display single function
    printf("\n+-------+\n");
    printf("|       |\n");

    if (discard == WILD) {
        printf("|  W    |\n"); // Display 'W' for WILD
    } 
    else if (discard == SKIP) {
        printf("|  S    |\n"); // Display 'S' for SKIP
    } 
    else {
        printf("| %3d   |\n", discard); // Display actual value
    }

    printf("|       |\n");
    printf("+-------+\n");
}

void readLeaderboardFile() { //Reads the leaderboard text file
    char line[LINE];
    int fieldIdx = ZERO;
    char* data[DATA];
    FILE* fp = fopen("leaderboard.txt", "r");
    printf("\n");
    printf("---------------------------------------\n");
    printf("           Phase 9 Leaderboard         \n");
    printf("---------------------------------------\n");
    printf("   Position      Player      Wins      \n");
    printf("   --------      ------     ------      \n");

    if(fp == NULL) {
        perror("Error opening file");
        return;
    }
    while(fgets(line, LINE, fp) != NULL) {
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
        printf("%9s %13s %8s\n", data[i], data[i + 1], data[i + 2]);
    }
}

int playerOption(char player[NAME]){ //Player option function
    int choice = ZERO;
    int valid = FALSE;
    while(valid == FALSE) {
        printf("\n%s, select an option:\n", player);
        printf("1. Pick up discard\n");
        printf("2. Draw from deck\n");
        scanf("%d", &choice);
        printf("\n");
        if(choice != DISCARD && choice != DRAW) {
            valid = FALSE;
        }
        else {
            valid = TRUE;
        }
    }
    return choice;
}

int draw(int deck[DECK], int* deckIdx){ //Draw function
    int card = deck[*deckIdx];
    (*deckIdx)++;
    return card;
}

int discardCard(char player[NAME], int playerHand[HAND], int pickUp) { //Discard card function
    int choice = ZERO;
    int valid = ZERO;
    displayPlayerHand(player, playerHand);
    printf("   (1)     (2)     (3)     (4)     (5)     (6)     (7)     (8)     (9)     (10)");
    displaySingle(pickUp);
    printf("  (11)\n");
    while(!valid) {
        printf("\nSelect which card to discard (1 - 11): ");
        scanf("%d", &choice);
        if(choice >= 1 && choice <= 11) {
            valid = TRUE;
        }
        else {
            valid = FALSE;
        }
    }
    return choice;
}

void updateHand(char player[NAME], int playerHand[HAND], int discardIdx, int* discard, int newCard) { //Update hand function
    if(discardIdx == ELEVEN) {
        printf("\n%s selected the drawn card to discard, hand does not change.\n", player);
        return;
    }
    else {
        int card = playerHand[discardIdx - ONE];
        playerHand[discardIdx - ONE] = newCard;
        //displayPlayerHand(player, playerHand);
        qsort(playerHand, HAND, sizeof(playerHand[ZERO]), comp);
        *discard = card;
        displayPlayerHand(player, playerHand);
        printf("\nDiscarded card");
        displaySingle(*discard);
    }
}

int checkPhase(struct Player player) { //Check phase function
    int sets = ZERO;
    int setsTwo = ZERO;
    int runs = ZERO;
    switch(player.currentPhase) {
        case ONE:
            sets = countSets(player.playerHand, HAND, THREE);
            return sets >= TWO;
            break;
        case TWO:
            sets = countSets(player.playerHand, HAND, THREE);
            runs = countRuns(player.playerHand, HAND, FOUR);
            return sets >= ONE && runs >= ONE;
            break;
        case THREE:
            sets = countSets(player.playerHand, HAND, FOUR);
            runs = countRuns(player.playerHand, HAND, FOUR);
            return sets >= ONE && runs >= ONE;
            break;
        case FOUR:
            runs = countRuns(player.playerHand, HAND, SEVEN);
            return runs >= ONE;
            break;
        case FIVE:
            runs = countRuns(player.playerHand, HAND, EIGHT);
            return runs >= ONE;
            break;
        case SIX:
            runs = countRuns(player.playerHand, HAND, NINE);
            return runs >= ONE;
            break;
        case SEVEN:
            sets = countSets(player.playerHand, HAND, FOUR);
            return sets >= TWO;
            break;
        case EIGHT:
            sets = countSets(player.playerHand, HAND, FIVE);
            setsTwo = countSets(player.playerHand, HAND, TWO);
            return sets >= ONE && setsTwo >= ONE;
            break;
        case NINE:
            sets = countSets(player.playerHand, HAND, FIVE);
            setsTwo = countSets(player.playerHand, HAND, THREE);
            return sets >= ONE && setsTwo >= ONE;
            break;
        default:
            return ZERO;
            break;
    }
}

int countSets(int playerHand[HAND], int size, int setSize) { //Count sets function
    int counts[THIRTEEN] = {ZERO};
    int setCount = ZERO;
    for(int i = ZERO; i < size; i++) {
        if(playerHand[i] >= ONE && playerHand[i] <= TWELVE) {
            counts[playerHand[i] - ONE]++;
        }
        for(int i = ZERO; i < THIRTEEN; i++) {
            if(counts[i] >= setSize) {
                setCount++;
            }
        }
    }
    return setCount;
}

int countRuns(int playerHand[HAND], int size, int runSize) { //Count run function
    int runs = ZERO;
    for(int i = ZERO; i < size; i++) {
        int currentRun = ONE;
        for(int j = i + ONE; j < size; j++) {
            if(playerHand[j] == playerHand[i] + currentRun) {
                currentRun++;
                if(currentRun == runSize) {
                    runs++;
                    break;
                }
            }
        }
    }
    return runs;
}

void updatePhase(struct Player* player) { //Update phase function
    if(player->currentPhase < NINE) {
        player->currentPhase++;
    }
}

void displayPhase(int currentPhase) { //Display phase function
    switch(currentPhase) {
        case ONE:
            printf("\nCurrent phase: 2 sets of 3\n");
            break;
        case TWO:
            printf("\nCurrent phase: 1 set of 3 + 1 run of 4\n");
            break;
        case THREE:
            printf("\nCurrent phase: 1 set of 4 + 1 run of 4\n");
            break;
        case FOUR:
            printf("\nCurrent phase: 1 run of 7\n");
            break;
        case FIVE:
            printf("\nCurrent phase: 1 run of 8\n");
            break;
        case SIX:
            printf("\nCurrent phase: 1 run of 9\n");
            break;
        case SEVEN:
            printf("\nCurrent phase: 2 sets of 4\n");
            break;
        case EIGHT:
            printf("\nCurrent phase: 1 set of 5 + 1 set of 2\n");
            break;
        case NINE:
            printf("\nCurrent phase: 1 set of 5 + 1 set of 3\n");
            break;
    }
}

void displayLeaderboard() { //Display leaderboard function
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

int comp(const void* a, const void* b) { //Shuffle card function
    return (*(int*)a - *(int*)b);
}

char* trim(char* str) { //Trims white space
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