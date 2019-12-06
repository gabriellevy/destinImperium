#ifndef ASSASSINORUM_H
#define ASSASSINORUM_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"

class NoeudProbable;
class GenEvt;
class Effet;
class Condition;


class Assassinorum
{
    static int COMPTEUR;
public:
    Assassinorum();

    QString m_Nom = "";
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant l'événement
    Condition* m_ConditionSelecteurProba = nullptr; // proba d'exécution de cet événement
    QList<Condition*> m_Conditions; // éventuelle limitation bloquant ou activant l'exécution de cet événement
    QMap<QString, QString> m_ModificateursCaracs;
    std::function<void()> m_CallbackDisplay = nullptr;

    Effet* GenererEffet(GenEvt* genEvt);

    static void GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

    static QString DeterminerTempleAleatoire();

    // caracs
    static QString C_TEMPLE;
    // valeurs de C_TEMPLE
    static QString EVERSOR;
    static QString CALLIDUS;
    static QString VINDICARE;
    static QString CULEXUS;

};

#endif // ASSASSINORUM_H
