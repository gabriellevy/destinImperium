#ifndef MISSION_H
#define MISSION_H

#include <QString>
#include <QMap>

class NoeudProbable;
class GenEvt;
class Condition;

/*enum TypeVoyage {
    AffectationPlanete // être affecté à une planète quelconque pour sa mission
};*/

/**
 * @brief inclut les événements et effets liés aux voyages warp
 *  - réaffectation vers une planète
 */
class Voyage
{
    static int COMPTEUR;
    QString m_Description = "";

public:
    Voyage();
    QString GetDescription();

    QString m_Nom = "";
    QMap<QString, QString> m_ModificateursCaracs;
    QString m_Image = ""; // chemin vers une éventuelle image représentant le métier
    Condition* m_Condition = nullptr; // proba de se voir affecter ce métier
    std::function<void()> m_CallbackDisplay = nullptr;

    static void GenererNoeudsVoyage(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

    static QString REAFFECTATION_PLANETE;
    static QString DESTINATION_PLANETE;
    static QString ALEATOIRE;
    static QString VOYAGE_WARP;
};

#endif // MISSION_H
