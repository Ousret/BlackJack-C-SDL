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
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h> //Pour imprimer du texte graphiquement
#include <SDL_image.h> //Pour imprimer des images
#include <ESDL.h> //EasySDL
#include <string.h> //Gestion des chaines

#include "includes/bj_engine.h"

void handleBlackJack();
void giveawayCard(t_window * window, int idplayer);
void handleHUD(t_window * window, char * scoreDealer, char * scorePlayer, char * betPlayer, char * soldePlayer);
int ingameAnnouncement(char * message, SDL_Color couleur);

//int nbVictoireConseq = 0;

int main (int argc, char *argv[]) {

	char menu_content[N][M] = { "Nouvelle partie", "Mes comptes", "Quitter"};
	char name[50], mise[50], miseMin[100], miseMax[100], stats[100], ratio[100];
	
	int UserChoise = 0, NbEntry = 3;
    int btnOK = 0;
    t_window * popup = NULL;
    
    memset(name, 0, sizeof(name));
    
	SDL_init(800, 600, "BlackJack ESDL 0.2", 1, "global.ttf", 20, 1); //800x600 +tff_support +audio_support
	joueurs[1].solde = 300;
	srand(time (NULL));
	
	while (1) {
		
		//SDL_Ambiance("ambiance.wav");
		BJ_setGameProperties((((joueurs[1].solde)/100)+1), ((joueurs[1].solde)/2), 0);
		memset(mise, 0, sizeof(mise));
		UserChoise = SDL_generateMenu(NbEntry, menu_content); //On affiche un menu de cinq entrée
		
		switch (UserChoise) {
			
			case 0: 
				
				popup = SDL_newWindow("Mise", 200, 200, 500, 250);
				
				SDL_newTexture(popup, NULL, "popup.png", 0, 0, 500, 250);
				
				SDL_newObj(popup, NULL, 1, "Mise", mise, NUMERIC,70, 70, 40, 400);
				SDL_newText(popup, NULL, "Avant de rejoindre le salon, placez une mise.", couleurBlanche, 10, 40);
				
				sprintf(miseMin, "Mise minimale: %li euro(s)", MinimalBet);
				sprintf(miseMax, "Mise maximale: %li euro(s)", MaximalBet);
				sprintf(stats, "Il vous reste %li euro(s)", joueurs[1].solde);
				
				SDL_newText(popup, NULL, stats, couleurRouge, 80, 110);
				SDL_newText(popup, NULL, miseMin, couleurBlanche, 80, 140);
				SDL_newText(popup, NULL, miseMax, couleurBlanche, 80, 160);
				
				SDL_newObj(popup, &btnOK, 0, "OK", NULL , ALL, 10, 200, 40, 230);
				SDL_newObj(popup, NULL, 0, "Annuler", NULL, ALL, 240, 200, 40, 230);
				
				if (SDL_generate(popup) == btnOK) {
				
					if (BJ_setBet(1, atoi(mise))) {
						
						handleBlackJack();
						
					}else {
						
						SDL_delObj(popup, 2);
						SDL_delObj(popup, 1);
						SDL_modObj(popup, 0, 0, "OK", NULL, ALL, 150, 200, 40, 230);
						SDL_delText(popup, 3);
						SDL_delText(popup, 2);
						SDL_delText(popup, 1);
						
						SDL_modText(popup, 0, "La saisie est incorrecte !", couleurRouge, 30, 100);
						
						SDL_generate(popup);
						
					}
				
				}
				
				SDL_freeWindow(popup);
				
				break;
				
			case 1:
				
				popup = SDL_newWindow("Mes comptes", 200, 200, 500, 250);
				
				SDL_newTexture(popup, NULL, "popup.png", 0, 0, 500, 250);
				SDL_newText(popup, NULL, "Voici le recapitulatif de votre session", couleurBlanche, 10, 40);
				SDL_newObj(popup, NULL, 1, "Pseudo", name , ALL, 70, 70, 40, 400);
				
				sprintf(miseMin, "Mise minimale: %li euro(s)", MinimalBet);
				sprintf(miseMax, "Mise maximale: %li euro(s)", MaximalBet);
				sprintf(stats, "Il vous reste %li euro(s)", joueurs[1].solde);
				
				SDL_newText(popup, NULL, stats, couleurRouge, 80, 110);
				SDL_newText(popup, NULL, miseMin, couleurBlanche, 80, 130);
				SDL_newText(popup, NULL, miseMax, couleurBlanche, 80, 150);
				
				sprintf(ratio, "Ratio: %i V / %i D", nbVictoire, nbDefaite);
				SDL_newText(popup, NULL, ratio, couleurBlanche, 80, 170);
				SDL_newObj(popup, &btnOK, 0, "Fermer", NULL , ALL, 150, 200, 40, 230);
				
				SDL_generate(popup);
				SDL_freeWindow(popup);
				
				break;
			
			case 2:				
				exit(0);
				break;
				
			default:
				break;
				
		}
		
	}
	
	return 0;
	
}


