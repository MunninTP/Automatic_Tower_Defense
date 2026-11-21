#include <stdio.h>
#include <stdlib.h>
#include "towerdefendManip.h"
#include "towerdefendInternalTypes.h"

Tunite *creeTourSol(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourSol;
    nouv->campUnite = campRoi;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 75;
    nouv->portee = 2; //originel a 5
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->cible = NULL;
    nouv->score_emplacement = 0;
    return nouv;
}
Tunite *creeTourAir(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourAir;
    nouv->campUnite = campRoi;
    nouv->cibleAttaquable = air;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.0;
    nouv->degats = 75;
    nouv->portee = 2;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->cible = NULL;
    nouv->score_emplacement = 0;
    return nouv;
}
Tunite *creeTourRoi(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourRoi;
    nouv->campUnite = campRoi;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 15;
    nouv->vitesseAttaque = 1.2;
    nouv->degats = 50;
    nouv->portee = 3;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->cible = NULL;
    nouv->score_emplacement = 0;
    nouv->indiceChemin = 0;
    return nouv;
}
Tunite *creeDragon(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = dragon;
    nouv->campUnite = campHorde;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 200;
    nouv->vitesseAttaque = 1.1;
    nouv->degats = 1;
    nouv->portee = 2;
    nouv->vitessedeplacement = 2;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->cible = NULL;
    nouv->score_emplacement = 0;
    nouv->indiceChemin = 0;

    return nouv;
}
//Fonction qui creer un chevalier
Tunite *creeChevalier(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = chevalier;
    nouv->campUnite = campHorde;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 400;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 1;
    nouv->portee = 1;
    nouv->vitessedeplacement = 2;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->cible = NULL;
    nouv->score_emplacement = 0;
    nouv->indiceChemin = 0;

    return nouv;
}

//fonction qui creer une gargouille
Tunite *creeGargouille(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = gargouille;
    nouv->campUnite = campHorde;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.6;
    nouv->degats = 1;
    nouv->portee = 1;
    nouv->vitessedeplacement = 3;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->cible = NULL;
    nouv->score_emplacement = 0;
    nouv->indiceChemin = 0;

    return nouv;
}

//fonction qui creer un archer
Tunite *creeArcher(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = archer;
    nouv->campUnite = campHorde;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.7;
    nouv->degats = 1;
    nouv->portee = 3;
    nouv->vitessedeplacement = 1;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->cible = NULL;
    nouv->score_emplacement = 0;
    nouv->indiceChemin = 0;

    return nouv;
}

/*----------------------------------------FONCTIONS DE MANIPULATION POUR UNE TUNITE----------------------------------------*/

int get_IndiceCheminUnit(const Tunite* unite){
    return unite->indiceChemin;
}

int get_VitesseDeplacUnit(const Tunite* unite){
    return unite->vitessedeplacement;
}

int get_PosXUnit(const Tunite* unite){
    return unite->posX;
}

int get_PosYUnit(const Tunite* unite){
    return unite->posY;
}

int get_PorteeUnit(const Tunite* unite){
    return unite->portee;
}

void set_PositionUnit(Tunite* unite, int newposX, int newposY, int newIndice){
    unite->posX = newposX;
    unite->posY = newposY;
    unite->indiceChemin = newIndice;
}

void set_PositionTour(Tunite* unite, int newposX, int newposY, int scoreEmplacement){
    unite->posX = newposX;
    unite->posY = newposY;
    unite->score_emplacement = scoreEmplacement;
}

int get_ScoreEmplacement(const Tunite* unite){
    return unite->score_emplacement;
}

void addPvUnit(Tunite *unite, int pv){
    unite->pointsDeVie += pv;
}

void increaseDmgUnit (Tunite* unite, int degatsExtra){
    unite->degats += degatsExtra;
}

void increaseAtkSpdUnit(Tunite *unite, float atkspdExtra){
    unite->vitesseAttaque += atkspdExtra;
}

