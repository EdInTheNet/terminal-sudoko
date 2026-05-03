#include "headers/gameLogic.h"

void drawBoard(i16 board[9][9])
{
    printf("\033[0m");
    printf("   1 2 3   4 5 6   7 8 9\n");
    for (u8 y = 0; y < 9; ++y)
    {
        if (y == 3 || y == 6)
            printf("  -------+-------+------+---\n");

        printf("%c  ", 'A' + y);
        for (u8 x = 0; x < 9; ++x)
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

bool parseSetCommand(const char *line, i8 *x, i8 *y, i8 *value)
{
    char rowChar = 0;
    long column = 0;
    long parsedValue = 0;

    // akzeptiert sowohl "set A1 5" als auch "set A 1 5"
    int parsed = sscanf(line, "set %c%ld %ld", &rowChar, &column, &parsedValue);
    if (parsed != 3)
        parsed = sscanf(line, "set %c %ld %ld", &rowChar, &column, &parsedValue);

    if (parsed != 3)
        return false;

    rowChar = (char)toupper((unsigned char)rowChar);
    if (rowChar < 'A' || rowChar > 'I')
        return false;

    if (column < 1 || column > 9 || parsedValue < 1 || parsedValue > 9)
        return false;

    *y = (i8)(rowChar - 'A');
    *x = (i8)(column - 1);
    *value = (i8)parsedValue;

    return true;
}

bool isLegal(i16 sodokuBoard[9][9], i8 x, i8 y, i16 value)
{
    // checkt ob ich auf dem Brett bin
    if (x < 0 || x >= 9 || y < 0 || y >= 9)
        return false;

    // schaut das die eingabe auch nicht ueber 9 oder unter 1 ist
    if (value < 1 || value > 9)
        return false;

    // negative Werte sind fixe Startwerte und duerfen nicht ueberschrieben werden
    if (sodokuBoard[x][y] < 0)
        return false;

    // checkt row und column
    for (u8 i = 0; i < 9; ++i)
        if (i != x && abs(sodokuBoard[i][y]) == value)
            return false;

    for (u8 i = 0; i < 9; ++i)
        if (i != y && abs(sodokuBoard[x][i]) == value)
            return false;

    // checkt das subgrid also alles in der x und y richtung ob die Zahl eingesetzt werden darf
    i8 subgrid_x = (x / 3) * 3;
    i8 subgrid_y = (y / 3) * 3;

    for (u8 xx = subgrid_x; xx < subgrid_x + 3; ++xx)
    {
        for (u8 yy = subgrid_y; yy < subgrid_y + 3; ++yy)
        {
            if ((xx != x || yy != y) && abs(sodokuBoard[xx][yy]) == value)
                return false;
        }
    }

    return true;
}