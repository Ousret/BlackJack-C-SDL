/**
* \file bj_engine.c
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

#include "includes/bj_engine.h"

//On définie les variables de base
long MinimalBet = 0, MaximalBet = 0;
short NbBot = 0;

t_joueur joueurs[8]; //7 joueurs max. + croupier

t_carte tas[56];
int nbCard_tas = 0;

int BJ_getScore(int id) {
/* Renvoi le score */

	int total = 0;
	int i = 0;
	
	for (i = 0; i < (joueurs[id].nbCard)+1; i++) {
		
		switch (joueurs[id].jeu[i].valeur) {
			case deux:
				total+=2;
				break;
			case trois:
				total+=3;
				break;
			case quatre:
				total+=4;
				break;
			case cinq:
				total+=5;
				break;
			case six:
				total+=6;
				break;
			case sept:
				total+=7;
				break;
			case huit:
				total+=8;
				break;
			case neuf:
				total+=9;
				break;
			case dix:
				total+=10;
				break;
			case valet:
				total+=10;
				break;
			case dame:
				total+=10;
				break;
			case roi:
				total+=10;
				break;
			case as:
				//On n'oublie pas de rétrograder l'AS si on est cramé !
				if ((total + 11) > 21) {
					total+=1;
				}else{
					total+=11;
				}
				
				break;
		}
		
		
	}
	
	
	
	return total;
}

void BJ_setBotAction(int id) {
/* Under construct, DO NOT DELETE */

}

int BJ_setBet(int id, long bet) {
/* Place une mise et le retire du solde..! */

	if (bet < MinimalBet || bet > MaximalBet) {
	
		return 0;
		
	}else{
	
		joueurs[id].mise+=bet;
		joueurs[id].solde-=bet;
		
		return 1;
	}
	
}

int BJ_getPStatus(int id) {

	if (joueurs[id].points > joueurs[0].points) {
	
		return 1; //Gagne la manche..!
		
	}else if (joueurs[id].points == joueurs[0].points) {
		
		return 0; //Reprend ses sous !
		
	}else{
		
		return -1; //Perds ses sous..!
		
	}

}

void BJ_attrCard(int id) {
/* Donne une carte au joueur N */
	int i = 0;

	if (joueurs[id].nbCard < 8) {
		
		joueurs[id].jeu[(joueurs[id].nbCard)] = tas[0];
		
		for (i = 0; i < nbCard_tas; i++) {
			tas[i] = tas[i+1];
		}
		
		nbCard_tas--;
		joueurs[id].nbCard++;
		
	}

}

int BJ_setGameProperties(long MiseMin, long MiseMax, short NbrBot) {

	if (NbrBot > 6) return -1;
	
	int i = 0;
	
	MinimalBet = MiseMin;
	MaximalBet = MiseMax;
	NbBot = NbrBot;
	
	for (i = 0; i <= (NbrBot+2); i++) {
		
		//Banque, emplacement 0 et 1 emplacement joueur !
		if (i > 1) {
			joueurs[i].solde = Random(300, 10000);
		}else{
			//On prend dans profil.sav
		}
		
		joueurs[i].mise = 0;
		
		joueurs[i].nbCard = 0;
		
		joueurs[i].points = 0;
		
	}
	
	return 0;

}

void BJ_setCards() {
/* Initialise le tas avec les cartes, fait en sorte de ne pas avoir de doublon.. Sa serai regrettable ! */

	t_valeur tas_coeurs[13] = {deux, trois, quatre, cinq, six, sept, huit, neuf, dix, valet, dame, roi, as};
	t_valeur tas_carreaux[13] = {deux, trois, quatre, cinq, six, sept, huit, neuf, dix, valet, dame, roi, as};
	t_valeur tas_piques[13] = {deux, trois, quatre, cinq, six, sept, huit, neuf, dix, valet, dame, roi, as};
	t_valeur tas_trefles[13] = {deux, trois, quatre, cinq, six, sept, huit, neuf, dix, valet, dame, roi, as};
	
	int taille_coeurs = 13, taille_carreaux = 13, taille_piques = 13, taille_trefles = 13;
	int randpos = 0, randtype = 0; //Contiendra le choix au hasard 
	int c = 0; //On comptera le nombre de carte ajouté au tas !
	t_carte tmp;
	int i = 0;
	
	while (taille_coeurs > 0 || taille_carreaux > 0 || taille_piques > 0 || taille_trefles > 0) {
	
		randtype = Random(0, 4);
		//fprintf(stdout, "On a mis %i carte\n taille_coeur: %i\n taille_carreaux: %i\n taille_piques: %i\n taille_trefles: %i\n", c, taille_coeurs, taille_carreaux, taille_piques, taille_trefles);
		
		if (randtype == 0 && taille_coeurs > 0) {
			
			randpos = Random (0, taille_coeurs);
			tmp.valeur = tas_coeurs[randpos];
			tmp.couleur = coeurs;
			
			for (i = randpos; i < 13; i++) {
				tas_coeurs[i] = tas_coeurs[i+1];
			}
			
			tas[c] = tmp;
			taille_coeurs--;
			
			c++;
			
		}else if(randtype == 1 && taille_carreaux > 0) {
			
			randpos = Random (0, taille_carreaux);
			tmp.valeur = tas_carreaux[randpos];
			tmp.couleur = carreaux;
			
			for (i = randpos; i < 13; i++) {
				tas_carreaux[i] = tas_carreaux[i+1];
			}
			
			tas[c] = tmp;
			taille_carreaux--;
			
			c++;
			
		}else if(randtype == 2 && taille_piques > 0) {
		
			randpos = Random (0, taille_piques);
			tmp.valeur = tas_piques[randpos];
			tmp.couleur = piques;
			
			for (i = randpos; i < 13; i++) {
				tas_piques[i] = tas_piques[i+1];
			}
			
			tas[c] = tmp;
			taille_piques--;
			
			c++;
			
		}else if (randtype == 3 && taille_trefles > 0) {
		
			randpos = Random (0, taille_trefles);
			tmp.valeur = tas_trefles[randpos];
			tmp.couleur = trefles;
			
			for (i = randpos; i < 13; i++) {
				tas_trefles[i] = tas_trefles[i+1];
			}
			
			tas[c] = tmp;
			taille_trefles--;
			
			c++;
		
		}
	
	
	}
	
	nbCard_tas = c;
	
}

int Random (int _iMin, int _iMax)
{
	return (rand() % (_iMax - _iMin) + _iMin);
}