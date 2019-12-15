#ifndef PSYKER_H
#define PSYKER_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

class Psyker : public GenerateurNoeudsProbables
{
public:
    Psyker(int indexEvt);

    static QString GetNiveauPsykerNaissance();

    static Condition* AjouterConditionSiPsyker();
    static Condition* AjouterConditionSiNonPsyker();
    static Condition* AjouterModifProbaSiPsyker(Condition* cond, double poidsProba);
    static Condition* AjouterModifProbaSiNonPsyker(Condition* cond, double poidsProba);

    // caracs :
    static QString C_PSYKER;
    //valeurs de C_PSYKER
    static QString POTENTIEL_PSY;
    static QString SANS_AME;

};

#endif // PSYKER_H
