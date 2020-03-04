#ifndef ECONOMIEEVT_H
#define ECONOMIEEVT_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

class EconomieEvt : public GenerateurNoeudsProbables
{
public:
    EconomieEvt(int indexEvt);

    // caracs :
    // valeur int approximant la réputation et le niveau de salaire du personnage dans son métier (relativement à sa classe sociale).
    // une très forte valeur pourrait lui voir arriver des promotions voire changer de classe sociale
    // marche aussi en sens négatif
    // valable en tant que réputation dans les métiers où l'argent est secondaire
    static QString C_NIVEAU_ECONOMIQUE;

    static std::shared_ptr<Condition> AjouterConditionSiNiveauEconomiqueSuperieurA(int niv);
};

#endif // ECONOMIEEVT_H
