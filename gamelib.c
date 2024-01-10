#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#include "gamelib.h"
#include "terminallib.h"
#include "players.h"
#include "enemy.h"
#include "maps.h"

/*
+-------------------------+
|    dichiarazione metodi     |
+-------------------------+
*/

static void inserisci_zona(Zona_segrete **pFirst, Zona_segrete **pLast);
static void headInsertion(Zona_segrete *zona);
static void tailInsertion(Zona_segrete *zona);
static void posInsertion(Zona_segrete *zona, int index);
static void playerLoader();

static int throwDice(int n);
static bool isGenerated(int n, int turnArray[]);
static void stmpTurns(int turnArray[]);
static void turnRandomizer(int turnArray[]);
static void stampa_giocatore(int player);
static void stampa_zona(int player);
static void avanza(int player);
static void indietreggia(int player);
static void prendi_tesoro(int player);
static bool scappa(int player);
static void apri_porta(int player);
static void combatti(int player);
static void gioca_potere_speciale(int player);
static void attack(int player, Abitante *enemy, int turn);
static bool winCheck();
static bool deathCheck();

Giocatore arrayGiocatori[4];
Zona_segrete *pFirst;
Zona_segrete *pLast;
extern bool created;
unsigned int zoneCounter = 0;
int nGiocatori;
int level = 0;

/*
+-------------------------+
|    Player Methods       |
+-------------------------+
*/
void playerLoader()
{
    do
    {
        bgCyan();
        printf("L'avventura comincia avventurieri. Quanti siete nella squadra? (max 4 players)\n");
        reset();

        scanf("%d", &nGiocatori);
        clear();
        while (getchar() != '\n')
            ;
    } while ((nGiocatori < 1 || nGiocatori > 4) && !isdigit(nGiocatori));

    for (int i = 0; i < nGiocatori; i++)
    {
        Giocatore *tmpGc = (Giocatore *)malloc(sizeof(struct Giocatore));
        bgCyan();
        printf("\nQual'è il tuo nome?  %i ", i + 1);
        reset();

        scanf("%s", tmpGc->nome);

        clear();

        int classChoice;

        do
        {
            printf("Benissimo %s, ora la parte più importante...Adesso sta a te la scelta della tua razza.\n", tmpGc->nome);

            stmpPlayableClasses();

            scanf("%d", &classChoice);
            while (getchar() != '\n')
                ;
            clear();
        } while ((classChoice < 1 || classChoice > 4) && !isdigit(classChoice));
        switch (classChoice)
        {
        case 1:
            tmpGc->classe = barbaro;
            tmpGc->dadi_attacco = 3;
            tmpGc->dadi_difesa = 2;
            tmpGc->p_vita = 8;
            tmpGc->mente = rand() % 2 + 1;
            tmpGc->potere_speciale = 0;
            tmpGc->posizione = 0;
            break;
        case 2:
            tmpGc->classe = nano;
            tmpGc->dadi_attacco = 2;
            tmpGc->dadi_difesa = 2;
            tmpGc->p_vita = 7;
            tmpGc->mente = rand() % 2 + 2;
            tmpGc->potere_speciale = 1;
            tmpGc->posizione = 0;
            break;
        case 3:
            tmpGc->classe = elfo;
            tmpGc->dadi_attacco = 2;
            tmpGc->dadi_difesa = 2;
            tmpGc->p_vita = 6;
            tmpGc->mente = rand() % 2 + 3;
            tmpGc->potere_speciale = 1;
            tmpGc->posizione = 0;
            break;
        case 4:
            tmpGc->classe = mago;
            tmpGc->dadi_attacco = 1;
            tmpGc->dadi_difesa = 2;
            tmpGc->p_vita = 4;
            tmpGc->mente = rand() % 2 + 4;
            tmpGc->potere_speciale = 3;
            tmpGc->posizione = 0;
            break;
        default:
            break;
        }
        bool tmpEnd = false;
        while ((tmpGc->mente > 0 && tmpGc->p_vita > 1) && !tmpEnd)
        {
            int tmpChoice = 0;
            do
            {
                printf("%s->%s, pv->%d, mente->%d\n", tmpGc->nome, classConverter(tmpGc->classe), tmpGc->p_vita, tmpGc->mente);
                printf("Trade offer:\n[1]Sacrifica un punto mente per un punto vita\n[2]Sacrifica un punto vita per un punto mente\n[3]Rifiuta e vai avanti\n");
                scanf("%d", &tmpChoice);
                while (getchar() != '\n')
                    ;
                clear();
            } while ((tmpChoice < 1 || tmpChoice > 3) && !isdigit(tmpChoice));
            switch (tmpChoice)
            {
            case 1:
                tmpGc->mente = tmpGc->mente - 1;
                tmpGc->p_vita = tmpGc->p_vita + 1;
                break;
            case 2:
                tmpGc->mente = tmpGc->mente + 1;
                tmpGc->p_vita = tmpGc->p_vita - 1;
                break;
            case 3:
                tmpEnd = true;
                break;
            default:
                printf("Errore nell'input, controlla che sia corretto");
                while (getchar() != '\n')
                    ;
                getchar();
                break;
            }
            clear();
        }
        tmpGc->posizione_mappa = 0;
        *(arrayGiocatori + i) = *tmpGc;
        free(tmpGc);
        clear();
        stmpPlayers(arrayGiocatori);
    }
}

