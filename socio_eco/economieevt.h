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

    static Condition* AjouterConditionSiAMetier();

    // caracs :
    // valeur int approximant la réputation et le niveau de salaire du personnage dans son métier (relativement à sa classe sociale).
    // une très forte valeur pourrait lui voir arriver des promotions voire changer de classe sociale
    // marche aussi en sens négatif
    static QString C_NIVEAU_ECONOMIQUE;
};

#endif // ECONOMIEEVT_H
