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
#include <string.h>

#include "includes/bj_engine.h"

//On définie les variables de base
long MinimalBet = 0, MaximalBet = 0;
short NbBot = 0;

t_joueur joueurs[8]; //7 joueurs max. + croupier

t_carte tas[56];
int nbCard_tas = 0;
int nbVictoireConseq = 0;
int nbVictoire = 0, nbDefaite = 0;

/**
*\fn int BJ_getScore(int id)
*\brief Fonction renvoyant le score d'un joueur 
*\param int id permet de savoir qu'elle est le joueur dont il faut recuperer le score 
*\return renvoi le score du joueur 
*/
int BJ_getScore(int id) {
/* Renvoi le score */

	int total = 0;
	int i = 0;

	for (i = 0; i < (joueurs[id].nbCard); i++) {
		
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

/**
*\fn void BJ_setBotAction(int id)
*\brief Fonction definissant les actions d'un bot (IA) en fonction de son id
*\param int id correspond a l'id du bot qu'il faut faire jouer  
*/
void BJ_setBotAction(int id) {
/* Under construct, DO NOT DELETE */

}

/**
*\fn int BJ_setBet(int id, long bet)
*\brief Fonction permettant de placer une mise en jeu et de la retirer du solde du joueur
*\param int id correspond au joueur qui mise 
*\param long bet correspond a la valeur de la mise du joueur
*\return renvoi vrai si la mise peut-etre place en jeu faux sinon 
*/
int BJ_setBet(int id, long bet) {
/* Place une mise et le retire du solde..! */

	if (bet < MinimalBet || bet > MaximalBet) {
	
		return 0;
		
	}else if (bet > joueurs[id].solde) {
	
		return -1;
		
	}else{
	
		joueurs[id].mise+=bet;
		joueurs[id].solde-=bet;
		
		return 1;
	}
	
}

/**
*\fn void BJ_setMonney(int id, long solde)
*\brief Changer le solde d'un joueur
*\param int id correspond au joueur qui mise 
*\param long solde correspond a la valeur du nouveau solde
*\return Aucune valeur de retour
*/
void BJ_setMonney(int id, long solde) {
/* Remet de l'argent pour.. id */

	joueurs[id].solde+=solde;
		
	
}

/**
*\fn BJ_getPStatus(int id)
*\brief Fonction permettant de savoir si le joueur gagne 
*\param int id represente le joueur dont on veut connaitre s'il gagne ou non
*\return renvoi 1 si le joueur gagne la manche, 0 si il reprend son argent, et -1 si il perd tout 
*/
int BJ_getPStatus(int id) {

	
	if (joueurs[id].points > joueurs[0].points) {
	
		return 1; //Gagne la manche..!
		
	}else if (joueurs[id].points == joueurs[0].points) {
		
		return 0; //Reprend ses sous !
		
	}else{
		
		return -1; //Perds ses sous..!
		
	}

}


/**
*\fn void BJ_attCard(int id)
*\brief Fonction attribuant une carte a un joueur 
*\param int id correspond au joueur dont on veut attribuer une carte 
*/
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
/**
*\fn BJ_setGameProperties(long MiseMin , long MiseMax, short NBrbot)
*\brief Fonction definissant les les propriete de la partie 
*\param long MiseMin correspond a la mise minimale
*\param long MiseMax correspond a la mise maximale
*\param short NbrBot correspond au nombre de bot dans la partie
*\return renvoi -1 si il y a trop de bot, 0 si les parametres sont correctes
*/
int BJ_setGameProperties(long MiseMin, long MiseMax, short NbrBot) {

	if (NbrBot > 6) return -1;
	
	int i = 0;
	
	MinimalBet = MiseMin;
	MaximalBet = MiseMax;
	NbBot = NbrBot;
	nbCard_tas = 0;
	
	for (i = 0; i <= (NbrBot+2); i++) {
		
		//Banque, emplacement 0 et 1 emplacement joueur !
		if (i > 1) {
			joueurs[i].solde = Random(300, 10000);
		}
		
		joueurs[i].mise = 0;
		joueurs[i].nbCard = 0;
		joueurs[i].points = 0;
		
	}
	
	return 0;

}

/**
*\fn void BJ_setCards(void)
*\brief Fonction permettant l'initialisation du tas de cartes sans doublons
*/
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

void BJ_getCardfilename(int playerid, int cardid, char * destname) {

	char msg[100];
	int calcPos = 0;
	
	if ((joueurs[playerid].jeu[cardid].couleur) == trefles) {
		calcPos = 1;
	}else if ((joueurs[playerid].jeu[cardid].couleur) == carreaux) {
		calcPos = 14;
	}else if ((joueurs[playerid].jeu[cardid].couleur) == coeurs) {
		calcPos = 27;
	}else{
		calcPos = 40;
	}
			
	switch (joueurs[playerid].jeu[cardid].valeur) {
			
		case deux:
			calcPos+=1;
			break;
		case trois:
			calcPos+=2;
			break;
		case quatre:
			calcPos+=3;
			break;
		case cinq:
			calcPos+=4;
			break;
		case six:
			calcPos+=5;
			break;
		case sept:
			calcPos+=6;
			break;
		case huit:
			calcPos+=7;
			break;
		case neuf:
			calcPos+=8;
			break;
		case dix:
			calcPos+=9;
			break;
		case valet:
			calcPos+=10;
			break;
		case dame:
			calcPos+=11;
			break;
		case roi:
			calcPos+=12;
			break;
		case as:
			break;
				
	}
	
	sprintf(msg, "cartes/%i.BMP", calcPos);
	strcpy(destname, msg);
	
	return;

}

/**
*\fn int Random(int _iMin, int _iMax)
*\brief Fonction permmettant de renvoyer une valeur entiere aleatoire entre 2 valeurs
*\param int _iMin correspond a la valeur minimale pour effectuer l'aleatoire 
*\param int _iMax correspond a la valeur maximale pour effectuer l'aleatoire 
*\return renvoi le nombre choisi aleatoirement 
*/
int Random (int _iMin, int _iMax)
{
	return (rand() % (_iMax - _iMin) + _iMin);
}
