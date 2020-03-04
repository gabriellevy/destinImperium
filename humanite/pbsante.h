#ifndef SANTE_H
#define SANTE_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;


/**
 * @brief Tout ce qui concerne la santé y compris la mort par vieillesse et les maladies
 */
class PbSante : public GenerateurNoeudsProbables
{
public:
    PbSante(int indexEvt);

    // caracs liées :
    static QString C_SANTE;
    static QString C_CONSTITUTION; // influe sur espérance de vie
    // valeurs de C_CONSTITUTION "" = normal
    static QString RESISTANT;
    static QString FRELE;
    // valeurs de C_SANTE
    static QString MORT;
    static QString FOLIE;
    static QString PESTE;

    static std::shared_ptr<Condition> AjouterModifProbaSiMort(std::shared_ptr<Condition> cond, double poidsProba);
    static std::shared_ptr<Condition> AjouterConditionSiVivant();
    static std::shared_ptr<Condition> AjouterConditionSiAgeSuperieurA(int ageAnnees);
};

#endif // SANTE_H
