/**
 * \file main.c
 * \brief BlackJack - Algorithme Avance L2 SPI
 * \author TAHRI Ahmed, SIMON Jérémy, DEZERE Florian, PROVOST Valentin
 * \version 0.1
 * \date 29 Octobre 2014
 *
 * Generation du jeu du blackjack
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ESDL.h> //EasySDL
#include <string.h> //Gestion des chaines

#include "bj_engine.h"
#define N 50

void handleBlackJack();
void giveawayCard(t_context * context, int idplayer);
void handleHUD(t_context * context, char * scoreDealer, char * scorePlayer, char * betPlayer, char * soldePlayer);
int ingameAnnouncement(char * message, SDL_Color couleur);

//int nbVictoireConseq = 0;

d_save *profil = NULL;

int main(int argc, char *argv[]) {

	char ** menu_content = (char**) malloc(N * sizeof(char*));; //{ "Nouvelle partie", "Mes comptes", "Quitter"}
	int i = 0;
	for (i = 0; i < N; i++)
		menu_content[i] = (char*) malloc(N * sizeof(char));
	
	menu_content[0] = "Nouvelle partie";
	menu_content[1] = "Mes comptes";
	menu_content[2] = "Quitter";
	
	char name[50], mise[50], miseMin[100], miseMax[100], stats[100], ratio[100];
	
	int UserChoise = 0, NbEntry = 3;
    int btnOK = 0;
    t_context * popup = NULL;
    
    memset(name, 0, sizeof(name));
    
	SDL_initWindow(800, 600, 0, "BlackJack with ESDL 0.5", "M_ICON.png", 1, "global.ttf", 20, 1); //800x600 +tff_support +audio_support
	 
	profil = initProfil("blackjack.sav");
	/* Get lastest data */
	 
	//writeParam(profil, "username", "Ousret");
	
	char *name_tmp = readParam(profil, "username");
	if (name_tmp) strcpy(name, name_tmp);
	char *solde_tmp = readParam(profil, "account");
	
	if (solde_tmp) {
		joueurs[1].solde = atoi(solde_tmp);
	}else{
		joueurs[1].solde = 3000;
		sprintf(mise, "%li", joueurs[1].solde);
		writeParam(profil, "account", mise);
		
	}
	
	srand(time (NULL));
	
	while (1) {
		
		BJ_setGameProperties((((joueurs[1].solde)/100)+1), ((joueurs[1].solde)/2)+1, 0);
		
		memset(mise, 0, sizeof(mise));
		UserChoise = SDL_generateMenu("app_bg.png", NbEntry, menu_content); //On affiche un menu de cinq entrée
		
		switch (UserChoise) {
			
			case 0: 
				
				memset(mise, 0, sizeof(mise));
				
				popup = SDL_newContext("Mise", 200, 200, 500, 250);
				
				SDL_newImage(popup, NULL, "popup.png", 0, 0);
				
				SDL_newObj(popup, NULL, 1, "Mise", ALIGN_LEFT, mise, NUMERIC,70, 70);
				SDL_newText(popup, NULL, "Avant de rejoindre le salon, placez une mise.", colorWhite, 10, 40);
				
				sprintf(miseMin, "Mise minimale: %li euro(s)", MinimalBet);
				sprintf(miseMax, "Mise maximale: %li euro(s)", MaximalBet);
				sprintf(stats, "Il vous reste %li euro(s)", joueurs[1].solde);
				
				SDL_newText(popup, NULL, stats, colorRed, 80, 110);
				SDL_newText(popup, NULL, miseMin, colorWhite, 80, 140);
				SDL_newText(popup, NULL, miseMax, colorWhite, 80, 160);
				
				SDL_newObj(popup, &btnOK, 0, "OK", ALIGN_CENTER, NULL , NONE, 10, 200);
				SDL_newObj(popup, NULL, 0, "Annuler", ALIGN_CENTER, NULL, NONE, 240, 200);
				
				if (SDL_generate(popup) == btnOK) {
				
					if (BJ_setBet(1, atoi(mise))) {
						
						handleBlackJack();
						SDL_unloadallSound();
						
					}else {
						
						SDL_delObj(popup, 2);
						SDL_delObj(popup, 1);
						SDL_editObj(popup, 0, 0, "OK", ALIGN_CENTER, NULL, NONE, 150, 200);
						SDL_delText(popup, 3);
						SDL_delText(popup, 2);
						SDL_delText(popup, 1);
						
						SDL_editText(popup, 0, "La saisie est incorrecte !", colorRed, 30, 100);
						
						SDL_generate(popup);
						
					}
				
				}
				
				SDL_freeContext(popup);
				sprintf(mise, "%li", joueurs[1].solde);
				writeParam(profil, "account", mise);
				
				break;
				
			case 1:
				
				popup = SDL_newContext("Mes comptes", 200, 200, 500, 250);
				
				SDL_newImage(popup, NULL, "popup.png", 0, 0);
				SDL_newText(popup, NULL, "Voici le recapitulatif de votre session", colorWhite, 10, 40);
				SDL_newObj(popup, NULL, INPUT, "Pseudo", ALIGN_LEFT, name , NONE, 70, 70);
				
				sprintf(miseMin, "Mise minimale: %li euro(s)", MinimalBet);
				sprintf(miseMax, "Mise maximale: %li euro(s)", MaximalBet);
				sprintf(stats, "Il vous reste %li euro(s)", joueurs[1].solde);
				
				SDL_newText(popup, NULL, stats, colorRed, 80, 110);
				SDL_newText(popup, NULL, miseMin, colorWhite, 80, 130);
				SDL_newText(popup, NULL, miseMax, colorWhite, 80, 150);
				
				sprintf(ratio, "Ratio: %i V / %i D", nbVictoire, nbDefaite);
				SDL_newText(popup, NULL, ratio, colorWhite, 80, 170);
				SDL_newObj(popup, &btnOK, BUTTON, "Fermer", ALIGN_CENTER, NULL , NONE, 150, 200);
				
				SDL_generate(popup);
				SDL_freeContext(popup);
				writeParam(profil, "username", name);
				
				break;
			
			case 2:				
				saveProfil(profil);
				freeProfil(profil);
				exit(0);
				break;
				
			default:
				break;
				
		}
		
	}
	
	saveProfil(profil);
	freeProfil(profil);
	return 0;
	
}


