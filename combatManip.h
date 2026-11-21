#ifndef COMBATMANIP_H_INCLUDED
#define COMBATMANIP_H_INCLUDED

#include "towerdefendTypes.h"

/*
Auteur : Munteanu Stefanel
Signature fonction : bool peutAttaquerUnite(Tunite *uniteAttaquante, Tunite *uniteCible)
Tunite *uniteAttaquante : l'unité qui fait l'attaque
Tunite *uniteCible : l'unite cible de l'attaquant
Fonction qui renvoie un booleen pour savoir si une uniteAttaquante peut attaquer une uniteCible
*/
bool peutAttaquerUnite(Tunite *uniteAttaquante, Tunite *uniteCible);

/*
Auteur : Munteanu Stefanel
Signature fonction : TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante)
TPlateauJeu jeu : le plateau de jeu
Tunite *uniteAttaquante : l'unite considérée
Fonction qui renvoie une TListePlayer avec l'ensemble des ennemis dans la portee d'uniteAttaquante
Cette liste peut être nulle, et pour un uniteAttaquante du camp de la horde, elle ne peut avoir q'une seule unité (le roi)
*/
TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante);

/*
Auteur : Mimault Maxime
Signature : void combat(Tunite *UniteAttaquante, Tunite *UniteCible)
Tunite *UniteAttaquante : l'unite qui attaque
Tunite *UniteCible : l'unite qui est attaque
Fait prendre des degats a l'unite cible*/
void combat(Tunite *UniteAttaquante, Tunite *UniteCible);

#endif // COMBATMANIP_H_INCLUDED
