#ifndef MISSION_H
#define MISSION_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

/*enum TypeVoyage {
    AffectationPlanete // être affecté à une planète quelconque pour sa mission
};*/

/**
 * @brief inclut les événements et effets liés aux voyages warp
 *  - réaffectation vers une planète
 */
class Voyage : public GenerateurNoeudsProbables
{
public:
    Voyage(int indexEvt);
    QString GetDescription();

    static QString REAFFECTATION_PLANETE;
    static QString DESTINATION_PLANETE;
    static QString ALEATOIRE;
    static QString VOYAGE_WARP;
};

#endif // MISSION_H
