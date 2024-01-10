typedef struct Abitante
{
    char nome[64];
    char p_vita;
    unsigned char dadi_attacco;
    unsigned char dadi_difesa;
} Abitante;

void enemyGeneration(Abitante *enemy, int level);
void stmpEnemy(Abitante *enemy);
