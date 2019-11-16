#include "planet.h"
//#include "../destinLib/noeudnarratif.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"

int Planete::COMPTEUR = 0;
QMap<QString, Planete*> Planete::PLANETES;

Planete::Planete()
{
    m_Nom = "";
    m_Population = -1;
    m_TypePlanete = Divers;

    switch (Planete::COMPTEUR) {
    case 0 : {
        m_Nom = "Terre";
        m_Population = 50;// sans doute plus...
    }break;
    case 1 : {
        m_Nom = "Accatran";
        m_Population = 10;
        m_TypePlanete = MondeForge;
        m_Faction = new Factions(AdeptusMechanicus);
    }break;
    }

    Planete::COMPTEUR++;
}
QString Planete::GetTypeMondeAsStr()
{
    switch (m_TypePlanete) {
    case MondeForge : return "Monde forge";
    case MondeAgricole : return "Monde agricole";
    case Divers : default : return "";

    }
}

QVector<NoeudProbable*> Planete::ConstruireToutePlanetes(GenEvt* genEvt)
{
    QVector<NoeudProbable*> effetPlanetes;
    Planete* planete = new Planete();
    while ( planete->m_Population > 0) {
        Planete::PLANETES[planete->m_Nom] = planete;

        QString texteNaissance = "Vous êtes nés sur " +
                planete->m_Nom +
                (planete->GetTypeMondeAsStr() == "" ? "." : ", " + planete->GetTypeMondeAsStr() + ".");

        if ( planete->m_Faction != nullptr) {
            texteNaissance += "\nCette planète est contrôlée par " + planete->m_Faction->m_Nom + ".";
        }

        NoeudProbable* noeud = new NoeudProbable(
                    genEvt->AjouterEffetNarration(
                        texteNaissance,
                        "",
                        "naissance_planete_" + planete->m_Nom),
                    new Condition(planete->m_Population));

        effetPlanetes.push_back(noeud);

        planete = new Planete();
    }

    return effetPlanetes;
}
