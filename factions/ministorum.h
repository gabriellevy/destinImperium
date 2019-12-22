#ifndef MINISTORUM_H
#define MINISTORUM_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

class AdepteMinistorum {
public:
    AdepteMinistorum() {
        DeterminerAffectation();
    }
    QString m_Fonction = "";
    QString m_Description = "";
    QString m_Image = "";

    void DeterminerAffectation();
    void DeterminerAffectationFonction();
    void DeterminerImage();
};

class MinistorumEvts : public GenerateurNoeudsProbables
{
public:
    MinistorumEvts(int indexEvt);

    Condition* AjouterConditionSiMinistorum();

    // caracs
    static QString C_FONCTION;
    // valeurs de C_POSTE
    static QString CONFESSEUR; // haut placé mais relativement mobile et indépendant

};

#endif // MINISTORUM_H
