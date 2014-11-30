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
#include <SDL.h> //librairie contenant toutes les fonctions de base de la SDL
#include <SDL_mixer.h> //Librairies du mixage.. ( LOVE PARAPHRASE :-D )
#include <SDL_ttf.h> //Pour imprimer du texte graphiquement
#include <SDL_image.h> //Pour imprimer des images
#include <string.h> //Gestion des chaines

#include "includes/STJ_SDL.h" // librairie contenant la SDL pour le blackjack
#include "includes/BlackJack.h"	

SDL_Surface *screen = NULL;

SDL_Color couleurRouge = {255, 0, 0};
SDL_Color couleurBlanche = {255, 255, 255};
SDL_Color couleurNoire = {0, 0, 0};

SDL_Event GlobalEvent;

int channel = 0;	
Mix_Chunk *sound = NULL;

//BlackJack vars
// définition d'un tableau de 52 emplacements, représentant le jeu de cartes
short cartes[52];
// definition de la variable nb_as_joueur qui contient le nombre d'as d'un joueur
int nb_as_joueur = 0;
// définition de la variable nb_as_banque qui contient le nombre d'as de la banque 
int nb_as_banque = 0;
// définition de la variable nb_cartes_joueur qui contient le nombre de cartes du joueur
int nb_cartes_joueur = 0;
// définition de la variable nb_cartes_banque qui contient le nombre de cartes de la banque
int nb_cartes_banque = 0;

t_main mainjoueur[12]; // initialisation de la main du joueur
t_main mainbanque[12]; // initialisation de la main de la banque

t_main tas[50]; //Le tas de cartes

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

	char sommaire[N][M] = { "Partie locale", "Mes comptes", "Quitter"};
	
	TTF_Font *police_menu = NULL; //Police d'écriture pour le menu 
	TTF_Font *police_std = NULL; //Police pour tout le reste sauf menu
	
	int MenuChoix = 0;
    
	SPI_SDL_Init_Video(800,600,"BlackJack SDL Alpha",1,1); //800x600 +tff_support +audio_support
	
	//SDL_Splash("ressources/Splash0.png", 1500);
	//SDL_Splash("ressources/Splash1.png", 1500);
	
	police_menu = TTF_OpenFont("ressources/ttf/global.ttf", 25);
	police_std = TTF_OpenFont("ressources/ttf/global.ttf", 20);
	
	while (1) {
		
		MenuChoix = SDL_Create_Menu(police_menu, 3, sommaire); //On affiche un menu de cinq entrÈe
		
		switch (MenuChoix) {
			
			case 0: 
				//Contre CPU
				break;
				
			case 1:
				//Mes comptes
				break;
			
			case 2:
				//ByeBye..
				exit(0);
				break;
				
			default:
				break;
				
		}
		
	}
	return 0;
}
