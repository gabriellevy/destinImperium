#ifndef CRIME_H
#define CRIME_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"

class NoeudProbable;
class GenEvt;
class Effet;
class Condition;


class Crime
{
    static int COMPTEUR;
public:
    Crime();

    QString m_Nom = "";
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant l'événement
    Condition* m_ConditionSelecteurProba = nullptr; // proba d'exécution de cet événement
    QList<Condition*> m_Conditions; // éventuelle limitation bloquant ou activant l'exécution de cet événement
    QMap<QString, QString> m_ModificateursCaracs;

    Effet* GenererEffet(GenEvt* genEvt);

    static void GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

    // ajoute à la liste de conditions une condition validée seulement si on est une personne libre
    static QList<Condition*> AjouterConditionSiLibre(QList<Condition*> conditions);
    static QList<Condition*> AjouterConditionSiNonLibre(QList<Condition*> conditions);


    // caracs :
    static QString C_CRIMINEL;
    //valeurs de C_CRIMINEL : ("" signifie innocent). Note : êre jugé innocent même si n est coupable remet en ""
    static QString DELINQUANT;
    static QString CRIMINEL;
    // valeurs de GenVieHumain::C_LIBERTE :
    static QString CAPTURE_POLICE;
    static QString CAPTURE_ARBITES;
};

#endif // CRIME_H
