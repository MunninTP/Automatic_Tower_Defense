#ifndef TOWERDEFENDINTERNALTYPES_H_INCLUDED
#define TOWERDEFENDINTERNALTYPES_H_INCLUDED

#include "towerdefendTypes.h"

struct Tunite {
    TuniteDuJeu nom;
    Tcible cibleAttaquable;	//indique le type des unités que l’on peut attaquer
    Tcible maposition;		//indique soit « air » soit « sol », utile pour savoir
                            //qui peut nous attaquer
    int pointsDeVie;
    float vitesseAttaque;	//en seconde, plus c’est petit plus c’est rapide
    int degats;
    int portee ;			//en metre, distance sur laquelle on peut atteindre une
                            //cible

    int vitessedeplacement;	//en m/s
    int posX, posY;			//position sur le plateau de jeu

    struct Tunite *cible; //Cible pour dessineAttaque

    TCamp campUnite;

    int score_emplacement;  //Le nombre de cases chemin qu'une tour touche (invalable aux unites de la horde)
    int indiceChemin; //Indice du chemin sur lequel l'unite se trouve
};

struct T_cell{
    struct T_cell *suiv;
    Tunite *pdata; //pointeur vers une unite
};

struct jeu {
    int nbToursJeu; //Nombre de tours passes pendant la partie

    int vagueEncours ; //0 pour non, 1 pour oui

    int nbUnitesVagues; //Combien d'unites restent a etre deployees pour la vague

    int cooldownVague; //Combien de tours on passe sans vagues
};

#endif // TOWERDEFENDINTERNALTYPES_H_INCLUDED
