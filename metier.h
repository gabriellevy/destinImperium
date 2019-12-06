#ifndef METIER_H
#define METIER_H

#include <QString>
#include <QMap>

class NoeudProbable;
class GenEvt;
class Condition;

class Metier
{
    static int COMPTEUR;
public:
    Metier();

    QString m_Nom = ""; // et id
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant le métier
    Condition* m_ConditionSelecteurProba = nullptr; // proba d'exécution de cet événement
    QList<Condition*> m_Conditions; // éventuelle limitation bloquant ou activant l'exécution de cet événement
    QMap<QString, QString> m_ModificateursCaracs;
    std::function<void()> m_CallbackDisplay = nullptr;

    static void GenererNoeudsSelectionMetier(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

    static QMap<QString, Metier*> METIERS;

    static QString C_METIER;
    // valeurs de métiers :
    static QString PAYSAN;
    static QString GARDE_IMPERIAL;
    static QString ADEPTE_ADMINISTRATUM;
    // Adeptus Arbites :
    static QString ARBITES; // Adeptus Arbites
    // mondes chevaliers :
    static QString NOBLE_CHEVALIER;
    static QString INQUISITEUR;
    static QString SERVANT_ADEPTUS_ASTRONOMICA;
    static QString ADEPTUS_ASSASSINORUM;
    static QString ADEPTUS_MINISTORUM;
};

#endif // METIER_H
