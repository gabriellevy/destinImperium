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
public:
    Crime(int indexEvt);

    // ajoute à la liste de conditions une condition validée seulement si on est une personne libre
    static QList<Condition*> AjouterConditionSiLibre(QList<Condition*> conditions);
    static QList<Condition*> AjouterConditionSiNonLibre(QList<Condition*> conditions);
    static QList<Condition*> AjouterConditionSiJamaisCriminel(QList<Condition*> conditions);

    static QList<QString> NOMS_GANGS;
    static QString GenererNomGang();

    // caracs :
    static QString C_CRIMINEL;
    static QString C_GANG;
    //valeurs de C_CRIMINEL : ("" signifie innocent). Note : êre jugé innocent même si n est coupable remet en ""
    static QString DELINQUANT;
    static QString CRIMINEL;
    // valeurs de GenVieHumain::C_LIBERTE :
    static QString CAPTURE_POLICE;
    static QString CAPTURE_ARBITES;
};

#endif // CRIME_H
