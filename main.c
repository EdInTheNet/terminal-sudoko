#include "headers/gameLogic.h"

int main(void)
{
    bool running = true;

    i16 sodokuBoard[9][9] = {
        {-6, 0, 9, 0, 0, -2, -5, -1, 0},
        {-4, 0, 0, -7, -8, 0, 0, 0, -3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {-3, 0, -4, 0, -6, 0, 0, 0, 0},
        {0, 0, 0, 0, -9, 0, -8, 0, 0},
        {-5, 0, -8, 0, 0, -7, 0, -9, -1},
        {-1, 0, 0, 0, -2, 0, -9, 0, 0},
        {0, 0, -6, 0, 0, -8, 0, -2, -4},
        {0, -5, -2, -9, 0, 0, 0, -3, 0}};

    while (running)
    {
        // system("cls");
        drawBoard(sodokuBoard);
        printf("Um ein wert in das Brett einzusetzen verwende 'set' gefollgt von der x und y Koordinate und den wert den du einsetzen willst :) \n");

        char line[128];
        if (!fgets(line, sizeof(line), stdin))
            break;

        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "exit") == 0)
        {
            running = false;
        }
        else if (strncmp(line, "set", 3) == 0 && (line[3] == '\0' || line[3] == ' ' || line[3] == '\t'))
        {
            i8 x;
            i8 y;
            i8 userValue;

            if (parseSetCommand(line, &x, &y, &userValue))
            {
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
                printf("ungueltige Eingabe. Beispiel: set A1 5\n");
            }
        }
        else
        {
            printf("unbekennte eingabe\n");
        }
    }

    return 0;
}