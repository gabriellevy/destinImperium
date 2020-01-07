#ifndef BIONIQUE_H
#define BIONIQUE_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;


class Bionique : public GenerateurNoeudsProbables
{
public:
    Bionique(int indexEvt);

    static QString C_BIONIQUE_LONGEVITE; // nombre de bioniques ajouté au corps pour augmenter la longévité
};

#endif // BIONIQUE_H
