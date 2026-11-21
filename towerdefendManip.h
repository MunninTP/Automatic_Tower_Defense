#ifndef TOWERDEFENDMANIP_H_INCLUDED
#define TOWERDEFENDMANIP_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include "towerdefendTypes.h"

Tunite *creeTourSol(int posx, int posy);
Tunite *creeTourAir(int posx, int posy);
Tunite *creeTourRoi(int posx, int posy);
Tunite *creeDragon(int posx, int posy);
Tunite *creeGargouille(int posx, int posy);
Tunite *creeChevalier(int posx, int posy);
Tunite *creeArcher(int posx, int posy);

/*----------------------------------------FONCTIONS DE MANIPULATION POUR UNE TUNITE----------------------------------------*/

//FONCTIONS DE TYPE GET/SET POUR L'ENCAPSULATION DES UNITES
int get_IndiceCheminUnit(const Tunite* unite);
int get_VitesseDeplacUnit(const Tunite* unite);
void set_PositionUnit(Tunite* unite, int newposX, int newposY, int newIndice);
void set_PositionTour(Tunite* unite, int newposX, int newposY, int scoreEmplacement);
int get_PosXUnit(const Tunite* unite);
int get_PosYUnit(const Tunite* unite);
int get_PorteeUnit(const Tunite* unite);
int get_ScoreEmplacement(const Tunite* unite);
void addPvUnit(Tunite *unite, int pv);
void increaseDmgUnit (Tunite* unite, int degatsExtra);
void increaseAtkSpdUnit(Tunite *unite, float atkspdExtra);
TCamp get_CampUnit(const Tunite *unite);
TuniteDuJeu get_NomUnit(const Tunite *unite);
Tcible get_PositionUnit(const Tunite *unite);
Tcible get_PosAtkUnit(const Tunite *unite);
int get_DegatsUnit(const Tunite *unite);
void unitePrendsDegats(Tunite *unite, int degats);
int get_PvUnit(const Tunite *unite);
void set_PvUnit(Tunite *unite, int newPv);
void set_IndiceCheminUnit(Tunite *unite, int newIndice);
void set_cibleUnit(Tunite *unite, Tunite *cible);
Tunite* get_cibleUnit(const Tunite *unite);

/*
Auteur : Mimault Maxime
Signature : bool uniteEstVivante(Tunite* unite)
Tunite* unite : l'unite a verifier
Indique si une unite donnee est vivante
*/
bool uniteEstVivante(const Tunite* unite);

/*
Auteur : Mimault Maxime
Signature : void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu)
TListePlayer player : le camps dans lequel on veut mettre les unites sur le plateau
TplateauJeu : le plateau de jeu
Positionne les unites d'un joueur donnee sur le plateau de jeu
*/
void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu);

/*
Auteur : Munteanu Stefanel
Signature fonction : void positionneUniteOnPlateau(Tunite *unite, TplateauJeu jeu)
Tunite *unite : l'unite considérée
TPlateauJeu jeu : le plateau de jeu
Fonction qui place une unite sur le plateau de jeu, pour un affichage incrémental
*/
void positionneUniteOnPlateau(Tunite *unite, TplateauJeu jeu);

/*
Auteur : Munteanu Stefanel
Signature fonction : void supprimeUniteDuPlateau(Tunite *unite, TplateauJeu jeu)
Tunite *unite : l'unite considérée
TPlateauJeu jeu : le plateau de jeu
Fonction qui supprime une unite du plateau de jeu, pour un affichage incrémental
*/
void supprimeUniteDuPlateau(Tunite *unite, TplateauJeu jeu);

/*----------------------------------------FONCTIONS DE MANIPULATION POUR UNE TUNITE END----------------------------------------*/

/*----------------------------------------FONCTIONS DE MANIPULATION POUR UNE TLISTEPLAYER----------------------------------------*/

TListePlayer getNextCell(const TListePlayer playerList);

int getNbUnits (const TListePlayer playerList);

Tunite *getPdata(const TListePlayer playerList);

/*fonction qui affiche l'ensemble des unites d'une playerList*/
void afficheListeUnites(const TListePlayer playerList);

/*Permet de swap des PtrData, utile pour le tri selection*/
void swapPtrData(TListePlayer source, TListePlayer destination);

