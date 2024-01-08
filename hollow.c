#include <stdio.h>

#include "defs.h"

void initHollow(EscapeType *, char[][MAX_COL]); // done
void serializeHollow(EscapeType *, char *);     // done
void setPos(PositionType *, int, int);          // done
void outputHollow(EscapeType *);                // done

/*
  Purpose:  initalizes the hollow grid and places the heros and flyers in it
       in:  pointer to EscapeType
   in-out:  the 2d array grid
   return:
*/
void initHollow(EscapeType *hollow, char grid[][MAX_COL])
{
    for (int i = 0; i < MAX_ROW; ++i)
    {
        for (int j = 0; j < MAX_COL; ++j)
        {
            if (i == 0 || i == MAX_ROW - 1)
            {
                grid[i][j] = '-';
            }
            else if (i == MAX_ROW - 2 && (j == 0 || j == MAX_COL - 1))
            {
                grid[i][j] = '=';
            }
            else if (j == 0 || j == MAX_COL - 1)
            {
                grid[i][j] = '|';
            }
            else
            {
                grid[i][j] = ' ';
            }
        }
    }

    for (int i = 0; i < hollow->heroes.size; ++i)
    {
        HeroType *hero = hollow->heroes.elements[i];
        grid[hero->partInfo.pos.row][hero->partInfo.pos.col] = hero->partInfo.avatar;
    }

    for (int i = 0; i < hollow->flyers.size; ++i)
    {
        FlyerType *flyer = hollow->flyers.elements[i];
        if (flyer->partInfo.pos.col < 0 && flyer->partInfo.pos.row < 0)
        {
            continue;
        }
        grid[flyer->partInfo.pos.row][flyer->partInfo.pos.col] = flyer->partInfo.avatar;
    }
}

/*
  Purpose:  serializes the hollow grid into a 1d array
       in:  pointer to EscapeType
   in-out:  pointer to the output character in which the grid is put
   return:
*/
void serializeHollow(EscapeType *hollow, char *output)
{

    char grid[MAX_ROW][MAX_COL];

    initHollow(hollow, grid);

    int index = 0;
    for (int i = 0; i < MAX_ROW; ++i)
    {
        for (int j = 0; j < MAX_COL; ++j)
        {
            output[index] = grid[i][j];
            index++;
        }

        if (i == MAX_ROW - 1)
        {
            output[index] = '\0';
        }
        else
        {
            output[index] = '\n';
        }
        index++;
    }
}

/*
  Purpose:  sets the position for heroes and flyers and checks if they are out of bounds
      out:  pointer to PositionTypE
       in:  row pos
       in:  col pos
   return:
*/
void setPos(PositionType *pos, int row, int col)
{
    pos->row = row;
    pos->col = col;

    if (pos->row < 0)
    {
        pos->row = 0;
    }
    else if (pos->row >= MAX_ROW)
    {
        pos->row = MAX_ROW - 1;
    }

    if (pos->col < 0)
    {
        pos->col = 0;
    }
    else if (pos->col >= MAX_COL)
    {
        pos->col = MAX_COL - 1;
    }
}

/*
  Purpose:  outputs the serialized hollow grid as a string
   in-out:  pointer to EscapeType
   return:
*/
void outputHollow(EscapeType *hollow)
{
    char serialized[MAX_ROW * (MAX_COL + 1)];
    serializeHollow(hollow, serialized);
    printf("%s\n", serialized);
}