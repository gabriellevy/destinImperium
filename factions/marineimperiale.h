#ifndef MARINEIMPERIALE_H
#define MARINEIMPERIALE_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"

class NoeudProbable;
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


class MarineImperiale
{
    static int COMPTEUR;
public:
    MarineImperiale();

    QString m_Nom = "";
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant l'événement
    Condition* m_ConditionSelecteurProba = nullptr; // proba d'exécution de cet événement
    QList<Condition*> m_Conditions; // éventuelle limitation bloquant ou activant l'exécution de cet événement
    QMap<QString, QString> m_ModificateursCaracs;
    std::function<void()> m_CallbackDisplay = nullptr;

    Effet* GenererEffet(GenEvt* genEvt);

    static void GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

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
