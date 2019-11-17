#ifndef METIER_H
#define METIER_H

#include <QString>

class NoeudProbable;
class GenEvt;
class Condition;

enum e_Metier {
    Paysan,
    FonctionnaireAdministratum,
    // mondes chevaliers :
    NobleChevalier
};

class Metier
{
    e_Metier m_Metier;
    static int COMPTEUR;
public:
    Metier();

    QString m_Nom = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant le métier
    Condition* m_Condition = nullptr; // proba de se voir affecter ce métier

    static void GenererNoeudsSelectionMetier(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);
};

#endif // METIER_H
