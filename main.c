#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "gamelib.h"
#include "terminallib.h"
#include "players.h"
#include "maps.h"

bool created = false;

int main()
{
    time_t t;
    srand((unsigned)time(&t));
    clear();

    int tmpChoice = 0;

    do
    {

        do
        {

            yellow();
            bold();

            printf("███████╗ ██████╗ █████╗ ██╗      ██████╗  ██████╗ ███╗   ██╗ █████╗        ██████╗ ██╗   ██╗███████╗███████╗████████╗\n");
            printf("██╔════╝██╔════╝██╔══██╗██║     ██╔═══██╗██╔════╝ ████╗  ██║██╔══██╗      ██╔═══██╗██║   ██║██╔════╝██╔════╝╚══██╔══╝\n");
            printf("███████╗██║     ███████║██║     ██║   ██║██║  ███╗██╔██╗ ██║███████║█████╗██║   ██║██║   ██║█████╗  ███████╗   ██║   \n");
            printf("╚════██║██║     ██╔══██║██║     ██║   ██║██║   ██║██║╚██╗██║██╔══██║╚════╝██║▄▄ ██║██║   ██║██╔══╝  ╚════██║   ██║   \n");
            printf("███████║╚██████╗██║  ██║███████╗╚██████╔╝╚██████╔╝██║ ╚████║██║  ██║      ╚██████╔╝╚██████╔╝███████╗███████║   ██║   \n");
            printf("╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝       ╚══▀▀═╝  ╚═════╝ ╚══════╝╚══════╝   ╚═╝   \n");

            printf("\n**Through the Fire and Flames di sottofondo**\n");
            reset();
            cyan();
            printf("\n[1]Imposta Gioco");
            reset();
            printf("%s", ((created) ? "\n[2]Gioca" : "")); // if the map has not been created, the user cannot choose the play option. Input check carried out anyway
            red();
            printf("\n[3]Termina gioco \n");

            reset();

            scanf("%d", &tmpChoice);

            while (getchar() != '\n')
                ;
            clear();
        } while ((tmpChoice < 1 || tmpChoice > 5) && !isdigit(tmpChoice));

        clear();

        switch (tmpChoice)
        {
        case 1:
            clear();
            imposta_gioco();
            break;
        case 2:
            if (created)
            {
                gioca();
            }
            else
            {
                clear();
                bgRed();
                printf("Mappa non ancora creata e giocatori non ancora inseriti, hai mancato un pò di step mio caro Game Master...\n");
                reset();
            }
            break;
        case 3:
            termina_gioco();
            break;
        default:
            bgRed();
            printf("Input errato. Ricontrolla che sia nell'intervallo 1-3\n");
            reset();
            break;
        }

    } while (tmpChoice < 1 || tmpChoice > 3 || tmpChoice != 3);

    return 0;
}