/*
+-------------------------+
|    Map methods          |
+-------------------------+
*/
static void genera_mappa()
{
    for (int i = 0; i < 15; i++)
    {
        Zona_segrete *zona = (Zona_segrete *)malloc(sizeof(Zona_segrete));
        int tipo = rand() % 10;
        int tesoro = rand() % 4;
        int porta = rand() % 3;

        (zona)->zona = tipo;
        (zona)->tesoro = tesoro;
        (zona)->porta = porta;
        (zona)->zona_precedente = NULL;
        (zona)->zona_successiva = NULL;
        (zona)->tesoro_preso = false;
        if (pFirst == NULL && i == 0)
        {
            headInsertion(zona);
        }
        else if (pLast == NULL && i == 14)
        {
            pLast = (zona);
            tailInsertion(zona);
        }
        else
        {
            posInsertion(zona, i);
        }
    }
    for (int i = 0; i < nGiocatori; i++)
    {
        (arrayGiocatori + i)->posizione = pFirst;
    }
}

static void headInsertion(Zona_segrete *zona)
{
    if (pFirst == NULL)
    {
        pFirst = zona;
    }
    else
    {
        zona->zona_successiva = pFirst;
        (pFirst)->zona_precedente = zona;
        pFirst = zona;
    }
    zoneCounter++;
}

static void posInsertion(Zona_segrete *zona, int index)
{
    Zona_segrete *tmpCurrent = pFirst;
    unsigned int tmpCounter = 1;

    while (tmpCurrent != NULL && tmpCounter < index)
    {
        tmpCurrent = tmpCurrent->zona_successiva;
        tmpCounter++;
    }

    if (tmpCurrent == NULL)
    {
        printf("errore nella posizione\n");
        free(zona);
    }
    else
    {
        zona->zona_precedente = tmpCurrent;
        if (tmpCurrent->zona_successiva != NULL)
        {
            zona->zona_successiva = tmpCurrent->zona_successiva;
            tmpCurrent->zona_successiva->zona_precedente = zona;
        }
        tmpCurrent->zona_successiva = zona;

        zoneCounter++;
    }
}

static void tailInsertion(Zona_segrete *zona)
{
    Zona_segrete *tmpCurrent = pFirst;
    Zona_segrete *tmpPrev = NULL;

    while (tmpCurrent != NULL)
    {
        tmpPrev = tmpCurrent;
        tmpCurrent = tmpCurrent->zona_successiva;
    }
    tmpPrev->zona_successiva = zona;
    zona->zona_precedente = tmpPrev;

    pLast = zona;

    zoneCounter++;
}

