/**
 * \file STJ_SDL.c
 * \brief Librairies SDL/C 1.2
 * \author TAHRI Ahmed, SIMON J�r�my, DEZERE Florian, PROVOST Valentin
 * \version 0.2
 * \date 27 Octobre 2014
 *
 * Toutes les fonctions utiles la SDL
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h> //Librairies du mixage.. ( LOVE PARAPHRASE :-D )
#include <SDL_ttf.h> //Pour imprimer du texte graphiquement
#include <SDL_image.h> //Pour imprimer des images
#include <string.h> //Gestion des chaines

#include "includes/STJ_SDL.h"
#include "includes/bj_engine.h"

/** 
* \fn void SPI_SDL_Init_Video(int x, int y, char titre[100], int ttf_support, int audio_support)
* \brief Initialise le son, la police d'ecriture et la taille de la fenetre pour l'affichage en SDL du blackjack
*
* \param x defini la taille de la fenetre 
* \param y defini la taille de la fenetre
* \param titre tableau de caractere contenant le tire de la fenetre 
* \param ttf_support entier definissant la police d'ecriture 
* \param audio_support entier definissant le support audio 
*/
void SPI_SDL_Init_Video(int x, int y, char titre[100], int ttf_support, int audio_support) {
	
    int sdl_start = 0;
	
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;
	
    /* Initialize SDL */
    if (audio_support == 1) {
    	sdl_start = SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    }else {
    	sdl_start = SDL_Init (SDL_INIT_VIDEO);
    }
    
    if (sdl_start < 0)
    {
        
        fprintf (stderr, "La SDL n'a pas pu s'initialiser: %s\n", SDL_GetError ());
        exit (1);
        
    }
    
	atexit (SDL_Quit);

    screen = SDL_SetVideoMode (x, y, 16, SDL_SWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL)
    {
        
        fprintf (stderr, "Impossible d'initialiser la fenetre en %ix%i mode 16 bits': %s\n", x, y ,SDL_GetError ());
        exit (2);
        
    }
    
	SDL_WM_SetCaption (titre, NULL);
	
	if (audio_support == 1) {
		
		if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
			
			fprintf (stderr, "Erreur d'initialisation audio: %s", Mix_GetError());
		    exit (1);
		    
		}
		
	}
	
	if (ttf_support == 1) {
		
		if(TTF_Init() == -1)
		{
	    	fprintf (stderr, "Erreur d'initialisation de la SDL_ttf !");
	        exit (1);
		}
		
		SDL_EnableUNICODE(1);
		
	}
	
}

int SDL_Create_Menu(TTF_Font *police, int nb_entre, char sommaire[N][M]) {
	
	int i = 0, action = 0;
	int lastevent = -1;

	sound = Mix_LoadWAV("ressources/snd/select.wav");
	
	//On ne quitte pas la boucle tant qu'aucune selection n'a �t� faite
	while (1) {
		
		action = SDL_WaitEvent(&GlobalEvent); /* R�cup�ration de l'�v�nement dans event (non-blocant) */
		
		SDL_Print_bg("ressources/images/app_bg.png", 0, 0); //Fond d'�cran
		SDL_Print_bg("ressources/images/BarreLaterale.png", 80, 25); //Barre du menu
		
		for (i = 0; i < nb_entre; i++) {
			SDL_Create_Menu_Ch(police, i, sommaire[i], 100, 100+(i*50));
		}
		
		if (lastevent != sel_menu_m) {
		
			SDL_Flip (screen);
			channel = Mix_PlayChannel(-1, sound, 0);
			lastevent = sel_menu_m;
		
		}
		
		if (action) {
				
			switch (GlobalEvent.type)
        	{
		        case SDL_MOUSEBUTTONDOWN: //Si on clique
		        	
					if (SDL_Souris_Survol(40, 230, 100, 100+(sel_menu_m*50)) == 1) {
						sound = Mix_LoadWAV("ressources/snd/enter.wav");
						channel = Mix_PlayChannel(-1, sound, 0);
						while(Mix_Playing(channel) != 0);
						return sel_menu_m;
					}
					
					break;
					
		        case SDL_QUIT:
		        
		        	exit (0);
					break;
					
			}
		}
		
		SDL_Delay(20);
		
	}
	
}

