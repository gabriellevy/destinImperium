#ifndef ADMINISTRATUM_H
#define ADMINISTRATUM_H

#include <QString>
#include <QMap>

class NoeudProbable;
class GenEvt;
class Effet;
class Condition;

/**
 * @brief événements spécifiques à l'administratum
 */
class Administratum
{
    static int COMPTEUR;
public:
    Administratum();

    QString m_Nom = "";
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant le métier
    Condition* m_Condition = nullptr; // proba de se voir affecter ce métier
    QMap<QString, QString> m_ModificateursCaracs;

    Effet* GenererEffet(GenEvt* genEvt);

    static void GenererNoeudsAdministratum(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

    Condition* AjouterModifProbaSiAdepteAdministratum(Condition* cond, double poidsProba);
    Condition* AjouterModifProbaSiAdepteAdministratum40Ans(Condition* cond, double poidsProba);
    Condition* AjouterModifProbaSiADivision(Condition* cond, double poidsProba);

    // caracs :
    static QString RANG; // dans l'administratum
    static QString C_DIVISION; // sous partie d'administration
    // valeurs de caracs
    static QString DEPARTMENTO_MUNITORUM;
    static QString DEPARTMENTO_EXACTA;
    static QString ESTATE_IMPERIUM;
    static QString REVISION_HISTORIQUE;
    static QString OFFICIO_MEDICAE;
    static QString LOGIS_STRATEGOS;
    static QString FLOTTE_IMPERIALE_DE_GUERRE;
    static QString FLOTTE_MARCHANDE;
    static QString FLOTTE_CIVILE;
    static QString OFFICIO_ASSASSINORUM;
    static QString OFFICIO_SABATORUM;
    static QString OFFICIO_AGRICULTAE;
    static QString ORDO_TEMPESTUS;
    static QVector<QString> DIVISIONS;

    // ids d'effets
    static QString ID_AFFECTATION_DIVISION;
};

class DivisionAdministratum
{
    static int COMPTEUR;
    static QVector<DivisionAdministratum*> DIVISIONS;
public:
    DivisionAdministratum();

    QString m_Nom = "";
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant la division
    Condition* m_Condition = nullptr; // proba de se voir affecter à cette diviion
    QMap<QString, QString> m_ModificateursCaracs;


    static void GenererDivisions();
    static void GenererNoeudsAffectation(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

};

#endif // ADMINISTRATUM_H
