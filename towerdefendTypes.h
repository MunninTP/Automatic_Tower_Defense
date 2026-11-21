#ifndef TOWERDEFENDTYPES_H_INCLUDED
#define TOWERDEFENDTYPES_H_INCLUDED

#define LARGEURJEU 11
#define HAUTEURJEU 19
#define NBCOORDPARCOURS 34
#define X 0
#define Y 1
#define SPAWNRATETOWERS 30
#define SPAWNRATEHORDE 40
#define DIFFICULTYSETTER 20 //A configurer si on veut que les unites hordes deviennent fortes plus/moins rapidemment
#define COOLDOWNWAVE 10 //Apres combien de tours on a une vague qui spawn



typedef enum{tourSol, tourAir, tourRoi, archer, chevalier, dragon, gargouille} TuniteDuJeu;
typedef enum{sol, solEtAir, air } Tcible;
typedef enum{campRoi, campHorde} TCamp; // Afin de différencier les unites entre camps

typedef struct Tunite Tunite;
typedef struct T_cell *TListePlayer; //types opaques
typedef struct jeu TJeu;

typedef Tunite* ** TplateauJeu;  ////tableau a deux dimensions de largeur 11 et hauteur 19 contenant des pointeurs (Tunite*)


#endif // TOWERDEFENDTYPES_H_INCLUDED