static void inserisci_zona(Zona_segrete **pFirst, Zona_segrete **pLast)
{
    clear();

    int tipo = rand() % 10;
    int tesoro = rand() % 4;
    int porta = rand() % 3;

    Zona_segrete *zona = (Zona_segrete *)malloc(sizeof(Zona_segrete));

    (zona)->zona = tipo;
    (zona)->tesoro = tesoro;
    (zona)->porta = porta;
    (zona)->zona_precedente = NULL;
    (zona)->zona_successiva = NULL;
    (zona)->tesoro_preso = false;

    int pos;

    while (true)
    {
        do
        {
            printf("Inerisci la posizione in cui dovrà stare la zona\n ricorda, la zona deve essere compresa tra 0 e %d\n", (zoneCounter));
            scanf("%d", &pos);
            while (getchar() != '\n')
                ;
        } while ((pos < 0 || pos > zoneCounter) && !isdigit(pos));
        if (pos == 0)
        {
            headInsertion(zona);
            break;
        }
        else if (pos > 0 && pos < zoneCounter)
        {
            posInsertion(zona, pos);
            break;
        }
        else if (pos == zoneCounter)
        {
            tailInsertion(zona);
            break;
        }
        else
        {
            while (getchar() != '\n')
                ;
            clear();
            red();
            printf("Numero sbagliato, premi invio ora e inseriscilo di nuovo\n");
            reset();
        }
    }
    clear();
}

static void headDeletion()
{
    Zona_segrete *tmpZone = pFirst->zona_successiva;
    tmpZone->zona_precedente = NULL;
    free(pFirst);
    pFirst = tmpZone;
    zoneCounter--;
}

static void tailDeletion()
{
    Zona_segrete *tmpZone = pLast->zona_precedente;
    tmpZone->zona_successiva = NULL;
    free(pLast);
    pLast = tmpZone;
    zoneCounter--;
}

static void posDeletion(int index)
{
    Zona_segrete *tmpCurrent = pFirst;

    for (int i = 0; i < index; i++)
    {
        tmpCurrent = tmpCurrent->zona_successiva;
    }

    if (tmpCurrent == NULL)
    {
        printf("errore nella posizione\n");
    }
    else
    {

        tmpCurrent->zona_successiva->zona_precedente = tmpCurrent->zona_precedente;
        tmpCurrent->zona_precedente->zona_successiva = tmpCurrent->zona_successiva;
        free(tmpCurrent);

        zoneCounter--;
    }
}

static void cancella_zona()
{
    clear();
    red();
    printf("Cancellazione zona\n");
    reset();
    stmpZone(pFirst);

    while (true)
    {

        int pos = 0;
        printf("\nInerisci la posizione che dovrà essere eliminata\n Ricorda, la zona deve essere compresa tra 0 e %d", (zoneCounter));
        scanf("%d", &pos);

        if (pos == 0)
        {
            headDeletion();
            break;
        }
        else if (pos > 0 && pos < zoneCounter)
        {
            posDeletion(pos);
            break;
        }
        else if (pos == zoneCounter)
        {
            tailDeletion();
            break;
        }
        else
        {
            clear();
            red();
            printf("numero sbagliato, inseriscilo di nuovo\n");
            reset();
        }
    }
    clear();
}

static void mapsMenu()
{

    int tmpChoice = 0;
    bool isOk = false;

    while (isOk != true)
    {
        do
        {
            bgCyan();
            printf("Menu della mappa.\n");
            printf("Cosa vuoi fare game master?");
            reset();
            printf("\n\n");
            if (!created)
            {
                printf("[1] Genera Mappa\n");
            }
            if (created)
            {
                printf("[2] Inserisci zona\n");
                printf("[3] Cancella zona\n");
                printf("[4] Stampa mappa\n");
                printf("[5] Chiudi Mappa\n");
            }
            scanf("%d", &tmpChoice);

            while (getchar() != '\n')
                ;
            clear();
        } while ((tmpChoice < 1 || tmpChoice > 5) && !isdigit(tmpChoice));
        switch (tmpChoice)
        {
        case 1:
            if (!created)
            {
                clear();
                genera_mappa();
                created = true;
            }
            break;
        case 2:
            clear();
            inserisci_zona(&pFirst, &pLast);
            break;
        case 3:
            clear();
            if (zoneCounter <= 0)
            {
                red();
                printf("La mappa non è stata creata\n");
                reset();
            }
            else
            {
                cancella_zona();
            }
            break;
        case 4:
            clear();
            stmpZone(pFirst);
            break;
        case 5:
            clear();
            if (zoneCounter >= 15)
            {
                isOk = true;
            }
            else
            {
                red();
                printf("La mappa ha troppe poche zone\n");
                reset();
            }
            break;
        default:
            clear();
            while (getchar() != '\n')
                ;
            break;
        }
    }
}

