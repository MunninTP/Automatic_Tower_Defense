#ifndef MOVEMENTMANIP_H_INCLUDED
#define MOVEMENTMANIP_H_INCLUDED

#include "towerdefendTypes.h"


void ecritCheminVersleHaut(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante);
void ecritCheminVerslaDroite(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante);
void ecritCheminVerslaGauche(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante);

/*
Auteur : Munteanu Stefanel
Signature fonction : void avancerUnite(Tunite* unite, int** tabParcours, TplateauJeu jeu)
Tunite* unite : une unite du camp de la horde
int** tabParcours : le chemin du jeu
TplateauJeu jeu : le plateau de jeu
Fonction qui fait avancer une unité du camp de la horde de vitesseDeplacement cases (dans le cas du possible).
S'il y a une autre unité devant l'unité qui avance, elle s'arrête.
Une unité ne peut pas dépasser une autre, ou être sur la même case qu'une autre unité.
*/
void avancerUnite(Tunite* unite, int** tabParcours, TplateauJeu jeu);


#endif // MOVEMENTMANIP_H_INCLUDED
