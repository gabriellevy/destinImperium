#ifndef MISSION_H
#define MISSION_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;
class Planete;

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
    static void DeclencherVoyageWarpVersPlanete(Planete* planete);
    static void RafraichirPhrases();

    // caracs
    static QString C_REAFFECTATION_PLANETE; // nom de la planète de réaffectation (vers laquelle un voyage sera bientôt déclenché)
    static QString C_DESTINATION_PLANETE; // Voyage::ALEATOIRE ou sinon le nom d'une planète
    static QString C_DUREE_VOYAGE_WARP; // int correspondant à l'estimation du nombre de mois de voyage restants dans le warp

    // valeur de C_REAFFECTATION_PLANETE (en dehors d'un nom de planète)
    static QString ALEATOIRE;
};

#endif // MISSION_H
