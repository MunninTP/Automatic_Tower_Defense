#include <stdio.h>
#include <stdlib.h>

#include "saveAndRestore.h"
#include "towerdefendTypes.h"
#include "towerdefendManip.h"
#include "deployManip.h"


/*------------------------------------SAUVEGARDES BINAIRES START------------------------------------*/
//Sauvegarde un entier
void saveNbInList(int NbUnit, FILE* saveBin)
{
    fwrite(&NbUnit, sizeof(int), 1, saveBin);
}

//Sauvegarde les cases du chemin
void saveChemin(int** chemin, FILE* saveBin)
{
    for(int i = 0; i < NBCOORDPARCOURS; i++)
    {
        for(int j = 0; j < 2; j++) //deux for, 1 pour parcourir d'abord tout le tableau du chemin, le 2eme pour avoir X et Y
        {
            fwrite(&chemin[i][j], sizeof(int), 1, saveBin); //ecrit la coordonee (d'abord X puis Y)
        }
    }
}

//-----RESTAURATION-----

int readNbInList(FILE* saveBin)
{
    int nombre;
    fread(&nombre, sizeof(int), 1, saveBin);
    return nombre;
}

int** readChemin(int** chemin, FILE* saveBin) //ecrase l'ancien chemin
{
    for(int i = 0; i < NBCOORDPARCOURS; i++)
    {
        for(int j = 0; j < 2; j++) //deux for, 1 pour parcourir d'abord tout le tableau du chemin, le 2eme pour avoir X et Y
        {
            fread(&chemin[i][j], sizeof(int), 1, saveBin); //lis la coordonee (d'abord X puis Y)
        }
    }
    return chemin;
}

void sauvegardeBin(const char *fileName, const TListePlayer Horde, const TListePlayer Roi,
                    int** tabParcours, const TJeu *etatJeu)
{
    FILE* saveBin = fopen(fileName, "wb");

    //save le nb de d'unite dans la horde
    saveNbInList(getNbUnits(Horde), saveBin);
    saveListHordeOuRoi(getNbUnits(Horde), Horde, saveBin);
    //save le nb de d'unite dans la liste du roi
    saveNbInList(getNbUnits(Roi), saveBin);
    saveListHordeOuRoi(getNbUnits(Roi), Roi, saveBin);
    //save le chemin
    saveChemin(tabParcours, saveBin);

    fclose(saveBin); // ferme le fichier
}

void chargementBin(const char *fileName, TListePlayer *Horde, TListePlayer *Roi, int** tabParcours, TJeu *etatJeu, Tunite **uniteRoiGlobal, TplateauJeu jeu)
{
    detruireListe(Horde);
    detruireListe(Roi);
    initPlateauAvecNULL(jeu, LARGEURJEU, HAUTEURJEU);

    FILE* saveBin = fopen(fileName, "rb");

    int nbUnitHorde = readNbInList(saveBin);
    readListHordeOuRoi(nbUnitHorde, Horde, saveBin, uniteRoiGlobal);

    int nbUnitRoi = readNbInList(saveBin);
    readListHordeOuRoi(nbUnitRoi, Roi, saveBin, uniteRoiGlobal);

    //chemin
    tabParcours = readChemin(tabParcours, saveBin);

    fclose(saveBin); // ferme le fichier
    //MAJ du plateau de jeu
    PositionnePlayerOnPlateau(*Horde, jeu);
    PositionnePlayerOnPlateau(*Roi, jeu);
}

/*------------------------------------SAUVEGARDES BINAIRES END------------------------------------*/

/*------------------------------------SAUVEGARDES SEQUENTIELLES START------------------------------------*/
void sauvegardeSeq(const char *fileName, const TListePlayer listeHorde, const TListePlayer listeRoi,
                    int** tabParcours, const TJeu *etatJeu){
    //On ouvre le fichier
    FILE *f = fopen(fileName, "w");

    //On stocke l'etat actuel du jeu sous la forme : NbToursPases VagueEnCours nbUnitesVagues cooldownVague
    fprintf(f, "%d %d %d %d\n", get_NbToursJeu(etatJeu), get_VagueEnCours(etatJeu),
            get_NbUnitesVague(etatJeu), get_CooldownVague(etatJeu));

    //On sauvegarde les coordonees des cases du chemin
    for (int i = 0; i < NBCOORDPARCOURS; i++){
        fprintf(f, "%d %d\n", tabParcours[i][X], tabParcours[i][Y]);
    }

    //On sauvegarde le nb d'unites de la horde, ainsi que les unites
    int nbUnitesHordes = getNbUnits(listeHorde);
    fprintf(f, "%d\n", nbUnitesHordes);

    //On stocke les unites horde dans l'ordre suivante: nom pointsDeVie posX posY indiceChemin
    for (TListePlayer ptr = listeHorde; ptr != NULL; ptr = getNextCell(ptr)){
            Tunite *unit = getPdata(ptr);
            fprintf(f, "%d %d %d %d %d\n", get_NomUnit(unit), get_PvUnit(unit),
                     get_PosXUnit(unit), get_PosYUnit(unit), get_IndiceCheminUnit(unit));
    }

    //On sauvegarde le nb d'unites du roi, ainsi que les unites
    int nbUnitesRoi = getNbUnits(listeRoi);
    fprintf(f, "%d\n", nbUnitesRoi);

    //On stocke les unites Roi dans l'ordre suivante: nom pointsDeVie posX posY indiceChemin
    for (TListePlayer ptr = listeRoi; ptr != NULL; ptr = getNextCell(ptr)){
            Tunite *unit = getPdata(ptr);
            fprintf(f, "%d %d %d %d %d\n", get_NomUnit(unit), get_PvUnit(unit),
                     get_PosXUnit(unit), get_PosYUnit(unit), get_IndiceCheminUnit(unit));
    }

    //On ferme le fichier
    fclose(f);
}

