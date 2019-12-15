#ifndef SECTECHAOS_H
#define SECTECHAOS_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

/**
 * @brief événements de sectes du chaos
 */
class SecteChaos : public GenerateurNoeudsProbables
{
public:
    SecteChaos(int indexEvt);

    static QPair<QString, QString>  DeterminerDieuVenere();

    // caracs :
    static QString C_SECTE_CHAOS;
    static QString C_DIEU; // dieu vénéré
    // valeurs caracs
    static QString KHORNE;
    static QString TZEENTCH;
    static QString SLAANESH;
    static QString NURGLE;

};

#endif // SECTECHAOS_H