/*
+-------------------------+
|    Metodi per il        |
|    proseguimento        |
|    del gioco            |
+-------------------------+
*/

static int throwDice(int n)
{
    return ((rand() % n) + 1);
}

static bool isGenerated(int n, int turnArray[])
{
    for (int i = 0; i < nGiocatori; i++)
    {
        if (turnArray[i] == n)
        {
            return true;
        }
    }
    return false;
}

static void stmpTurns(int turnArray[])
{
    printf("Turni: {");
    for (int i = 0; i < nGiocatori; i++)
    {
        if (turnArray[i] != -1)
        {
            printf(" %d ", turnArray[i]);
        }
    }
    printf("}\n\n");
}

static void turnRandomizer(int turnArray[])
{
    for (int i = 0; i < nGiocatori; i++)
    {
        turnArray[i] = -1;
    }

    int alive = 0;
    for (int i = 0; i < nGiocatori; i++)
    {
        if ((arrayGiocatori + i)->p_vita > 0)
        {
            alive++;
        }
    }

    for (int i = 0; i < alive; i++)
    {
        int tmpN = -1;
        do
        {
            tmpN = (rand() % nGiocatori);
        } while (isGenerated(tmpN, turnArray) || ((arrayGiocatori + tmpN)->p_vita <= 0));
        turnArray[i] = tmpN;
    }
}

static void stampa_giocatore(int player)
{
    printf("%s:\n", (arrayGiocatori + player)->nome);
    printf("Classe -> %s\n", classConverter((arrayGiocatori + player)->classe));
    printf("Punti vita -> %d\n", (arrayGiocatori + player)->p_vita);
    printf("Dadi attacco -> %d\n", (arrayGiocatori + player)->dadi_attacco);
    printf("Dadi difesa -> %d\n", (arrayGiocatori + player)->dadi_difesa);
    printf("Mente -> %d\n", (arrayGiocatori + player)->mente);
    printf("Potere speciale -> %d\n", (arrayGiocatori + player)->potere_speciale);
    printf("Posizione attuale -> %s\n", zoneConverter((arrayGiocatori + player)->posizione->zona));
    printf("-----------------------------------------------\n");
}

static void stampa_zona(int player)
{
    printf("%s\n", zoneConverter((arrayGiocatori + player)->posizione->zona));
    printf("%s; ", ((arrayGiocatori + player)->posizione->tesoro != 0) ? "Tesoro presente" : "Nessun tesoro");
    printf("%s\n\n", ((arrayGiocatori + player)->posizione->porta != 0) ? "Porta presente\n" : "Nessuna porta");
    printf("-----------------------------------------------\n");
}

