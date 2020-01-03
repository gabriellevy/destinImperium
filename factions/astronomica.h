#ifndef ASTRONOMICA_H
#define ASTRONOMICA_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;


class Astronomica : public GenerateurNoeudsProbables
{
public:
    Astronomica(int indexEvt);

    static void RafraichirPhrasesAstronomica(QString typePlanete, QString classeSociale);

    // caracs
    static QString C_POSTE;
    // VALEURS DE C_POSTE
    static QString INSTRUCTEUR;
    static QString ACOLYTE;
    static QString ELU;

};

#endif // ASTRONOMICA_H
