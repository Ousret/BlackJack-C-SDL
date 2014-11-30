/**
 * \file main.c
 * \brief Mot-mêlés - Projet Info SPI L2
 * \author TAHRI Ahmed, SIMON Jérémy
 * \version 0.1
 * \date 29 Octobre 2014
 *
 * Générateur de mot-meles avec la SDL/C 1.2
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

Mix_Chunk *music = NULL;
int channel_music = 0;

//SDL_mutex *MutexEcran = NULL; Inutile pour l'instant.
//FILE * fichier_db = NULL;

int sel_menu_m = 0;

/**
 * \fn int main (int argc, char *argv[])
 * \brief Entrée du programme.
 *
 * \return 0 - Arrêt normal du programme.
 */
int main (int argc, char *argv[]) {

	char sommaire[N][M] = { "Partie locale", "Mes comptes", "Quitter"};
	char ingame[N][M] = { "Abandon", "Rester", "Frapper"};
	
	TTF_Font *police_menu = NULL; //Police d'écriture pour le menu 
	TTF_Font *police_std = NULL; //Police pour tout le reste sauf menu
	
	int MenuChoix = 0;
    
	SPI_SDL_Init_Video(800,600,"BlackJack SDL",1,1); //800x600 +tff_support +audio_support
	
	//SDL_Splash("ressources/Splash0.png", 1500);
	//SDL_Splash("ressources/Splash1.png", 1500);
	
	police_menu = TTF_OpenFont("ressources/ttf/global.ttf", 25);
	police_std = TTF_OpenFont("ressources/ttf/global.ttf", 20);
	
	srand(time (NULL));
	
	while (1) {
		
		SDL_Ambiance("ambiance.wav");
		MenuChoix = SDL_Create_Menu(police_menu, 3, sommaire); //On affiche un menu de cinq entrÈe
		
		switch (MenuChoix) {
			
			case 0: 
				//Contre CPU
				BJ_setGameProperties(10, 150, 0);
				BJ_setCards();
				
				if (BJ_setBet(1, SDL_Ask_Bet(police_std)) == 1) {
				
					SDL_Create_Local(police_std, 3, ingame);
					
				}else{
					
					SDL_Open_PopUp(3, police_std, "Mauvaise saisie du montant, vous n'etes pas accepte !" ,"Mise minimale: 10 euros", "Mise maximale: 150 euros");
					
				}
				
				break;
				
			case 1:
				//Mes comptes
				SDL_Open_PopUp(3, police_std, "Il vous reste 300 euros" ,"Attention, les jeux d'argents peuvent rendre addict.", "Effet secondaire(?): Richesse, exil fiscal.. (Non exhaustif)");
				break;
			
			case 2:
				//ByeBye..
				exit(0);
				break;
				
			default:
				break;
				
		}
		
	}

}