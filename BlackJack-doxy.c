/**
* \file BlackJack-avec doxy a copier.c
* \brief Les fonctions de bases du programme de black jack
* \author TAHRI Ahmed, SIMON Jérémy, DEZERE Florian, PROVOST Valentin
* \version 1.0
* \date 21 Octobre 2014
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "includes/BlackJack.h" // librairie contenant les definitions des fonctions utiles au blackjack

// initialisation du jeu de cartes a un etat 0 : la carte est piochable

/**
* \fn void init(void)
* \brief Initialisation des mains joueur et banque
*/
void init(){
	int i;
	for (i = 0; i < 52; i++){
	
		if (i < 12){
			mainjoueur[i].valeur = nocarte;
			mainjoueur[i].couleur = nocouleur;
			
			mainbanque[i].valeur = nocarte;
			mainbanque[i].couleur = nocouleur;
		}
		
		cartes[i] = 0;
		
	}
}

// 

// Fonction qui génère une carte aléatoire (carte)

/**
* \fn short carte_aleatoire (void)
* \brief Fonction permettant de sortir un nombre aléatoire entre 0 et 51
* \return Renvoit un nombre choisi de maniere aleatoire
*/
short carte_aleatoire(){
	
	srand(time(NULL));
	
	return (rand() % 52);
}

// Retourne une carte encore non utilisée

/**
* \fn short tirer_carte (short joueur, t_main main)
*\brief Fonction qui permet de tirer une carte de maniere aleatoire pour un joueur 
*\param short joueur correspond au joueur auquel il faut tirer une carte 
*\param t_main main defini le tableau de type dans lequel est stocke la carte tire
*\return renvoi le numero de la carte tiree
*/
short tirer_carte(short joueur, t_main main){

	short carte = carte_aleatoire();
	
	/*while (tas[carte]!=0){
		carte = carte_aleatoire();
	}
	
	cartes[carte]=joueur;
	main[(main[0].valeur)+1].valeur=carte%13;
	main[(main[0].valeur)+1].couleur=carte/13;
	main[0].valeur += 1;
	*/
	
	return carte;
}

// fonction qui donne la valeur d'une carte

/**
*\fn short donner_valeur_carte (int i)
*\brief Fonction permettant de connaitre la valeur d'une carte en fonction de son numero 
*\param int i correspondant a la valeur d'une carte
*\return renvoi la valeur de la carte
*/
short donner_valeur_carte (int i){
	
	int carte = i;
	
	if (carte == 0){
		return 11;
	}
	if (carte >= 10 && carte <= 12){
		return 10;
	}
	if (carte >= 1 && carte <= 9){
		return carte+1;
	}
	
	return 0; //Check this..
}

// fonction qui donne le score d'un joueur/  

/**
*\fn evaluer_score (t_main *main, int *nb_cartes, int nb_as)
*\brief Fonction permettant l'evaluation du score d'un joueur (son nombre de point du a ses cartes)
*\param t_main *main pointeur sur la main d'un joueur 
*\param int *nb_cartes pointeur sur le nombre de carte distribue au joueur 
*\param int nb_as correspond au nombre d'as du joueur 
*\return renvoi le nombre de point du joueur
*/   
short evaluer_score(t_main *main, int *nb_cartes, int nb_as){

	int i, valeur_carte;
	int points=0;
	
	for(i=0; i < (*nb_cartes); i++)
	{
		valeur_carte = donner_valeur_carte(main[i].valeur);
		points = points + valeur_carte;
	}
	
	if(points > 21 && nb_as>0)
	{
		points = points - (nb_as*10);
	}
	return points;
	
}
