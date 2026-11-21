#include <stdio.h>
#include <stdlib.h>

#include "maSDL.h"

#include "towerdefend.h"
#include "towerdefendTypes.h"

#include "deployManip.h"
#include "movementManip.h"
#include "combatManip.h"
#include "towerdefendManip.h"

//typedef Tunite* ** TplateauJeu;

TplateauJeu AlloueTab2D(int largeur, int hauteur){
    TplateauJeu jeu;
    jeu = (Tunite***)malloc(sizeof(Tunite**)*largeur);
    for (int i=0;i<largeur;i++){
        jeu[i] = (Tunite**)malloc(sizeof(Tunite*)*hauteur);
    }
    return jeu;  //tab2D contenant des pointeurs
}

void afficheCoordonneesParcours(int **chemin, int nbcoord){
    printf("Liste coordonnees: ");
    for (int i=0; i<nbcoord; i++){
        printf("(%d, %d)",chemin[i][X], chemin[i][Y]);
    }
    printf("\nfin liste coordonnees\n");
}

void freeChemin(int **tab){
    for (int j=0;j<NBCOORDPARCOURS;j++){
        free(tab[j]);  //libere chaque case, qui est un tableau de 2 cases
    }
    free(tab);
}

void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur){
    //pour un affichage sur la console, en relation avec enum TuniteDuJeu
    const char* InitialeUnite[7]={"s", "a", "r", "A", "C", "D", "G"};

    printf("\n");
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
                // A ne pas donner aux etudiants
            if (jeu[i][j] != NULL){
                    printf("%s",InitialeUnite[get_NomUnit(jeu[i][j])]);
            }
            else printf(" ");  //cad pas d'unite sur cette case
        }
        printf("\n");
    }
}

int **initCheminRand(){
    int **chemin = (int**)malloc(sizeof(int*)*NBCOORDPARCOURS);
    for (int j=0; j < NBCOORDPARCOURS ;j++){
        chemin[j] = (int*)malloc(sizeof(int)*2);  //2 cases :indice 0 pour la coord en X, indice 1 pour la coord en Y
    }
    int ydepart = 18;  //et non 19
    int xdepart = rand()%11;  //5 = milieu de la fenetre de 11 de largeur (0-10)
    int i = 0;  //parcourt les i cases du chemin
    int distanceMaxRestante = NBCOORDPARCOURS;
    int DGH = 3;
    int DGHprec = DGH;
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 2, &distanceMaxRestante);
    while(i < NBCOORDPARCOURS)
    {
        DGH = rand()%3+1;
        //rand entre 1 : droite, 2 : gauche et 3 : haut pour avoir une direction random

        if(DGH == 1 && ((xdepart + 2) <= 10) && (DGHprec == 1 || DGHprec == 3 ))
        {
            ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, 2, &distanceMaxRestante);
            DGHprec = DGH; // dans les if car, si jamais on entre dans aucune conditions, on doit garder l'ancien DGH
        }
        if(DGH == 2 && ((xdepart - 2) >= 0) && (DGHprec == 2 || DGHprec == 3))
        {
            ecritCheminVerslaGauche(chemin, &i , &xdepart, &ydepart, 2, &distanceMaxRestante);
            DGHprec = DGH;
        }
        if(DGH == 3 && ((ydepart - 2) > 0) && DGHprec != 3)
        {
            ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 2, &distanceMaxRestante);
            DGHprec = DGH;
        }
    }
    return chemin;  //tab2D contenant des pointeurs
}

/*------------------------------------PHASE DEPLOIMENT START------------------------------------*/

//fonction qui verifie si le roi est mort
bool tourRoiDetruite(const Tunite *tourRoi)
{
    bool isDestroyed = false;
    if(get_PvUnit(tourRoi) <= 0)
    {
        isDestroyed = true;
    }
    return isDestroyed;
}


void phaseCreation(TListePlayer *listeHorde, TListePlayer *listeRoi, int** tabParcours, TplateauJeu jeu, TJeu *etatJeu){
    Tunite* uniteRoiNew = NULL;
    Tunite* uniteHordeNew = NULL;

    //On traite la creation (ou pas), d'une unite du camp du roi
    uniteRoiNew = creerUniteRandom(campRoi, tabParcours, jeu, get_NbToursJeu(etatJeu));
    if (uniteRoiNew != NULL){
        positionneUniteOnPlateau(uniteRoiNew, jeu);
        AjouterUnite(listeRoi, uniteRoiNew);
    }
    //On traite la creation (ou pas), d'une unite du camp de la horde / de la vague
    //On verifie que toutes les cases chemins ne sont pas occupees (On arrete le deploiement)
    if (getNbUnits(*listeHorde) == NBCOORDPARCOURS){
        increment_NbToursJeu(etatJeu);
        return;
    }

    //Si on n'a pas de vague, on creer une unite horde comme d'habitude
    if (!(get_VagueEnCours(etatJeu))){
        uniteHordeNew = creerUniteRandom(campHorde, tabParcours, jeu, get_NbToursJeu(etatJeu));
        if (uniteHordeNew != NULL){
                positionneUniteOnPlateau(uniteHordeNew, jeu);
                AjouterUnite(listeHorde, uniteHordeNew);
        }
        //On indique qu'on a pas eu de vague
        int currentCooldownVague = get_CooldownVague(etatJeu);
        set_CooldownVague(etatJeu, currentCooldownVague + 1);
        //On regarde si le prochain tour commencera une vague, si oui on prepare la structure
        if (get_CooldownVague(etatJeu) == COOLDOWNWAVE){
            set_VagueEnCours(etatJeu, 1);
            set_CooldownVague(etatJeu, 0);
            set_NbUnitesVague(etatJeu, 5);
        }
    }

    //Si au contraire une vague est en cours
    if (get_VagueEnCours(etatJeu)){
        int cheminX = tabParcours[0][X];
        int cheminY = tabParcours[0][Y];
        //On creer l'unite et on la pose ou il le faut
        if (jeu[cheminX][cheminY] == NULL){
            int level = get_NbToursJeu(etatJeu)/DIFFICULTYSETTER;
            uniteHordeNew = creerUniteHordeRandom(cheminX, cheminY, level);
            positionneUniteOnPlateau(uniteHordeNew, jeu);
            AjouterUnite(listeHorde, uniteHordeNew);

            //On met a jour le nb d'unites a spawn pour la vague
            int currentNbUnitesVague = get_NbUnitesVague(etatJeu);
            set_NbUnitesVague(etatJeu, currentNbUnitesVague - 1);
        }
        //On verifie si on a finit la vague
        if (get_NbUnitesVague(etatJeu) == 0){
            set_VagueEnCours(etatJeu, 0);
        }
    }
    increment_NbToursJeu(etatJeu);
}