static void apri_porta(int player)
{
    clear();
    printf("Oops! La stanza ha una porta!");
    printf("\nTira un");
    bgPurple();
    printf(" d%d ", 6);
    reset();
    printf("per vedere che succede\n");
    printf("[key]Lancia dado\n");
    while (getchar() != '\n')
        ;
    int diceResult = throwDice(6);

    bgPurple();
    printf("Risultato: %d\n", diceResult);
    reset();
    while (getchar() != '\n')
        ;
    if (diceResult <= ((arrayGiocatori + player)->mente))
    {
        (arrayGiocatori + player)->posizione = (arrayGiocatori + player)->posizione->zona_successiva;
        (arrayGiocatori + player)->posizione_mappa = (arrayGiocatori + player)->posizione_mappa + 1;
        (arrayGiocatori + player)->posizione->tesoro_preso = false;
        bgGreen();
        printf("Con le tue innate abilità di scassinatore riesci ad aprire la porta ed avanzi nella zona successiva\n");
        reset();
    }
    else
    {
        int effect = ((rand() % 100) + 1);
        if (effect <= 10)
        {
            bgRed();
            printf("La porta non è stata scassinata correttamente.\nI tuoi attrezzi si sono rotti.\nPreso dalla rabbia cerchi di uscire dal dungeon per andare a prendere delle cariche di esplosivo plastico per poi renderti conto che non è ancora stato inventato.\nTi ritrovi nella prima stanza a piangere\n");
            reset();
            (arrayGiocatori + player)->posizione = pFirst;
        }
        else if (effect > 10 && effect <= 60)
        {
            bgRed();
            printf("La porta non è stata scassinata correttamente.\nIn preda alla inizi a prendere a pugni la porta, svegliando un Abitante che era in pausa e che stava dormendo.\nSpalanca la porta, ti da un destro in faccia e la richiude.\nPerdi un punto vita");
            reset();
            (arrayGiocatori + player)->p_vita = ((arrayGiocatori + player)->p_vita) - 1;
        }
        else
        {
            bgRed();
            printf("La porta non è stata scassinata correttamente.\nAppare un abitante da combattere!\n\n");
            reset();
            combatti(player);
        }
    }
    while (getchar() != '\n')
        ;
    clear();
}

static void avanza(int player)
{
    if ((arrayGiocatori + player)->posizione->zona_successiva->porta != 0)
    {
        apri_porta(player);
    }
    else
    {
        (arrayGiocatori + player)->posizione = (arrayGiocatori + player)->posizione->zona_successiva;
        (arrayGiocatori + player)->posizione->tesoro_preso = false;
        (arrayGiocatori + player)->posizione_mappa = (arrayGiocatori + player)->posizione_mappa + 1;

        level++;
        if ((arrayGiocatori + player)->posizione->zona_successiva == NULL)
        {
            bgRed();
            printf("Complimenti giocatore, sei arrivato all'ultima stanza del dungeon.\nOra dovrai affrontare l'ultimo dei tuoi avversari.\n");
            reset();
            while (getchar() != '\n')
                ;
            combatti(player);
        }
        else
        {
            int prob = rand() % 3 + 1;
            if (prob == 1)
            {
                bgRed();
                printf("Nella stanza era presente un avversario...preparai a combatterlo\n");
                reset();
                combatti(player);
            }
        }
    }
}

static void indietreggia(int player)
{
    (arrayGiocatori + player)->posizione = (arrayGiocatori + player)->posizione->zona_precedente;
    (arrayGiocatori + player)->posizione->tesoro_preso = false;
    (arrayGiocatori + player)->posizione_mappa = (arrayGiocatori + player)->posizione_mappa - 1;
    int prob = rand() % 3 + 1;
    if (prob == 1)
    {
        bgRed();
        printf("Appare un abitante da combattere!\n");
        while (getchar() != '\n')
            ;
        getchar();
        combatti(player);
        reset();
    }
}

