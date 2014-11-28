/**
* \file Black_jack.c
* \brief Les fonctions de bases du programme de black jack
* \author Groupe 4 du TP6
* \version 1.0
* \date 21 Octobre 2014
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "includes/BlackJack.h"

// initialisation du jeu de cartes a un etat 0 : la carte est piochable
void init_game(){
	int i = 0;
	mainjoueur.indice=-1;
	mainbanque.indice=-1;
	for (i=0 ; i < 52 ; i++){
		cartes[i]=0;
	}
	fprintf(stdout,"\nPaquet et mains initialisés");
}

// Fonction qui ajoute une carte à la main ()
void ajout(t_main * joueur, int valeur, int couleur){
	joueur->indice = joueur->indice + 1;
	joueur->carte[joueur->indice].valeur = valeur;
	joueur->carte[joueur->indice].couleur = couleur;
}

// Fonction qui génère une carte aléatoire (carte)
short carte_aleatoire(){
	return (rand()+1 % 52);
}

// Retourne une carte encore non utilisée
short tirer_carte(short joueur){

	int tvaleur;
	int tcouleur;
	short carte = carte_aleatoire();
	
	// Tant que la carte n'est pas libre
	while (cartes[carte]!=LIBRE){
		carte = carte_aleatoire();
	}

	// Calcul de la valeur de la carte et sa couleur
	tvaleur=carte%13;
	tcouleur=carte/13;

	
	// On attribue la carte à la bonne main
	if(joueur==BANQUE){
		if(mainbanque.indice == -1){
			cartes[carte]=1;
		}
		else cartes[carte]=2; // RAJOUTER LA FONCTION CARTE CACHEE
		ajout(&mainbanque,tvaleur,tcouleur);
	}
	else if(joueur == JOUEUR){
		cartes[carte]=1; 
		ajout(&mainjoueur,tvaleur,tcouleur);
	}	
	
	return carte;
}

// fonction qui donne la valeur d'une carte
short donner_valeur_carte (int carte){
	
	if (carte == 0){
		return 11;
	}
	if (carte >= 11 && carte <= 14){
		return 10;
	}
	if (carte >= 2 && carte <= 10){
		return carte-1;
	}
	
	return 0; //Check this..
}

// fonction qui donne le score d'un joueur/     
void evaluer_score(t_main * mainj){

	int i, valeur_carte;
	int points=0;
	
	for(i=0; i < (mainj->indice); i++)
	{
		valeur_carte = donner_valeur_carte(mainj->carte[i].valeur);
		points = points + valeur_carte;
	}
	
	if(points > 21 && mainj->nb_as > 0)
	{
		points = points - (mainj->nb_as*10);
	}
	mainj->valeurmain = points;
	
}