//Fonction qui initialise le plateau du jeu au Depart avec 1 roi et 1 tours
void jeuInit(TListePlayer *ListeRoi, Tunite** roi, int** tabParcours, TplateauJeu jeu)
{
    int pXRoi = tabParcours[NBCOORDPARCOURS-1][X];
    int pYRoi = tabParcours[NBCOORDPARCOURS-1][Y] - 1;

    Tunite* premiereTour = creerUniteRoiRandom(jeu, tabParcours);
    AjouterUnite(ListeRoi, premiereTour);
    positionneUniteOnPlateau(premiereTour, jeu);

    Tunite* Roi = creeTourRoi(pXRoi, pYRoi);
    *roi = Roi;
    positionneUniteOnPlateau(Roi, jeu);
    AjouterUnite(ListeRoi, Roi);
}

/*------------------------------------PHASE DEPLOIMENT END------------------------------------*/


/*------------------------------------PHASE AVANCEMENT START------------------------------------*/

void avancerHorde(TListePlayer listeHorde, int** tabParcours, TplateauJeu jeu){ //Changee
    //Si la liste es vide, on ne fait rien
    if (listeHorde == NULL){
        return;
    }
    if (getNbUnits(listeHorde) == NBCOORDPARCOURS){
        return;
    }
    TListePlayer lHordeTriee = listeHorde;
    //On trie la liste par unite la plus proche du roi
    tri_selection_TLP(lHordeTriee, comp_indChemin_AsupB);
    //On parcours chaque unite de la liste et on la fait avancee
    while(lHordeTriee != NULL){
        Tunite* uniteCourante = getPdata(lHordeTriee);
        //On recupere les valeurs de l'unite avant le deplacement
        int ancienChemin = get_IndiceCheminUnit(uniteCourante);
        int ancienX = get_PosXUnit(uniteCourante), ancienY = get_PosYUnit(uniteCourante);
        avancerUnite(uniteCourante, tabParcours, jeu);

        jeu[get_PosXUnit(uniteCourante)][get_PosYUnit(uniteCourante)] = uniteCourante;
        //Si un deplacement a bien eu lieu, on met a jour le plateau de jeu pour les prochaines unites.
        if (ancienChemin != get_IndiceCheminUnit(uniteCourante)){
            jeu[ancienX][ancienY] = NULL;
        }
        lHordeTriee = getNextCell(lHordeTriee);
    }
}

/*------------------------------------PHASE AVANCEMENT END------------------------------------*/

/*------------------------------------PHASE COMBAT START------------------------------------*/

void phaseCombat(TListePlayer *listeHorde, TListePlayer *listeRoi, TplateauJeu jeu)
{

    //On cree une liste avec l'ensemble des unites
    TListePlayer toutesLesUnites = fusionListes(*listeHorde, *listeRoi);

    //On la trie par vitesse d'attaque decroissante
    tri_selection_TLP(toutesLesUnites, comp_vitesseATK_AsupB);
    TListePlayer ptrAll = toutesLesUnites;
    // je fusionne et trie les listes, je parcours ma liste fusionne et applique combat si unite a porte, parcours horde et roi pour free les unité morte
    // Ici on fait tous les combats d'abord
    while (ptrAll != NULL)
    {
        TListePlayer cible = quiEstAPortee(jeu, getPdata(ptrAll));
        if(cible != NULL)
        {
            Tunite *uniteAtk = getPdata(ptrAll);
            Tunite *uniteCible = getPdata(cible);

            combat(uniteAtk, uniteCible);
            //Utilisee pour DessineAttaque, qu'on n'utilise pas ici
            set_cibleUnit(uniteAtk, uniteCible);
            if (get_PvUnit(uniteCible) <= 0){
                    supprimeUniteDuPlateau(uniteCible, jeu);
            }
            //On free la liste de cibles
            freeListeCellules(cible);
        }
        ptrAll = getNextCell(ptrAll);
    }
    //On free toutesLesUnites (les cellules, pas les unites)
    freeListeCellules(toutesLesUnites);
}

void dessinerToutesLesAttaques(TListePlayer Horde, TListePlayer Roi, SDL_Surface *surface)
{
    for (TListePlayer ptrRoi = Roi; ptrRoi != NULL; ptrRoi = getNextCell(ptrRoi))
    {
        Tunite *uniteTour = getPdata(ptrRoi);
        if (get_cibleUnit(uniteTour) != NULL) {
            dessineAttaque(surface, uniteTour, get_cibleUnit(uniteTour));
            set_cibleUnit(uniteTour, NULL);
        }
    }
}
/*------------------------------------PHASE COMBAT END------------------------------------*/
