#ifndef MINISTORUM_H
#define MINISTORUM_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

class Ministorum : public GenerateurNoeudsProbables
{
public:
    Ministorum(int indexEvt);

    // caracs
};

#endif // MINISTORUM_H
