#ifndef COMBAT_H
#define COMBAT_H

#include <QString>

class Combat
{
public:
    Combat();

    /**
     * @brief JouerCombat
     * @param forceEnnemi force de l'ennemi à combattre entre 0 et 10
     * @param forceJoueur : si non renseigné on récupère la force de base du joueur
     * @return < 0 est une défaite, 0 un combat serré et > 0 est une victoire. -4 est une défaite très grave, +4 une très grande victoire
     */
    static int JouerCombat(int forceEnnemi, int forceJoueur = -1);

    /**
      Ordre de force des personnages :
      0  : infirme
      1  : adulte en forme
      2  : soldat
      3  : soldat d'élite / ork / eldar
      4  : space marine / nob / nécron
      5  : terminator
      6  :
      7  :
      8  :
      9  :
      10 : prince démon / primarque
      **/

    // caracs :
    static QString C_FORCE_COMBAT;
};

#endif // COMBAT_H
