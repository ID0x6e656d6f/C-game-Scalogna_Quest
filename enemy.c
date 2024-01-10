#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#include "enemy.h"

const char *nomiCattivi[] = {
    "Bowser",
    "Ganondorf",
    "Sephiroth",
    "Albert Wesker",
    "Darth Vader",
    "GLaDOS",
    "Handsome Jack",
    "Kefka Palazzo",
    "Shao Kahn",
    "Vaas Montenegro",
    "Spaventapasseri",
    "Jigglypuff",
    "The Joker",
    "Saren Arterius",
    "Arthas Menethil",
    "Andrew Ryan",
    "Alduin",
    "Pyramid Head",
    "Magus",
    "Skeletor",
    "M. Bison",
    "Dr. Robotnik",
    "Chak’lok",
    "Carmen Sandiego",
    "Xehanort",
    "Diablo",
    "Raul Menendez",
    "Pagan Min",
    "Jack of Blades",
    "Mother Brain",
    "Shredder",
    "Vladimir Makarov",
    "Cyrus Temple",
    "The Illusive Man",
    "crota",
    "Blinky",
    "Doomslayer",
    "Capitano Servitore Skiff",
    "Ridley",
    "Queen Myrrah",
    "The Flood",
    "Vorselon",
    "Vaas Montenegro",
    "The Covenant",
    "Bowser Jr.",
    "Kamek",
    "King K. Rool"};

void enemyGeneration(Abitante *enemy, int level)
{
    int pos = rand() % (sizeof(nomiCattivi) / sizeof(nomiCattivi[0]));

    if (strcmp(nomiCattivi[pos], "Doomslayer") == 0)
    {
        strcpy((enemy->nome), nomiCattivi[pos]);
        enemy->p_vita = 10;
        enemy->dadi_attacco = 4 + (level % 2);
        enemy->dadi_difesa = 4 + (level % 2);
    }
    else if (strcmp(nomiCattivi[pos], "Jigglypuff") == 0)
    {
        strcpy((enemy->nome), nomiCattivi[pos]);
        enemy->p_vita = 10;
        enemy->dadi_attacco = 3 + (level % 2);
        enemy->dadi_difesa = 2 + (level % 2);
    }
    else
    {
        strcpy((enemy->nome), nomiCattivi[pos]);
        enemy->p_vita = 3;
        enemy->dadi_attacco = 3 + (level % 2);
        enemy->dadi_difesa = 2 + (level % 2);
    }
}

void stmpEnemy(Abitante *enemy)
{
    printf("%s:\n", enemy->nome);
    printf("Punti vita -> %d\n", enemy->p_vita);
    printf("Dadi attacco -> %d\n", enemy->dadi_attacco);
    printf("Dadi difesa -> %d\n", enemy->dadi_difesa);
}