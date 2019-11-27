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
 * @brief dénominations abstraites des classes, qui sont précisées selon les planètes
 */
enum e_ClasseSociale {
    Miserable,
    Pauvre,
    ClasseMoyenne,
    Influents,
    Maitres // nobles etc
};

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
    Condition* m_Condition = nullptr;
    QMap<QString, QString> m_ModificateursCaracs;

    Effet* GenererEffet(GenEvt* genEvt);

    static void GenererNoeudsClasseSociale(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);


    static e_ClasseSociale GetClasseSocialeAleatoire(TypePlanete typeMonde);

    static QString GetClasseSocialeAsStr(e_ClasseSociale classSociale, TypePlanete typeMonde);

    // caracs :
    static QString CLASSE_SOCIALE;
};

#endif // CLASSESOCIALE_H
