#ifndef TOWERDEFEND_H_INCLUDED
#define TOWERDEFEND_H_INCLUDED

#include <stdbool.h>
#include "SDL.h"
#include "towerdefendTypes.h"
#include "towerdefendManip.h"


TplateauJeu AlloueTab2D(int largeur, int hauteur);
void afficheCoordonneesParcours(int **t, int nbcoord);
void freeChemin(int **tab);

void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur);

/*-------------------------------------FONCTIONS A CODER----------------------------------------------*/

/*
Auteur : Mimault Maxime
Signature : bool tourRoiDetruite(Tunite tourRoi)
Tunite tourRoi : l'unite tour du roi
Retourne un boolean qui indique si le roi est toujours en vie ou pas (hp <= 0).
*/
bool tourRoiDetruite(const Tunite *tourRoi);

/*
Auteur : Mimault Maxime
Signature : int **initCheminRand()
Cree un chemin aleatoire, en fonction de DGH, droite si DGH = 1, gauche = 2, haut = 3
DGHprec sert a savoir ou on est allez precedement pour ne pas refaire la meme chose.
Les cases sont faites de deux en deux.
*/
int **initCheminRand();

/*
Auteur : Mimault Maxime
Signature : void phaseCombat(TListePlayer *Horde, TListePlayer *Roi, TplateauJeu jeu)
TListePlayer *Horde : la liste de la Horde
TListePlayer *Roi : la liste du Roi
TplateauJeu jeu : Le plateau de jeu
Fait tout les combats d'un tour de jeu
*/
void phaseCombat(TListePlayer *Horde, TListePlayer *Roi, TplateauJeu jeu);

/*
Auteur : Mimault Maxime
Signature : void jeuInit(TListePlayer *ListeRoi, Tunite** roi, int** tabParcours, TplateauJeu jeu)
Fonction qui initialise le jeu avec le roi et une tour.
*/
void jeuInit(TListePlayer *ListeRoi, Tunite** roi, int** tabParcours, TplateauJeu jeu);

/*
Auteur : Mimault Maxime
Signature : void dessinerToutesLesAttaques(TListePlayer Horde, TListePlayer Roi, SDL_Surface* surface)
Fonction qui fait le dessin de toutes les attaques. A l'appel de cette fonction aucune unité n'est free
*/
void dessinerToutesLesAttaques(TListePlayer Horde, TListePlayer Roi, SDL_Surface* surface);

/*
Auteur : Munteanu Stefanel
Signature fonction : void avancerHorde(TListePlayer listeHorde, int** tabParcours, TplateauJeu jeu)
TListePlayer listeHorde : la liste contenant l'ensemble des unités du camp de la horde
int** tabParcours : le chemin du jeu
TplateauJeu jeu : le plateau de jeu
Fonction qui fait avancer l'ensemble des unités du camp de la horde.
l'ordre de l'avancement est du plus proche Roi au plus loin, ainsi toutes les unités du camp de la Horde
avance au moins une fois.
Cete fonction ne fait rien si le chemin est rempli d'unités (getNbUnites(listeHorde) == NBCOORDPARCOURS)
*/
void avancerHorde(TListePlayer listeHorde, int** tabParcours, TplateauJeu jeu);

/*
Auteur : Munteanu Stefanel
Signature fonction : void phaseCreation(TListePlayer *listeHorde, TListePlayer *listeRoi, int** tabParcours, TplateauJeu jeu, Tjeu *etatJeu);
TListePlayer *listeHorde : la liste qui contient l'ensemble des unités de la Horde
TListePlayer *listeRoi : la liste qui contient l'ensemble des unités du Roi
int** tabParcours : le chemin du jeu
TplateauJeu jeu : le plateau de jeu
Fonction qui se charge de la phase de création du jeu, soit:
-Création (ou non), d'une tour, avec mis à jour de listeRoi et jeu appropriée (si créée);
-Création (ou non), d'une unité horde, avec mis à jour de listeHorde et jeu appropriée (si créée);
-Incréméntation de nbRoundsPassed de 1.
*/
void phaseCreation(TListePlayer *listeHorde, TListePlayer *listeRoi, int** tabParcours, TplateauJeu jeu, TJeu *etatJeu);


#endif // TOWERDEFEND_H_INCLUDED