TCamp get_CampUnit(const Tunite *unite){
    return unite->campUnite;
}

TuniteDuJeu get_NomUnit(const Tunite *unite){
    return unite->nom;
}

Tcible get_PositionUnit(const Tunite *unite){
    return unite->maposition;
}

Tcible get_PosAtkUnit(const Tunite *unite){
    return unite->cibleAttaquable;
}

int get_DegatsUnit(const Tunite *unite){
    return unite->degats;
}

void unitePrendsDegats(Tunite *unite, int degats){
    unite->pointsDeVie -= degats;
}

int get_PvUnit(const Tunite *unite){
    return unite->pointsDeVie;
}

void set_IndiceCheminUnit(Tunite *unite, int newIndice){
    unite->indiceChemin = newIndice;
}

void set_PvUnit(Tunite *unite, int newPv){
    unite->pointsDeVie = newPv;
}

void set_cibleUnit(Tunite *unite, Tunite *cible){
    if (cible != NULL){
        unite->cible = cible;
    }
    else {
        unite->cible = NULL;
    }
}

Tunite* get_cibleUnit(const Tunite *unite){
    return unite->cible;
}

bool uniteEstVivante(const Tunite *unite){
    return (unite != NULL && unite->pointsDeVie > 0);
}

void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu)
{
    int pX, pY;
    TListePlayer ptr = player;
    while (ptr != NULL)
    {
        //mets les coordonnees des unites dans le plateau
        pX = get_PosXUnit(getPdata(ptr));
        pY = get_PosYUnit(getPdata(ptr));
        jeu[pX][pY] = getPdata(ptr);
        ptr = getNextCell(ptr);
    }
}

void positionneUniteOnPlateau(Tunite *unite, TplateauJeu jeu){
    int unitX = unite->posX;
    int unitY = unite->posY;
    jeu[unitX][unitY] = unite;
}

void supprimeUniteDuPlateau(Tunite *unite, TplateauJeu jeu){
    int unitX = unite->posX;
    int unitY = unite->posY;
    jeu[unitX][unitY] = NULL;
}

/*----------------------------------------FONCTIONS DE MANIPULATION POUR UNE TLISTEPLAYER----------------------------------------*/
TListePlayer getNextCell(const TListePlayer playerList){
    if (playerList == NULL || playerList->suiv == NULL)
        return NULL;
    return playerList->suiv;
}

int getNbUnits (const TListePlayer playerList){
    int taille = 0;
    TListePlayer ptr = playerList;
    while (ptr!=NULL){
        taille++;
        ptr = getNextCell(ptr);
    }
    return taille;
}

Tunite *getPdata(const TListePlayer playerList){
    if (playerList == NULL)
        return NULL;
    return playerList->pdata;
}

void afficheListeUnites(const TListePlayer playerList)
{
    TListePlayer ptr = playerList;
    if (playerList == NULL){
        printf("{}\n");
    }
    else{
        char* tabNames[]= {"tourSol", "tourAir", "tourRoi", "archer", "chevalier", "dragon", "gargouille"};
        printf("{\n");
        while (ptr != NULL)
        {

        printf("%s : pv = %d, vitesseAtk = %.2f \n", tabNames[getPdata(ptr)->nom], getPdata(ptr)->pointsDeVie, getPdata(ptr)->vitesseAttaque);
        ptr = getNextCell(ptr);
        }
        printf("}\n");
    }
}

void swapPtrData(TListePlayer source, TListePlayer destination ){
    if (source == NULL || destination == NULL){
        printf("Au moins un des 2 parametres sont nuls\n");
        return;
    }
    else {
        Tunite* ptrDataSrc = getPdata(source);
        source->pdata = destination->pdata;
        destination->pdata = ptrDataSrc;
    }
}

TListePlayer getLastCell(const TListePlayer player)
{
    if(player == NULL)
    {
        return NULL;
    }
    TListePlayer tmp = player;
    while (tmp->suiv != NULL)
    {
        tmp = tmp->suiv;
    }
    return tmp;
}

