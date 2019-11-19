#ifndef ADMINISTRATUM_H
#define ADMINISTRATUM_H

#include <QString>
#include <QMap>

class NoeudProbable;
class GenEvt;
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
    static QVector<QString> DIVISIONS;
};

#endif // ADMINISTRATUM_H
