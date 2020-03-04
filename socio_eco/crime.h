#ifndef CRIME_H
#define CRIME_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

class Crime : public GenerateurNoeudsProbables
{
private:
    static void PrononcerLaSentence();

public:
    Crime(int indexEvt);

    // ajoute à la liste de conditions une condition validée seulement si on est une personne libre
    static std::shared_ptr<Condition> AjouterConditionSiLibre();
    static std::shared_ptr<Condition> AjouterConditionSiNonLibre();
    static std::shared_ptr<Condition> AjouterConditionSiDelinquant();
    static std::shared_ptr<Condition> AjouterConditionSiJamaisCriminel();
    static std::shared_ptr<Condition> AjouterConditionSiMalhonnete();
    static std::shared_ptr<Condition> AjouterModificateurDeProbaSiDelinquant(std::shared_ptr<Condition> cond, double poidsProba);
    static std::shared_ptr<Condition> AjouterModificateurDeProbaSiCriminel(std::shared_ptr<Condition> cond, double poidsProba);

    static QList<QString> NOMS_GANGS;
    static QString GenererNomGang();

    // caracs :
    static QString C_CRIMINEL;
    static QString C_GANG;
    static QString C_MOIS_PRISON; //  nombre de mois de prisons restants
    //valeurs de C_CRIMINEL : ("" signifie innocent). Note : êre jugé innocent même si n est coupable remet en ""
    static QString DELINQUANT;
    static QString CRIMINEL;
    // valeurs de GenVieHumain::C_LIBERTE :
    static QString CAPTURE_POLICE;
    static QString CAPTURE_ORDO_HERETICUS;
    static QString CAPTURE_ARBITES;
    static QString PRISON;
};

#endif // CRIME_H