void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite){

    //On creer la nouvelle cellule avec l'unite
    TListePlayer newPlayer = (TListePlayer)malloc(sizeof(struct T_cell));
    newPlayer->suiv = *player;
    newPlayer->pdata = nouvelleUnite;

    *player = newPlayer;
}

//fonction qui supprime une case de player, ou se trouve l'unite et fait les liaisons
void supprimerUnite(TListePlayer* player, Tunite *UniteDetruite)
{
    //Cas 0: verifie si la liste est vide ou si l'unite a detruire est nulle
    if (*player == NULL || UniteDetruite == NULL)
        return;
    TListePlayer tmp = *player;
    //Cas 1: On supprime la premiere unite de la liste
    if (tmp->pdata == UniteDetruite){
        *player = tmp->suiv;
        free(tmp->pdata);
        free(tmp);
    }
    else
    {
        //Cas 2: On supprime l'unite apres le debut
        //On cherche l'unite dans la liste
        TListePlayer ptrPrec = tmp;
        TListePlayer ptrAct = tmp->suiv;
        while (ptrAct != NULL && ptrAct->pdata != UniteDetruite)
        {
            ptrPrec = getNextCell(ptrPrec);
            ptrAct = getNextCell(ptrAct);

        }
        //MAJ des liens dans la liste
        if(ptrAct != NULL)  //si on a trouve l'unite dans la liste
        {
            TListePlayer ptrSuiv = ptrAct->suiv; // creer un nouveau pointeur car on peut pas ptrPrec->suiv = ptrAct->suiv vu qu'il a ete FREE
            free(ptrAct->pdata);
            free(ptrAct);
            ptrPrec->suiv = ptrSuiv;
        }
    }
    UniteDetruite = NULL; // NULL ici car sinon pointe vers une zone memoire libere
}

void nettoyerListe(TListePlayer* listePlayer)
{
    TListePlayer ptr = *listePlayer;

    while (ptr != NULL)
    {
        TListePlayer nextCell = getNextCell(ptr);

        if (get_PvUnit(getPdata(ptr)) <= 0)
        {
            supprimerUnite(listePlayer, getPdata(ptr));
        }

        ptr = nextCell;
    }
}

void detruireListe(TListePlayer *listePlayer)
{
    TListePlayer ptr = *listePlayer;

    while (ptr != NULL)
    {
        TListePlayer next = ptr->suiv;
        free(ptr->pdata);
        free(ptr);
        ptr = next;
    }

    *listePlayer = NULL;
}


void freeListeCellules(TListePlayer listePlayer)
{
    TListePlayer tmp;
    while (listePlayer != NULL)
    {
        tmp = listePlayer;
        listePlayer = listePlayer->suiv;
        free(tmp);
    }
}

TListePlayer fusionListes(const TListePlayer listePlayer1, const TListePlayer listePlayer2){
    TListePlayer fusionListes = NULL;

    for (TListePlayer tmp1 = listePlayer1; tmp1 != NULL; tmp1 = getNextCell(tmp1))
        AjouterUnite(&fusionListes, tmp1->pdata);

    for (TListePlayer tmp2 = listePlayer2; tmp2 != NULL; tmp2 = getNextCell(tmp2))
        AjouterUnite(&fusionListes, tmp2->pdata);

    return fusionListes;
}

/*----------------------------------------FONCTIONS DE COMPARAISON----------------------------------------*/
bool comp_pv_AinfB(const Tunite *A, const Tunite *B){
    return ((A->pointsDeVie) < (B->pointsDeVie));
}

bool comp_vitesseATK_AsupB(const Tunite *A, const Tunite *B){
    return ((A->vitesseAttaque) > (B->vitesseAttaque));
}

bool comp_indChemin_AsupB(const Tunite *A, const Tunite *B){
    return ((A->indiceChemin) > (B->indiceChemin));
}

