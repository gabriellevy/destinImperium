#ifndef ARBITES_H
#define ARBITES_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

/**
 * @brief événements de l'Adeptus Arbites
 */
class Arbites : public GenerateurNoeudsProbables
{
public:
    Arbites(int indexEvt);

    // grades :
    static QString JUGE_ARBITES; //  => inateignable pour l'instant
    static QString PREVOT_MARECHAL; // chef de tout l'adeptus => innateignable pour l'instant
};

#endif // ARBITES_H