void handleBlackJack() {

	t_window * ingame = SDL_newWindow("BlackJack", 0, 0, 800, 600);
	char * scoreDealer = malloc(sizeof(char) * 50), *scorePlayer = malloc(sizeof(char) * 50), *betPlayer = malloc(sizeof(char) * 50), *soldePlayer = malloc(sizeof(char) * 50);
	int choise = 0;
	
	SDL_newTexture(ingame, NULL, "app_bg_ingame.png", 0, 0, 800, 600);
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
		effect = Mix_LoadWAV("ressources/snd/Female/killingspree.wav");
		channel_effect = Mix_PlayChannel(-1, effect, 0);
		BJ_setMonney(1, ((joueurs[1].mise)*2)+((joueurs[1].mise)/2));
		ingameAnnouncement("BlackJack au service..! Pas mal.", couleurBlanche);
		SDL_freeWindow(ingame);
		return;
	}
	
	SDL_newObj(ingame, NULL, 0, "Abandon", NULL , ALL, 50, 530, 40, 230);
	SDL_newObj(ingame, NULL, 0, "Rester", NULL, ALL, 280, 530, 40, 230);
	SDL_newObj(ingame, NULL, 0, "Frapper", NULL, ALL, 510, 530, 40, 230);
	
	choise = SDL_generate(ingame);
	
	while (choise == 2) {
	
		giveawayCard(ingame, 1);
		handleHUD(ingame, scoreDealer, scorePlayer, betPlayer, soldePlayer);
		
		//Check if not being burned
		if (BJ_getScore(1) > 21) {
			//popup instant BJ
			SDL_delObj(ingame, 2);
			SDL_delObj(ingame, 1);
			SDL_delObj(ingame, 0);
			SDL_generate(ingame);
			effect = Mix_LoadWAV("ressources/snd/lose.wav");
			channel_effect = Mix_PlayChannel(-1, effect, 0);
			nbVictoireConseq = 0;
			nbDefaite++;
			SDL_Delay(1000);
			ingameAnnouncement("T'es crame, tu depasse 21 mon vieux.", couleurRouge);
			SDL_freeWindow(ingame);
			
			return;
			
		}else if (BJ_getScore(1) == 21) {
			
			SDL_delObj(ingame, 2);
			SDL_delObj(ingame, 1);
			SDL_delObj(ingame, 0);
			SDL_generate(ingame);
			nbVictoireConseq++;
			nbVictoire++;
			effect = Mix_LoadWAV("ressources/snd/gotblackjack.wav");
			channel_effect = Mix_PlayChannel(-1, effect, 0);
			SDL_Delay(1000);
			BJ_setMonney(1, (joueurs[1].mise)*2);
			ingameAnnouncement("BlackJack ! Bon jeu..! Revenez, la prochaine je gagne..", couleurBlanche);
			SDL_freeWindow(ingame);
			
			return;
			
		}
		
		choise = SDL_generate(ingame);
		
	}
	
	if (choise == 0) {
		//popup instant BJ
		nbVictoireConseq = 0;
		nbDefaite++;
		ingameAnnouncement("Bonne ou mauvaise idee, tu ne le saura jamais.", couleurRouge);
		SDL_freeWindow(ingame);
		return;
	}
	
	SDL_delObj(ingame, 2);
	SDL_delObj(ingame, 1);
	SDL_delObj(ingame, 0);
	
	while (BJ_getScore(0) < 17) {
		
		giveawayCard(ingame, 0);
		handleHUD(ingame, scoreDealer, scorePlayer, betPlayer, soldePlayer);
		SDL_generate(ingame);
		SDL_Delay(1000);
		
	}
	
	if (BJ_getScore(0) > 21) {
		
		
		if (nbVictoireConseq == 2) {
			effect = Mix_LoadWAV("ressources/snd/Female/dominating.wav");
			channel_effect = Mix_PlayChannel(-1, effect, 0);
		}else if(nbVictoireConseq > 2) {
			effect = Mix_LoadWAV("ressources/snd/Female/unstoppable.wav");
			channel_effect = Mix_PlayChannel(-1, effect, 0);
		}else {
			effect = Mix_LoadWAV("ressources/snd/aplause.wav");
			channel_effect = Mix_PlayChannel(-1, effect, 0);
		}
		
		SDL_Delay(1000);
		nbVictoireConseq++;
		nbVictoire++;
		BJ_setMonney(1, (joueurs[1].mise)*2);
		ingameAnnouncement("Je me suis crame, une revanche ?", couleurBlanche);
		SDL_freeWindow(ingame);
		
	}else if(BJ_getScore(0) > BJ_getScore(1)) {
		
		effect = Mix_LoadWAV("ressources/snd/lose.wav");
		channel_effect = Mix_PlayChannel(-1, effect, 0);
		nbVictoireConseq = 0;
		nbDefaite++;
		SDL_Delay(1000);
		ingameAnnouncement("Les jeux sont fait, n'hesite pas a revenir !", couleurRouge);
		SDL_freeWindow(ingame);
		
	}else if(BJ_getScore(0) < BJ_getScore(1)) {
		
		if (nbVictoireConseq == 2) {
			effect = Mix_LoadWAV("ressources/snd/Female/dominating.wav");
			channel_effect = Mix_PlayChannel(-1, effect, 0);
		}else if(nbVictoireConseq > 2) {
			effect = Mix_LoadWAV("ressources/snd/Female/unstoppable.wav");
			channel_effect = Mix_PlayChannel(-1, effect, 0);
		}else {
			effect = Mix_LoadWAV("ressources/snd/aplause.wav");
			channel_effect = Mix_PlayChannel(-1, effect, 0);
		}
		
		SDL_Delay(1000);
		nbVictoireConseq++;
		nbVictoire++;
		BJ_setMonney(1, (joueurs[1].mise)*2);
		ingameAnnouncement("Pas mal du tout !", couleurBlanche);
		SDL_freeWindow(ingame);
		
	}else if(BJ_getScore(0) == BJ_getScore(1)) {
		
		SDL_Delay(1000);
		BJ_setMonney(1, joueurs[1].mise);
		ingameAnnouncement("Sa ce termine sur une belle egalite..! Revanche ?", couleurBlanche);
		SDL_freeWindow(ingame);
		
	}
	
}

