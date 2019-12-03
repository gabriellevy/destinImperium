#ifndef CLASSESOCIALE_H
#define CLASSESOCIALE_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"

class NoeudProbable;
class GenEvt;
class Effet;
class Condition;

/**
 * @brief événements liés à la classe sociale des personnages
 */
class ClasseSociale
{
    static int COMPTEUR;
public:
    ClasseSociale();

    QString m_Nom = "";
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant l'événement
    Condition* m_ConditionSelecteurProba = nullptr; // proba d'exécution de cet événement
    QList<Condition*> m_Conditions; // éventuelle limitation bloquant ou activant l'exécution de cet événement
    QMap<QString, QString> m_ModificateursCaracs;

    Effet* GenererEffet(GenEvt* genEvt);

    static void GenererNoeudsClasseSociale(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);


    static QString GetClasseSocialeAleatoire(QString typeMonde);

    // caracs :
    static QString C_CLASSE_SOCIALE;
    // valeurs de caracs :
    static QString MISERABLES;
    static QString PAUVRES;
    static QString CLASSE_MOYENNE;
    static QString INFLUENTS;
    static QString MAITRES;

};

#endif // CLASSESOCIALE_H