static void prendi_tesoro(int player)
{
    int eff = (arrayGiocatori + player)->posizione->tesoro;
    switch (eff)
    {
    case 0:
        printf("La stanza è vuota, non trovi alcun tesoro\n");
        break;
    case 1:
        printf("Hai aperto uno scrigno dall'aspetto celestiale e al suo interno trovi una bottitglia con una croce verde disegnata sopra.\nDecidi di fidarti del gioco e la bevi.\nDopo qualche minuto inizi a vomitare, controlli la bottiglia e scopri che era scaduta all'incirca 1000anni prima.\nPer fortuna hai vomitato prima che ti entrasse troppo in circolo, perdi solamente un punto vita.\n");
        (arrayGiocatori + player)->p_vita = (arrayGiocatori + player)->p_vita - 1;
        break;
    case 2:
        printf("Hai aperto uno scrigno dall'aspetto celestiale e al suo interno trovi una bottitglia con una croce verde disegnata sopra.\nDecidi di fidarti del gioco e la bevi.\nL'unghia scheggiata ti riscresce e guadagni un punto vita.\n");
        (arrayGiocatori + player)->p_vita = (arrayGiocatori + player)->p_vita + 1;
        break;
    case 3:
        printf("Hai aperto uno scrigno dall'aspetto celestiale e al suo interno trovi una bottitglia con una croce verde disegnata sopra.\nDecidi di fidarti del gioco e la bevi.\nTi senti subito al massimo delle tue forze e guadagni due punti vita.\nSicuro che non era dell'eroina?\n");
        (arrayGiocatori + player)->p_vita = (arrayGiocatori + player)->p_vita + 2;
        break;
    default:
        break;
    }
    (arrayGiocatori + player)->posizione->tesoro_preso = true;
}

static bool scappa(int player)
{
    clear();
    printf("\nTira un");
    bgPurple();
    printf(" d%d ", 6);
    reset();
    printf("per scappare\n");
    printf("[key]Lancia dado\n");
    while (getchar() != '\n')
        ;
    getchar();
    int diceResult = throwDice(6);

    bgPurple();
    printf("Risultato: %d\n", diceResult);
    reset();
    while (getchar() != '\n')
        ;

    if (diceResult <= (arrayGiocatori + player)->mente)
    {
        printf("Sei riuscito fortunatamente a scappare, torni nella zona successiva\n");
        (arrayGiocatori + player)->posizione = (arrayGiocatori + player)->posizione->zona_precedente;
        (arrayGiocatori + player)->posizione->tesoro_preso = false;
        (arrayGiocatori + player)->posizione_mappa = (arrayGiocatori + player)->posizione_mappa - 1;
        while (getchar() != '\n')
            ;
        return true;
    }
    else
    {
        printf("Non sei riuscito a scappare, torni al combattimento\n");
        while (getchar() != '\n')
            ;
        return false;
    }
}

