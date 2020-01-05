#ifndef INQUISITION_H
#define INQUISITION_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

/**
 * @brief événements d'inquisition
 */
class Inquisition : public GenerateurNoeudsProbables
{
public:
    Inquisition(int indexEvt);

    Effet* GenererEffet(GenEvt* genEvt);

    // caracs :
    static QString C_ORDO; // sous partie d'administration
    // valeurs de caracs
    static QString ORDO_XENOS;
    static QString ORDO_MALLEUS;
    static QString ORDO_HERETICUS;
    static QString ORDO_MACHINUM;
    static QString ORDO_MILITUM;
    static QString ORDO_OBSULETUS;
    static QString ORDO_ORIGINATUS;
    static QString ORDO_REDACTUS;
    static QString ORDO_SCRIPTORUM;
    static QString ORDO_SEPULTURUM;
    static QString ORDO_SICARIUS;

    static QString ID_AFFECTATION_ORDO;

    Condition* AjouterModifProbaSiAOrdo(Condition* cond, double poidsProba);

    Condition* AjouterModifProbaSiInquisiteur(Condition* cond, double poidsProba);

    static void RafraichirPhrases(); // phrases d'ambiance
};

class Ordo
{
    static int COMPTEUR;
    static QVector<Ordo*> ORDOS;
public:
    Ordo();

    QString m_Nom = "";
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant la division
    Condition* m_ConditionSelecteurProba = nullptr; // proba de se voir affecter à cette diviion
    QList<Condition*> m_Conditions;
    QMap<QString, QString> m_ModificateursCaracs;

    static void GenererOrdos();
    static void GenererNoeudsAffectation(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

};

#endif // INQUISITION_H
