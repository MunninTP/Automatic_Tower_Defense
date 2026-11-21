#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "deployManip.h"
#include "towerdefendManip.h"

int calculerScoreEmplacement(const Tunite* unite, int** tabChemin){ //Changee
    if (tabChemin == NULL){
        return -1;
    }
    int scoreEmplacement = 0;
    int unitX, unitY, portee;
    unitX = get_PosXUnit(unite);
    unitY = get_PosYUnit(unite);
    portee = get_PorteeUnit(unite);

    //Pour chaque case du chemin
    for (int i = 0; i < NBCOORDPARCOURS; i++){
        int caseX = tabChemin[i][X], caseY = tabChemin[i][Y];
        //On calcule les differences (xChemin - xUnite) et (yChemin - yUnite), soit les distances en X/Y entre l'unite et la case de chemin
        int dX = caseX - unitX;
        int dY = caseY - unitY;
        //Eviter d'utiliser la fonction abs. On regarde si les distances calculees depassent la portee
        if (dX > portee || dX < -portee){
            continue;
        }
        if (dY > portee || dY < -portee){
            continue;
        }
        //Sion, la case est touchee par la tour. +1 au score
        scoreEmplacement++;
    }
    return scoreEmplacement;
}

bool caseEstDuChemin(int caseX, int caseY, int** tabParcours){
    for (int i =0; i < NBCOORDPARCOURS; i++){
        if (caseX == tabParcours[i][X] && caseY == tabParcours[i][Y]){
            return true;
        }
    }
    return false;
}

void reduireParcoursTab(int *xMin, int *xMax, int *yMin, int *yMax, int tourPortee, TplateauJeu jeu, int** tabParcours){
    for (int k = 0; k < NBCOORDPARCOURS; k++){
        int x = tabParcours[k][X];
        int y = tabParcours[k][Y];
        if (x < *xMin) {*xMin = x;}
        if (x > *xMax) {*xMax = x;}
        if (y < *yMin) {*yMin = y;}
        if (y > *yMax) {*yMax = y;}
    }

    *yMin -= tourPortee;
    *xMin -= tourPortee;
    *yMax += tourPortee;
    *xMax += tourPortee;

    if (*yMin < 0){ *yMin = 0;}
    if (*xMin < 0){ *xMin = 0;}
    if (*yMax >= HAUTEURJEU) {*yMax = HAUTEURJEU - 1;}
    if (*xMax >= LARGEURJEU) {*xMax = LARGEURJEU - 1;}
}

void determinerMeilleurEmplacementV2(Tunite *uniteTour, TplateauJeu jeu, int** tabParcours)
{
    int bestX = 0, bestY = 0, bestScore = 0, tmpBestScore = 0;
    int tourPortee = get_PorteeUnit(uniteTour);

    //On initialise les bornes
    int yMin = HAUTEURJEU - 1;
    int yMax = 0;
    int xMin = LARGEURJEU - 1;
    int xMax = 0;

    //On borne les valeurs de x et y a parcourir
    reduireParcoursTab(&xMin, &xMax, &yMin, &yMax,tourPortee, jeu, tabParcours);

    //On fait le parcours reduit
    for (int j = yMin; j <= yMax; j++){
        for (int i = xMin; i <= xMax; i++){
            //On skip les cases occupees et les cases chemins
            if (jeu[i][j] != NULL || caseEstDuChemin(i, j, tabParcours)){
                    continue;
            }
            else{
                Tunite* tmp = uniteTour;
                set_PositionTour(tmp, i, j, 0);
                tmpBestScore = calculerScoreEmplacement(tmp, tabParcours);
                if (tmpBestScore >= bestScore){
                        bestX = i;
                        bestY = j;
                        bestScore = tmpBestScore;
                }
            }
        }
    }

    //On fait la mise a jour finale
    set_PositionTour(uniteTour, bestX, bestY, bestScore);
}

Tunite* creerUniteRoiRandom(TplateauJeu jeu, int** tabParcours){
    //on choisi une tour au hasard
    Tunite* uniteRoi = NULL;
    int choix_unite = rand()%2;
    switch (choix_unite){
        //On a eu une tourSoul
        case 0:
            //on cree une unite provisoire pour recuperer certaines informations
            uniteRoi = creeTourSol(0, 0);
            break;
        //On a eu une tourAir
        case 1:
            //on cree une unite provisoire pour recuperer certaines informations
            uniteRoi = creeTourAir(0,0);
            break;
    }

    //On determine le meilleur emplacement pour la tour, et on met a jour l'unite du camp Roi
    determinerMeilleurEmplacementV2(uniteRoi, jeu, tabParcours);
    //Si le score de la tour est inferieure ou egale a 0, elle ne sert a rien
    if (get_ScoreEmplacement(uniteRoi) <= 0){
            free(uniteRoi);
            return NULL;
    }
    return uniteRoi;
}

Tunite* creerUniteHordeRandom(int cheminX, int cheminY, int level){
    Tunite* uniteHorde = NULL;
    //On choisi une unite horde au hasard
    int choix_unite = rand()%4+3;
    switch (choix_unite){
        case 3:
            uniteHorde = creeArcher(cheminX, cheminY);
            break;
        case 4:
            uniteHorde = creeChevalier(cheminX, cheminY);
            break;
        case 5:
            uniteHorde = creeDragon(cheminX, cheminY);
            break;
        case 6:
            uniteHorde = creeGargouille(cheminX, cheminY);
            break;
    }
    return uniteHorde;
}

Tunite* creerUniteRandom(TCamp campSouhaite, int** tabParcours, TplateauJeu jeu, int nbRoundsPassed){
    Tunite *unite = NULL;
    int spawnInt = rand()%100; //Entre 0 et 99
    //Si l'unite random souhaitee est du camp du roi
    if (campSouhaite == campRoi){
            //Si on peut spawn l'unite
            if (spawnInt < SPAWNRATETOWERS){
                //on choisi et cree une tour au hasard
                unite = creerUniteRoiRandom(jeu, tabParcours);
            }
    }
    //Sinon on cree une unite du camp horde
    else{
        int difficultyLevel = nbRoundsPassed/DIFFICULTYSETTER;
        //Si on peut spawn l'unite
        if (spawnInt < SPAWNRATEHORDE + difficultyLevel){
            //on verifie tout d'abord que le debut du chemin n'est pas occupe
            int cheminX = tabParcours[0][X];
            int cheminY = tabParcours[0][Y];
            //Si la case est libre
            if (jeu[cheminX][cheminY] == NULL){
                //On choisi et creer une unite horde au hasard
                unite = creerUniteHordeRandom(cheminX, cheminY, difficultyLevel);
                //On la met a jour
                upgradeUnit(unite, difficultyLevel);
            }
        }
    }
    return unite;
}

void upgradeUnit(Tunite *unite, int level){

    //Toutes les unites recoivent la meme augmentation de points de vie
    addPvUnit(unite, (level * 100));
    TuniteDuJeu nomUnite = get_NomUnit(unite);
    switch (nomUnite){
        case gargouille :
            addPvUnit(unite, (level * 10));
            break;
        case chevalier :
            increaseDmgUnit(unite, level);
            break;
        case archer :
            increaseDmgUnit(unite, (level / 2));
            break;
        case dragon :
            increaseAtkSpdUnit(unite, (0.1 * level));
            break;
        case tourRoi : break;
        case tourSol : break;
        case tourAir : break;
    }
}