int ingameAnnouncement(char * message, SDL_Color couleur) {
	
	t_window * popup = SDL_newWindow("Mes comptes", 200, 200, 500, 250);
	char ratio[50];
	
	SDL_newTexture(popup, NULL, "popup.png", 0, 0, 500, 250);
	
	SDL_newText(popup, NULL, message, couleur, 50, 100);
	sprintf(ratio, "Ratio: %i V / %i D", nbVictoire, nbDefaite);
	SDL_newText(popup, NULL, ratio, couleurBlanche, 50, 120);
	
	SDL_newObj(popup, NULL, 0, "OK", NULL , ALL, 150, 200, 40, 230);
	
	SDL_generate(popup);
	SDL_freeWindow(popup);
	
	return 1;
	
}

void giveawayCard(t_window * window, int idplayer) {
	
	char * fileName = malloc(sizeof(char) * 50);
	memset(fileName, 0, sizeof(char)*50);
	
	/*Begin, give away card to idplayer*/
	BJ_attrCard(idplayer); 
	
	effect = Mix_LoadWAV("ressources/snd/deal.wav");
	channel_effect = Mix_PlayChannel(-1, effect, 0);
	
	BJ_getCardfilename(idplayer, (joueurs[idplayer].nbCard-1), fileName);
	
	switch (idplayer) {
		
		case 0:
			SDL_newTexture(window, NULL, fileName, 350+((joueurs[idplayer].nbCard-1)*30), 100, 71, 96);
			break;
		case 1:
			SDL_newTexture(window, NULL, fileName, 350+((joueurs[idplayer].nbCard-1)*30), 380, 71, 96);
			break;
			
	}
	
}

void handleHUD(t_window * window, char * scoreDealer, char * scorePlayer, char * betPlayer, char * soldePlayer) {
	
	sprintf(scoreDealer, "%i", BJ_getScore(0));
	sprintf(scorePlayer, "%i", BJ_getScore(1));
	sprintf(betPlayer, "%li euro(s)", joueurs[1].mise);
	sprintf(soldePlayer, "%li", joueurs[1].solde);
	
	if (window->nbText == 0) {
		
		SDL_newText(window, NULL, scoreDealer, couleurBlanche, 330, 100);
		SDL_newText(window, NULL, scorePlayer, couleurBlanche, 330, 380);
		SDL_newText(window, NULL, betPlayer, couleurBlanche, 350, 360);
		SDL_newText(window, NULL, soldePlayer, couleurBlanche, 115, 580);
		
	}else{
		
		if (BJ_getScore(0) > 21) {
		
			SDL_modText(window, 0, scoreDealer, couleurRouge, 330, 100);
			
		}else{
		
			SDL_modText(window, 0, scoreDealer, couleurBlanche, 330, 100);
			
		}
		
		if (BJ_getScore(1) > 21) {
		
			SDL_modText(window, 1, scorePlayer, couleurRouge, 330, 380);
			
		}else{
		
			SDL_modText(window, 1, scorePlayer, couleurBlanche, 330, 380);
			
		}
		
		SDL_modText(window, 2, betPlayer, couleurBlanche, 350, 360);
		SDL_modText(window, 3, soldePlayer, couleurBlanche, 115, 580);
		
	}

}