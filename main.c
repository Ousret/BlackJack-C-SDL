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
#include <string.h> //Gestion des chaines
#include "includes/STJ_SDL.h"
#include "includes/bj_engine.h"
SDL_Surface *screen = NULL;

SDL_Color couleurRouge = {255, 0, 0};
SDL_Color couleurBlanche = {255, 255, 255};
SDL_Color couleurNoire = {0, 0, 0};

SDL_Event GlobalEvent;

int channel = 0;	
Mix_Chunk *sound = NULL;

int channel_effect = 0;	
Mix_Chunk *effect = NULL;

Mix_Chunk *music = NULL;
int channel_music = 0;

//SDL_mutex *MutexEcran = NULL; Inutile pour l'instant.
//FILE * fichier_db = NULL;

int sel_menu_m = 0;

/**
 * \fn int main (int argc, char *argv[])
 * \brief Entrée du programme.
 * \param argc entree standard du main
 * \param argv entree standard du main
 *
 * \return 0 - Arrêt normal du programme.
 */
int main (int argc, char *argv[]) {

	char sommaire[N][M] = { "Partie locale", "Mes comptes", "Quitter", "Quitter"};
	char ingame[N][M] = { "Abandon", "Rester", "Frapper"};
	
	char stats[200];
	int videurCheck = 0;
	
	memset(stats, 0, sizeof(stats));
	
	TTF_Font *police_menu = NULL; //Police d'écriture pour le menu 
	TTF_Font *police_std = NULL; //Police pour tout le reste sauf menu
	
	int MenuChoix = 0, NbOption = 3;
    
	SPI_SDL_Init_Video(800,600,"BlackJack SDL",1,1); //800x600 +tff_support +audio_support
	
	//SDL_Splash("ressources/Splash0.png", 1500);
	
	police_menu = TTF_OpenFont("ressources/ttf/global.ttf", 25);
	police_std = TTF_OpenFont("ressources/ttf/global.ttf", 20);
	
	srand(time (NULL));
	joueurs[1].solde = 300; //On lui offre 300 euros pour commencer
	
	
	while (1) {
		
		SDL_Ambiance("ambiance.wav");
		BJ_setGameProperties(((joueurs[1].solde)/100), ((joueurs[1].solde)/2), 0);
		
		if ((joueurs[1].solde) < 40) {
		
			strcpy(sommaire[2], "Hypotheque");
			NbOption = 4;
			
		}else{
		
			strcpy(sommaire[2], "Quitter");
			NbOption = 3;
			
		}
		
		MenuChoix = SDL_Create_Menu(police_menu, NbOption, sommaire); //On affiche un menu de cinq entrée
		
		switch (MenuChoix) {
			
			case 0: 
				
				//Local!
				BJ_setCards();
				videurCheck = BJ_setBet(1, SDL_Ask_Bet(police_std));
				
				if (videurCheck == 1) {
				
					SDL_Create_Local(police_std, 3, ingame);
					
				}else if (videurCheck == -1) {
					
					sprintf(stats, "Vous avez %li euro(s) restant..!", joueurs[1].solde);
					SDL_Open_PopUp(2, police_std, stats ,"Et devinez quoi, vous ne pouvez pas rentrer", "");
					
				}else{
					
					sprintf(stats, "Mise minimale = %li eur et mise max = %li eur", MinimalBet, MaximalBet);
					SDL_Open_PopUp(2, police_std, "Mauvaise saisie du montant !" ,stats, "");
					
				}
				
				break;
				
			case 1:
				//Mes comptes
				sprintf(stats, "Vous avez %li euro(s) restant", joueurs[1].solde);
				SDL_Open_PopUp(3, police_std, stats ,"Attention, les jeux d'argents peuvent rendre addict.", "Effet secondaire(?): Richesse, exil fiscal.. (Non exhaustif)");
				break;
			
			case 2:
				
				if (NbOption == 3) {
					//ByeBye..
					exit(0);
				}else{
					sprintf(stats, "Vous avez %li euro(s) restant, cliquez sur OK pour accepter!", joueurs[1].solde);
					SDL_Open_PopUp(3, police_std, stats ,"Vous n'avez plus grand chose a nous offrir..?", "C'est soit en nature ou on viendra prendre votre batterie..");
					SDL_Open_PopUp(1, police_std, "+1000 euros, bouger pas, on arrive !", "", "");
					BJ_setMonney(1, 1000);
				}
				
				break;
				
			case 3:
			
				exit(0);
				break;
				
			default:
				break;
				
		}
		
	}
	return 0;
}
