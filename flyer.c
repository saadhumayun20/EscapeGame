#include <stdio.h>

#include "defs.h"

void spawnFlyer(EscapeType *, char, int, int, int);    // done
void addFlyer(FlyerArrayType *, FlyerType *);          // done
void moveFlyer(FlyerType *, EscapeType *);             // done
void computeHeroDir(EscapeType *, FlyerType *, int *); // done

/*
  Purpose:  intitalizes the flyer and allocates memory
       in:  pointer to EscapeType
       in:  flyer avatar's character
       in:  the row position
       in:  the col position
       in:  the strength of the flyer
   return:
*/
void spawnFlyer(EscapeType *hollow, char flyerAvatar, int rowPos, int colPos, int flyerStrength)
{
    if (hollow->flyers.size >= MAX_ARR)
    {
        return;
    }
    FlyerType *flyer = malloc(sizeof(FlyerType));
    if (flyer == NULL)
    {
        fprintf(stderr, "Memory allocation for flyer failed.");
    }

    flyer->partInfo.avatar = flyerAvatar;
    flyer->partInfo.pos.row = rowPos;
    flyer->partInfo.pos.col = colPos;
    flyer->strength = flyerStrength;

    if (hollow->flyers.size > MAX_ARR)
    {
        printf("The flyer array is full, cannot add.");
    }

    addFlyer(&(hollow->flyers), flyer);
}

/*
  Purpose:  adds the initalized flyers to the flyerArray
   in-out:  pointer to FlyerArrayType
       in:  pointer to FlyerType
   return:
*/
void addFlyer(FlyerArrayType *flyerArr, FlyerType *flyer)
{

    flyerArr->elements[flyerArr->size++] = flyer;
}

/*
  Purpose:  move the flyers in the grid
   in-out:  pointer to FlyerType
       in:  pointer to EscapeType
   return:
*/
void moveFlyer(FlyerType *flyer, EscapeType *hollow)
{
    int probability1;
    int probability2;
    if (flyerIsDone(flyer))
    {
        flyer->partInfo.pos.col = -1;
        flyer->partInfo.pos.row = -1;
    }

    if (flyer->partInfo.pos.col < 0 && flyer->partInfo.pos.row < 0)
    {
        return;
    }
    int newCol = flyer->partInfo.pos.col;
    int newRow = flyer->partInfo.pos.row;

    if (flyer->partInfo.avatar == 'v')
    {
        newRow += 1;
        probability1 = randomInt(3);
        if (probability1 == 0)
        {
        }
        if (probability1 == 1)
        {
            newCol += 1;
        }
        else
        {
            newCol -= 1;
        }
    }

    else if (flyer->partInfo.avatar == '@')
    {
        int direction;
        computeHeroDir(hollow, flyer, &direction);
        probability1 = randomInt(7);
        if (probability1 == 0)
        {
            newRow -= 3;
        }
        if (probability1 == 1)
        {
            newRow -= 2;
        }
        if (probability1 == 2)
        {
            newRow -= 1;
        }
        if (probability1 == 3)
        {
        }
        if (probability1 == 4)
        {
            newRow += 1;
        }
        if (probability1 == 5)
        {
            newRow += 2;
        }
        else
        {
            newRow += 3;
        }

        probability2 = randomInt(3);
        if (direction == DIR_LEFT)
        {
            if (probability2 == 0)
            {
                newCol -= 1;
            }
            if (probability2 == 1)
            {
                newCol -= 2;
            }
            else
            {
                newCol -= 3;
            }
        }
        if (direction == DIR_RIGHT)
        {
            if (probability2 == 0)
            {
                newCol += 1;
            }
            if (probability2 == 1)
            {
                newCol += 2;
            }
            else
            {
                newCol += 3;
            }
        }
    }

    flyer->partInfo.pos.row = newRow;
    flyer->partInfo.pos.col = newCol;
    setPos(&(flyer->partInfo.pos), flyer->partInfo.pos.row, flyer->partInfo.pos.col);
}

/*
  Purpose:  finds the closest hero to the monkey flyer
       in:  pointer to EscapeType
       in:  pointer to FlyerType
      out:  pointer to the int direction
   return:
*/
void computeHeroDir(EscapeType *hollow, FlyerType *flyer, int *dir)
{
    int minDistance = MAX_COL;
    *dir = DIR_SAME;
    HeroType *hero = NULL;

    for (int i = 0; i < hollow->heroes.size; ++i)
    {
        hero = hollow->heroes.elements[i];
        int distance = abs(hero->partInfo.pos.col - flyer->partInfo.pos.col);
        if (distance < minDistance)
        {
            minDistance = distance;

            if (hero->partInfo.pos.col < flyer->partInfo.pos.col)
            {
                *dir = DIR_LEFT;
            }
            else if (hero->partInfo.pos.col > flyer->partInfo.pos.col)
            {
                *dir = DIR_RIGHT;
            }
            else
            {
                *dir = DIR_SAME;
            }
        }
    }
}