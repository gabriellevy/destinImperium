#ifndef ADEPTUSMECHANICUS_H
#define ADEPTUSMECHANICUS_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

class AdeptusMechanicus : public GenerateurNoeudsProbables
{
public:
    AdeptusMechanicus(int indexEvt);

    static QString DeterminerDivisionAleatoire();

    static QList<QString> DIVISIONS;

    // caracs
    static QString C_DIVISION;
    // valeurs de C_DIVISION
    static QString ALCHEMYS;
    static QString BIOLOGIS;
    static QString TECHNICUS;
    static QString LOGIS;
    static QString XENOLOGIS;
    static QString LEXMECHANICUS;
    static QString ORBOLOGIS;
    static QString CYBERNETIKA;
    static QString XENOBIOLOGIS;
    static QString ASTROLOGICUS;
    static QString DIGITALIS;
    static QString FABRICATOR;
    static QString GENETUS;
    static QString PHYSIC;

};

#endif // ADEPTUSMECHANICUS_H