static void attack(int player, Abitante *enemy, int turn)
{
    if (turn == 1)
    {
        int dmg = 0;
        printf("%s tocca a te tirare i dadi\nAttacchi con->", (arrayGiocatori + player)->nome);
        while (getchar() != '\n')
            ;
        for (int i = 0; i < (arrayGiocatori + player)->dadi_attacco; i++)
        {
            int res = throwDice(6);
            if (res <= 3)
            {
                dmg++;
            }
        }
        printf("%d", dmg);

        while (getchar() != '\n')
            ;

        int def = 0;
        for (int i = 0; i < enemy->dadi_difesa; i++)
        {
            int res = throwDice(6);

            if (res == 6)
            {
                def++;
            }
        }

        printf("\n%s si difende con %d", enemy->nome, def);

        while (getchar() != '\n')
            ;
        clear();

        if (dmg > def)
        {
            bgYellow();
            printf("Turno finito: %s ha perso %d punti vita\n", enemy->nome, (dmg - def));
            reset();
            enemy->p_vita = enemy->p_vita - (dmg - def);
        }
        else
        {
            bgYellow();
            printf("Turno finito, %s ha parato tutti i colpi\n", enemy->nome);
            reset();
        }
        while (getchar() != '\n')
            ;
    }
    else if (turn == 0)
    {
        int dmg = 0;
        for (int i = 0; i < enemy->dadi_attacco; i++)
        {
            int res = throwDice(6);

            if (res <= 3)
            {
                dmg++;
            }
        }
        printf("\n%s attacca con %d", enemy->nome, dmg);

        int def = 0;

        printf("\n%s tocca a te tirare i dadi\nTi difendi con con->", (arrayGiocatori + player)->nome);

        while (getchar() != '\n')
            ;

        for (int i = 0; i < (arrayGiocatori + player)->dadi_difesa; i++)
        {
            int res = throwDice(6);
            if (res <= 2)
            {
                def++;
            }
        }
        printf("%d\n", def);

        while (getchar() != '\n')
            ;
        clear();
        if (dmg > def)
        {
            bgRed();
            printf("Turno finito: %s hai perso %d punti vita\n", (arrayGiocatori + player)->nome, (dmg - def));
            reset();
            (arrayGiocatori + player)->p_vita = (arrayGiocatori + player)->p_vita - (dmg - def);
        }
        else
        {
            bgGreen();
            printf("Turno finito, %s hai parato tutti i colpi\n", (arrayGiocatori + player)->nome);
            reset();
        }

        while (getchar() != '\n')
            ;
    }
    else if (turn == 2)
    {
        int dmg = 0;
        for (int i = 0; i < enemy->dadi_attacco; i++)
        {
            int res = throwDice(6);

            if (res <= 3)
            {
                dmg++;
            }
        }
        printf("\n%s attacca con %d", enemy->nome, dmg);

        int def = 0;

        printf("\n%s tocca a te tirare i dadi\nTi difendi con con un numero di dadi dimezzato->", (arrayGiocatori + player)->nome);

        while (getchar() != '\n')
            ;

        for (int i = 0; i < ((arrayGiocatori + player)->dadi_difesa) / 2; i++)
        {
            int res = throwDice(6);
            if (res <= 2)
            {
                def++;
            }
        }
        printf("%d\n", def);

        while (getchar() != '\n')
            ;
        clear();
        if (dmg > def)
        {
            bgRed();
            printf("Turno finito: %s hai perso %d punti vita\n", (arrayGiocatori + player)->nome, (dmg - def));
            reset();
            (arrayGiocatori + player)->p_vita = (arrayGiocatori + player)->p_vita - (dmg - def);
        }
        else
        {
            bgGreen();
            printf("Turno finito, %s hai parato tutti i colpi\n", (arrayGiocatori + player)->nome);
            reset();
        }

        while (getchar() != '\n')
            ;
    }
}

static void combatti(int player)
{
    Abitante *enemy = (Abitante *)malloc(sizeof(struct Abitante));
    enemyGeneration(enemy, level);
    stmpEnemy(enemy);

    printf("Hai incontrato %s\n", enemy->nome);
    while (getchar() != '\n')
        ;
    clear();
    int playerThrow = throwDice(6);
    int enemyThrow = throwDice(6);
    bool isPlayer = (playerThrow >= enemyThrow) ? true : false;
    bool success;
    int cnt = 0;
    do
    {
        bold();
        printf("COMBATTIMENTO\n");
        reset();
        stmpEnemy(enemy);
        if (isPlayer)
        {
            printf("\nE' li tuo turno eroe:\n");
            printf("%s", (arrayGiocatori + player)->potere_speciale > 0 ? "[0]gioca potere speciale\n" : "");
            printf("[1]scappa\n");
            printf("[2]attacca\n");
            int tmpChoice;
            scanf("%d", &tmpChoice);
            switch (tmpChoice)
            {
            case 0:
                if ((arrayGiocatori + player)->potere_speciale > 0)
                {
                    gioca_potere_speciale(player);
                    success = true;
                    enemy->p_vita = 0;
                }
                break;
            case 1:
                success = scappa(player);
                if (success)
                {
                    if ((arrayGiocatori + player)->posizione_mappa == 0)
                    {
                        enemy->p_vita = 0;
                    }
                    else
                    {
                        (arrayGiocatori + player)->posizione = (arrayGiocatori + player)->posizione->zona_precedente;
                        (arrayGiocatori + player)->posizione_mappa = (arrayGiocatori + player)->posizione_mappa - 1;
                        (arrayGiocatori + player)->posizione->tesoro_preso = false;
                    }
                }
                else
                {
                    attack(player, enemy, 2);
                }
                break;
            case 2:
                attack(player, enemy, 1);
                break;
            default:
                break;
            }
            isPlayer = false;
            cnt++;
        }
        else
        {
            printf("\nE' li turno dell'avversario:\n");
            attack(player, enemy, 0);
            isPlayer = true;
            cnt++;
        }
        if (cnt >= 2)
        {
            cnt = 0;
            playerThrow = throwDice(6);
            enemyThrow = throwDice(6);
            isPlayer = (playerThrow >= enemyThrow) ? true : false;
        }
    } while ((arrayGiocatori + player)->p_vita > 0 && enemy->p_vita > 0 && !success);
    free(enemy);
}

