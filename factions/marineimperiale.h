#ifndef MARINEIMPERIALE_H
#define MARINEIMPERIALE_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

class MarinImperial {
public:
    MarinImperial() {
        DeterminerAffectation();
    }
    QString m_Fonction = "";
    QString m_Flotte = "";
    QString m_Image = "";

    void DeterminerAffectation();
    QString DeterminerAffectationFlotte();
    QString DeterminerAffectationFonction();
    QString DeterminerImage();
};


class MarineImperiale : public GenerateurNoeudsProbables
{
public:
    MarineImperiale(int indexEvt);

    // conditions perso :
    QList<Condition*> AjouterConditionSiMarineImperiale(QList<Condition*> conditions);

    // caracs
    static QString C_FLOTTE;
    static QString C_FONCTION;
    // valeurs C_FONCTION :
    static QString OPERATEUR;
    // valeurs de C_FLOTTE
    static QString AGRIPINAA;
    static QString ARMAGEDDON;
    static QString BAKKA;
    static QString CADIA;
    static QString CALIXIS;
    static QString CORONA;
    static QString CORRIBRA;
    static QString GOTHIC;
    static QString KORONUS;
    static QString ORPHEUS;
    static QString SCARUS;
    static QString SOLAR;

    static QList<QString> FLOTTES;
    static QString GetFlotteAlmatoire();
};

#endif // MARINEIMPERIALE_H
