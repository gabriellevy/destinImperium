#ifndef HUMAIN_H
#define HUMAIN_H

#include "../destinLib/gestionnairecarac.h"
#include "planet.h"

class Humain : public DPerso
{
    static Humain* ME;
public:
    Humain(QString nom);

    static Humain* GetHumainJoue();

    Planete* GetPlanete();
    int GetAge();
};

#endif // HUMAIN_H
