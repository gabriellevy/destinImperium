#ifndef ASSASSINORUM_H
#define ASSASSINORUM_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;


class Assassinorum : public GenerateurNoeudsProbables
{
public:
    Assassinorum(int indexEvt);

    static QString DeterminerTempleAleatoire();

    // caracs
    static QString C_TEMPLE;
    // valeurs de C_TEMPLE
    static QString EVERSOR;
    static QString CALLIDUS;
    static QString VINDICARE;
    static QString CULEXUS;

};

#endif // ASSASSINORUM_H
