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

    static void RafraichirPhrases();

    static Condition* AjouterConditionSiPasAffectation();

    static QString C_GRADE;
    static QString C_AFFECTATION;
    // valeurs de C_GRADE ("" = arbitrator de base) :
    static QString SENIOR; //  => inateignable pour l'instant
    static QString JUGE_ARBITES; //  => inateignable pour l'instant
    static QString PREVOT_MARECHAL; // chef de tout l'adeptus => innateignable pour l'instant
    // valeurs de C_AFFECTATION ("" = travail dans une fortresse standard)
    static QString ACOLYTE_INQUISITEUR;
    static QString VERISPEX;
    static QString CHATISSEUR;
    static QString DETECTIVE;
    static QString CHAPELAIN;
};

#endif // ARBITES_H