static void gioca_potere_speciale(int player)
{
    (arrayGiocatori + player)->potere_speciale = (arrayGiocatori + player)->potere_speciale - 1;
}

static bool winCheck()
{
    for (int i = 0; i < nGiocatori; i++)
    {
        if ((arrayGiocatori + i)->posizione->zona_successiva == NULL)
        {
            return true;
        }
    }
    return false;
}

static bool deathCheck()
{
    if ((arrayGiocatori + 0)->p_vita > 0 || (arrayGiocatori + 1)->p_vita > 0 || (arrayGiocatori + 2)->p_vita > 0 || (arrayGiocatori + 3)->p_vita > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/*
+-------------------------+
|Metodo per impostazione  |
|    del gioco            |
+-------------------------+
*/
void imposta_gioco()
{
    playerLoader();

    clear();

    mapsMenu();
}

/*
+-------------------------+
|  Metodo main del gioco  |
+-------------------------+
*/
void gioca()
{
    int turnCicler = 0;
    int turnArray[4];
    do
    {
        clear();
        turnRandomizer(turnArray);
        bool moved = false;
        do
        {
            int tmpChoice = 0;
            stmpTurns(turnArray);
            int actualPlayer = (turnArray[turnCicler]);
            bool isFirstZone = (arrayGiocatori + actualPlayer)->posizione == pFirst;
            do
            {
                reset();
                printf("%s cosa desideri fare?\n", (arrayGiocatori + actualPlayer)->nome);

                printf("%s", (moved) ? "" : "[1]avanza\n");
                printf("%s", (isFirstZone) ? "" : "[2]indietreggia\n");
                printf("[3]Stampa info Giocatore\n");
                printf("[4]Stampa info Zona Attuale\n");
                printf("[5]Prendi tesoro\n");
                printf("[6]passa turno\n");

                scanf("%d", &tmpChoice);

                while (getchar() != '\n')
                    ;
                clear();

                printf("Errore nell'input\n");
            } while (((tmpChoice < 1 || tmpChoice > 6) && !isdigit(tmpChoice)) || (moved && (tmpChoice == 1)) || (isFirstZone && (tmpChoice == 2)));
            clear();

            switch (tmpChoice)
            {
            case 1:
                moved = true;
                avanza(actualPlayer);
                break;
            case 2:
                indietreggia(actualPlayer);
                break;
            case 3:
                stampa_giocatore(actualPlayer);
                break;
            case 4:
                stampa_zona(actualPlayer);
                break;
            case 5:
                prendi_tesoro(actualPlayer);
                break;
            case 6:
                printf("Hai passato il turno\n");
                while (getchar() != '\n')
                    ;
                break;
            default:
                break;
            }

            if (tmpChoice == 6 || (((arrayGiocatori + actualPlayer)->p_vita <= 0)))
            {
                turnCicler++;
                moved = false;
            }

        } while (turnCicler < (nGiocatori) && !winCheck() && !deathCheck());
        if (level <= 7)
        {
            level++;
            clear();
        }
        turnCicler = 0;
    } while (!winCheck() && !deathCheck());

    printf("game finito");

    while (getchar() != '\n')
        ;
}

void termina_gioco()
{
    red();
    printf("Con le tenebre pronte a prendere il controllo i nostri eroi ci abbandonano, lasciando il nostro mondo nelle mani della distruzione.\nQuelli che un tempo potevano essere i nostri eroi, ora verranno ricordati come dei miserabili vigliacchi pronti a sacrificare il nostro mondo per non si sa far bene cosa...\nshame\n");
    reset();
}