/*Permet de renvoyer la derniere case de la TListePlayer*/
TListePlayer getLastCell(const TListePlayer player);

/*Fusionne 2 listes et renvoie une nouvelle liste a part*/
TListePlayer fusionListes(const TListePlayer listePlayer1, const TListePlayer listePlayer2);

/*Fonction qui nettoie une liste des unites mortes. Supprimes cellules+pdata associes*/
void nettoyerListe(TListePlayer *listePlayer);

/*Fonction qui detruit une liste completement*/
void detruireListe(TListePlayer *listePlayer);

/*Fonction qui free l'ensemble des cellules, MAIS PAS DES PDATA*/
void freeListeCellules(TListePlayer listePlayer);

/*Supprime une unite de la liste des unites du joueur*/
void supprimerUnite(TListePlayer* player, Tunite *UniteDetruite);

/*Ajoutes une nouvelle unite dans la liste du joueur, ainsi que sur le plateau de jeu*/
void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite);

/*----------------------------------------FONCTIONS DE MANIPULATION POUR UNE TLISTEPLAYER END----------------------------------------*/

/*----------------------------------------FONCTIONS DE COMPARAISON----------------------------------------*/

bool comp_pv_AinfB(const Tunite *A, const Tunite *B);
bool comp_unite_AegalB(const Tunite *A, const Tunite *B);
bool comp_vitesseATK_AsupB(const Tunite *A, const Tunite *B);
bool comp_indChemin_AsupB(const Tunite *A, const Tunite *B);

/*----------------------------------------FONCTIONS DE COMPARAISON END----------------------------------------*/

/*----------------------------------------FONCTION DE TRI----------------------------------------*/
void tri_selection_TLP(TListePlayer l, bool (*fcomp) (const Tunite *a, const Tunite *b));

/*----------------------------------------FONCTIONS AUXILIAIRES----------------------------------------*/
/*
Auteur : Munteanu Stefanel
Signature fonction : int maxVal(int a, int b)
Fonction qui renvoie la plus grande valeur entre a et b
*/
int maxVal(int a, int b);

/*
Auteur : Munteanu Stefanel
Signature fonction : int minVal(int a, int b)
Fonction qui renvoie la plus petite valeur entre a et b
*/
int minVal(int a, int b);

/*----------------------------------------FONCTIONS MANIPULATION PLATEAU----------------------------------------*/

void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur);

/*----------------------------------------FONCTIONS MANIPULATION TJEU----------------------------------------*/
int get_NbToursJeu(const TJeu *jeu);
int get_VagueEnCours(const TJeu *jeu);
int get_NbUnitesVague(const TJeu *jeu);
int get_CooldownVague(const TJeu *jeu);

void set_NbToursJeu(TJeu *jeu, int newNbToursJeu);
void set_VagueEnCours(TJeu *jeu, int newVagueEnCours);
void set_NbUnitesVague(TJeu *jeu, int newNbUniteVague);
void set_CooldownVague(TJeu *jeu, int newCooldownVague);

void increment_NbToursJeu(TJeu *jeu);
TJeu* creer_JeuStats();
void detruireJeu(TJeu *jeu);

/*----------------------------------------FONCTIONS MANIPULATION SAUVEGARDE BIN----------------------------------------*/
/*
Auteur : Mimault Maxime
Signature : void saveListHordeOuRoi(int NbList, TListePlayer player, FILE* saveBin)
int NbList : le nombre d'unite dans la liste
TListePlayer player : la liste a sauvegarder
FILE* saveBin : le fichier dans les sauvegardes
Fonction qui sauvegarde la liste du joueur

*/
void saveListHordeOuRoi(int NbList, TListePlayer player,  FILE* saveBin);

/*
Auteur : Mimault Maxime
Signature : void readListHordeOuRoi(int NbList, TListePlayer* player, FILE* saveBin,Tunite **roiGlobal)
Lis les unitees sauvegarder dans le fichier (de chaque joueur) et mets a jour la position du roi dans la liste
*/
void readListHordeOuRoi(int NbList, TListePlayer* player, FILE* saveBin, Tunite** roiGlobal);





#endif // TOWERDEFENDMANIP_H_INCLUDED