Tunite *chargerUnite(FILE *file){
    int nom, pv, posX, posY, indiceChemin;

    //On recupere les stats de l'unite lors du save
    fscanf(file, "%d %d %d %d %d\n", &nom, &pv, &posX, &posY, &indiceChemin);

    Tunite *uniteACharger = NULL;

    //On cree l'unite correspondante
    switch(nom){
        case tourSol: uniteACharger = creeTourSol(posX, posY); break;
        case tourAir: uniteACharger = creeTourAir(posX, posY); break;
        case tourRoi: uniteACharger = creeTourRoi(posX, posY); break;
        case archer: uniteACharger = creeArcher(posX, posY); break;
        case chevalier: uniteACharger = creeChevalier(posX, posY); break;
        case dragon: uniteACharger = creeDragon(posX, posY); break;
        case gargouille: uniteACharger = creeGargouille(posX, posY); break;
    }

    if (uniteACharger == NULL)
        return NULL;

    //On met a jour les stats
    set_PvUnit(uniteACharger, pv);
    set_IndiceCheminUnit(uniteACharger, indiceChemin);
    set_cibleUnit(uniteACharger, NULL);

    return uniteACharger;
}

void chargementSeq(const char *fileName, TListePlayer *listeHorde, TListePlayer *listeRoi, int** tabParcours,
                   TJeu *etatJeu, Tunite **roiGlobal, TplateauJeu jeu){
    //On ouvre le fichier en lecture seulement
    FILE *f = fopen(fileName, "r");
    if (f == NULL){
        return;
    }
    //On clean les variables actuelles, pour eviter des doublons/fuites doublons.
    *roiGlobal = NULL;
    initPlateauAvecNULL(jeu, LARGEURJEU, HAUTEURJEU);
    detruireListe(listeHorde);
    detruireListe(listeRoi);

    //On charge l'etat de jeu
    int nbToursJeuseq, vagueEncoursseq, nbUnitesVaguesseq, cooldownVagueseq;
    fscanf(f, "%d %d %d %d\n", &nbToursJeuseq, &vagueEncoursseq, &nbUnitesVaguesseq, &cooldownVagueseq);
    set_NbToursJeu(etatJeu, nbToursJeuseq);
    set_VagueEnCours(etatJeu, vagueEncoursseq);
    set_NbUnitesVague(etatJeu, nbUnitesVaguesseq);
    set_CooldownVague(etatJeu, cooldownVagueseq);

    //On charge/met a jour le nouveau tableau de parcours
    for (int i = 0; i < NBCOORDPARCOURS; i++){
        fscanf(f, "%d %d\n", &tabParcours[i][X], &tabParcours[i][Y]);
    }

    //On charge la liste de la horde
    int nbUnitesHorde = 0;
    fscanf(f, "%d\n", &nbUnitesHorde);

    for (int i = 0; i < nbUnitesHorde; i++){
        Tunite *uniteACharger = chargerUnite(f);
        AjouterUnite(listeHorde, uniteACharger);
    }

    //On charge la liste du roi
    int nbUnitesRoi = 0;
    fscanf(f, "%d\n", &nbUnitesRoi);

    for (int i = 0; i < nbUnitesRoi; i++){
        Tunite *uniteACharger = chargerUnite(f);
        if (get_NomUnit(uniteACharger) == tourRoi){
            *roiGlobal = uniteACharger;
        }
        AjouterUnite(listeRoi, uniteACharger);
    }

    //On positionne les unites sur le plateau
    PositionnePlayerOnPlateau(*listeHorde, jeu);
    PositionnePlayerOnPlateau(*listeRoi, jeu);

    //On ferme le fichier
    fclose(f);
}

/*------------------------------------SAUVEGARDES SEQUENTIELLES END------------------------------------*/