void SDL_Create_Menu_Ch(TTF_Font *police, int id, char titre[M], int x, int y) {
	
	SDL_Rect positionFond; //(dynamique)
	SDL_Surface *imageDeFond = NULL, *titre_ttf = NULL;
	positionFond.x = x;
	positionFond.y = y;
	
	int sel_souris = SDL_Souris_Survol(40, 230, x, y);
	
	
	//On charge l'image concern�e ++ si souris survol choix
	if (sel_souris == 1) {
		imageDeFond = IMG_Load("ressources/images/m_bg_s1.png");
		sel_menu_m = id;
	}else{
		imageDeFond = IMG_Load("ressources/images/m_bg_s0.png");
	}
	
	SDL_BlitSurface(imageDeFond, NULL, screen, &positionFond);
	
	titre_ttf = TTF_RenderText_Blended(police, titre, couleurBlanche);
	positionFond.x += 20;
	positionFond.y += 5;
	SDL_BlitSurface(titre_ttf, NULL, screen, &positionFond);
	
	SDL_FreeSurface(imageDeFond);
	SDL_FreeSurface(titre_ttf);
	
}

void SDL_Print_bg(char file[50], int x, int y) {
	
	SDL_Rect positionFond; //(dynamique)
	SDL_Surface *imageDeFond = NULL;
	
	positionFond.x = x;
	positionFond.y = y;
	
	if (x == 0 && y == 0) SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	
	imageDeFond = IMG_Load(file);
	
	SDL_BlitSurface(imageDeFond, NULL, screen, &positionFond);
	
	SDL_FreeSurface(imageDeFond);
	
}

void SDL_Print_popup() {
	
	SDL_Rect positionFond; //(dynamique)
	SDL_Surface *imageDeFond = NULL;
	
	positionFond.x = 100;
	positionFond.y = 100;
	
	//SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	
	imageDeFond = IMG_Load("ressources/images/popup.png");
	
	SDL_BlitSurface(imageDeFond, NULL, screen, &positionFond);
	
	SDL_FreeSurface(imageDeFond);
	
}

int SDL_Souris_Survol(int hauteur, int largeur, int x, int y) {
	
	if ( GlobalEvent.button.y > y && GlobalEvent.button.y <= y+hauteur && GlobalEvent.button.x > x && GlobalEvent.button.x <= x+largeur ) {
		return 1;
	}else{
		return 0;
	}
	
}

void SDL_Open_PopUp(int ligne, TTF_Font *police, char txt_ligne1[200], char txt_ligne2[200], char txt_ligne3[200]) {
	
	int action = 0;
	
	while (1) {
		
		action = SDL_WaitEvent(&GlobalEvent); /* R�cup�ration de l'�v�nement dans event (non-blocant) */
		
		//SDL_Print_bg("ressources/images/", 0, 0);
		SDL_Print_popup();
		
		SDL_Write_popup(ligne, police, txt_ligne1, txt_ligne2, txt_ligne3);
		SDL_Print_Btn(1, police, "OK", 270, 300);
		
		SDL_Flip (screen);
		
		if (action) {
			switch (GlobalEvent.type)
        	{
		        case SDL_MOUSEBUTTONDOWN: //Si on clique
		        	
					if (SDL_Souris_Survol(40, 140, 270, 300) == 1) {
						return;
					}
					break;
					
		        case SDL_QUIT:
		        	exit (0);
					break;
			}
		}
		
		
		SDL_Delay (20);
		
	}
	
}

