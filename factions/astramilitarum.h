#ifndef ASTRAMILITARUM_H
#define ASTRAMILITARUM_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"

class NoeudProbable;
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
class AstraMilitarum
{
    static int COMPTEUR;
public:
    AstraMilitarum();

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
    QList<Condition*> AjouterConditionSiAstraMilitarum(QList<Condition*> conditions);

    // caracs
    static QString C_FONCTION_ASTRA_MILITARUM;
    static QString C_REGIMENT_ASTRA_MILITARUM;
    // valeurs FONCTION_ASTRA_MILITARUM :
    static QString FANTASSIN;
    // valeurs REGIMENT_ASTRA_MILITARUM :
    static QString CADIAN;
    static QString LEGIONS_D_ACIER;
};

#endif // ASTRAMILITARUM_H
