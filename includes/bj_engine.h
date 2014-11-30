//En ce qui concerne les valeurs de cartes
typedef enum {deux = 2, trois, quatre, cinq, six, sept, huit, neuf, dix, valet, dame, roi, as = 1} t_valeur;
typedef enum {coeurs, carreaux, piques, trefles} t_couleur;

typedef struct {t_valeur valeur; t_couleur couleur; } t_carte;
typedef struct {long solde; long mise; t_carte jeu[10]; int nbCard; int points;} t_joueur;

extern long MinimalBet, MaximalBet;
extern short NbBot;

extern t_joueur joueurs[8]; //7 joueurs max. + croupier

extern t_carte tas[56];
extern int nbCard_tas;


/* Prototype des fonctions BJ_ */
int BJ_getScore(int id);
void BJ_setBotAction(int id);
int BJ_setBet(int id, long bet);
void BJ_setMonney(int id, long solde);
int BJ_getPStatus(int id);
void BJ_attrCard(int id);
int BJ_setGameProperties(long MiseMin, long MiseMax, short NbrBot);
void BJ_setCards();
int Random (int _iMin, int _iMax);