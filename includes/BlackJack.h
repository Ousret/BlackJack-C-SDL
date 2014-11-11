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
#define BANQUE 1 // la carte est possédée par la banque et on peut la voir 
#define JOUEUR 2 // la carte est possédée par le joueur 
#define BANQUE_CACHEE 3 // la carte est possédée par la banque et elle n'est pas visible *

// definition d'une énumération contenant les valeurs d'une carte // option nous sert d'indice pour nb_carte
typedef enum {nocarte = -1, option, as, deux, trois, quatre, cinq, six, sept, huit, neuf, dix, valet, dame, roi} t_carte;

// definition d'une énumération contenant la couleur d'une carte 
typedef enum {nocouleur = -1, coeurs = 0, carreaux, piques, trefles} t_couleur;

typedef struct {t_carte valeur; t_couleur couleur;} t_main;

/* Prototypes */
void init_pioche(short tas[52]);
short tirer_carte(short joueur, t_main main);
void afficher_carte(short num, t_carte *main, int* nb_cartes);
void afficher_main(t_main *main, int* nb_cartes);
short donner_valeur_carte (int i);
short evaluer_score(t_main *main, int *nb_cartes, int nb_as);

// définition d'un tableau de 52 emplacements, représentant le jeu de cartes
extern short cartes[52];

// definition de la variable nb_as_joueur qui contient le nombre d'as d'un joueur
extern int nb_as_joueur;

// définition de la variable nb_as_banque qui contient le nombre d'as de la banque 
extern int nb_as_banque;

// définition de la variable nb_cartes_joueur qui contient le nombre de cartes du joueur
extern int nb_cartes_joueur;

// définition de la variable nb_cartes_banque qui contient le nombre de cartes de la banque
extern int nb_cartes_banque;

extern t_main mainjoueur[12]; // initialisation de la main du joueur
extern t_main mainbanque[12]; // initialisation de la main de la banque

extern t_main tas[50];