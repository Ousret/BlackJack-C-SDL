/**
* \file Black_jack.c
* \brief Les fonctions de bases du programme de black jack
* \author Groupe 4 du TP6
* \version 1.0
* \date 21 Octobre 2014
*
*/
// définition des différents états d'une carte du jeu de cartes
#define LIBRE 0 // la carte est piochable
#define PRISE 1 // la carte est dans une main
#define CACHEE 2 // la carte est possédée mais n'est pas visible

// définition des différents joueurs
#define JOUEUR 3
#define BANQUE 4

// definition d'une énumération contenant les valeurs d'une carte // option nous sert d'indice pour nb_carte
typedef enum {as, deux, trois, quatre, cinq, six, sept, huit, neuf, dix, valet, dame, roi} t_valeur;

// definition d'une énumération contenant la couleur d'une carte 
typedef enum {coeurs, carreaux, piques, trefles} t_couleur;

typedef struct {t_valeur valeur; t_couleur couleur;} t_carte;

typedef struct {t_carte carte[12]; int indice; int nb_as; int valeurmain} t_main;

/* Prototypes */
void init_game();
void ajout(t_main * joueur, int valeur, int couleur);
short carte_aleatoire()
short tirer_carte(short joueur);
void afficher_carte(short num, t_carte *main, int* nb_cartes);
short tirer_carte(short joueur);
short donner_valeur_carte (int carte);
void evaluer_score(t_main * mainj);

// définition d'un tableau de 52 emplacements, représentant le jeu de cartes
extern short cartes[52];

// définition des structures t_main
extern t_main mainjoueur; // déclaration de la main du joueur
extern t_main mainbanque; // déclaration de la main de la banque

//extern t_main tas[50];