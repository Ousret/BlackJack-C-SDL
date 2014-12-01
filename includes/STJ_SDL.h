/**
 * \file STJ_SDL.h
 * \brief Librairies SDL/C 1.2
 * \author TAHRI Ahmed, SIMON Jérémy, DEZERE Florian, PROVOST Valentin
 * \version 0.2
 * \date 27 Octobre 2014
 *
 * Toutes les fonctions utiles la SDL
 *
 */
 
#define N 10
#define M 50


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
void SPI_SDL_Init_Video(int x, int y, char titre[100], int ttf_support, int audio_support);


/**
 * \fn int SDL_Create_Menu(TTF_Font *police, int nb_entre, char sommaire[N][M])
 * \brief Fonction de création d'un menu avec selection à la souris
 *
 * \param *police Adresse de la police chargée avec SDL_TTF
 * \param nb_entre Nombre de choix du menu
 * \param sommaire[N][M] Le texte associé aux entrées du menu, matrice de NxM
 * \return L'identifiant (int) du bouton choisis, de 0 à nb_entre.
 */
int SDL_Create_Menu(TTF_Font *police, int nb_entre, char sommaire[N][M]);

/**
 * \fn void SDL_Create_Menu_Ch(TTF_Font *police, int id, char titre[M], int x, int y)
 * \brief Prépare l'affichage d'un bouton
 *
 * \param *police Adresse de la police chargée avec SDL_TTF
 * \param id Identifiant du bouton à charger en mémoire
 * \param titre Le texte associé au bouton
 * \param x Position en X du bouton (pixel)
 * \param y Position en Y du bouton (pixel)
 * \return Ne retourne rien
 */
void SDL_Create_Menu_Ch(TTF_Font *police, int id, char titre[M], int x, int y);

/**
 * \fn void SDL_Print_Btn(int id,TTF_Font *police, char titre[30], int x, int y)
 * \brief Prépare l'affichage d'un bouton
 *
 * \param id Identifiant du bouton à préparer
 * \param *police Adresse de la police chargée avec SDL_TTF
 * \param titre Intitulé du bouton
 * \param x Position X (pixel) 
 * \param y Position Y (pixel) 
 * \return Ne retourne rien
 */
void SDL_Print_Btn(int id,TTF_Font *police, char titre[30], int x, int y);

/**
 * \fn void SDL_Print_bg(char file[50], int x, int y)
 * \brief Imprime une image en arrière plan
 *
 * \param file Nom du fichier image PNG/JPG à imprimer
 * \param x Position X (pixel)
 * \param y Position Y (pixel)
 * \return Ne retourne rien
 */
void SDL_Print_bg(char file[50], int x, int y);

/**
 * \fn void SDL_Print_popup()
 * \brief Affiche la fenêtre popup formatée
 *
 * \return Ne retourne rien
 */
void SDL_Print_popup();

/**
 * \fn int SDL_Souris_Survol(int hauteur, int largeur, int x, int y)
 * \brief Vérifier si la souris est dans une zone donnée
 *
 * \param hauteur Hauteur (pixel) de la zone
 * \param largeur Largeur (pixel) de la zone
 * \param x Position (pixel) coin supérieur gauche
 * \param y Position (pixel) coin supérieur gauche
 * \return Renvoie 1 si la souris survol la zone 0 sinon.
 */
int SDL_Souris_Survol(int hauteur, int largeur, int x, int y);

/**
 * \fn void SDL_Write_popup(int ligne, TTF_Font *police, char txt_ligne1[200], char txt_ligne2[200], char txt_ligne3[200])
 * \brief Prépare l'affichage du texte sur une fenêtre popup
 *
 * \param ligne Nombre de ligne de texte à afficher
 * \param *police Adresse de la police chargée avec SDL_TTF
 * \param txt_ligne1 Première ligne de texte
 * \param txt_ligne2 Deuxième ligne de texte
 * \param txt_ligne3 Troisième ligne de texte
 * \return Ne retourne rien
 */
void SDL_Write_popup(int ligne, TTF_Font *police, char txt_ligne1[200], char txt_ligne2[200], char txt_ligne3[200]);

/**
 * \fn void SDL_Open_PopUp(int ligne, TTF_Font *police, char txt_ligne1[200], char txt_ligne2[200], char txt_ligne3[200])
 * \brief Ouvre une fenêtre popup et y insère des champs
 *
 * \param ligne Nombre de ligne de texte à afficher
 * \param *police Adresse de la police chargée avec SDL_TTF
 * \param txt_ligne1 Première ligne de texte
 * \param txt_ligne2 Deuxième ligne de texte
 * \param txt_ligne3 Troisième ligne de texte
 * \return Ne retourne rien
 */
void SDL_Open_PopUp(int ligne, TTF_Font *police, char txt_ligne1[200], char txt_ligne2[200], char txt_ligne3[200]);