void handleBlackJack() {

	t_context * ingame = SDL_newContext("BlackJack", 0, 0, 800, 600);
	char scoreDealer[50], scorePlayer[50], betPlayer[50], soldePlayer[50];
	int choise = 0, BTN_GIVEUP = 0, BTN_DOUBLET = 0, BTN_HIT = 0, BTN_STAY = 0;
	
	SDL_loadSound("lose.wav");
	SDL_loadSound("gotblackjack.wav");
	SDL_loadSound("Female/dominating.wav");
	SDL_loadSound("aplause.wav");
	SDL_loadSound("deal.wav");
	
	SDL_newImage(ingame, NULL, "app_bg_ingame.png", 0, 0);
	handleHUD(ingame, scoreDealer, scorePlayer, betPlayer, soldePlayer);
	BJ_setCards(); //Prepare cards 
	
	SDL_generate(ingame);
	SDL_Delay(1000);
	
	giveawayCard(ingame, 0);
	handleHUD(ingame, scoreDealer, scorePlayer, betPlayer, soldePlayer);
	SDL_generate(ingame);
	SDL_Delay(1000);
	
	giveawayCard(ingame, 1);
	handleHUD(ingame, scoreDealer, scorePlayer, betPlayer, soldePlayer);
	SDL_generate(ingame);
	SDL_Delay(1000);
	
	giveawayCard(ingame, 1);
	handleHUD(ingame, scoreDealer, scorePlayer, betPlayer, soldePlayer);
	SDL_generate(ingame);
	SDL_Delay(1000);
	
	//Instant BlackJack ?
	if (BJ_getScore(1) == 21) {
		//popup instant BJ
		nbVictoireConseq++;
		nbVictoire++;
		
		SDL_playSound("gotblackjack.wav");
		
		BJ_setMonney(1, ((joueurs[1].mise)*2)+((joueurs[1].mise)/2));
		ingameAnnouncement("BlackJack au service..! Pas mal.", colorWhite);
		SDL_freeContext(ingame);
		return;
	}
	
	SDL_newObj(ingame, &BTN_GIVEUP, BUTTON, "Abandon", ALIGN_CENTER, NULL, NONE, 50, 520);
	SDL_newObj(ingame, &BTN_STAY, BUTTON, "Rester", ALIGN_CENTER, NULL, NONE, 280, 520);
	SDL_newObj(ingame, &BTN_HIT, BUTTON, "Carte!", ALIGN_CENTER, NULL, NONE, 510, 520);
	SDL_newObj(ingame, &BTN_DOUBLET, BUTTON, "Doublet", ALIGN_CENTER, NULL, NONE, 280, 565);
	
	choise = SDL_generate(ingame);
	if (choise == 3) BJ_setBet(1, joueurs[1].mise);
	
	while (choise == 2 || choise == 3) {
	
		giveawayCard(ingame, 1);
		handleHUD(ingame, scoreDealer, scorePlayer, betPlayer, soldePlayer);
		
		//Check if not being burned
		if (BJ_getScore(1) > 21) {
			//popup instant BJ
			SDL_delObj(ingame, BTN_GIVEUP);
			SDL_delObj(ingame, BTN_DOUBLET);
			SDL_delObj(ingame, BTN_HIT);
			SDL_delObj(ingame, BTN_STAY);
			SDL_generate(ingame);
			
			SDL_playSound("lose.wav");
			
			nbVictoireConseq = 0;
			nbDefaite++;
			SDL_Delay(1000);
			ingameAnnouncement("T'es crame, tu depasse 21 mon vieux.", colorRed);
			SDL_freeContext(ingame);
			
			return;
			
		}
		
		if (choise == 3) break;
		choise = SDL_generate(ingame);
		
	}
	
	if (choise == 0) {
		//popup instant BJ
		nbVictoireConseq = 0;
		nbDefaite++;
		ingameAnnouncement("Bonne ou mauvaise idee, tu ne le saura jamais.", colorRed);
		SDL_freeContext(ingame);
		return;
	}
	
	SDL_delObj(ingame, BTN_GIVEUP);
	SDL_delObj(ingame, BTN_DOUBLET);
	SDL_delObj(ingame, BTN_HIT);
	SDL_delObj(ingame, BTN_STAY);
	
	while (BJ_getScore(0) < 17) {
		
		giveawayCard(ingame, 0);
		handleHUD(ingame, scoreDealer, scorePlayer, betPlayer, soldePlayer);
		SDL_generate(ingame);
		SDL_Delay(1000);
		
	}
	
	if (BJ_getScore(0) > 21) {
		
		
		if (nbVictoireConseq == 2) {
			SDL_playSound("Female/dominating.wav");
		}else if(nbVictoireConseq > 2) {
			SDL_playSound("Female/unstoppable.wav");
		}else {
			SDL_playSound("aplause.wav");
		}
		
		SDL_Delay(1000);
		nbVictoireConseq++;
		nbVictoire++;
		BJ_setMonney(1, (joueurs[1].mise)*2);
		ingameAnnouncement("Je me suis crame, une revanche ?", colorWhite);
		SDL_freeContext(ingame);
		
	}else if(BJ_getScore(0) > BJ_getScore(1)) {
		
		SDL_playSound("lose.wav");
		
		nbVictoireConseq = 0;
		nbDefaite++;
		SDL_Delay(1000);
		ingameAnnouncement("Les jeux sont fait, n'hesite pas a revenir !", colorRed);
		SDL_freeContext(ingame);
		
	}else if(BJ_getScore(0) < BJ_getScore(1)) {
		
		if (nbVictoireConseq == 2) {
			SDL_playSound("Female/dominating.wav");
		}else if(nbVictoireConseq > 2) {
			SDL_playSound("Female/unstoppable.wav");
		}else {
			SDL_playSound("aplause.wav");
		}
		
		nbVictoireConseq++;
		nbVictoire++;
		BJ_setMonney(1, (joueurs[1].mise)*2);
		ingameAnnouncement("Pas mal du tout !", colorWhite);
		SDL_freeContext(ingame);
		
	}else if(BJ_getScore(0) == BJ_getScore(1)) {
		
		SDL_Delay(1000);
		BJ_setMonney(1, joueurs[1].mise);
		ingameAnnouncement("Sa ce termine sur une belle egalite..! Revanche ?", colorWhite);
		SDL_freeContext(ingame);
		
	}
	
}

