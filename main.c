#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

bool isLegal(int sodokuBoard[9][9], int x, int y, int value)
{
    // chaeckt ob ich auf dem Brett bin
    if (x < 0 || x >= 9 || y < 0 || y >= 9)
        return false;

    // schaut das die eingabe auch nicht über 9 oder unter 1 ist
    if (value < 1 || value > 9)
        return false;

    // negative Werte sind fixe Startwerte und duerfen nicht ueberschrieben werden
    if (sodokuBoard[x][y] < 0)
        return false;

    // checkt row und column
    for (int i = 0; i < 9; ++i)
        if (i != x && abs(sodokuBoard[i][y]) == value)
            return false;

    for (int i = 0; i < 9; ++i)
        if (i != y && abs(sodokuBoard[x][i]) == value)
            return false;

    // checkt das subgrid also alles in der x und y richtung ob die Zahl eingesetzt werden darf
    int subgrid_x = (x / 3) * 3;
    int subgrid_y = (y / 3) * 3;

    for (int xx = subgrid_x; xx < subgrid_x + 3; ++xx)
    {
        for (int yy = subgrid_y; yy < subgrid_y + 3; ++yy)
        {
            if ((xx != x || yy != y) && abs(sodokuBoard[xx][yy]) == value)
                return false;
        }
    }

    return true;
}

void drawBoard(int board[9][9])
{
    printf("\033[0m");
    printf("   1 2 3   4 5 6   7 8 9\n");
    for (int y = 0; y < 9; ++y)
    {
        if (y == 3 || y == 6)
            printf("  -------+-------+------+---\n");

        printf("%c  ", 'A' + y);
        printf("");
        for (int x = 0; x < 9; ++x)
        {
            if (x == 3 || x == 6)
                printf("| ");

            int cell = board[x][y];
            if (cell < 0)
            {
                printf("\033[36m%d\033[0m ", abs(cell));
            }
            else
            {
                printf("%d ", cell);
            }
        }
        printf("\n");
    }
}

int main()
{
    bool running = true;

    int sodokuBoard[9][9] = {
        {-1, 0, 0, 0, 0, 0, -5, 0, 0},
        {0, 0, -8, 0, -5, -4, 0, -9, -7},
        {0, 0, 0, 0, 0, -3, -2, 0, -6},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, -9, -7, 0},
        {0, 0, 0, 0, 0, 0, 0, -5, -2},
        {-6, 0, -7, 0, -1, 0, 0, 0, 0},
        {-5, -2, 0, -9, -7, 0, -3, 0, 0},
        {0, 0, -9, 0, 0, 0, 0, 0, -5}
    };

    while (running)
    {
        // system("cls");
        drawBoard(sodokuBoard);
        printf("Um ein wert in das Brett einzusetzen verwende 'set' gefollgt von der x und y Koordinate und den wert den du einsetzen willst :) \n");

        char command[16];
        char rowChar;
        int collumNumber;
        int userValue;

        if (scanf("%15s", command) != 1)
        {
            break;
        }

        if (strncmp(command, "set", 3) == 0)
        {
            if (scanf(" %c%d %d", &rowChar, &collumNumber, &userValue) == 3)
            {
                int y = rowChar - 'a';
                int x = collumNumber - 1;

                if (isLegal(sodokuBoard, x, y, userValue))
                {
                    sodokuBoard[x][y] = userValue;
                }
                else
                {
                    printf("nicht genehmigte eingabe oder feld ist fix\n");
                }
            }
            else
            {
                printf("Coordinaten sind ausserhalb des Spielfeldes");
            }
        }
        else if (strcmp(command, "exit") == 0)
        {
            running = false;
        }
        else
        {
            printf("unbekennte eingabe");
        }
    }

    return 0;
}