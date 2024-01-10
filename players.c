#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "gamelib.h"
#include "terminallib.h"
#include "players.h"
#include "maps.h"

// metodi del giocatore
void stmpPlayers(Giocatore *arrayGiocatori)
{
    for (int i = 0; i < sizeof(arrayGiocatori); i++)
    {
        char *tmpNome = (arrayGiocatori + i)->nome;
        if (strcmp(tmpNome, ""))
        {
            printf("%s->%s, pv->%d, mente->%d\n", (arrayGiocatori + i)->nome, classConverter((arrayGiocatori + i)->classe), (arrayGiocatori + i)->p_vita, (arrayGiocatori + i)->mente);
        }
    }
}
char *classConverter(int class)
{
    switch (class)
    {
    case 0:
        return "barbaro";
        break;
    case 1:
        return "nano";
        break;
    case 2:
        return "elfo";
        break;
    case 3:
        return "mago";
        break;
    default:
        return "errore";
        break;
    }
}

void stmpPlayableClasses()
{
    bgRed();
    printf("\n!ATTENZIONE!\nScegli accuratamente il tuo personaggio però!\nOgni personaggio ha le sue abilità precise con tanto di bonus e malus...\n\n");
    reset();

    purple();
    printf("[1] Barbaro: un barbaro dalle pelli selvagge, porta sulle spalle le cicatrici delle sue molte battaglie. Con un'ascia ornata e lo sguardo come fuoco, è il selvaggio guardiano delle terre selvagge, dove il suo ruggito è leggenda.\n");
    printf("Le sue caratteristiche sono:\n3 DADI ATTACCO, 2 DADI DIFESA, 8 PUNTI VITA, 1/2 DI MENTE, 0 POTERE SPECIALE\n\n");

    green();
    printf("[2] Nano: un nano dal elmo gemmato e barba intricata, brandisce un'ascia fiammeggiante nelle viscere delle montagne, protetto dalla sua corazza d'acciaio.\n");
    printf("Le sue caratteristiche sono:\n2 DADI ATTACCO, 2 DADI DIFESA, 7 PUNTI VITA, 2/3 DI MENTE, 1 POTERE SPECIALE\n\n");

    blue();
    printf("[3] Elfo: un elfo dai capelli argentei e occhi acuti, danza tra gli alberi con una freccia letale. Avvolta in una veste di foglie, è la guardiana degli antichi boschi.\n");
    printf("Le sue caratteristiche sono:\n2 DADI ATTACCO, 2 DADI DIFESA, 6 PUNTI VITA, 3/4 DI MENTE, 1 POTERE SPECIALE\n\n");

    white();
    printf("[4] Stregone: un mago dal mantello stellato e bacchetta d'avorio, custodisce il mistero. Il suo sguardo saggio rivela la conoscenza di mondi oltre il visibile.\n");
    printf("Le sue caratteristiche sono:\n1 DADI ATTACCO, 2 DADI DIFESA, 4 PUNTI VITA, 4/5 DI MENTE, 3 POTERE SPECIALE\n\n");
    reset();
}
