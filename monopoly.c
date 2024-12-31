/* Description : This program is menu-driven simplified monopoly game, instead of 40 spaces and 28 properties,
                this game has 10 positions; 7  purchasable properties, jailtime,  feelin; lucky
                and the start position. Two players take alternating turns in rolling the dice to determine what
                position they are in the board, they are allowed to buy properties or resell them when players
                can no longer pay rent. Ownership details are shown through a 9-digit integer, the leftmost being
                the 9th position and the rightmost being the 1st position.
                The program determines the winner when one player goes bankrupt or when game end conditions are met
                but once the game ends, the menu option will be shown again to the players.

    Programmed by: Gabrielle Tongol
    Last Modified: February 6,2022
    Version: v 1.0
    Acknowledgements: https://devdocs.io/c/
                    https://stackoverflow.com/
 */

// Project done!! already revised after the project
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void displayDivider()
{
    int j;

    for (j = 1; j <= 88; j++)
    {
        if (j == 1)
            printf("\n");

        printf("*");

        if (j == 88)
            printf("\n");
    }
}
void displayBoard()
{

    printf("----------------------------------------------------------------------------------------\n");
    printf("||       0       |        1        |       2        |       3        |        4       ||\n");
    printf("||       Go      |    Tree House   |  Electric Co.  |   Beach House  |    Jail Time   ||\n");
    printf("|| Collect $200  |    COST: $20    |   COST: $150   |    COST: $60   | Lose next turn ||\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("||       9       |        8        |       7        |       6        |        5       ||\n");
    printf("||  Farm House   |      Igloo      |    Rail Road   |  Feelin' Lucky |      Castle    ||\n");
    printf("||   COST: $40   |    COST: $20    |    COST: $100  | Roll to Collect|   COST: $100   ||\n");
    printf("----------------------------------------------------------------------------------------\n");
}
/*
Description: This function gets random values from the two dice
Precondition: none
Return: returns the sum of two dice
*/
int simulateDice()
{
    int nDice1;
    int nDice2;
    int nSum;
    srand(time(NULL));
    nDice1 = (rand() % 7);
    nDice2 = (rand() % 7);
    nSum = nDice1 + nDice2;
    return nSum;
}
/*
Description: This function determines the position of the player
Precondition: position of the player is non-negative
                @nPlayerPos  initial value is 0
Return: returns the sum of two dice
*/
int getboardPosition(int nPlayerPos)
{
    return nPlayerPos + simulateDice() % 10;
}
/*
Description: This function displays/prints the statement whenever a player
            lands on a position.
Precondition: position of the player is non-negative
                @nPlayerPos  checks the position of the player.
                Initial value is 0
Return: print statement
*/
void displayPosition(int nPlayerPos)
{
    switch (nPlayerPos)
    {
    case 0:
        printf("You are at Position %d: Start\n", nPlayerPos);
        break;
    case 1:
        printf("You are at Position %d: Tree House\n", nPlayerPos);
        break;
    case 2:
        printf("You are at Position %d: Electric Company\n", nPlayerPos);
        break;
    case 3:
        printf("You are at Position %d: Beach House\n", nPlayerPos);
        break;
    case 4:
        printf("You are at Position %d: Jail Time\n", nPlayerPos);
        break;
    case 5:
        printf("You are at Position %d: Castle\n", nPlayerPos);
        break;
    case 6:
        printf("You are at Position %d: Feelin' Lucky\n", nPlayerPos);
        break;
    case 7:
        printf("You are at Position %d: RailRoad\n", nPlayerPos);
        break;
    case 8:
        printf("You are at Position %d: Igloo\n", nPlayerPos);
        break;
    case 9:
        printf("You are at Position %d: Farm House\n", nPlayerPos);
        break;
    }
}
/*
Description: This function includes money denominations and buying of properties which will be subtracted to the current balance of the player.
            This also includes the conditions for the GO and FEELIN' LUCKY position which will both add amount into the player’s balance.
Precondition: position of the player and playermoney is non-negative
                @nPlayerPos  checks the position of the player, initial value is 0
                @fPlayerMoney  represents the money value of both players,
                initial value is 200
Return: money balance of the player
*/
float theBank(float fPlayerMoney, int nPlayerPos)
{
    int n500 = 500; // money denominations
    int n200 = 200;
    int n150 = 150;
    int n100 = 100;
    int n50 = 50;
    int n20 = 20;
    int n10 = 10;
    int n5 = 5;
    int n1 = 1;

    switch (nPlayerPos)
    {
        // GO
    case 0:
        return fPlayerMoney += 200;
        // Feelin' Lucky
    case 6:
        if (simulateDice() % 2 != 0 || simulateDice() == 2) // prime
        {
            srand(time(NULL));
            return rand() % (n200 - n100 + 1) + n100;
        }
        else if (simulateDice() % 2 == 0) // even
        {
            srand(time(NULL));
            return rand() % (n150 - n50 + 1) + n50;
        }
    case 1:
    case 3:
    case 5:
    case 8:
    case 9:
        return nPlayerPos % 7 * n20;
    case 2:
        return n150;
    case 7:
        return n100;
    }
}
/*
Description: this function computes for divisor which will be later on used for the digit checker function
Precondition: @nPlayerPos values ranges from 1-9
Return: divisor, values can range from 1 - 100000000
*/
int getDiv(int nPlayerPos)
{
    int nDiv = 1;
    int j;

    for (j = 0; j < nPlayerPos - 1; j++)
    {
        nDiv *= 10;
    }
    return nDiv;
}
/*
Description: This function will be used in order to determine the values in the digit places
            in the tracker. This uses the functions: getDiv and getMod
Precondition: @nTracker should be non-negative, digit places in the tracker should
                only include 0, 1, 2, 3 and 4
                @nPlayerPos should be non negative, numbers: 1-9
Return: should only return a one digit integer, numbers: 0-4 only
*/
int digitChecker(int nPlayerPos, int nTracker)
{
    int nDiv = getDiv(nPlayerPos);
    int nMod = nDiv * 10;

    nTracker %= nMod;
    nTracker /= nDiv;

    return nTracker;
}
/*
Description: The functions, nineDigitInt, adds integer numbers to the tracker whenever
            a player buys that particular property.
Precondition:  @nPlayer1Pos and @nPlayer2Pos checks the position of player.
                This does not include 0, 4 and 6 as they are not purchasable.
Return: values ranges from 1 - 100000000 || 2 - 200000000
*/

int nineDigitInt(int nPlayerPos, int nPlayerTurn)
{
    int nTracker = 0;
    int nAdd;
    int nAdd2 = 2;

    nAdd = getDiv(nPlayerPos);
    nAdd2 *= getDiv(nPlayerPos);

    if (nPlayerTurn % 2 == 0)
        return nTracker += nAdd;
    else
        return nTracker += nAdd2;
}
int updateRenovatedTracker(int nPlayerPos)
{
    int nTracker = 0;
    int nAdd2 = 2;

    nAdd2 *= getDiv(nPlayerPos);

    return nTracker += nAdd2;
}
/*
Description: This function uses the digitChecker in order to check if the player owns the property
            or not. This will be later on used in the purchasing and paying rent of the players.
Precondition:  player position should always be non-negative, always greater than 0 and less than
                equal to 9.
                @nPlayerPos position of the player. This does not include 0, 4 and 6
                as they are not purchasable.
                @nTracker integer value, non-negative and should only include the values:
                0, 1,2,3 or 4
Return: returns 1 if conditions are met.
*/
int checkOwnedP1(int nPlayerPos, int nTracker)
{
    nTracker = digitChecker(nPlayerPos, nTracker);

    if (nTracker == 1)
        return 1;
    else if (nTracker == 3)
        return 1;

    return 0;
}
int checkOwnedP2(int nPlayerPos, int nTracker)
{
    nTracker = digitChecker(nPlayerPos, nTracker);

    if (nTracker == 2)
        return 1;
    else if (nTracker == 4)
        return 1;

    return 0;
}
/*
Description: The functions, renovateCheckP1, and renovateCheckP2, will be used to check if the player is
            eligible for renovating their property. This function also makes use of the digitChecker
            function
Precondition: player position should always be non-negative, always greater than 0 and less than
                equal to 9.
                @nPlayer1Pos position of the player. This does not include 0, 4 and 6
                as they are not purchasable.
                @nTracker ownership details should only have 0, 1 or 2
Return: returns 1 if conditions are met.
*/
int renovateCheckP1(int nPlayerPos, int nTracker)
{
    nTracker = digitChecker(nPlayerPos, nTracker);

    if (nTracker == 1)
        return 1;
    return 0;
}
int renovateCheckP2(int nPlayerPos, int nTracker)
{
    nTracker = digitChecker(nPlayerPos, nTracker);

    if (nTracker == 2)
        return 1;
    return 0;
}
/*
Description: This function calculates the rent that should be paid to the player who owns the property.
            First, it checks the position of the player, then it calculates using digitChecker
            to check if the property has been renovated or not.
            Player 1 = 1 - owned , 3 - owned and renovated
            Player 2 = 2 - owned , 4 - owned and renovated
Precondition:
            @nPlayerPos Checks the current position of player. This does not not include
            pos 0, 4, 6 and also property 7 since it cannot be renovated.
            @nTracker ownership details
Return:  cost for renovated or unrenovated property rent
*/
int payRent(int nTracker, int nPlayerPos, int nRentCost7)
{
    nTracker = digitChecker(nPlayerPos, nTracker);

    switch (nPlayerPos)
    {
    case 1:
        if (nTracker == 1 || nTracker == 2)
            return 0.2 * 20;
        else if (nTracker == 3 || nTracker == 4)
            return 0.2 * 20 * 2 + 1;
    case 2:
        return simulateDice() * 8;
    case 3:
        if (nTracker == 1 || nTracker == 2)
            return 0.2 * 60;
        else if (nTracker == 3 || nTracker == 4)
            return 0.2 * 60 * 2 + 1;
    case 5:
        if (nTracker == 1 || nTracker == 2)
            return 0.2 * 100;
        else if (nTracker == 3 || nTracker == 4)
            return 0.2 * 100 * 2 + 1;
    case 7:
        return nRentCost7;
    case 8:
        if (nTracker == 1 || nTracker == 2)
            return 0.2 * 20;
        else if (nTracker == 3 || nTracker == 4)
            return 0.2 * 20 * 2 + 1;
    case 9:
        if (nTracker == 1 || nTracker == 2)
            return 0.2 * 40;
        else if (nTracker == 3 || nTracker == 4)
            return 0.2 * 40 * 2 + 1;
    }
}
/*
Description: The functions displayResellCostP1 and displayResellCostP2 checks what property the
             player owns using the tracker and then prints the reselling cost statement.
Precondition:
            @nTracker a 9 digit integer that should ony include the digits; 0,1,2,3 and 4.
Return: prints the statement
*/
void displayResellCostP1(int nTracker)
{
    int h;
    int nCheck;
    for (h = 1; h <= 9; h++)
    {
        nCheck = digitChecker(h, nTracker);

        switch (h)
        {
        case 1:
            if (nCheck == 1 || nCheck == 3)
                printf("Position 1: Tree House = $10\n");
            break;
        case 2:
            if (nCheck == 1 || nCheck == 3)
                printf("Position 2: Electric Company = $75\n");
            break;
        case 3:
            if (nCheck == 1 || nCheck == 3)
                printf("Position 3: Beach House = $30\n");
            break;
        case 5:
            if (nCheck == 1 || nCheck == 3)
                printf("Position 5: Castle = $50\n");
            break;
        case 7:
            if (nCheck == 1 || nCheck == 3)
                printf("Position 7: Rail Road = $50\n");
            break;
        case 8:
            if (nCheck == 1 || nCheck == 3)
                printf("Position 8: Igloo = $10\n");
            break;
        case 9:
            if (nCheck == 1 || nCheck == 3)
                printf("Position 9: Farm House = $20\n");
            break;
        }
    }
}
void displayResellCostP2(int nTracker)
{
    int n;
    int nCheck;
    for (n = 1; n <= 9; n++)
    {
        nCheck = digitChecker(n, nTracker);

        switch (n)
        {
        case 1:
            if (nCheck == 2 || nCheck == 4)
                printf("Position 1: Tree House = $10\n");
            break;
        case 2:
            if (nCheck == 2 || nCheck == 4)
                printf("Position 2: Electric Company = $75\n");
            break;
        case 3:
            if (nCheck == 2 || nCheck == 4)
                printf("Position 3: Beach House = $30\n");
            break;
        case 5:
            if (nCheck == 2 || nCheck == 4)
                printf("Position 5: Castle = $50\n");
            break;
        case 7:
            if (nCheck == 2 || nCheck == 4)
                printf("Position 7: Rail Road = $50\n");
            break;
        case 8:
            if (nCheck == 2 || nCheck == 4)
                printf("Position 8: Igloo = $10\n");
            break;
        case 9:
            if (nCheck == 2 || nCheck == 4)
                printf("Position 9: Farm House = $20\n");
            break;
        }
    }
}
/*
Description: adds value to player money if the player agrees to resell their property
Precondition: @nSold  property the player wants to sell
            @fPlayerMoney  in this case, player money may be negative or less than
            the asked amount for rent
Return: playermoney plus half the initial selling amount of the property
*/
float resellProperty(int nSold, float fPlayerMoney)
{

    switch (nSold)
    {
    case 1:
        return fPlayerMoney + 10;
    case 2:
        return fPlayerMoney + 75;
    case 3:
        return fPlayerMoney + 30;
    case 5:
    case 7:
        return fPlayerMoney + 50;
    case 8:
        return fPlayerMoney + 10;
    case 9:
        return fPlayerMoney + 20;
    }
}
/*
Description: This function checks what value the player inputs, it will then find the place where
            the sold digit is through the use of the function digitChecker. When it corresponds to a
            particular condition, it will subtract it with a particular digit computed and stored
            in the integer nNew.
Precondition:
                @nTracker 9 digit integer (ownership details)
                @nSold  property the player wants to resell
Return: new 9 digit integer with 0 on the place where the player/s has sold their property
*/
int updateTracker(int nSold, int nTracker) // pass
{
    int i;
    int nNew = digitChecker(nSold, nTracker);

    for (i = 0; i < nSold - 1; i++)
    {
        nNew *= 10;
    }
    return nTracker -= nNew;
}
/*
Description: The functions checkWin  will determine if the game will stop.
Precondition: player money can negative or less than the asked amount
               @fPlayer1Money and  @fPlayer2Money
               @fAmntToPay amount to pay in rent
               @fGameEnd input from the user
Return: return 1 if the conditions are met, else it will return -1.
*/
float checkWin(float fPlayer1Money, float fPlayer2Money, float fGameEnd)
{
    if (fPlayer1Money <= 0)
        return 1;

    else if (fPlayer2Money <= 0)
        return 1;

    else if (fPlayer1Money == fGameEnd)
        return 1;

    else if (fPlayer2Money == fGameEnd)
        return 1;
    else
        return -1;

    return 0;
}

int main()
{
    // general
    char cGameEnd;         // game end condition option
    char cConfigMenu;      // configuration option
    char cMenu;            // menu choice ('S','s','E','e')
    char cDiceRoll;        // dice choice ('r')
    char cBuyChoice;       // choice if player will buy ('b')
    char cRenoChoice;      // choice if player wants to renovate the property ('u')
    int nPlayerTurn = 4;   // player turn condition
    int nTracker = 0;      // 9 digit integer that tracks ownership details
    int nSum;              // returns sum for dice
    int winner;            // stores either -1 or 1
    int nSold;             // stores the property value the player wants to sell
    float fAmnt;           // amount to pay in rent
    float fRenoCost = 50;  // renovation cost
    float fRentCost7 = 35; // rent cost for railroad
    float fGameEnd = 0;    // specific amount that will be part of game end condition

    // player 1
    int nPlayer1Pos = 0;     // player 1 current position
    float fPlay1Money = 200; // cash amount P1 have

    // player 2
    int nPlayer2Pos = 0;     // player 2 current position
    float fPlay2Money = 200; // cash amount P2 have

    do // loops the whole game including the menu with the condition of while (winner == 1)
    {
        printf("\n\tWELCOME TO PROPERTY...PROPERTY GAME!\nSelect from the Menu below\n");
        displayDivider();

        printf("1. Configure and Game end condition (Enter 'C')\n");
        printf("2. Start  a new game. (Enter 'S')\n");
        printf("3. Exit Game. (Enter 'E')\n");
        printf("Choice: ");
        scanf(" %c", &cMenu);

        while (cMenu != 'S' && cMenu != 's' && cMenu != 'E' && cMenu != 'e' &&
               cMenu != 'C' && cMenu != 'c')
        {
            printf("Invalid input! enter again: ");
            scanf(" %c", &cMenu);
        }

        switch (cMenu)
        {
        case 'C': // configuration option
        case 'c':

            printf("\n1. Initial cash on hand (Player 1) = $%.2f\n", fPlay1Money);
            printf("2. Initial cash on hand (Player 2) = $%.2f\n", fPlay2Money);
            printf("3. Initial rent payable (Rail Road) = $%.2f\n", fRentCost7);
            printf("4. Initial cost of renovation = $%.2f\n", fRenoCost);

            printf("\n\t\t\t\t5. GAME END CONDITION:\n");
            printf("Originally, the game will end when one player goes bankrupt or player cash-on-hand value is 0.\n");
            printf("You can opt to activate another game end condition by entering a specific amount\n");
            printf("that will determine the game's end.\n");

            printf("\nEnter 'c' to change Option 1 and 2, enter 'n' otherwise: ");
            scanf(" %c", &cConfigMenu);
            while (cConfigMenu != 'c' && cConfigMenu != 'n')
            {
                printf("Invalid input! enter again: ");
                scanf(" %c", &cConfigMenu);
            }

            switch (cConfigMenu)
            {
            case 'c':

                printf("\nNew initial cash on hand (Player 1): ");
                scanf("%f", &fPlay1Money);

                printf("\nNew initial cash on hand (Player 2): ");
                scanf("%f", &fPlay2Money);
                break;
            case 'n':
                break;
            }

            printf("\nEnter 'p' to change Option 3, enter 'n' otherwise: ");
            scanf(" %c", &cConfigMenu);
            while (cConfigMenu != 'p' && cConfigMenu != 'n')
            {
                printf("Invalid input! enter again: ");
                scanf(" %c", &cConfigMenu);
            }

            switch (cConfigMenu)
            {
            case 'p':
                printf("\nNew rent payable (Rail Road): ");
                scanf("%f", &fRentCost7);
                break;
            case 'n':
                break;
            }

            printf("\nEnter 'r' to change Option 4, enter 'n' otherwise: ");
            scanf(" %c", &cConfigMenu);
            while (cConfigMenu != 'r' && cConfigMenu != 'n')
            {
                printf("Invalid input! enter again: ");
                scanf(" %c", &cConfigMenu);
            }

            switch (cConfigMenu)
            {
            case 'r':
                printf("\nNew cost of renovation: ");
                scanf("%f", &fRenoCost);
                break;
            case 'n':
                break;
            }

            printf("\nEnter 'g' to change game end condition, enter 'n' otherwise: ");
            scanf(" %c", &cGameEnd);

            while (cGameEnd != 'g' && cGameEnd != 'n')
            {
                printf("Invalid input! enter again: ");
                scanf(" %c", &cGameEnd);
            }
            switch (cGameEnd)
            {
            case 'g':
                printf("Enter amount: ");
                scanf("%f", &fGameEnd);

                break;

            case 'n':
                break;
            }

            printf("\nYOU CAN NOW START THE GAME!\n");

        case 'S': // start of the game
        case 's':
            displayDivider();

            printf("\t\t\tBoth players are at start position\n\n");

            printf("Player 1 Balance = $%.2f\n", fPlay1Money);
            printf("Player 2 Balance = $%.2f\n", fPlay2Money);

            do
            {
                if (nPlayerTurn % 2 == 0) // Player 1 turn
                {

                    displayDivider();
                    displayBoard();
                    printf("\n\t\t\t\t\tPlayer 1\nEnter 'r' to roll the dice: ");
                    scanf(" %c", &cDiceRoll);

                    while (cDiceRoll != 'r')
                    {
                        printf("Invalid input! enter again: ");
                        scanf(" %c", &cDiceRoll);
                    }

                    switch (cDiceRoll)
                    {
                    case 'r':
                        nSum = simulateDice();
                        printf("Dice Roll is: %d\n", nSum);
                        nPlayer1Pos = getboardPosition(nPlayer1Pos);

                        if (nPlayer1Pos > 9) // there are instances wherein the nPlayer1Pos exceeds 9, this statement will decrease it by 10
                            nPlayer1Pos -= 10;

                        displayPosition(nPlayer1Pos);
                    }

                    if (nPlayer1Pos == 0) // player should recieve +200 in existing balance
                    {
                        fPlay1Money = theBank(fPlay1Money, nPlayer1Pos);
                        printf("\nPlayer collects 200!\n");
                        printf("Player 1 Balance = $%.2f\n", fPlay1Money);
                        printf("\nOwnership details = %.9d\n", nTracker);
                    }

                    else if (nPlayer1Pos >= 1 && nPlayer1Pos <= 3 || nPlayer1Pos == 5 || nPlayer1Pos >= 7 && nPlayer1Pos <= 9)
                    {
                        if (renovateCheckP1(nPlayer1Pos, nTracker)) // checks if the player can renovate their property.
                        {
                            if (nPlayer1Pos == 2 || nPlayer1Pos == 7) /* these positions cannot be renovated since these are not
                                                                    house properties*/
                            {
                                printf("\nYou own this property but...\n");
                                printf("You cannot renovate this property\n");
                                printf("\nOwnership details = %.9d\n", nTracker);
                            }
                            else // Player positions 1,3,5,8 and 9
                            {
                                printf("Player 1 Balance = $%.2f", fPlay1Money);
                                printf("\nOwnership details = %.9d\n", nTracker);
                                printf("\n\nYou own this property...\nWould you like to renovate?\nCOST OF RENOVATION: $%.2f", fRenoCost);
                                printf("\nEnter 'u' to renovate, enter 'n' otherwise: ");
                                scanf(" %c", &cRenoChoice);

                                while (cRenoChoice != 'u' && cRenoChoice != 'n')
                                {
                                    printf("Invalid input! enter again: ");
                                    scanf(" %c", &cRenoChoice);
                                }

                                switch (cRenoChoice)
                                {
                                case 'u':
                                    printf("The property is now renovated!\nYou will receive higher rent!");
                                    fPlay1Money -= fRenoCost;
                                    printf("\nPlayer 1 Balance = $%.2f", fPlay1Money);
                                    nTracker += updateRenovatedTracker(nPlayer1Pos);
                                    printf("\nOwnership details = %.9d\n", nTracker);

                                    break;

                                case 'n':
                                    break;
                                }
                            }
                        }

                        else if (!checkOwnedP2(nPlayer1Pos, nTracker) && !checkOwnedP1(nPlayer1Pos, nTracker)) /* checks if owned
                                                                                                            by player 2 or 1*/
                        {
                            printf("Player 1 Balance = $%.2f", fPlay1Money);
                            fAmnt = theBank(fPlay1Money, nPlayer1Pos); // amount to be paid when property is bought

                            if (fPlay1Money < fAmnt)
                            {
                                printf("\nYou don't have enough cash to pay!\n");
                            }
                            else if (fPlay1Money > fAmnt)
                            {
                                printf("\n\nWould you like to buy the property %d?\n", nPlayer1Pos);
                                printf("Enter 'b' to buy, enter 'n' if otherwise: ");
                                scanf(" %c", &cBuyChoice);

                                while (cBuyChoice != 'b' && cBuyChoice != 'n')
                                {
                                    printf("Invalid input! enter again: ");
                                    scanf(" %c", &cBuyChoice);
                                }
                            }
                            switch (cBuyChoice)
                            {
                            case 'b':
                                fPlay1Money -= fAmnt;
                                printf("\nYou now own the property!\n");
                                printf("Player 1 Balance = $%.2f", fPlay1Money);
                                nTracker += nineDigitInt(nPlayer1Pos, nPlayerTurn);
                                printf("\nOwnership details = %.9d\n", nTracker);

                                cBuyChoice = 0;

                                break;

                            case 'n':
                                break;
                            }
                        }

                        else if (checkOwnedP2(nPlayer1Pos, nTracker)) // checks if player 1 should pay player 2 rent
                        {
                            printf("\nThis property is owned by PLAYER 2.\n");
                            printf("You must pay rent!\n");
                            fAmnt = payRent(nTracker, nPlayer1Pos, fRentCost7);
                            printf("An amount of $%.2f will be deducted from your balance.\n", fAmnt);
                            printf("\nOwnership details = %.9d\n", nTracker);

                            if (fAmnt > fPlay1Money)
                            {
                                printf("\nYou don't have enough cash!\nResell any of your properties back to the bank\n\n");

                                displayResellCostP1(nTracker);

                                printf("Which property would you like to sell (input number only): ");
                                scanf("%d", &nSold);

                                fPlay1Money = resellProperty(nSold, fPlay1Money);
                                printf("Player 1 Balance = %.2f", fPlay1Money);
                                nTracker = updateTracker(nSold, nTracker);
                                printf("\nOwnership details = %.9d\n", nTracker);
                            }

                            printf("You have paid rent!\n");
                            printf("Player 1 Balance = $%.2f\n", fPlay1Money -= fAmnt);
                            printf("Player 2 Balance = $%.2f\n", fPlay2Money += fAmnt);
                        }
                    }

                    else if (nPlayer1Pos == 4) // player loses turn
                    {
                        printf("\nSorry! You lose your next turn!\n");
                        printf("\nOwnership details = %.9d\n", nTracker);
                    }

                    else if (nPlayer1Pos == 6) // player rolls dice in order to get amount from specific range
                    {

                        printf("\nEnter 'r' to roll the dice: ");
                        scanf(" %c", &cDiceRoll);

                        while (cDiceRoll != 'r')
                        {
                            printf("Invalid input! enter again: ");
                            scanf(" %c", &cDiceRoll);
                        }

                        nSum = simulateDice();
                        printf("dice roll: %d", nSum);

                        if (nSum == 1) // part of feelin' lucky condition
                        {
                            printf("\nYou are now at the jail!\n");
                            nPlayer1Pos = 4;
                        }
                        else
                        {
                            fAmnt = theBank(fPlay1Money, nPlayer1Pos);

                            if (nSum % 2 != 0 || nSum == 2)
                            {
                                printf("\nCongratulations! You get an amount of $%.2f", fAmnt);
                                fPlay1Money += fAmnt;
                            }
                            else if (nSum % 2 == 0)
                            {
                                printf("\nSorry! An amount of $%.2f will be deducted in your balance", fAmnt);
                                fPlay1Money -= fAmnt;
                            }

                            printf("\nPlayer 1 Balance = $%.2f\n", fPlay1Money);
                            printf("\nOwnership details = %.9d\n", nTracker);
                        }
                    }

                    // Jail Time conditions

                    if (nPlayerTurn == 2)
                        nPlayerTurn = 0;

                    else if (nPlayer2Pos == 4 && nPlayerTurn != 0)
                        nPlayerTurn = 1;

                } // end of if statement

                else // Player 2 Turn
                {

                    displayDivider();
                    displayBoard();
                    printf("\n\t\t\t\t\tPlayer 2\nEnter 'r' to roll the dice: ");
                    scanf(" %c", &cDiceRoll);

                    while (cDiceRoll != 'r')
                    {
                        printf("Invalid input! enter again: ");
                        scanf(" %c", &cDiceRoll);
                    }

                    switch (cDiceRoll)
                    {
                    case 'r':
                        nSum = simulateDice();
                        printf("Dice Roll is: %d\n", nSum);
                        nPlayer2Pos = getboardPosition(nPlayer2Pos);

                        if (nPlayer2Pos > 9)
                            nPlayer2Pos -= 10;

                        displayPosition(nPlayer2Pos);
                    }
                    if (nPlayer2Pos == 0)
                    {
                        fPlay2Money = theBank(fPlay2Money, nPlayer2Pos);
                        printf("\nPlayer collects 200!\n");
                        printf("Player 2 Balance = $%.2f\n", fPlay2Money);
                        printf("\nOwnership details = %.9d\n", nTracker);
                    }
                    else if (nPlayer2Pos >= 1 && nPlayer2Pos <= 3 || nPlayer2Pos == 5 || nPlayer2Pos >= 7 && nPlayer2Pos <= 9)
                    {
                        if (renovateCheckP2(nPlayer2Pos, nTracker))
                        {
                            if (nPlayer2Pos == 2 || nPlayer2Pos == 7)
                            {
                                printf("\nYou own this property but...\n");
                                printf("You cannot renovate this property\n");
                                printf("\nOwnership details = %.9d\n", nTracker);
                            }
                            else
                            {

                                printf("\nPlayer 2 Balance = $%.2f", fPlay2Money);
                                printf("\nOwnership details = %.9d\n", nTracker);
                                printf("\n\nYou own this property...\nWould you like to renovate?\nCOST OF RENOVATION: $%.2f", fRenoCost);
                                printf("\nEnter 'u' to renovate, enter 'n' otherwise: ");
                                scanf(" %c", &cRenoChoice);

                                while (cRenoChoice != 'u' && cRenoChoice != 'n')
                                {
                                    printf("Invalid input! enter again: ");
                                    scanf(" %c", &cRenoChoice);
                                }

                                switch (cRenoChoice)
                                {
                                case 'u':
                                    printf("The property is now renovated!\nYou will receive higher rent!");
                                    fPlay2Money -= fRenoCost;
                                    printf("\nPlayer 2 Balance = $%.2f", fPlay2Money);
                                    nTracker += updateRenovatedTracker(nPlayer2Pos);
                                    printf("\nOwnership details = %.9d\n", nTracker);

                                    break;

                                case 'n':
                                    break;
                                }
                            }
                        }

                        else if (!checkOwnedP1(nPlayer2Pos, nTracker) && !checkOwnedP2(nPlayer2Pos, nTracker))
                        {

                            printf("\nPlayer 2 Balance = $%.2f", fPlay2Money);
                            fAmnt = theBank(fPlay2Money, nPlayer2Pos);

                            if (fPlay2Money < fAmnt)
                            {
                                printf("\nYou don't have enough cash to pay!\n");
                            }
                            else if (fPlay2Money > fAmnt)
                            {
                                printf("\n\nWould you like to buy the property %d?\n", nPlayer2Pos);
                                printf("Enter 'b' to buy, enter 'n' if otherwise: ");
                                scanf(" %c", &cBuyChoice);

                                while (cBuyChoice != 'b' && cBuyChoice != 'n')
                                {
                                    printf("Invalid input! enter again: ");
                                    scanf(" %c", &cBuyChoice);
                                }
                            }

                            switch (cBuyChoice)
                            {
                            case 'b':

                                fPlay2Money -= fAmnt;
                                printf("\nYou now own the property!\n");
                                printf("Player 2 Balance = $%.2f", fPlay2Money);
                                nTracker += nineDigitInt(nPlayer2Pos, nPlayerTurn);
                                printf("\nOwnership details = %.9d\n", nTracker);

                                cBuyChoice = 0;

                                break;
                            case 'n':
                                break;
                            }
                        }

                        else if (checkOwnedP1(nPlayer2Pos, nTracker))
                        {
                            printf("\nThis property is owned by PLAYER 1.\n");
                            printf("You must pay rent!\n");
                            fAmnt = payRent(nTracker, nPlayer2Pos, fRentCost7);
                            printf("An amount of $%.2f will be deducted from your balance.\n", fAmnt);
                            printf("\nOwnership details = %.9d\n", nTracker);

                            if (fAmnt > fPlay2Money)
                            {
                                printf("\nYou don't have enough cash!\nResell any of your properties back to the bank\n\n");

                                displayResellCostP2(nTracker);

                                printf("Which property would you like to sell (input number only): ");
                                scanf("%d", &nSold);

                                fPlay2Money = resellProperty(nSold, fPlay2Money);
                                printf("Player 2 Balance = %.2f", fPlay2Money);

                                nTracker = updateTracker(nSold, nTracker);
                                printf("\nOwnership details = %.9d\n", nTracker);
                            }
                            printf("You have paid rent!\n");
                            printf("Player 2 Balance = $%.2f\n", fPlay2Money -= fAmnt);
                            printf("Player 1 Balance = $%.2f\n", fPlay1Money += fAmnt);
                        }
                    }
                    else if (nPlayer2Pos == 4)
                    {
                        printf("\nSorry! You lose your next turn!\n");
                        printf("\nOwnership details = %.9d\n", nTracker);
                    }

                    else if (nPlayer2Pos == 6)
                    {

                        printf("\nInput 'r' to roll the dice: ");
                        scanf(" %c", &cDiceRoll);

                        while (cDiceRoll != 'R' && cDiceRoll != 'r')
                        {
                            printf("Invalid input! enter again: ");
                            scanf(" %c", &cDiceRoll);
                        }

                        nSum = simulateDice();
                        printf("Dice roll: %d", nSum);

                        if (nSum == 1)
                        {
                            printf("\nYou are now at the jail!\n");
                            nPlayer2Pos = 4;
                        }
                        else
                        {
                            fAmnt = theBank(fPlay2Money, nPlayer2Pos);

                            if (nSum % 2 != 0 || nSum == 2)
                            {
                                printf("\nCongratulations! You get an amount of $%.2f", fAmnt);
                                fPlay2Money += fAmnt;
                            }

                            else if (nSum % 2 == 0)
                            {
                                printf("\nSorry! An amount of $%.2f will be deducted in your balance", fAmnt);
                                fPlay2Money -= fAmnt;
                            }

                            printf("\nPlayer 2 Balance = $%.2f\n", fPlay2Money);
                            printf("\nOwnership details = %.9d\n", nTracker);
                        }
                    }

                    // Jail Time conditions

                    if (nPlayerTurn == 1)
                        nPlayerTurn = 3;

                    else if (nPlayer1Pos == 4 && nPlayerTurn != 3)
                        nPlayerTurn = 0;

                    else if (nPlayer2Pos == 4 && nPlayer1Pos == 4)
                        nPlayerTurn = 3;
                }

                winner = checkWin(fPlay1Money, fPlay2Money, fGameEnd); // return 1 if true

                nPlayerTurn++; // increments in order to initiate player turn

            } while (winner != 1);

            if (nPlayerTurn % 2 == 0)
                printf("\n***CONGRATULATIONS PLAYER 1! YOU WIN!***\n\n");

            else
                printf("\n***CONGRATULATIONS PLAYER 2! YOU WIN!***\n\n");

            if (winner == 1) // changes the variables back to their initial value
            {
                nPlayerTurn = 2;
                nPlayer1Pos = 0;
                nPlayer2Pos = 0;
                nTracker = 0;
                fPlay1Money = 200;
                fPlay2Money = 200;
                fRentCost7 = 35;
                fRenoCost = 50;
                fGameEnd = 0;
            }
            break; // game break statement

        case 'E': // exit
        case 'e':
            displayDivider();

            printf("You have exited the game!\n GoodBye!");
            break;
        }
    } while (winner == 1);

    return 0;
}
