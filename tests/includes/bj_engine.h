/**
* \file bj_engine.h
* \brief Les fonctions de bases du programme de black jack
* \author Groupe 4 du TP6
* \version 1.0
* \date 21 Octobre 2014
*
*/

/**
 * \enum t_valeur
 * \brief Constantes, identifiant des cartes
 *
 * t_valeur est ici pour faciliter l'écriture et l'identification de carte s
 */
typedef enum {

	deux = 2, 
	trois, 
	quatre, 
	cinq, 
	six, 
	sept, 
	huit, 
	neuf, 
	dix, 
	valet, 
	dame, 
	roi, 
	as = 1
	
} t_valeur;
typedef enum {coeurs, carreaux, piques, trefles} t_couleur;

/**
 * \struct t_carte
 * \brief Objet carte de jeu
 *
 * t_carte est une variable qui nous permettra d'identifier une carte
 * La valeur ainsi que la couleur est obligatoire
 */
typedef struct {

	t_valeur valeur; /*!< Valeur de la carte, deux, trois..valet, roi..as, etc.. */
	t_couleur couleur; /*!< Le type de la carte, coeurs, carreaux, etc.. . */
	
} t_carte;

/**
 * \struct t_joueur
 * \brief Objet fiche joueur
 *
 * t_joueur contient les informations sur un joueur.
 * Il est important d'initialiser à 0 avant toute chose.
 */
typedef struct {

	long solde; /*!< Le solde courant (entier long) */
	long mise; /*!< La mise actuelle (entier long) */
	t_carte jeu[10]; /*!< Le jeu de carte en main */
	int nbCard; /*!< Le nombre de carte en main */
	int points; /*!< La valeur de la main */
	
} t_joueur;

extern long MinimalBet, MaximalBet;
/** \brief Nombre de robot à ajouter */
extern short NbBot;
/** \brief Tableau de fiche joueurs (Banquier et joueur(s)) */
extern t_joueur joueurs[8]; //7 joueurs max. + croupier
/** \brief Tableau contenant le tas de carte */
extern t_carte tas[56];
/** \brief Nombre de carte présente dans le tas */
extern int nbCard_tas;
/** \brief Nombre de victoire à la suite */
extern int nbVictoireConseq;

/* Prototype des fonctions BJ_ */

/**
*\fn int BJ_getScore(int id)
*\brief Fonction renvoyant le score d'un joueur 
*\param int id permet de savoir qu'elle est le joueur dont il faut recuperer le score 
*\return renvoi le score du joueur 
*/
int BJ_getScore(int id);

/**
*\fn void BJ_setBotAction(int id)
*\brief Fonction definissant les actions d'un bot (IA) en fonction de son id
*\param int id correspond a l'id du bot qu'il faut faire jouer  
*/
void BJ_setBotAction(int id);

/**
*\fn int BJ_setBet(int id, long bet)
*\brief Fonction permettant de placer une mise en jeu et de la retirer du solde du joueur
*\param int id correspond au joueur qui mise 
*\param long bet correspond a la valeur de la mise du joueur
*\return renvoi vrai si la mise peut-etre place en jeu faux sinon 
*/
int BJ_setBet(int id, long bet);

/**
*\fn void BJ_setMonney(int id, long solde)
*\brief Changer le solde d'un joueur
*\param int id correspond au joueur qui mise 
*\param long solde correspond a la valeur du nouveau solde
*\return Aucune valeur de retour
*/
void BJ_setMonney(int id, long solde);

/**
*\fn BJ_getPStatus(int id)
*\brief Fonction permettant de savoir si le joueur gagne 
*\param int id represente le joueur dont on veut connaitre s'il gagne ou non
*\return renvoi 1 si le joueur gagne la manche, 0 si il reprend son argent, et -1 si il perd tout 
*/
int BJ_getPStatus(int id);

/**
*\fn void BJ_attCard(int id)
*\brief Fonction attribuant une carte a un joueur 
*\param int id correspond au joueur dont on veut attribuer une carte 
*/
void BJ_attrCard(int id);

/**
*\fn BJ_setGameProperties(long MiseMin , long MiseMax, short NBrbot)
*\brief Fonction definissant les les propriete de la partie 
*\param long MiseMin correspond a la mise minimale
*\param long MiseMax correspond a la mise maximale
*\param short NbrBot correspond au nombre de bot dans la partie
*\return renvoi -1 si il y a trop de bot, 0 si les parametres sont correctes
*/
int BJ_setGameProperties(long MiseMin, long MiseMax, short NbrBot);

/**
*\fn void BJ_setCards(void)
*\brief Fonction permettant l'initialisation du tas de cartes sans doublons
*/
void BJ_setCards();

/**
*\fn int Random(int _iMin, int _iMax)
*\brief Fonction permmettant de renvoyer une valeur entiere aleatoire entre 2 valeurs
*\param int _iMin correspond a la valeur minimale pour effectuer l'aleatoire 
*\param int _iMax correspond a la valeur maximale pour effectuer l'aleatoire 
*\return renvoi le nombre choisi aleatoirement 
*/
int Random (int _iMin, int _iMax);