/**
 * \fn void SDL_Print_Form(int id, TTF_Font *police, char titre[30], int etat, char dest[], int * sel_souris_form, int x, int y)
 * \brief Prépare l'affichage d'un champs de type formulaire
 *
 * \param id Identifiant du champs à préparer
 * \param *police Adresse de la police chargée avec SDL_TTF
 * \param titre Intitulé du champs
 * \param etat Champs accesible en écriture = 1 ou grisé = 0
 * \param dest Pointeur vers la destination, le contenu de la saisie y sera stocké et lu.
 * \param *sel_souris_from Pointeur vers un entier, identifiera si la souris survol le champs.
 * \param x Position X (pixel) du champs
 * \param y Position Y (pixel) du champs
 * \return Ne retourne rien
 */
void SDL_Print_Form(int id, TTF_Font *police, char titre[30], int etat, char dest[], int * sel_souris_form, int x, int y);

/**
 * \fn void SDL_Print_Cards(int id, int cardid, int x, int y)
 * \brief Prépare l'affichage d'une carte
 *
 * \param id Identifiant du joueur pour qui la carte sera imprimé
 * \param cardid Identifiant de la carte, son rang dans la structure joueurs.jeu
 * \param x Position X (pixel) de la carte
 * \param y Position Y (pixel) de la carte
 * \return Ne retourne rien
 */
void SDL_Print_Cards(int id, int cardid, int x, int y);

/**
 * \fn void SDL_Print_Score(TTF_Font *police, int score, int x, int y)
 * \brief Prépare l'affichage du score
 *
 * \param *police Adresse de la police d'écriture chargée avec SDL_TTF
 * \param score La valeur du score
 * \param x Position X (pixel) du score
 * \param y Position Y (pixel) du score
 * \return Ne retourne rien
 */
void SDL_Print_Score(TTF_Font *police, int score, int x, int y);

/**
 * \fn void SDL_Print_Bet(TTF_Font *police, long bet, int x, int y)
 * \brief Prépare l'affichage de la mise
 *
 * \param *police Adresse de la police d'écriture chargée avec SDL_TTF
 * \param bet Valeur de la mise
 * \param x Position X (pixel) de la mise
 * \param y Position Y (pixel) de la mise
 * \return Ne retourne rien
 */
void SDL_Print_Bet(TTF_Font *police, long bet, int x, int y);

/**
 * \fn void SDL_Print_Money(TTF_Font *police, long solde, int x, int y)
 * \brief Prépare l'affichage du solde
 *
 * \param *police Adresse de la police d'écriture chargée avec SDL_TTF
 * \param bet Valeur du solde
 * \param x Position X (pixel) du solde
 * \param y Position Y (pixel) du solde
 * \return Ne retourne rien
 */
void SDL_Print_Money(TTF_Font *police, long solde, int x, int y);

/**
 * \fn int SDL_Ask_Bet(TTF_Font *police)
 * \brief Ouvre une fenêtre popup pour demander une valeur de mise
 *
 * \param *police Adresse de la police d'écriture chargée avec SDL_TTF
 * \return Renvoie le montant de la mise
 */
int SDL_Ask_Bet(TTF_Font *police);

/**
 * \fn int SDL_Create_Local(TTF_Font *police, int nb_entre, char sommaire[N][M])
 * \brief Ouvre une session de jeu (locale)
 *
 * \param *police Adresse de la police d'écriture chargée avec SDL_TTF
 * \param nb_entre Nombre d'option possible durant le jeu
 * \param sommaire Matrice NxM contenant le texte associé aux options
 * \return Ne retourne rien de significatif
 */
int SDL_Create_Local(TTF_Font *police, int nb_entre, char sommaire[N][M]);

/**
 * \fn void SDL_Ambiance(char musicfic[100])
 * \brief Lance la lecture d'une musique en arrière plan (bas volume)
 *
 * \param musicfic Nom du fichier (*.wav) à lire en arrière plan
 * \return Aucune valeur de retours
 */
void SDL_Ambiance(char musicfic[100]);

/**
 * \fn void SDL_Splash(char img[100], int attente)
 * \brief Affiche un splash screen pendant (attente) ms
 *
 * \param img Nom du fichier image à afficher
 * \param attente Attente en millisecondes
 * \return Aucune valeur de retours
 */
void SDL_Splash(char img[100], int attente);

/** \brief Calque principal (sur lequel tout est superposé) */
extern SDL_Surface *screen;

/** \brief Couleurs RGB */
extern SDL_Color couleurRouge;
/** \brief Couleurs RGB */
extern SDL_Color couleurBlanche;
/** \brief Couleurs RGB */
extern SDL_Color couleurNoire;

/** \brief Contient la suite des événements capturés par la SDL (Clavier+Souris) */
extern SDL_Event GlobalEvent;
/* Fin pointeur SDL */

/* Variable pour le mixage */
extern int channel;	
/** \brief Mixage du son */
extern Mix_Chunk *sound;

extern Mix_Chunk *music;
/** \brief Mixage du son */
extern int channel_music;

extern int channel_effect;	
/** \brief Mixage du son */
extern Mix_Chunk *effect;

//SDL_mutex *MutexEcran = NULL; Inutile pour l'instant.. Faut s'en passer.. :D
//extern FILE * fichier_db;
/** \brief Identifiant du bouton survolé */
extern int sel_menu_m; //Indice du choix (menu) survolé à un moment t.