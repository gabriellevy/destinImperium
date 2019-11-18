#ifndef METIER_H
#define METIER_H

#include <QString>
#include <QMap>

class NoeudProbable;
class GenEvt;
class Condition;

enum e_Metier {
    Paysan,
    GardeImperial,
    FonctionnaireAdministratum,
    // Adeptus Arbites :
    Arbitrator, // Adeptus Arbites
    AdeptusArbitesJuge, //  => inateignable pour l'instant
    GrandPrevotMarechal, // chef de tout l'adeptus => innateignable pour l'instant
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
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant le métier
    Condition* m_Condition = nullptr; // proba de se voir affecter ce métier
    QMap<QString, QString> m_ModificateursCaracs;

    static void GenererNoeudsSelectionMetier(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);
};

#endif // METIER_H
