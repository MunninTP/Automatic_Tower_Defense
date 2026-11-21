#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "movementManip.h"
#include "towerdefendManip.h"

/*
void ecritCheminVersleHaut  : permet d'initilaiser le tab chemin de distance cases (avec des coord x y) dans une direction, a partir d'un point x y donne

int **chemin  : tab de coordonnees x y du chemin
int *ichemin  : indice de la case du chemin d'ou on part
int *xdepart, int *ydepart : valeur en x y de depart pouri la premiere case
int distance  : distance sur laquelle on va ecrire des coordonnees dans le tab chemin
int *distanceMaxRestante : securite pour ne pas sortir de la plage d'indice de chemin
*/
void ecritCheminVersleHaut(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante){
    if ((*distanceMaxRestante - distance)>=0){
        int y;
        for (y=*ydepart;y>*ydepart-distance;y--){
            chemin[*ichemin][X]= *xdepart;
            chemin[*ichemin][Y]= y;
            (*ichemin)++;
        }
        *ydepart=y;
    }
    else printf("erreur longueur chemin\n");
}

void ecritCheminVerslaDroite(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante){
    if ((*distanceMaxRestante - distance)>=0){
        int x;
        for (x=*xdepart;x<*xdepart+distance;x++){
            chemin[*ichemin][X]= x;
            chemin[*ichemin][Y]= *ydepart;
            (*ichemin)++;
        }
        *xdepart=x;
    }
    else printf("erreur longueur chemin\n");
}

void ecritCheminVerslaGauche(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante){
    if ((*distanceMaxRestante - distance)>=0){
        int x;
        for (x=*xdepart;x>*xdepart-distance;x--){
            chemin[*ichemin][X]= x;
            chemin[*ichemin][Y]= *ydepart;
            (*ichemin)++;
        }
        *xdepart=x;
    }
    else printf("erreur longueur chemin\n");
}

void avancerUnite(Tunite* unite, int** tabParcours, TplateauJeu jeu){
    int indiceTab = get_IndiceCheminUnit(unite), vitesseDeplacement = get_VitesseDeplacUnit(unite);
    //Si on est a la derniere case, on ne fait rien
    if (indiceTab == NBCOORDPARCOURS-1){
        return;
    }
    int newIndice = indiceTab;
    //On determine a quelle case on peut/doit aller
    for (int i = 1; (i <= vitesseDeplacement) && (indiceTab + i <= NBCOORDPARCOURS-1); i++){
        int testIndice = indiceTab + i;
        int testX = tabParcours[testIndice][X];
        int testY = tabParcours[testIndice][Y];
        //si la case qui suit est occupee, on sort, et les nouveaux coordonnes ne sont pas mises a jour
        if (jeu[testX][testY] != NULL){
            break;
        }
        //Sinon, l'unite peut aller a la prochaine case, et on continue la boucle (ou pas)
        newIndice = testIndice;
    }
    //On met a jour l'unite
    set_PositionUnit(unite, tabParcours[newIndice][X], tabParcours[newIndice][Y], newIndice);
}
