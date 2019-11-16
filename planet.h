#ifndef PLANET_H
#define PLANET_H

#include <QString>
#include <QList>
#include <QVector>
#include "factions.h"

class NoeudProbable;
class GenEvt;

enum TypePlanete {
    Divers,
    MondeAgricole,
    MondeForge
};

class Planete
{
    static int COMPTEUR;

public:
    Planete();

    QString m_Nom;
    double m_Population;// en milliards
    TypePlanete m_TypePlanete;
    Factions* m_Faction = nullptr;

    static QMap<QString, Planete*> PLANETES;
    static QVector<NoeudProbable*> ConstruireToutePlanetes(GenEvt* genEvt);

    QString GetTypeMondeAsStr();
};

#endif // PLANET_H
