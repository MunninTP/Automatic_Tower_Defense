// NOM prenom etudiant 1 : Munteanu Stefanel
// NOM prenom etudiant 2 : Mimault Maxime

#include <stdio.h>
#include <time.h>
#include "maSDL.h" //bibliotheque avec des fonctions d'affichage utilisant la SDL
#include "towerdefend.h"
#include "saveAndRestore.h"
#define SAVEBIN "partiebin.bin"
#define SAVESEQ "partieseq.tds"


/*--------- Main ---------------------*/
int main(int argc, char *argv[])
{
        srand(time(NULL));
        SDL_Window *pWindow;
        SDL_Init(SDL_INIT_VIDEO);

        pWindow = SDL_CreateWindow(
            "Appuyez sur ECHAP pour quitter, S/C ET D/V les gerer les sauvegardes",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            LARGEURJEU * 40,
            HAUTEURJEU * 40,
            SDL_WINDOW_SHOWN);

        // SDL_Renderer * renderer = SDL_CreateRenderer(pWindow, -1, 0);  //non utilise, pour memoire

        SDL_Surface *pWinSurf = SDL_GetWindowSurface(pWindow);                 // le sprite qui couvre tout l'ecran
        SDL_Surface *pSpriteTourSol = SDL_LoadBMP("./data/TourSol.bmp");       // indice 0 dans tabSprite (via l'enum TuniteDuJeu)
        SDL_Surface *pSpriteTourAir = SDL_LoadBMP("./data/TourAir.bmp");       // indice 1 dans tabSprite (via l'enum TuniteDuJeu)
        SDL_Surface *pSpriteTourRoi = SDL_LoadBMP("./data/TourRoi.bmp");       // indice 2
        SDL_Surface *pSpriteArcher = SDL_LoadBMP("./data/Archer.bmp");         // indice 3
        SDL_Surface *pSpriteChevalier = SDL_LoadBMP("./data/Chevalier.bmp");   // indice 4
        SDL_Surface *pSpriteDragon = SDL_LoadBMP("./data/Dragon.bmp");         // indice 5
        SDL_Surface *pSpriteGargouille = SDL_LoadBMP("./data/Gargouille.bmp"); // indice 6
        SDL_Surface *pSpriteEau = SDL_LoadBMP("./data/Eau.bmp");               // indice 7  Ne figure pas dans l'enum TuniteDuJeu
        SDL_Surface *pSpriteHerbe = SDL_LoadBMP("./data/Herbe.bmp");           // indice 8 idem
        SDL_Surface *pSpritePont = SDL_LoadBMP("./data/Pont.bmp");             // indice 9 idem
        SDL_Surface *pSpriteTerre = SDL_LoadBMP("./data/Terre.bmp");           // indice 10 idem

        // ASTUCE : on stocke le sprite d'une unite a l'indice de son nom dans le type enum TuniteDuJeu, dans le tableau TabSprite
        // SAUF pour l'Eau, l''herbe et le pont qui apparaitront en l absence d'unite (NULL dans le plateau) et en fonction de certains indices x,y definissant le chemin central
        SDL_Surface *TabSprite[11] = {pSpriteTourSol, pSpriteTourAir, pSpriteTourRoi, pSpriteArcher, pSpriteChevalier, pSpriteDragon, pSpriteGargouille, pSpriteEau, pSpriteHerbe, pSpritePont, pSpriteTerre};

        int **tabParcours = initCheminRand(); // tabParcours est un tableau de NBCOORDPARCOURS cases, chacune contenant un tableau a 2 cases (indice 0 pour X, indice 1 pour Y)

        if (pSpriteTourSol) // si le permier sprite a bien ete charge, on suppose que les autres aussi
        {
                TplateauJeu jeu = AlloueTab2D(LARGEURJEU, HAUTEURJEU);
                initPlateauAvecNULL(jeu, LARGEURJEU, HAUTEURJEU);
                affichePlateauConsole(jeu, LARGEURJEU, HAUTEURJEU);

                prepareAllSpriteDuJeu(jeu, tabParcours, LARGEURJEU, HAUTEURJEU, TabSprite, pWinSurf);
                maj_fenetre(pWindow);
                //dessinerToutesLesAttaques(Horde, Roi, pWinSurf); Le dessin n'est pas ce qu'on aurait attendus

                /**********************************************************************/
                /*                                                                    */
                /*              DEFINISSEZ/INITIALISER ICI VOS VARIABLES              */
                /*                                                                    */
                int cont = 1; //Arreter le jeu avec un evenement (Echap ou autre)
                TJeu* EtatJeu = creer_JeuStats();

                initPlateauAvecNULL(jeu, LARGEURJEU, HAUTEURJEU);

                TListePlayer Horde = NULL;
                TListePlayer Roi = NULL;
                Tunite *uniteRoiGlobal = NULL;

                jeuInit(&Roi, &uniteRoiGlobal, tabParcours, jeu);


                // FIN de vos variables                                               */
                /**********************************************************************/

                // boucle principale du jeu
                while (!tourRoiDetruite(uniteRoiGlobal) && cont)
                {
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu, tabParcours, LARGEURJEU, HAUTEURJEU, TabSprite, pWinSurf);


                        //BOUCLE DE GESTION DES EVENEMENTS
                        SDL_Event event;
                        while (SDL_PollEvent(&event)){
                            if (event.type == SDL_QUIT){
                                cont = 0;
                            }
                            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE && event.key.repeat == 0){
                                cont = 0; // sortie de la boucle
                            }
                            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_D){
                                /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur D */

                                // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                                sauvegardeSeq(SAVESEQ, Horde, Roi, tabParcours, EtatJeu);
                                message("Sauvegarde", "La sauvegarde du fichier a ete effectuee (fichier seq)");

                                // Ne pas modifiez les 4 lignes ci-dessous
                                efface_fenetre(pWinSurf);
                                prepareAllSpriteDuJeu(jeu, tabParcours, LARGEURJEU, HAUTEURJEU, TabSprite, pWinSurf);
                                maj_fenetre(pWindow);
                                SDL_Delay(300);
                            }
                            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_C && event.key.repeat == 0){
                                /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur C */

                                // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                                message("Sauvegarde", "La sauvegarde du fichier a ete effectuee (fichier bin)");
                                sauvegardeBin(SAVEBIN, Horde, Roi, tabParcours, EtatJeu);

                                // Ne pas modifiez les 4 lignes ci-dessous
                                efface_fenetre(pWinSurf);
                                prepareAllSpriteDuJeu(jeu, tabParcours, LARGEURJEU, HAUTEURJEU, TabSprite, pWinSurf);
                                maj_fenetre(pWindow);
                                SDL_Delay(300);

                            }
                            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_S && event.key.repeat == 0){
                                /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur S */

                                // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                                message("Chargement", "Le chargement du jeu a ete effectue (fichier bin)");
                                chargementBin(SAVEBIN, &Horde, &Roi, tabParcours, EtatJeu, &uniteRoiGlobal, jeu);


                                // Ne pas modifiez les 4 lignes ci-dessous
                                efface_fenetre(pWinSurf);
                                prepareAllSpriteDuJeu(jeu, tabParcours, LARGEURJEU, HAUTEURJEU, TabSprite, pWinSurf);
                                maj_fenetre(pWindow);
                                SDL_Delay(300);
                            }
                            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_V && event.key.repeat == 0){
                                /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur V */

                                // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                                chargementSeq(SAVESEQ, &Horde, &Roi, tabParcours, EtatJeu, &uniteRoiGlobal, jeu);
                                message("Chargement", "Le chargement du jeu a ete effectue (fichier seq)");

                                // Ne pas modifiez les 4 lignes ci-dessous
                                efface_fenetre(pWinSurf);
                                prepareAllSpriteDuJeu(jeu, tabParcours, LARGEURJEU, HAUTEURJEU, TabSprite, pWinSurf);

                                maj_fenetre(pWindow);

                                SDL_Delay(300);

                            }
                        }

                        /***********************************************************************/
                        /*                                                                     */
                        /*                                                                     */
                        // APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE JEU
                        //MERCI LES NAINS DU PROJET DU SEMESTRE DERNIER
                        avancerHorde(Horde, tabParcours, jeu);

                        phaseCreation(&Horde, &Roi, tabParcours, jeu, EtatJeu);

                        phaseCombat(&Horde, &Roi, jeu);

                        //On nettoye les 2 listes qui peuvent avoir des unites mortes
                        nettoyerListe(&Horde);
                        nettoyerListe(&Roi);

                        /*                                                                     */
                        /*                                                                     */
                        // FIN DE VOS APPELS
                        /***********************************************************************/
                        //Maj de la fenetre avec les attaques
                        maj_fenetre(pWindow);
                        SDL_Delay(500); // valeur du delai a modifier eventuellement

                }
                // fin boucle du jeu
                //On libère toutes nos structures dynamiques
                detruireJeu(EtatJeu);
                detruireListe(&Roi);
                detruireListe(&Horde);
                uniteRoiGlobal = NULL;
                free(jeu);
                freeChemin(tabParcours);

                SDL_FreeSurface(pSpriteTourSol); // Liberation de la ressource occupee par le sprite
                SDL_FreeSurface(pSpriteTourAir);
                SDL_FreeSurface(pSpriteTourRoi);
                SDL_FreeSurface(pSpriteArcher);
                SDL_FreeSurface(pSpriteChevalier);
                SDL_FreeSurface(pSpriteDragon);
                SDL_FreeSurface(pSpriteGargouille);
                SDL_FreeSurface(pSpriteEau);
                SDL_FreeSurface(pSpriteHerbe);
                SDL_FreeSurface(pSpritePont);
                SDL_FreeSurface(pWinSurf);
        }
        else
        {
                fprintf(stdout, "echec de chargement du sprite (%s)\n", SDL_GetError());
        }

        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        return 0;
}
