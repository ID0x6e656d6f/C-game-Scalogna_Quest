#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "gamelib.h"
#include "terminallib.h"
#include "players.h"
#include "maps.h"

extern unsigned int zoneCounter;

// metodi della mappa
char *zoneConverter(int class)
{
    switch (class)
    {
    case 0:
        return ("corridoio");
        break;
    case 1:
        return ("scala");
        break;
    case 2:
        return ("sala_banchetto");
        break;
    case 3:
        return ("magazzino");
        break;
    case 4:
        return ("giardino");
        break;
    case 5:
        return ("posto_guardia");
        break;
    case 6:
        return ("prigione");
        break;
    case 7:
        return ("cucina");
        break;
    case 8:
        return ("armeria");
        break;
    case 9:
        return ("tempio");
        break;
    default:
        return ("errore");
        break;
    }
}
char *tesoroConverter(int tesoro)
{
    switch (tesoro)
    {
    case 0:
        return ("nessun_tesoro");
        break;
    case 1:
        return ("veleno");
        break;
    case 2:
        return ("guarigione");
        break;
    case 3:
        return ("doppia_guarigione");
        break;
    default:
        return ("errore");
        break;
    }
}
char *portaConverter(int porta)
{
    switch (porta)
    {
    case 0:
        return ("Nessuna porta");
        break;
    case 1:
        return ("Porta normale");
        break;
    case 2:
        return ("Porta da scassinare");
        break;
    default:
        return ("errore");
        break;
    }
}
void stmpZone(Zona_segrete *pFirst)
{
    Zona_segrete *tmpCurrent = pFirst;
    int i = 0;

    while (i < zoneCounter || (tmpCurrent)->zona_successiva != NULL)
    {
        printf("\nZona %d: %s, %s, %s\n", i, zoneConverter((tmpCurrent)->zona), tesoroConverter((tmpCurrent)->tesoro), portaConverter((tmpCurrent)->porta));

        if (((tmpCurrent)->zona_precedente) != NULL)
            printf("%s\n", portaConverter((tmpCurrent)->zona_precedente->porta));

        if (((tmpCurrent)->zona_successiva) != NULL)
        {
            printf("%s\n", portaConverter((tmpCurrent)->zona_successiva->porta));
            tmpCurrent = tmpCurrent->zona_successiva;
        }

        printf("\n");

        i++;
    }
}