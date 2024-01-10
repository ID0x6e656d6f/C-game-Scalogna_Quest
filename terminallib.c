#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "terminallib.h"

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define BLINK "\033[5m"

#define RED "\033[31m"
#define GREEN "\033[32m" //nano
#define YELLOW "\033[33m"
#define BLUE "\033[34m"  //elfo
#define PURPLE "\033[35m" //barbaro
#define CYAN "\033[36m"
#define WHITE "\033[37m" //stregone

#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_PURPLE "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

void bold()
{
    printf(BOLD);
}

void bgRed()
{
    printf(BG_RED);
}

void bgGreen()
{
    printf(BG_GREEN);
}

void bgYellow()
{
    printf(BG_YELLOW);
}

void bgBlue()
{
    printf(BG_BLUE);
}

void bgPurple()
{
    printf(BG_PURPLE);
}

void bgCyan()
{
    printf(BG_CYAN);
}

void bgWhite()
{
    printf(BG_WHITE);
}

void red()
{
    printf(RED);
}
void green()
{
    printf(GREEN);
}
void yellow()
{
    printf(YELLOW);
}
void blue()
{
    printf(BLUE);
}
void purple()
{
    printf(PURPLE);
}
void cyan()
{
    printf(CYAN);
}
void white()
{
    printf(WHITE);
}

void reset()
{
    printf(RESET);
}

void clear()
{
    system("clear");
}