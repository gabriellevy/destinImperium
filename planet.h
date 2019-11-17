#ifndef PLANET_H
#define PLANET_H

#include <QString>
#include <QList>
#include <QVector>
#include "factions.h"
#include "tithegrade.h"

class NoeudProbable;
class GenEvt;
class Condition;

enum TypePlanete {
    Divers,
    MondeAgricole,
    MondeForge,
    MondeChevalier,
    MondeFeodal,
    MondeRuche
};

enum Climat {
    Tempere, // tempéré
    Froid,
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

    // modificateurs de condition standards :
    static Condition* AjouterModifProbaSiMondeAgricole(Condition* cond, double poidsProba);
    static Condition* AjouterModifProbaSiMondeFeodal(Condition* cond, double poidsProba);
    static Condition* AjouterModifProbaSiMondeChevalier(Condition* cond, double poidsProba);
};

#endif // PLANET_H
