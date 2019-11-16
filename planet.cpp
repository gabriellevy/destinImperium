#include "planet.h"
//#include "../destinLib/noeudnarratif.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"

int Planete::COMPTEUR = 0;
QMap<QString, Planete*> Planete::PLANETES;

Planete::Planete()
{
    switch (Planete::COMPTEUR) {
    case 0 : {
        m_Nom = "Terre";
        m_Population = 300;// sans doute plus...
        m_TypePlanete = MondeRuche;
        m_Faction = new Factions(Imperium);
        m_Image = ":/images/planetes/Terra_And_Luna.jpg";
        m_TitheGrade = new TitheGrade(AptusNon);
    }break;
    case 1 : {
        m_Nom = "Accatran";
        m_Population = 10;
        m_TypePlanete = MondeForge;
        m_Faction = new Factions(AdeptusMechanicus);
        m_Image = ":/images/planetes/Accatran.jpg";
        m_TypeDeVie = Souterraine;
        m_TitheGrade = new TitheGrade(AptusNon, IV_Secundi);
    }break;
    }

    Planete::COMPTEUR++;
}
QString Planete::GetTypeMondeAsStr()
{
    switch (m_TypePlanete) {
    case MondeForge : return "Monde forge";
    case MondeRuche : return "Monde ruche";
    case MondeAgricole : return "Monde agricole";
    case Divers : default : return "";

    }
}

QVector<NoeudProbable*> Planete::ConstruireToutePlanetes(GenEvt* genEvt, QString evtIdGoToApresEffet)
{
    QVector<NoeudProbable*> effetsPlanetes;
    Planete* planete = new Planete();
    while ( planete->m_Population > 0) {
        Planete::PLANETES[planete->m_Nom] = planete;

        QString texteNaissance = "Vous êtes nés sur " +
                planete->m_Nom +
                (planete->GetTypeMondeAsStr() == "" ? "" : ", " + planete->GetTypeMondeAsStr());

        if ( planete->m_TitheGrade != nullptr) {
            texteNaissance += " (" + planete->m_TitheGrade->GetIntitule() + ")";
        }
        texteNaissance += ".";

        if ( planete->m_Faction != nullptr) {
            texteNaissance += "\nCette planète est contrôlée par " + planete->m_Faction->m_Nom + ".";
        }

        Effet* effetNaissancePlanete = genEvt->AjouterEffetNarration(
                    texteNaissance,
                    planete->m_Image,
                    "naissance_planete_" + planete->m_Nom);
        effetNaissancePlanete->AjouterChangeurDeCarac(GenVieHumain::PLANETE, planete->m_Nom);
        effetNaissancePlanete->m_GoToEffetId = evtIdGoToApresEffet;
        NoeudProbable* noeud = new NoeudProbable(
                    effetNaissancePlanete,
                    new Condition(planete->m_Population));

        effetsPlanetes.push_back(noeud);

        planete = new Planete();
    }

    return effetsPlanetes;
}
