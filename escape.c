#include <stdio.h>

#include "defs.h"

void runEscape();                      // done
int escapeIsOver(EscapeType *);        // done
void initEscape(EscapeType *);         // done
void handleEscapeResult(EscapeType *); // done
void cleanupEscape(EscapeType *);      // done

/*
  Purpose:  runs the actual game with a loop, calling all the neseccary functions
       in:
   return:
*/
void runEscape()
{

    EscapeType hollow;

    initEscape(&hollow);

    while (!escapeIsOver(&hollow))
    {
        int probability1 = randomInt(100);
        int probability2 = randomInt(100);
        if (probability1 < BIRD_SPAWN_RATE)
        {
            int row = randomInt(5);
            int col = randomInt(MAX_COL);
            int strength = randomInt(3) + 3;

            spawnFlyer(&hollow, 'v', row, col, strength);
        }

        if (probability2 < MONKEY_SPAWN_RATE)
        {
            int row = randomInt(15);
            int col = randomInt(MAX_COL);
            int strength = randomInt(4) + 8;

            spawnFlyer(&hollow, '@', row, col, strength);
        }

        for (int i = 0; i < hollow.heroes.size; ++i)
        {
            moveHero(hollow.heroes.elements[i], &hollow);
        }

        for (int i = 0; i < hollow.flyers.size; ++i)
        {
            moveFlyer(hollow.flyers.elements[i], &hollow);
            FlyerType *flyer = hollow.flyers.elements[i];
            HeroType *collisionHero = checkForCollision(&(flyer->partInfo.pos), &hollow);
            if (collisionHero != NULL)
            {
                incurDamage(collisionHero, flyer);
            }
        }
        system("clear");
        outputHollow(&hollow);
        for (int i = 0; i < hollow.heroes.size; ++i)
        {
            printf(" %s[%d]", hollow.heroes.elements[i]->name, hollow.heroes.elements[i]->health);
        }
        printf("\n");
        usleep(100000);
    }
    handleEscapeResult(&hollow);
    cleanupEscape(&hollow);
}

/*
  Purpose:  checks if the heroes are either dead or escaped
       in:  pointer to EscapeType
   return:  1 or 0 depending on if true or not
*/
int escapeIsOver(EscapeType *hollow)
{
    for (int i = 0; i < hollow->heroes.size; ++i)
    {
        HeroType *hero = hollow->heroes.elements[i];

        int heroSafe = heroIsSafe(hero);
        int heroDead = hero->dead;

        if (!heroSafe && !heroDead)
        {
            return C_FALSE;
        }
    }
    return C_TRUE;
}

/*
  Purpose:  initalizes the escape where all elements are intilized
       in:  pointer to EscapeType
   return:
*/
void initEscape(EscapeType *hollow)
{

    srand((unsigned)time(NULL));

    hollow->heroes.elements = malloc(sizeof(HeroType *) * MAX_ARR);
    if (hollow->heroes.elements == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed for heroes.\n");
    }

    hollow->heroes.size = 0;
    hollow->flyers.size = 0;

    HeroType *hero1, *hero2;

    initHero(&hero1, 'T', MAX_ROW - 2, "Timmy");
    initHero(&hero2, 'H', MAX_ROW - 2, "Harold");

    addHero(&(hollow->heroes), hero1);
    addHero(&(hollow->heroes), hero2);

    hollow->listenSocket = -1;
    hollow->viewSocket = -1;
    //  setupServerSocket(&hollow->listenSocket);
    //  acceptConnection(hollow->listenSocket, &hollow->viewSocket);
}

/*
  Purpose:  prints the outcome of the game depending on what happens
       in:  pointer to EscapeType
   return:
*/
void handleEscapeResult(EscapeType *hollow)
{
    int hero1Escaped = 0;
    int hero2Escaped = 0;
    int hero1Dead = 0;
    int hero2Dead = 0;

    for (int i = 0; i < hollow->heroes.size; ++i)
    {
        HeroType *hero = hollow->heroes.elements[i];

        if (!hero->dead && heroIsSafe(hero))
        {
            if (i == 0)
            {
                hero1Escaped = 1;
                printf("%s has successfully escaped!\n", hero->name);
            }
            else
            {
                hero2Escaped = 1;
                printf("%s has successfully escaped!\n", hero->name);
            }
        }
        else if (hero->dead)
        {
            if (i == 0)
            {
                hero1Dead = 1;
                printf("%s has died.\n", hero->name);
            }
            else
            {
                hero2Dead = 1;
                printf("%s has died.\n", hero->name);
            }
        }
    }

    if ((hero1Escaped || hero1Dead) && (hero2Escaped || hero2Dead))
    {
        printf("Game over.\n");
    }
}

/*
  Purpose:  cleans up all the dynamically allocated memory
       in:  pointer to EscapeType
   return:
*/
void cleanupEscape(EscapeType *hollow)
{
    for (int i = 0; i < hollow->heroes.size; ++i)
    {
        free(hollow->heroes.elements[i]);
    }

    free(hollow->heroes.elements);

    for (int i = 0; i < hollow->flyers.size; ++i)
    {
        free(hollow->flyers.elements[i]);
    }

    if (hollow->viewSocket >= 0)
    {
        sendData(hollow->viewSocket, "QUIT\n");
    }

    close(hollow->listenSocket);
    close(hollow->viewSocket);
}