void SDL_Write_popup(int ligne, TTF_Font *police, char txt_ligne1[200], char txt_ligne2[200], char txt_ligne3[200]) {
	
	SDL_Surface *ligne1 = NULL, *ligne2 = NULL, *ligne3 = NULL;
	SDL_Rect positionLigne;
	
	positionLigne.x = 110;
	positionLigne.y = 140;
	
	switch (ligne) {
		
		case 1:
			ligne1 = TTF_RenderText_Blended(police, txt_ligne1, couleurBlanche);
			
			SDL_BlitSurface(ligne1, NULL, screen, &positionLigne);
			SDL_FreeSurface(ligne1);
			break;
		case 2:
			ligne1 = TTF_RenderText_Blended(police, txt_ligne1, couleurBlanche);
			ligne2 = TTF_RenderText_Blended(police, txt_ligne2, couleurBlanche);
			
			SDL_BlitSurface(ligne1, NULL, screen, &positionLigne);
			positionLigne.y += 25;
			SDL_BlitSurface(ligne2, NULL, screen, &positionLigne);
			
			SDL_FreeSurface(ligne1);
			SDL_FreeSurface(ligne2);
			break;
		case 3:
			ligne1 = TTF_RenderText_Blended(police, txt_ligne1, couleurBlanche);
			ligne2 = TTF_RenderText_Blended(police, txt_ligne2, couleurBlanche);
			ligne3 = TTF_RenderText_Blended(police, txt_ligne3, couleurBlanche);
			
			SDL_BlitSurface(ligne1, NULL, screen, &positionLigne);
			positionLigne.y += 25;
			SDL_BlitSurface(ligne2, NULL, screen, &positionLigne);
			positionLigne.y += 25;
			SDL_BlitSurface(ligne3, NULL, screen, &positionLigne);
			
			SDL_FreeSurface(ligne1);
			SDL_FreeSurface(ligne2);
			SDL_FreeSurface(ligne3);
			
			break;
	}
	
	
	
}

void SDL_Print_Btn(int id,TTF_Font *police, char titre[30], int x, int y) {
	
	SDL_Rect positionFond; //(dynamique)
	SDL_Surface *imageDeFond = NULL, *titre_ttf = NULL;
	
	positionFond.x = x;
	positionFond.y = y;
	
	int sel_souris = SDL_Souris_Survol(40, 140, x, y);
	
	//On charge l'image concern�e ++ si souris survol choix
	if (sel_souris == 1) {
		imageDeFond = IMG_Load("ressources/images/btn_s1.png");
		sel_menu_m = id;
	}else{
		imageDeFond = IMG_Load("ressources/images/btn_s0.png");
	}
	
	SDL_BlitSurface(imageDeFond, NULL, screen, &positionFond);
	
	titre_ttf = TTF_RenderText_Blended(police, titre, couleurNoire);
	positionFond.x += 50;
	positionFond.y += 5;
	SDL_BlitSurface(titre_ttf, NULL, screen, &positionFond);
	
	SDL_FreeSurface(imageDeFond);
	SDL_FreeSurface(titre_ttf);
	
}

