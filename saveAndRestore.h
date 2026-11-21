#ifndef SAVEANDRESTORE_H_INCLUDED
#define SAVEANDRESTORE_H_INCLUDED

#include "towerdefendTypes.h"

/*
Auteur : Mimault Maxime
Signature : void saveNbInList(int NbUnit, FILE* saveBin)
int NbUnit : le nombre a sauvegarder
FILE* saveBin : le fichier ou est sauvegarder la donner
sauvegarde un nombre donnee
*/
void saveNbInList(int NbUnit, FILE* saveBin);

/*
Auteur : Mimault Maxime
Signature : void saveChemin(int** chemin, FILE* saveBin)
int** chemin : le chemin a sauvegarder
FILE* saveBin : le fichier dans lequel il est sauvegarder
sauvegarde le chemin
*/
void saveChemin(int** chemin, FILE* saveBin);

/*
Auteur : Mimault Maxime
Signature : void saveListHordeOuRoi(int NbList, TListePlayer player, FILE* saveBin)
int NbList : le nombre d'unite dans la liste
TListePlayer player : la liste a sauvegarder
FILE* saveBin : le fichier dans les sauvegardes sont faites
sauvegarde la liste du joueur
*/
//void saveListHordeOuRoi(int NbList, TListePlayer player, FILE* saveBin);

/*
Auteur : Mimault Maxime
Signature : int readNbInList(FILE* saveBin)
Lis le nombre d'unite dans une liste
*/
int readNbInList(FILE* saveBin);

/*
Auteur : Mimault Maxime
Signature : int** readChemin(int** chemin, FILE* saveBin)
Lis le chemin sauvegarder dans le fichier
*/
int** readChemin(int** chemin, FILE* saveBin);

/*
Auteur : Mimault Maxime
Signature : void readListHordeOuRoi(int NbList, TListePlayer* player, FILE* saveBin,Tunite **roiGlobal)
Lis les unitees sauvegarder dans le fichier (de chaque joueur) et mets a jour la position du roi dans la liste
*/
//void readListHordeOuRoi(int NbList, TListePlayer* player, FILE* saveBin,Tunite **roiGlobal);


void sauvegardeBin(const char *fileName, const TListePlayer Horde, const TListePlayer Roi,int** tabParcours, const TJeu *etatJeu);

void chargementBin(const char *fileName, TListePlayer *Horde, TListePlayer *Roi, int** tabParcours, TJeu *etatJeu, Tunite **uniteRoiGlobal, TplateauJeu jeu);
/*
Auteur : Munteanu Stefanel
Signature fonction : void sauvegardeSeq(const char *fileName, TListePlayer listeHorde, TListePlayer listeRoi, int** tabParcours, TJeu EtatJeu)
Fonction qui permet de sauvegardes les données dynamiques d'une partie dans un fichier séquentiel.
Forme du fichier Séquentiel :
nbToursJeu vagueEncours nbUnitesVagues cooldownVague
tabParcours[0][X] tabParcours[0][Y]
...
tabParcours[NBCOORDPARCOURS-1][X] tabParcours[NBCOORDPARCOURS-1][Y]
getNbUnites(listeHorde)
nom pointsDeVie posX posY indiceChemin
...
nom pointsDeVie posX posY indiceChemin
getNbUnites(listeRoi)
nom pointsDeVie posX posY indiceChemin
...
nom pointsDeVie posX posY indiceChemin
*/
void sauvegardeSeq(const char *fileName, const TListePlayer listeHorde, const TListePlayer listeRoi, int** tabParcours, const TJeu *etatJeu);

/*
Auteur : Munteanu Stefanel
Signature fonction : Tunite *chargerUnite(FILE *file)
FILE *file : le fichier (QUI EST ICI OUVERT)
Fonction qui recrée une unité pour champ [nom pointsDeVie posX posY indiceChemin] sauvegardé
Cette fonction suppose qu'on a avancé correctement avec chargementSeq
*/
Tunite *chargerUnite(FILE *file);

/*
Auteur : Munteanu Stefanel
Signature fonction : chargementSeq(const char *fileName, TListePlayer *listeHorde, TListePlayer *listeRoi, int** tabParcours,
                                   TJeu *etatJeu, Tunite **roiGlobal, TplateauJeu jeu)
Fonction qui charge une partie sauvegardé dans un fichier séquentiel fixe, en mettant à jour les champs dynamiques du jeu, soit:
listeHorde, listeRoi, tabParcours, etatJeu, jeu
Mais aussi le pointeur roiGlobal, qui permet d'avoir accès au roi directement en O(1)
*/
void chargementSeq(const char *fileName, TListePlayer *listeHorde, TListePlayer *listeRoi, int** tabParcours, TJeu *etatJeu, Tunite **roiGlobal, TplateauJeu jeu);

#endif // SAVEANDRESTORE_H_INCLUDED