bool comp_unite_AegalB(const Tunite *A, const Tunite *B){
    bool sameNom = A->nom == B->nom;
    bool samePV = A->pointsDeVie == B->pointsDeVie;
    return sameNom && samePV;
}

/*----------------------------------------FONCTION DE TRI----------------------------------------*/

void tri_selection_TLP(TListePlayer l, bool (*fcomp) (const Tunite *a, const Tunite *b)){
    for (TListePlayer ptr = l; getNextCell(ptr) != NULL; ptr = getNextCell(ptr)){
        TListePlayer smallestPTR = ptr;
        for (TListePlayer ptrInner = ptr; ptrInner != NULL; ptrInner = getNextCell(ptrInner)){
            if (fcomp(getPdata(ptrInner), getPdata(smallestPTR))) {
                smallestPTR = ptrInner;
            }
        }
        swapPtrData(ptr, smallestPTR);
    }
}

/*----------------------------------------FONCTIONS AUXILIAIRES----------------------------------------*/
int maxVal(int a, int b){
    if (a > b)
        return a;
    return b;
}

int minVal(int a, int b){
    if (a > b)
        return b;
    return a;
}

/*----------------------------------------FONCTIONS MANIPULATION PLATEAU----------------------------------------*/

void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur){
    for (int i=0;i<largeur;i++){
        for (int j=0;j<hauteur;j++){
            jeu[i][j] = NULL;
        }
    }
}

/*----------------------------------------FONCTIONS MANIPULATION TJEU----------------------------------------*/

int get_NbToursJeu(const TJeu *jeu){
    return jeu->nbToursJeu;
}

int get_VagueEnCours(const TJeu *jeu){
    return jeu->vagueEncours;
}

int get_NbUnitesVague(const TJeu *jeu){
    return jeu->nbUnitesVagues;
}

int get_CooldownVague(const TJeu *jeu){
    return jeu->cooldownVague;
}

void set_NbToursJeu(TJeu *jeu, int newNbToursJeu){
    jeu->nbToursJeu = newNbToursJeu;
}

void set_VagueEnCours(TJeu *jeu, int newVagueEnCours){
    jeu->vagueEncours = newVagueEnCours;
}

void set_NbUnitesVague(TJeu *jeu, int newNbUniteVague){
    jeu->nbUnitesVagues = newNbUniteVague;
}

void set_CooldownVague(TJeu *jeu, int newCooldownVague){
    jeu->cooldownVague = newCooldownVague;
}

void increment_NbToursJeu(TJeu *jeu){
    jeu->nbToursJeu += 1;
}

TJeu* creer_JeuStats(){
    TJeu* jeu = malloc(sizeof(struct jeu));

    set_NbToursJeu(jeu, 0);
    set_VagueEnCours(jeu, 0);
    set_NbUnitesVague(jeu, 0);
    set_CooldownVague(jeu, 0);

    return jeu;
}

void detruireJeu(TJeu *jeu){
    free(jeu);
}

/*----------------------------------------FONCTIONS MANIPULATION SAUVEGARDES BIN----------------------------------------*/
//Sauvegarde les listes de la horde ou du roi
void saveListHordeOuRoi(int NbList, TListePlayer player,  FILE* saveBin)
{
    TListePlayer ptr = player;
    for(int i = 0; i < NbList; i++)
    {
        fwrite(getPdata(ptr), sizeof(Tunite), 1, saveBin);
        ptr = getNextCell(ptr);
    }
}

void readListHordeOuRoi(int NbList, TListePlayer* player, FILE* saveBin, Tunite** roiGlobal)
{
    for(int i = 0; i < NbList; i++)
    {
        Tunite* Unite = malloc(sizeof(Tunite));
        fread(Unite, sizeof(Tunite), 1, saveBin);
        if(get_NomUnit(Unite) == tourRoi)
        {
            *roiGlobal = Unite;
        }
        AjouterUnite(player, Unite);
    }
}
