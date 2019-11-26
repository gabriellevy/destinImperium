#ifndef INQUISITION_H
#define INQUISITION_H

#include <QString>
#include <QMap>

class NoeudProbable;
class GenEvt;
class Effet;
class Condition;

/**
 * @brief événements d'inquisition
 */
class Inquisition
{
    static int COMPTEUR;
public:
    Inquisition();

    QString m_Nom = "";
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant le métier
    Condition* m_Condition = nullptr; // proba de se voir affecter ce métier
    QMap<QString, QString> m_ModificateursCaracs;

    Effet* GenererEffet(GenEvt* genEvt);

    // caracs :
    static QString C_ORDO; // sous partie d'administration
    // valeurs de caracs
    static QString ORDO_XENOS;
    static QString ORDO_MALLEUS;
    static QString ORDO_HERETICUS;

    static QString ID_AFFECTATION_DIVISION;

    static void GenererNoeudsInquisition(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

    Condition* AjouterModifProbaSiAOrdo(Condition* cond, double poidsProba);

    Condition* AjouterModifProbaSiInquisiteur(Condition* cond, double poidsProba);
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
    Condition* m_Condition = nullptr; // proba de se voir affecter à cette diviion
    QMap<QString, QString> m_ModificateursCaracs;

    static void GenererOrdos();
    static void GenererNoeudsAffectation(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

};

#endif // INQUISITION_H