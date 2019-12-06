#ifndef ARBITES_H
#define ARBITES_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"

class NoeudProbable;
class GenEvt;
class Effet;
class Condition;

/**
 * @brief événements de l'Adeptus Arbites
 */
class Arbites
{
    static int COMPTEUR;
public:
    Arbites();

    QString m_Nom = "";
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant l'événement
    Condition* m_ConditionSelecteurProba = nullptr; // proba d'exécution de cet événement
    QList<Condition*> m_Conditions; // éventuelle limitation bloquant ou activant l'exécution de cet événement
    QMap<QString, QString> m_ModificateursCaracs;
    std::function<void()> m_CallbackDisplay = nullptr;

    Effet* GenererEffet(GenEvt* genEvt);

    static void GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

    // grades :
    static QString JUGE_ARBITES; //  => inateignable pour l'instant
    static QString PREVOT_MARECHAL; // chef de tout l'adeptus => innateignable pour l'instant
};

#endif // ARBITES_H
