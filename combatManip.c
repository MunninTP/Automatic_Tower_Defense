#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "combatManip.h"
#include "towerdefendManip.h"

bool peutAttaquerUnite(Tunite *uniteAttaquante, Tunite *uniteCible){
    TCamp campAttaquant = get_CampUnit(uniteAttaquante);
    //Si l'attaquant est une horde
    if (campAttaquant == campHorde){
        return get_NomUnit(uniteCible) == tourRoi;
    }
    //Si l'attaquant est le camp du roi
    else{
        Tcible positionCible = get_PositionUnit(uniteCible);
        Tcible cibleAttaquable = get_PosAtkUnit(uniteAttaquante);
        //Si les unites sont du meme camp, on ne s'attaque pas
        if (campAttaquant == get_CampUnit(uniteCible)){
            return false;
        }
        //Si l'attaquant n'attaque que des unites sol
        if (cibleAttaquable == sol)
            return (positionCible == sol);
        //Si l'attaquant n'attaque que des unites air
        if (cibleAttaquable == air)
            return (positionCible == air);
        //Si l'attaquant peut attaquer des unites sol ET air
        return true;
    }
}

TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante){
    TListePlayer ciblesPossible = NULL;

    //On recupere les informations utiles
    int xUnite = get_PosXUnit(UniteAttaquante);
    int yUnite = get_PosYUnit(UniteAttaquante);
    int portee = get_PorteeUnit(UniteAttaquante);

    //On determine les limites de la sous-matrice que l'unite "connait"
    int imin, imax, jmin, jmax;
    imin = maxVal(0, xUnite - portee);
    imax = minVal(LARGEURJEU - 1, xUnite + portee);
    jmin = maxVal(0, yUnite - portee);
    jmax = minVal(HAUTEURJEU - 1, yUnite + portee);
    //On cherche les unites dans cette sous-matrice , en dfferenciant unite amie et ennemie
    for (int i = imin; i <= imax; i++){
        for (int j = jmin; j <= jmax; j++){
                Tunite *uniteCible = jeu[i][j];
                if (uniteCible != NULL && peutAttaquerUnite(UniteAttaquante, uniteCible)){;
                    AjouterUnite(&ciblesPossible, uniteCible);
                }
        }
    }
    //On tri la liste trouvee par points de vie croissant
    tri_selection_TLP(ciblesPossible, comp_pv_AinfB);

    return ciblesPossible;
}


//met TListePlayer pour pouvoir supprimer les unites dont les pv sont <= a 0, TListePlayer est le camp de l'unite cible
void combat(Tunite *UniteAttaquante, Tunite *UniteCible)
{
    if(!uniteEstVivante(UniteCible) || !uniteEstVivante(UniteAttaquante))
    {
        return;
    }
    int degatsAPrendre = get_DegatsUnit(UniteAttaquante);
    unitePrendsDegats(UniteCible, degatsAPrendre);
}
