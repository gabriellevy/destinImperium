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
    static Condition* AjouterConditionSiPsykerPasIdentifie();
    static Condition* AjouterConditionSiNonPsyker();
    static Condition* AjouterModifProbaSiPsyker(Condition* cond, double poidsProba);
    static Condition* AjouterModifProbaSiNonPsyker(Condition* cond, double poidsProba);

    // caracs :
    static QString C_PSYKER; // si différent de "" alors c'est un psyker
    static QString C_RAPPORT_AU_GVT; // inconnu (""), enregistré, emprisonné, condamné
    static QString C_NIVEAU_PSYKER; // TODO MATHIEU : cette carac n'est pas utilisée pour l'instant
    //valeurs de C_PSYKER
    static QString POTENTIEL_PSY;
    static QString SANS_AME;
    //valeurs de C_RAPPORT_AU_GVT
    static QString IDENTIFIE;
    static QString CHARGE_DANS_VAISSEAU_NOIR;
    static QString DIGNE_DE_SERVIR;
    static QString SACRIFIABLE;
    // valeurs de C_NIVEAU_PSYKER :
    static QString OMICRON;
    static QString XI;
    static QString NU;
    static QString MU;
    static QString LAMBDA;
    static QString KAPPA;
    // les plus dangereux :
    static QString IOTA;
    static QString THETA;
    static QString ETA;
    static QString ALPHA_PLUS;

};

#endif // PSYKER_H
