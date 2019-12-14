#ifndef ECONOMIEEVT_H
#define ECONOMIEEVT_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"

class NoeudProbable;
class GenEvt;
class Effet;
class Condition;


class EconomieEvt
{
    static int COMPTEUR;
public:
    EconomieEvt();

    QString m_Nom = "";
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant l'événement
    Condition* m_ConditionSelecteurProba = nullptr; // proba d'exécution de cet événement
    QList<Condition*> m_Conditions; // éventuelle limitation bloquant ou activant l'exécution de cet événement
    QMap<QString, QString> m_ModificateursCaracs;
    QMap<QString, int> m_IncrementeursCaracs;

    Effet* GenererEffet(GenEvt* genEvt);

    static void GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

    static Condition* AjouterConditionSiAMetier();

    // caracs :
    // valeur int approximant la réputation et le niveau de salaire du personnage dans son métier (relativement à sa classe sociale).
    // une très forte valeur pourrait lui voir arriver des promotions voire changer de classe sociale
    // marche aussi en sens négatif
    static QString C_NIVEAU_ECONOMIQUE;
};

#endif // ECONOMIEEVT_H
