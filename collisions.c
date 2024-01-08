#include <stdio.h>

#include "defs.h"

int flyerIsDone(FlyerType *);                              // done
HeroType *checkForCollision(PositionType *, EscapeType *); // done
void incurDamage(HeroType *, FlyerType *);                 // done

/*
  Purpose:  check if a flyer has reached the ground
       in:  pointer to FlyerType
   return:  1 or 0 depending on if the flyer has reached the ground
*/
int flyerIsDone(FlyerType *flyer)
{
    if (flyer->partInfo.pos.row >= MAX_ROW - 2)
    {
        return C_TRUE;
    }

    return C_FALSE;
}

/*
  Purpose:  check to see if a hero and a flyer have collided
       in:  pointer to PositionType
       in:  pointer to EscapeType
   return:  the hero that was collided with
*/
HeroType *checkForCollision(PositionType *pos, EscapeType *hollow)
{
    for (int i = 0; i < hollow->heroes.size; ++i)
    {
        HeroType *hero = hollow->heroes.elements[i];
        if (hero != NULL && !hero->dead && hero->partInfo.pos.row == pos->row && hero->partInfo.pos.col == pos->col)
        {
            return hero;
        }
    }

    return NULL;
}

/*
  Purpose:  inflict damage to the collieded hero
   in-out:  pointer to HeroType
       in:  pointer to FlyerType
   return:
*/
void incurDamage(HeroType *hero, FlyerType *flyer)
{
    hero->health -= flyer->strength;

    if (hero->health <= 0)
    {
        hero->health = 0;
    }

    if (hero->health == 0)
    {
        hero->dead = C_TRUE;
        hero->partInfo.avatar = '+';
    }
}