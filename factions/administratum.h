#ifndef ADMINISTRATUM_H
#define ADMINISTRATUM_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

/**
 * @brief événements spécifiques à l'administratum
 */
class Administratum : public GenerateurNoeudsProbables
{
public:
    Administratum(int indexEvt);

    virtual Effet* GenererEffet(GenEvt* genEvt);

    Condition* AjouterModifProbaSiAdepteAdministratum(Condition* cond, double poidsProba);
    Condition* AjouterModifProbaSiScribeAdministratum40Ans(Condition* cond, double poidsProba);
    Condition* AjouterModifProbaSiOrdinateAdministratum50Ans(Condition* cond, double poidsProba);
    Condition* AjouterModifProbaSiPrefetAdministratum60Ans(Condition* cond, double poidsProba);
    Condition* AjouterModifProbaSiADivision(Condition* cond, double poidsProba);

    static void RafraichirPhrases();

    static void AffecterBureauMunitorum(); // runtime function

    // caracs :
    static QString C_DIVISION; // sous partie d'administration
    static QString C_BUREAU_MUNITORUM; // sous partie d'administration
    // valeurs de C_DIVISION
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
    // valeurs de C_BUREAU_MUNITORUM
    static QString OFFICIO_TACTICA;
    static QString BUREAU_COMMISSAIRE;
    static QString BUREAU_ENREGISTREMENT;
    static QString SCHOLA_PROGENIUM;
    static QString CORPS_EVALUATION;
    static QString COMMISSARIAT;
    static QString CORPS_INGENIEUR;
    static QString CORPS_EXECUTION;
    static QString CORPS_SAPEURS;
    static QString CORPS_PIONNIERS;
    static QString CORPS_SIEGE;

    // ids d'effets
    static QString ID_AFFECTATION_DIVISION;

    // grades
    static QString C_RANG; // dans l'administratum
    static QString GRADE_SCRIBE;
    static QString GRADE_ORDINATE;
    static QString GRADE_PREFET;
    static QString GRADE_MAITRE;
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
    static QVector<QPair<QString, QString>> BUREAU_MUNITORUM;

};

#endif // ADMINISTRATUM_H