int ingameAnnouncement(char * message, SDL_Color couleur) {
	
	t_context * popup = SDL_newContext("Mes comptes", 200, 200, 500, 250);
	char ratio[50];
	
	SDL_newImage(popup, NULL, "popup.png", 0, 0);
	
	SDL_newText(popup, NULL, message, couleur, 50, 100);
	sprintf(ratio, "Ratio: %i V / %i D", nbVictoire, nbDefaite);
	SDL_newText(popup, NULL, ratio, colorWhite, 50, 120);
	
	SDL_newObj(popup, NULL, 0, "OK", ALIGN_CENTER, NULL , NONE, 150, 200);
	
	SDL_generate(popup);
	SDL_freeContext(popup);
	
	return 1;
	
}

void giveawayCard(t_context * context, int idplayer) {
	
	char * fileName = calloc(50, sizeof(char));
	//memset(fileName, 0, sizeof(char)*50);
	
	/*Begin, give away card to idplayer*/
	BJ_attrCard(idplayer); 
	SDL_playSound("deal.wav");
	BJ_getCardfilename(idplayer, (joueurs[idplayer].nbCard-1), fileName);
	
	switch (idplayer) {
		
		case 0:
			SDL_newImage(context, NULL, fileName, 350+((joueurs[idplayer].nbCard-1)*30), 100);
			break;
		case 1:
			SDL_newImage(context, NULL, fileName, 350+((joueurs[idplayer].nbCard-1)*30), 380);
			break;
			
	}
	
	free(fileName);
	
}

