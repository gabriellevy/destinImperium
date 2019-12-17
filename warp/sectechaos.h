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

    static Condition* AjouterConditionSiLepreDeNurgle();
    static Condition* AjouterConditionSiInfluenceChaosSuperieurA(int nivInfluence);
    static Condition* AjouterModificateurProbaSiInfluenceChaosSuperieurA(Condition* condProba, int nivInfluence, double modifProba);

    // caracs :
    // int augmentant quand le chaos gagne de l'influence sur vous.
    // Il augmente les risques de rejoindre une secte, d'être possédé, d'être jugé hérétique...
    static QString C_INFLUENCE_CHAOS;
    static QString C_SECTE_CHAOS;
    static QString C_DIEU; // dieu vénéré
    // valeurs caracs
    static QString KHORNE;
    static QString TZEENTCH;
    static QString SLAANESH;
    static QString NURGLE;
    // valeurs de PbSante::SANTE liées à Nurgle
    static QString LEPRE_DE_NURGLE;


};

#endif // SECTECHAOS_H
