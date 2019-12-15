#ifndef SANTE_H
#define SANTE_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;


/**
 * @brief Tout ce qui concerne la santé y compris la mort par vieillesse et les maladies
 */
class PbSante : public GenerateurNoeudsProbables
{
public:
    PbSante(int indexEvt);

    // caracs liées :
    static QString PESTE;
    static QString C_SANTE;
    // valeurs de C_SANTE
    static QString MORT;

    static Condition* AjouterModifProbaSiMort(Condition* cond, double poidsProba);
    static Condition* AjouterConditionSiVivant();
};

#endif // SANTE_H