void SDL_Print_Form(int id, TTF_Font *police, char titre[30], int etat, char dest[], int * sel_souris_form, int x, int y) {
	
	SDL_Rect positionFond; //(dynamique)
	SDL_Surface *imageDeFond = NULL, *titre_ttf = NULL, *saisie_ttf = NULL;
	char saisie_content[100];
	
	memset (saisie_content, 0, sizeof (saisie_content));
	
	positionFond.x = x;
	positionFond.y = y;
	
	int sel_souris = SDL_Souris_Survol(40, 400, x, y);
	
	if ((sel_souris == 1) && (GlobalEvent.type == SDL_MOUSEBUTTONDOWN)) {
		*sel_souris_form = id;
		strcpy (saisie_content,dest);
  		strcat (saisie_content,"|");
  		//puts (saisie_content);
	}else if(id == *sel_souris_form) {
		strcpy (saisie_content,dest);
  		strcat (saisie_content,"|");
  		//puts (saisie_content);
	}else{
		strcpy (saisie_content,dest);
	}
	
	
	//On charge l'image concern�e ++ si souris survol choix
	if (etat == 1) {
		imageDeFond = IMG_Load("ressources/images/ch_saisie_actif.png");
		//sel_menu_m = id;
	}else{
		imageDeFond = IMG_Load("ressources/images/ch_saisie_grise.png");
	}
	
	SDL_BlitSurface(imageDeFond, NULL, screen, &positionFond);
	
	saisie_ttf = TTF_RenderText_Blended(police, saisie_content, couleurNoire);
	positionFond.x = x+10;
	positionFond.y = y+5;
	SDL_BlitSurface(saisie_ttf, NULL, screen, &positionFond);
	
	titre_ttf = TTF_RenderText_Blended(police, titre, couleurBlanche);
	positionFond.x = x-55;
	positionFond.y = y+5;
	SDL_BlitSurface(titre_ttf, NULL, screen, &positionFond);
	
	SDL_FreeSurface(imageDeFond);
	SDL_FreeSurface(titre_ttf);
	
}

