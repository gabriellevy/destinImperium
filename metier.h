#ifndef METIER_H
#define METIER_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

class Metier : public GenerateurNoeudsProbables
{
public:
    Metier(int indexEvt);

    static QMap<QString, Metier*> METIERS;

    static Condition* AjouterConditionSiAMetier();
    static Condition* AjouterConditionSiAPasMetier();

    static QString C_METIER;
    // valeurs de métiers :
    static QString PAYSAN;
    static QString MINEUR;
    static QString CHASSEUR_CUEILLEUR_NOMADE;
    static QString OUVRIER;
    static QString GARDE_IMPERIAL;
    static QString MARIN_IMPERIAL;
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
