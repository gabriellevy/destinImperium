#ifndef PLANET_H
#define PLANET_H

#include <QString>
#include <QList>
#include <QVector>
#include "factions/factions.h"
#include "tithegrade.h"

class NoeudProbable;
class GenEvt;
class Condition;

enum Xenos { // présence xénos sur la planète
    ex_MondeTombe, // contient des nécrons en sous-sol
    ex_SuivivantsTyranides, // pas une flotte complète : des survivants d'une invasion ratée
    ex_OrksSauvagesSurvivants, // orks survivants d'une guerre passée qui survivent en relativement petits nombres sur la planète
    ex_Ogryn // monde de recrutement Ogryn
};

enum PresenceNotableImperium { // organisations, bâtiments etc très importants de l'imperium présents sur la planète
    ep_RecrutementSpaceMarine,
    ep_MondeMereSpaceMarine, //  monde principal d'un chaître (unique pour ce chapitre, pas forcément recruteur)
    // uniques :
    ep_HautAutelTechnologie, // de Mars
    // semi courants
    ep_DefenseOrbitalesHautes // mondes particulièrement bien défendus
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
    QString m_TypePlanete = Planete::PLANETE_DIVERS;
    Climat m_Climat = Tempere;
    Factions* m_Faction = nullptr;// qui contrôle la planète
    TitheGrade* m_TitheGrade = nullptr;
    QVector<Xenos> m_Xenos;
    QVector<PresenceNotableImperium> m_PresenceNotableImperium;

    static QMap<QString, Planete*> PLANETES;
    static Planete* GetPlaneteAleatoire(bool usePopulationCommePoids = true, bool ignorePlaneteActuelle = false);
    static QVector<NoeudProbable*> ConstruireToutePlanetes();

    // modificateurs de condition standards :
    static Condition* AjouterModifProbaSiMondeAgricole(Condition* cond, double poidsProba);
    static Condition* AjouterModifProbaSiMondeFeodal(Condition* cond, double poidsProba);
    static Condition* AjouterModifProbaSiMondeFeral(Condition* cond, double poidsProba);
    static Condition* AjouterModifProbaSiMondeChevalier(Condition* cond, double poidsProba);
    static Condition* AjouterModifProbaSiMondeForge(Condition* cond, double poidsProba);
    static Condition* AjouterModifProbaSiMondeRuche(Condition* cond, double poidsProba);

    // caracs associées :
    static QString C_PLANETE;
    static QString C_TYPE_PLANETE;
    // valeurs de carac associées :
    static QString PLANETE_DIVERS;
    static QString PLANETE_AGRICOLE;
    static QString PLANETE_FORGE;
    static QString PLANETE_FERAL;
    static QString PLANETE_CHEVALIER;
    static QString PLANETE_FEODAL;
    static QString PLANETE_CIVILISE;
    static QString PLANETE_RUCHE;
    // valeurs de carac C_PLANETE
    static QString TERRE;
};

#endif // PLANET_H
