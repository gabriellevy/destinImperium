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
    MondeFeral,
    MondeChevalier,
    MondeFeodal,
    MondeRuche
};

enum Xenos { // présence xénos sur la planète
    MondeTombe, // contient des nécrons en sous-sol
    Ogryn // monde de recrutement Ogryn
};

enum Climat {
    Tempere, // tempéré
    Aride,
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
    QVector<Xenos> m_Xenos;

    static QMap<QString, Planete*> PLANETES;
    static QVector<NoeudProbable*> ConstruireToutePlanetes(GenEvt* genEvt, QString evtIdGoToApresEffet);

    QString GetTypeMondeAsStr();

    static QString GetTypeMondeAsStr(TypePlanete typePlanete);

    // modificateurs de condition standards :
    static Condition* AjouterModifProbaSiMondeAgricole(Condition* cond, double poidsProba);
    static Condition* AjouterModifProbaSiMondeFeodal(Condition* cond, double poidsProba);
    static Condition* AjouterModifProbaSiMondeFeral(Condition* cond, double poidsProba);
    static Condition* AjouterModifProbaSiMondeChevalier(Condition* cond, double poidsProba);
};

#endif // PLANET_H
