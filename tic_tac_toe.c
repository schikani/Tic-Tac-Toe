#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif
#include <stdio.h>

char square[10] = {};
char x_o[2] = {'X', 'O'};
int combination[8][3] = {
        {1, 2, 3},
        {1, 4, 7},
        {1, 5, 9},
        {2, 5, 8},
        {3, 5, 7},
        {3, 6, 9},
        {4, 5, 6},
        {7, 8, 9}
};

void drawBoard(int playAgain);
void markBoard(char mark, int position);
int checkRules(int block);
void play(void);
char checkForWin(void);

void drawBoard(int playAgain){

    if (playAgain == 0)
    {
        clrscr();
        printf("\n ~ TIC TAC TOE ~\n\n");
        printf("     |     |     \n");
        printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);

        printf("_____|_____|_____\n");
        printf("     |     |     \n");

        printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);

        printf("_____|_____|_____\n");
        printf("     |     |     \n");

        printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);
        printf("     |     |     \n\n");
    }
    else
    {
        clrscr();
        char numbersInBlocks[10] = {'N', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        for (int i = 0; i < 10; ++i)
            square[i] = numbersInBlocks[i];

        drawBoard(0);
    }
}

void markBoard(char mark, int position){
    square[position] = mark;
    drawBoard(0);
}

int checkRules(int block){

    int ruleBreak;
    int allBoxesMarked = 0;

    if (block != -1)
    {
        if (square[block] == x_o[0] || square[block] == x_o[1])
            ruleBreak = 1;

        else if (block <= 0 || block > 9)
            ruleBreak = 1;

        else

            ruleBreak = 0;
    }
    else
    {
        for (int i = 1; i < 10; ++i)
        {
            if (square[i] == x_o[0] || square[i] == x_o[1])
                ++allBoxesMarked;
        }

        if (allBoxesMarked == 9)
            ruleBreak = 2;
    }

    return ruleBreak;

}

void play(void){

    int position;
    char playAgain;
    drawBoard(1);

    char whoWon;

     while (1)
    {

        if (checkRules(-1) == 2)
        {
            whoWon = 'D';
            break;
        }

        while (1)
        {
            printf("%c's turn: ", x_o[0]);
            scanf("%i", &position);

            if (checkRules(position) == 1)
            {
                printf("\nInvalid input!\n\n");
                continue;
            }
            else
                break;
        }

        markBoard(x_o[0], position);
        if (checkForWin() == x_o[0])
        {
            whoWon = x_o[0];
            break;
        }

//----------------------------------------------------//

         if (checkRules(-1) == 2)
         {
             whoWon = 'D';
             break;
         }

         while (1)
         {
             printf("%c's turn: ", x_o[1]);
             scanf("%i", &position);

             if (checkRules(position) == 1)
             {
                 printf("\nInvalid input!\n\n");
                 continue;
             }
             else
                 break;
         }

         markBoard(x_o[1], position);
         if (checkForWin() == x_o[1])
         {
             whoWon = x_o[1];
             break;
         }
    }

     if (whoWon == x_o[0] || whoWon == x_o[1])
     {
         printf("\n%c wins!\n\n", whoWon);
     }
     else if (whoWon == 'D')
     {
         printf("The match is a draw!\n");
     }

     printf("Play again?\nType y / n: ");
     scanf("%s", &playAgain);

     if (playAgain == 'y' || playAgain == 'Y')
     {
         // Rotation
         int player1 = x_o[0];
         int player2 = x_o[1];
         x_o[0] = player2;
         x_o[1] = player1;
         play();
     }

     else
         printf("\nBye!\n\n");
}

char checkForWin(void){

    char winner = 'N';

    for (int p = 0; p < 8; ++p)
    {
        int position_1 = square[combination[p][0]];
        int position_2 = square[combination[p][1]];
        int position_3 = square[combination[p][2]];

        if (position_1 == x_o[0] && position_2 == x_o[0] && position_3 == x_o[0]) // X
        {
            winner = x_o[0];
            break;
        }

        else if (position_1 == x_o[1] && position_2 == x_o[1] && position_3 == x_o[1]) // O
        {
            winner = x_o[1];
            break;
        }

    }
    return winner;
}

int main(){
    play();
}