void handleHUD(t_context * context, char * scoreDealer, char * scorePlayer, char * betPlayer, char * soldePlayer) {
	
	sprintf(scoreDealer, "%i", BJ_getScore(0));
	sprintf(scorePlayer, "%i", BJ_getScore(1));
	sprintf(betPlayer, "%li euro(s)", joueurs[1].mise);
	sprintf(soldePlayer, "%li", joueurs[1].solde);
	
	if (context->nbText == 0) {
		
		SDL_newText(context, NULL, scoreDealer, colorWhite, 330, 100);
		SDL_newText(context, NULL, scorePlayer, colorWhite, 330, 380);
		SDL_newText(context, NULL, betPlayer, colorWhite, 350, 360);
		SDL_newText(context, NULL, soldePlayer, colorWhite, 115, 580);
		
	}else{
		
		if (BJ_getScore(0) > 21) {
		
			SDL_editText(context, 0, scoreDealer, colorRed, 330, 100);
			
		}else{
		
			SDL_editText(context, 0, scoreDealer, colorWhite, 330, 100);
			
		}
		
		if (BJ_getScore(1) > 21) {
		
			SDL_editText(context, 1, scorePlayer, colorRed, 330, 380);
			
		}else{
		
			SDL_editText(context, 1, scorePlayer, colorWhite, 330, 380);
			
		}
		
		SDL_editText(context, 2, betPlayer, colorWhite, 350, 360);
		SDL_editText(context, 3, soldePlayer, colorWhite, 115, 580);
		
	}

}