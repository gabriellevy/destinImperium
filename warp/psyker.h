#ifndef PSYKER_H
#define PSYKER_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"

class NoeudProbable;
class GenEvt;
class Effet;
class Condition;

class Psyker
{
    static int COMPTEUR;
public:
    Psyker();

    QString m_Nom = "";
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant l'événement
    Condition* m_ConditionSelecteurProba = nullptr; // proba d'exécution de cet événement
    QList<Condition*> m_Conditions; // éventuelle limitation bloquant ou activant l'exécution de cet événement
    QMap<QString, QString> m_ModificateursCaracs;

    Effet* GenererEffet(GenEvt* genEvt);

    static void GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

    static QString GetNiveauPsykerNaissance();

    // caracs :
    static QString C_PSYKER;
    //valeurs de C_PSYKER
    static QString POTENTIEL_PSY;
    static QString SANS_AME;

};

#endif // PSYKER_H
