#ifndef MONDERUCHE_H
#define MONDERUCHE_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

/**
 * @brief événements liés aux mondes ruches
 */
class MondeRuche : public GenerateurNoeudsProbables
{
public:
    MondeRuche(int indexEvt);

    static QList<QString> RUCHES; // noms de ruche stockés en vrac peu importe leur monde originel
    static QString GetNomRucheAleatoire();
    static void AssignerCaracsDeNaissance(QString classeSociale, Effet* effetAffectation);

    // caracs
    static QString C_ZONE_DHABITATION;
    // valeurs de C_ZONE_DHABITATION
    static QString POINTE;
    static QString RUCHE;
    static QString SOUSMONDE;
    static QString BASFONDS;
    static QString DESERT_DE_CENDRES;

};

#endif // MONDERUCHE_H