void SDL_Print_Cards(int id, int cardid, int x, int y) {
	
	SDL_Rect positionFond; //(dynamique)
	SDL_Surface *imageDeFond = NULL;
	char msg[100];
	int calcPos = 0;
	
	positionFond.x = x;
	positionFond.y = y;
	
	//int sel_souris = SDL_Souris_Survol(71, 96, x, y); //Une carte est de la taille 71x96
				
		if ((joueurs[id].jeu[cardid].couleur) == trefles) {
			calcPos = 1;
		}else if ((joueurs[id].jeu[cardid].couleur) == carreaux) {
			calcPos = 14;
		}else if ((joueurs[id].jeu[cardid].couleur) == coeurs) {
			calcPos = 27;
		}else{
			calcPos = 40;
		}
			
		switch (joueurs[id].jeu[cardid].valeur) {
			
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
			
	
	sprintf(msg, "ressources/images/cartes/%i.BMP", calcPos);
	imageDeFond = IMG_Load(msg);
	
	SDL_BlitSurface(imageDeFond, NULL, screen, &positionFond);
	SDL_FreeSurface(imageDeFond);
	
}

void SDL_Print_Score(TTF_Font *police, int score, int x, int y) {

	SDL_Rect positionFond; //(dynamique)
	SDL_Surface *titre_ttf = NULL;
	char ScoreStr[4];
	
	sprintf(ScoreStr, "%i", score);
	
	positionFond.x = x;
	positionFond.y = y;
	
	if (score <= 21) {
		titre_ttf = TTF_RenderText_Blended(police, ScoreStr, couleurNoire);
	}else{
		titre_ttf = TTF_RenderText_Blended(police, ScoreStr, couleurRouge);
	}
	
	SDL_BlitSurface(titre_ttf, NULL, screen, &positionFond);
	SDL_FreeSurface(titre_ttf);

}

void SDL_Print_Bet(TTF_Font *police, long bet, int x, int y) {

	SDL_Rect positionFond; //(dynamique)
	SDL_Surface *titre_ttf = NULL;
	char ScoreStr[50];
	
	sprintf(ScoreStr, "%li euros", bet);
	
	positionFond.x = x;
	positionFond.y = y;
	
	titre_ttf = TTF_RenderText_Blended(police, ScoreStr, couleurBlanche);
	
	SDL_BlitSurface(titre_ttf, NULL, screen, &positionFond);
	SDL_FreeSurface(titre_ttf);

}

void SDL_Print_Money(TTF_Font *police, long solde, int x, int y) {

	SDL_Rect positionFond; //(dynamique)
	SDL_Surface *titre_ttf = NULL;
	char ScoreStr[50];
	
	sprintf(ScoreStr, "%li", solde);
	
	positionFond.x = x;
	positionFond.y = y;
	
	titre_ttf = TTF_RenderText_Blended(police, ScoreStr, couleurBlanche);
	
	SDL_BlitSurface(titre_ttf, NULL, screen, &positionFond);
	SDL_FreeSurface(titre_ttf);

}


int SDL_Ask_Bet(TTF_Font *police){
	
	int action = 0, sel_saisie = 0, taille_saisie = 0;
	char str_betvalue[100], temps = 0;
	
	memset(str_betvalue, 0, sizeof(str_betvalue));
	
	while (1) {
		
		action = SDL_WaitEvent(&GlobalEvent); /* R�cup�ration de l'�v�nement dans event (non-blocant) */
		
		//SDL_Print_bg("ressources/images/", 0, 0);
		SDL_Print_popup();
		SDL_Print_Form(1, police, "Mise:", 1, str_betvalue, &sel_saisie, 165, 150);
		//SDL_Write_popup(ligne, police, txt_ligne1, txt_ligne2, txt_ligne3);
		SDL_Print_Btn(1, police, "Let's roll", 270, 300);
		
		SDL_Flip (screen);
		
		if (action) {
			switch (GlobalEvent.type)
        	{
		        case SDL_MOUSEBUTTONDOWN: //Si on clique
		        	
					if (SDL_Souris_Survol(40, 140, 270, 300) == 1) {
					
						return atoi(str_betvalue);
						
					}
					break;
					
				case SDL_KEYDOWN: //Si on enfonce une touche
                   
                    temps=GlobalEvent.key.keysym.unicode;
                   
                    switch (sel_saisie) {
                       
                        case 1: //Saisie bet..
                           
                            if (taille_saisie < 35) {
                               
                                if (temps == '\b' || temps == 127) { //127 pour clavier MacOS X BT
                               
                                    if (taille_saisie > 0) {
                                        taille_saisie--;
                                        str_betvalue[taille_saisie] = 0;
                                    }           
                                           
                                }else if (temps >= '0' && temps <= '9') {
                                           
                                    str_betvalue[taille_saisie] = temps;
                                    taille_saisie++; 
                                   
                                }
                               
                            }
                           
                        break;
                        
                    }
                    break;
					
		        case SDL_QUIT:
		        	exit (0);
					break;
			}
		}
		
		
		SDL_Delay (20);
		
	}
	
}

int SDL_Create_Local(TTF_Font *police, int nb_entre, char sommaire[N][M]) {

	int i = 0, action = 0;
	int lastevent = -1;
	
	int firstDraw = 0, lastMoveDone = 0, lastMoveBk = 0;
	int setWaitEvent = 0;
	int instantBlackJack = 0; 

	sound = Mix_LoadWAV("ressources/snd/select.wav");
	BJ_attrCard(0); //Donne une carte au dealer
	
	//On ne quitte pas la boucle tant qu'aucune selection n'a �t� faite
	while (1) {
		
		if (setWaitEvent == 1) {
			action = SDL_WaitEvent(&GlobalEvent); /* R�cup�ration de l'�v�nement dans event (non-blocant) */
		}
		
		SDL_Print_bg("ressources/images/app_bg_ingame.png", 0, 0); //Fond d'�cran
		
		for (i = 0; i < nb_entre; i++) {
			SDL_Create_Menu_Ch(police, i, sommaire[i], 50+(i*230), 530);
		}
		
		if (firstDraw < 2) {
			
			BJ_attrCard(1);
			
			effect = Mix_LoadWAV("ressources/snd/deal.wav");
			channel_effect = Mix_PlayChannel(-1, effect, 0);
			
			firstDraw++;
			if (firstDraw >= 2) setWaitEvent = 1;
			lastevent = 0;
			
			//Check if immediate BlackJack!
			if (BJ_getScore(1) == 21) {
				instantBlackJack = 1;
			}
			
		}else if ((lastMoveDone == 1)&&(BJ_getScore(0) < 17)){
			
			BJ_attrCard(0);
			
			effect = Mix_LoadWAV("ressources/snd/deal.wav");
			channel_effect = Mix_PlayChannel(-1, effect, 0);
			
			lastevent = 0;
			
			if (BJ_getScore(0) >= 17) {
				lastMoveBk = 1;
				setWaitEvent = 1;
			}
		}
		
		//On imprime les cartes du joueurs
		for (i = 0; i < joueurs[1].nbCard; i++) {
			SDL_Print_Cards(1, i, 350+(30*i), 380);
		}
		
		SDL_Print_Score(police, BJ_getScore(1) , 330, 380);
		SDL_Print_Bet(police, joueurs[1].mise, 350, 360);
		
		//Aussi celle du banquier ..!
		for (i = 0; i < joueurs[0].nbCard; i++) {
			SDL_Print_Cards(0, i, 350+(30*i), 100);
		}
		
		SDL_Print_Score(police, BJ_getScore(0) , 330, 100);
		SDL_Print_Money(police, joueurs[1].solde, 115, 580);
		
		
		if (lastevent != sel_menu_m) {
		
			SDL_Flip (screen);
			channel = Mix_PlayChannel(-1, sound, 0);
			lastevent = sel_menu_m;
		
		}
		
		//First blood!
		if (instantBlackJack == 1) {
			
			nbVictoireConseq++;
			effect = Mix_LoadWAV("ressources/snd/female/killingspree.wav");
			channel_effect = Mix_PlayChannel(-1, effect, 0);
			SDL_Open_PopUp(3, police, "Holy shit! Vous etes pas trop rentable comme joueur..!", "Beau BlackJack !", "Partie finie..");
			BJ_setMonney(1, ((joueurs[1].mise)*2)+((joueurs[1].mise)/2));
			return 0;
		}
		
		if (BJ_getScore(1) > 21) {
			
			//Grill�..
			effect = Mix_LoadWAV("ressources/snd/lose.wav");
			channel_effect = Mix_PlayChannel(-1, effect, 0);
			nbVictoireConseq = 0;
			SDL_Open_PopUp(2, police, "Vous etes crame.. Merci pour les sous !", "La partie est finie", "");
			
			return 0;
			
		}else if (BJ_getScore(0) > 21) {
			
			nbVictoireConseq++;
			if (nbVictoireConseq == 2) {
					
				effect = Mix_LoadWAV("ressources/snd/female/dominating.wav");
				channel_effect = Mix_PlayChannel(-1, effect, 0);
				
			}else if(nbVictoireConseq > 2) {
					
				effect = Mix_LoadWAV("ressources/snd/female/unstoppable.wav");
				channel_effect = Mix_PlayChannel(-1, effect, 0);
					
			}else {
				effect = Mix_LoadWAV("ressources/snd/aplause.wav");
				channel_effect = Mix_PlayChannel(-1, effect, 0);
			}
			SDL_Open_PopUp(2, police, "Vous avez gagne.. Je me suis grille!", "La partie est finie", "");
			BJ_setMonney(1, (joueurs[1].mise)*2);
			
			return 0;
		
		}else if (BJ_getScore(1) == 21) {
			
			effect = Mix_LoadWAV("ressources/snd/gotblackjack.wav");
			channel_effect = Mix_PlayChannel(-1, effect, 0);
			
			SDL_Open_PopUp(2, police, "Vous avez gagne.. BlackJack!!", "La partie est finie", "");
			BJ_setMonney(1, (joueurs[1].mise)*2);
			return 0;
			
		}
		
		
		if (lastMoveBk == 1) {
			
			if (BJ_getScore(1) > BJ_getScore(0)) {
				
				nbVictoireConseq++;
				if (nbVictoireConseq == 2) {
					
					effect = Mix_LoadWAV("ressources/snd/female/dominating.wav");
					channel_effect = Mix_PlayChannel(-1, effect, 0);
					
				}else if(nbVictoireConseq > 2) {
					
					effect = Mix_LoadWAV("ressources/snd/female/unstoppable.wav");
					channel_effect = Mix_PlayChannel(-1, effect, 0);
					
				}else {
					effect = Mix_LoadWAV("ressources/snd/aplause.wav");
					channel_effect = Mix_PlayChannel(-1, effect, 0);
				}
				SDL_Open_PopUp(2, police, "Vous avez gagne.. C'est juste de la chance !", "La partie est finie", "");
				BJ_setMonney(1, (joueurs[1].mise)*2);
				
				return 0;
				
			}else if (BJ_getScore(1) < BJ_getScore(0)) {
			
				//Humili�
				nbVictoireConseq = 0;
				effect = Mix_LoadWAV("ressources/snd/lose.wav");
				channel_effect = Mix_PlayChannel(-1, effect, 0);
				SDL_Open_PopUp(2, police, "Qui a le plus gros score..? Merci pour les sous !", "La partie est finie", "");
			
				return 0;
				
			}else if (BJ_getScore(1) == BJ_getScore(0)) {
				
				SDL_Open_PopUp(2, police, "Draw..! egalite!", "La partie est finie", "");
				BJ_setMonney(1, joueurs[1].mise);
				return 0;
				
			}
			
		}
		
		
		
		if (action) {
				
			switch (GlobalEvent.type)
        	{
		        case SDL_MOUSEBUTTONDOWN: //Si on clique
		        	
					if (SDL_Souris_Survol(40, 230, 50+(sel_menu_m*230), 530) == 1) {
						
						switch (sel_menu_m) {
							
							case 0: //Abandon
								
								sound = Mix_LoadWAV("ressources/snd/enter.wav");
								channel = Mix_PlayChannel(-1, sound, 0);
								while(Mix_Playing(channel) != 0);
								return sel_menu_m;
								break;
								
							case 1: //Rester.. Prend du recul.. c'est bien !
								
								if (lastMoveDone == 0) {
									//On prend des cartes pour le banquier jusqu'� au moins 17
									sound = Mix_LoadWAV("ressources/snd/enter.wav");
									channel = Mix_PlayChannel(-1, sound, 0);
									lastMoveDone = 1;
									setWaitEvent = 0;
								}
								
								break;
								
							case 2: //Frapper.. Courageux..! On demande une autre carte
							
								if (lastMoveDone == 0) {
									BJ_attrCard(1);
								
									effect = Mix_LoadWAV("ressources/snd/deal.wav");
									channel_effect = Mix_PlayChannel(-1, effect, 0);
									
									lastevent = 0;
								}
								
								break;
								
						}
						
						sound = Mix_LoadWAV("ressources/snd/select.wav");
						
					}
					
					break;
					
		        case SDL_QUIT:
		        
		        	exit (0);
					break;
					
			}
		}
		
		if (setWaitEvent == 0) {
			SDL_Delay(400);
		}else{
			SDL_Delay(25);
		}
		
		
	}

}

void SDL_Ambiance(char musicfic[100]) {
	
	char chemin_complet[200];
	
	if (Mix_Playing(channel_music) == 0) {
		
		sprintf(chemin_complet, "ressources/snd/%s", musicfic);
		music = Mix_LoadWAV(chemin_complet);
		channel_music = Mix_PlayChannel(-1, music, 0);
		Mix_Volume(channel_music, 10);
	}
	
}

void SDL_Splash(char img[100], int attente) {
	
	SDL_Rect positionFond; //(dynamique)
	SDL_Surface *imageDeFond = NULL;
	//int i = 0;
	
	positionFond.x = 0;
	positionFond.y = 0;

	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	
	imageDeFond = IMG_Load(img);
	SDL_BlitSurface(imageDeFond, NULL, screen, &positionFond);
	
		
	SDL_Flip (screen);
	SDL_FreeSurface(imageDeFond);
	SDL_Delay(attente);
	
}
