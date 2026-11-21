#ifndef DEPLOYMANIP_H_INCLUDED
#define DEPLOYMANIP_H_INCLUDED

#include "towerdefendTypes.h"

/*
Auteur : Munteanu Stefanel
Signature fonction : void reduireParcoursTab(int *xMin, int *xMax, int *yMin, int *yMax, int portee, TplateauJeu jeu, int** tabParcours)
int *xMin : adresse de la borne en xMin
int *xMax : adresse de la borne en xMax
int *yMin : adresse de la borne en yMin
int *yMax : adresse de la borne en yMax
int portee : la portee de la tour considérée dans determinerMeilleurEmplacementV2
TPlateauJeu jeu : le plateau de jeu
int** tabParcours : tableau qui contient l'ensemble du chemin du jeu
Fonction qui restreint la recherche du meilleur emplacement (c.f. determinerMeilleurEmplacementV2) pour ne
pas parcourir tout le tableau inutillement.
xMin = la plus petite valeur X trouvée de l'ensemble des cases du chemin
xMax = la plus grande valeur X trouvée de l'ensemble des cases du chemin
Même logique pour yMin/yMax avec Y
*/
void reduireParcoursTab(int *xMin, int *xMax, int *yMin, int *yMax, int portee, TplateauJeu jeu, int** tabParcours);

/*
Auteur : Munteanu Stefanel
Signature fonction : bool caseEstDuChemin(int caseX, int caseY, int** tabParcours)
int caseX : une coordonnée en x
int caseY : une coordonnée en y
int** tabParcours : le chemin du jeu
Fonction qui renvoie un booleen si une case de coordonnees (caseX, caseY) fait partie du chemin
*/
bool caseEstDuChemin(int caseX, int caseY, int** tabParcours);

/*
Auteur : Munteanu Stefanel
Signature fonction : int calculerScoreEmplacement(Tunite unite, int** tabChemin)
Tunite unite : l'unite considérée
int** tabChemin : le chemin du jeu
Fonction qui renvoie le nombre de cases du chemin qu'une unité (de type tour) peut toucher.
*/
int calculerScoreEmplacement(const Tunite* unite, int** tabChemin);

/*
Auteur : Munteanu Stefanel
Signature fonction : void determinerMeilleurEmplacementV2(Tunite *uniteTour, TplateauJeu jeu, int** tabParcours)
Tunite *uniteTour : l'unite de type tour considérée
TplateauJeu jeu : le plateau de jeu
int** tabParcours : le chemin du jeu
Fonction qui détermine le meilleur emplacement pour une uniteTour donnée, et met à jour ses champs
posX, posY, et score_emplacement.
*/
void determinerMeilleurEmplacementV2(Tunite *uniteTour, TplateauJeu jeu, int** tabParcours);

/*
Auteur : Munteanu Stefanel
Signature fonction : Tunite* creerUniteRoiRandom(TplateauJeu jeu, int** tabParcours)
TplateauJeu jeu : le plateau de jeu
int** tabParcours : le chemin du jeu
Fonction qui crée et retourne une unite aléatoire du camp du roi (autre qu'une tourRoi).
Si le score_emplacement calculé est 0, alors aucune unité n'est créée (l'unité est libérée + renvoie d'un pointeur NULL).
*/
Tunite* creerUniteRoiRandom(TplateauJeu jeu, int** tabParcours);

/*
Auteur : Munteanu Stefanel
Signature fonction : Tunite* creerUniteHordeRandom(int cheminX, int cheminY, int level)
int cheminX : la coordonnée en x du début du chemin
int cheminY : la coordonnée en y du début du chemin
int level : le niveau de l'unité horde
Fonction qui crée et retourne une unite aléatoire du camp de la horde.
Cette fonction renvoie forcément une unité.
*/
Tunite* creerUniteHordeRandom(int cheminX, int cheminY, int level);

/*
Auteur : Munteanu Stefanel
Signature fonction : Tunite* creerUniteRandom(TCamp campSouhaite, int** tabParcours, TplateauJeu jeu, int nbRoundsPassed)
TCamp campSouhaite : le camp de l'unité aléatoire qu'on souhaite créer
int** tabParcours : le chemin du jeu
TplateauJeu jeu : le plateau du jeu
int nbRoundsPassed : le nombre de tours du jeu passées, utilisé pour le calcul du niveau des unités Horde
Fonction qui crée et retourne une unite aléatoire d'un camp campSouhaite choisi.
Cette fonction peut renvoyer un NULL (Chemin rempli => pas d' unité Horde créée, score_emplacement = 0 pour une tour du Roi)
Le niveau d'une unité Horde est calculée avec nbRoundsPassed/DIFFICULTYSETTER, où DIFFICULTYSETTER (c.f. towerdefendTypes.h)
détermines après combien de tours de jeu on augment le niveau.
*/
Tunite* creerUniteRandom(TCamp campSouhaite, int** tabParcours, TplateauJeu jeu, int nbRoundsPassed);

/*
Auteur : Munteanu Stefanel
Signature fonction : void upgradeUnit(Tunite *unite, int level)
Tunite *unite : l'unite qu'on veut améliorer
int level : le niveau d'amelioration
Fonction qui améliore une unité selon le niveau de jeu atteint (c.f. creerUniteHordeRandom)
*/
void upgradeUnit(Tunite *unite, int level);


#endif // DEPLOYMANIP_H_INCLUDED
