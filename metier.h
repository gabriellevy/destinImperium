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

    static std::shared_ptr<Condition> AjouterConditionSiAMetier();
    static std::shared_ptr<Condition> AjouterConditionSiACeMetier(QString metier);
    static std::shared_ptr<Condition> AjouterConditionSiAPasMetier();
    static std::shared_ptr<Condition> AjouterModifProbaSiAMetierIntegre(std::shared_ptr<Condition> proba, double modifProbaVal);
    static QList<QString> METIERS_INTEGRES; //  métiers où la criminalité est extrêmement faible

    static QString C_METIER;
    // valeurs de métiers :
    static QString INEMPLOYABLE; // quand le eprso n'est plus bon à rien (maladie extrêmement grave par ex)
    static QString PAYSAN;
    static QString MINEUR;
    static QString CHASSEUR_CUEILLEUR_NOMADE;
    static QString OUVRIER;
    static QString GARDE_IMPERIAL;
    static QString MARIN_IMPERIAL;
    static QString ADEPTE_ADMINISTRATUM;
    static QString TECHNOPRETRE;
    // Adeptus Arbites :
    static QString ARBITES; // Adeptus Arbites
    // mondes chevaliers :
    static QString NOBLE_CHEVALIER;
    static QString INQUISITEUR;
    static QString SERVANT_ADEPTUS_ASTRONOMICA;
    static QString ADEPTUS_ASSASSINORUM;
    static QString ADEPTUS_MINISTORUM;
    // psykers
    static QString SCHOLIA_PSYKANA;
    static QString ASTRONOMICA;
    static QString PSYKER_PRIMARIS;
    static QString ASTROPATHE;
};

#endif // METIER_H
