
#include <stdio.h> /*Write the preprocessor command to include the stdio.h header
file from the C library*/

void welcomeScreen();
void playGame();
void displayHand();
void displayDiscard();

int main() /* Write function to return type int*/
{
    welcomeScreen(); /*Write the function declaration or prototype for function
welcomeScreen*/

    playGame(); /*Write the function declaration or prototype for function
playGame*/

    displayHand(); /*Write the function declaration or prototype for function
displayHand*/

    displayDiscard(); /*Write the function declaration or prototype for function
displayDiscard*/

    return 0; /*Returns 0 to indicate successful operation of the program*/
}

void welcomeScreen() /*Call function welcomeScreen*/
{
    printf("XXXX    X  X      X      XXXX   XXXX    XXXX \n"); /*printf the name of the game and the instructions as shown*/
    printf("X   X   X  X     X X    XX      X      X    X\n");
    printf("XXXX    XXXX    XX XX    XX     XXX     XXXX \n");
    printf("X       X  X    X   X       XX  X         X  \n");
    printf("X       X  X   X    X    XXXX   XXXX    XX   \n");
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

void playGame() /*Call function playGame*/
{
    char one[20]; /*used to store the player’s name that will be Player One*/
    char two[20]; /*used to store the player’s name that will be Player Two*/

    printf("\nPlayer One, enter your name: "); /*Write a printf statement to prompt Player One to enter
their name*/
    scanf("%s", one); /*Write a scanf statement to store Player One’s name in
variable one*/

    printf("Player Two, enter your name: "); /*Write a printf statement to prompt Player Two to enter
their name*/
    scanf("%s", two); /*Write a scanf statement to store Player Two’s name in
variable two*/
    printf("\n%s and %s let's play Phase 9!\n", one, two); /*Write a printf statement using the entered player names to
play Phase 9*/
}

void displayHand() /*Call function displayHand*/
{
    printf("\nPlayer's hand\n\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|     |     |     |     |     |     |     |     |     |     |\n");
    printf("|  2  |  2  |  4  |  4  |  5  |  7  |  8  |  8  |  9  |  9  |\n");
    printf("|     |     |     |     |     |     |     |     |     |     |\n");
    printf("+-----------------------------------------------------------+\n");
    /*printf hardcoded values for 10 cards to displayHand function output*/
}

void displayDiscard() /*Call function displayDiscard*/
{
    printf("\nDiscard pile\n\n");
    printf("+------+\n");
    printf("|      |\n");
    printf("|  12  |\n");
    printf("|      |\n");
    printf("+------+\n");
    /*Output to the screen by using a series of calls to function
printf a hardcoded value for the discard Figure 6
displayDiscard function output*/
}