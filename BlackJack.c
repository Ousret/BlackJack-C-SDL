/**
* \file Black_jack.c
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
* \fn short carte_aleatoire 
* \brief Fonction permettant de sortir un nombre aléatoire entre 0 et 51
* \return Renvoit un nombre choisit de maniere aleatoire
*/
short carte_aleatoire(){
	
	srand(time(NULL));
	
	return (rand() % 52);
}

// Retourne une carte encore non utilisée
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
