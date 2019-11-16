#ifndef PLANET_H
#define PLANET_H

#include <QString>
#include <QList>
#include <QVector>
#include "factions.h"
#include "tithegrade.h"

class NoeudProbable;
class GenEvt;

enum TypePlanete {
    Divers,
    MondeAgricole,
    MondeForge,
    MondeRuche
};

enum TypeDeVie { // type de vie sur cette planète pour l'humain typique
    Banale, // villes blablabla
    Souterraine
};



class Planete
{
    static int COMPTEUR;

public:
    Planete();

    QString m_Nom = "";
    QString m_Image = "";
    double m_Population = -1;// en milliards
    TypePlanete m_TypePlanete = Divers;
    TypeDeVie m_TypeDeVie = Banale;
    Factions* m_Faction = nullptr;// qui contrôle la planète
    TitheGrade* m_TitheGrade = nullptr;

    static QMap<QString, Planete*> PLANETES;
    static QVector<NoeudProbable*> ConstruireToutePlanetes(GenEvt* genEvt, QString evtIdGoToApresEffet);

    QString GetTypeMondeAsStr();
};

#endif // PLANET_H
