#ifndef ASTRAMILITARUM_H
#define ASTRAMILITARUM_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

class SoldatImperial {
public:
    SoldatImperial() {
        DeterminerAffectation();
    }
    QString m_Fonction = "";
    QString m_Regiment = "";
    QString m_Image = "";

    void DeterminerAffectation();
    QString DeterminerAffectationRegiment();
    QString DeterminerAffectationFonction();
    QString DeterminerImage();
};

/**
 * @brief générateur d'événements de l'Astra Militarum
 */
class AstraMilitarum : public GenerateurNoeudsProbables
{
public:
    AstraMilitarum(int indexEvt);

    // conditions perso :
    QList<Condition*> AjouterConditionSiAstraMilitarum(QList<Condition*> conditions);

    // caracs
    static QString C_FONCTION_ASTRA_MILITARUM;
    static QString C_REGIMENT_ASTRA_MILITARUM;
    // valeurs FONCTION_ASTRA_MILITARUM :
    static QString FANTASSIN;
    static QString LEGION_PENALE;
    // valeurs REGIMENT_ASTRA_MILITARUM :
    static QString CADIAN;
    static QString LEGIONS_D_ACIER;
};

#endif // ASTRAMILITARUM_H
