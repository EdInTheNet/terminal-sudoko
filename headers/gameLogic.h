#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "types.h"
#include <stdlib.h>
#include <stdio.h>

void drawBoard(i16 board[9][9]);

bool parseSetCommand(const char *line, i8 *x, i8 *y, i8 *value);

bool isLegal(i16 sodokuBoard[9][9], i8 x, i8 y, i16 value);

#endif