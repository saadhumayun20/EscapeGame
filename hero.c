#include <stdio.h>

#include "defs.h"

void initHero(HeroType **, char, int, char *); // done
void addHero(HeroArrayType *, HeroType *);     // done
void moveHero(HeroType *, EscapeType *);       // done
int heroIsSafe(HeroType *);                    // done

/*
  Purpose:  intitalizes the hero and allocates memory
       in:  double pointer to HeroType
       in:  hero avatar's character
       in:  the inital row position
       in:  pointer to the hero name's character
   return:
*/
void initHero(HeroType **hero, char HeroAvatar, int initRow, char *HeroName)
{
    *hero = malloc(sizeof(HeroType));
    if (*hero == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
    }

    (*hero)->partInfo.avatar = HeroAvatar;
    (*hero)->partInfo.pos.row = initRow;
    (*hero)->partInfo.pos.col = randomInt(4);
    strcpy((*hero)->name, HeroName);
    (*hero)->name[MAX_STR - 1] = '\0';
    (*hero)->health = MAX_HEALTH;
    (*hero)->dead = C_FALSE;
}

/*
  Purpose:  adds the initalized heroes to the flyerArray
   in-out:  pointer to HeroArrayType
       in:  pointer to HeroType
   return:
*/
void addHero(HeroArrayType *heroArr, HeroType *hero)
{
    if (heroArr->size >= MAX_ARR)
    {
        printf("Hero array is full\n");
        return;
    }

    heroArr->elements[heroArr->size++] = hero;
}

/*
  Purpose:  move the heroes in the grid
   in-out:  pointer to HeroType
       in:  pointer to EscapeType
   return:
*/
void moveHero(HeroType *hero, EscapeType *hollow)
{
    int probability;

    if (hero->dead == C_TRUE)
    {
        return;
    }

    int newPos = hero->partInfo.pos.col;

    if (hero->partInfo.avatar == 'T')
    {
        if (heroIsSafe(hero))
        {
            newPos = -1;
            hero->partInfo.pos.row = -1;
            return;
        }
        probability = randomInt(100);
        if (probability < 50)
        {
            newPos += 2;
        }
        if (probability < 80)
        {
            newPos -= 1;
        }
        else
        {
            newPos += 1;
        }
    }

    else if (hero->partInfo.avatar == 'H')
    {
        if (heroIsSafe(hero))
        {
            newPos = -1;
            hero->partInfo.pos.row = -1;
            return;
        }
        probability = randomInt(100);
        if (probability < 20)
        {
        }
        if (probability < 30)
        {
            newPos += 5;
        }
        if (probability < 40)
        {
            newPos -= 4;
        }
        if (probability < 80)
        {
            newPos += 3;
        }
        else
        {
            newPos -= 2;
        }
    }

    setPos(&(hero->partInfo.pos), hero->partInfo.pos.row, newPos);
}

/*
  Purpose:  checks if the heroes have reached the end of the grid
   in-out:  pointer to HeroType
   return:  1 or 0 depending on if the hero reached the end
*/
int heroIsSafe(HeroType *hero)
{
    if (hero->partInfo.pos.col >= MAX_COL - 1)
    {
        return C_TRUE;
    }
    return C_FALSE;
}