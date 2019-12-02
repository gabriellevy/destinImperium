#ifndef HUMAIN_H
#define HUMAIN_H

#include "../destinLib/gestionnairecarac.h"
#include "types_planete/planet.h"

class Humain : public DPerso
{
    static Humain* ME;
public:
    Humain(QString nom);

    static Humain* GetHumainJoue();

    Planete* GetPlanete();
    int GetAge();

    virtual QString GetValeurCarac(QString id);
    virtual int GetValeurCaracAsInt(QString id);
    virtual void ExecutionPostChangeCarac();
};

#endif // HUMAIN_H
