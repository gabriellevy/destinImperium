#ifndef SANTE_H
#define SANTE_H

#include <QString>
#include <QMap>

class NoeudProbable;
class GenEvt;
class Condition;

enum IdPbSante {
    MortVieillesse, // risque de mourir quand on dépasse 50 ans
    PesteNoire // réservé aux mondes féodaux (réduit grandement l'espérance de vie générale)
};


/**
 * @brief Tout ce qui concerne la santé y compris la mort par vieillesse et les maladies
 */
class PbSante
{
    IdPbSante m_IdPbSante;
    static int COMPTEUR;
public:
    PbSante();

    Condition* m_ConditionSelecteurProba = nullptr; // proba d'exécution de cet événement
    QList<Condition*> m_Conditions; // éventuelle limitation bloquant ou activant l'exécution de cet événement
    QString m_Intitule = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant le problème de santé
    QMap<QString, QString> m_ModificateursCaracs; // ce que le problèmed e santé change comme carac

    static void GenererNoeudsSelectionPbSante(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

    // caracs liées :
    static QString PESTE;
    static QString C_SANTE;
    // valeurs de C_SANTE
    static QString MORT;

    static Condition* AjouterModifProbaSiMort(Condition* cond, double poidsProba);
};

#endif // SANTE_H