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
    MondeFeodal,
    MondeRuche
};

enum Climat {
    Tempere, // tempéré
    AtmosphereQuasiMorte // vie souterraine ou en ruche obligatoire
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
    Climat m_Climat = Tempere;
    Factions* m_Faction = nullptr;// qui contrôle la planète
    TitheGrade* m_TitheGrade = nullptr;

    static QMap<QString, Planete*> PLANETES;
    static QVector<NoeudProbable*> ConstruireToutePlanetes(GenEvt* genEvt, QString evtIdGoToApresEffet);

    QString GetTypeMondeAsStr();

    static QString GetTypeMondeAsStr(TypePlanete typePlanete);
};

#endif // PLANET_H
