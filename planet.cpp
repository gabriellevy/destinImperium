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
        m_Climat = Tempere;
        m_TitheGrade = new TitheGrade(AptusNon);
    }break;
    case 1 : {
        m_Nom = "Accatran";
        m_Population = 10;
        m_TypePlanete = MondeForge;
        m_Faction = new Factions(AdeptusMechanicus);
        m_Image = ":/images/planetes/Accatran.jpg";
        m_Climat = AtmosphereQuasiMorte;
        m_TitheGrade = new TitheGrade(AptusNon, IV_Secundi);
    }break;
    case 2 : {
        m_Nom = "Acreage";
        m_Population = 1;
        m_TypePlanete = MondeFeodal;
        m_Faction = new Factions(Imperium);
        m_Image = ":/images/planetes/Acreage.gif";
        m_Climat = Tempere;
    }break;
    case 3 : {
        m_Nom = "Adrastapol";
        m_Population = 10;
        m_TypePlanete = MondeChevalier;
        m_Faction = new Factions(Imperium);
        m_Climat = Tempere;
    }break;
    case 4 : {
        m_Nom = "Aerius";
        m_Population = 10;
        m_TypePlanete = MondeRuche;
        m_Faction = new Factions(Imperium);
        m_Climat = Tempere;
    }break;
    case 5 : {
        m_Nom = "Aexe Cardinal";
        m_Population = 10;
        m_TypePlanete = MondeAgricole;
        m_Faction = new Factions(Imperium);
        m_Climat = Tempere;
    }break;
    case 6 : {
        m_Nom = "Agripinaa";
        m_Population = 1;
        m_TypePlanete = MondeForge;
        m_Faction = new Factions(AdeptusMechanicus);
        m_Image = ":/images/planetes/Agripinaa.jpg";
        m_Climat = Froid;
        m_TitheGrade = new TitheGrade(Exactis_Tertius, I_Extremis);
    }break;
    }

    Planete::COMPTEUR++;
}
QString Planete::GetTypeMondeAsStr()
{
    return Planete::GetTypeMondeAsStr(m_TypePlanete);
}

QString Planete::GetTypeMondeAsStr(TypePlanete typePlanete)
{
    switch (typePlanete) {
    case MondeForge : return "Monde forge";
    case MondeRuche : return "Monde ruche";
    case MondeAgricole : return "Monde agricole";
    case MondeChevalier : return "Monde chevalier";
    case Divers : default : return "";

    }
}

Condition* Planete::AjouterModifProbaSiMondeAgricole(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(GenVieHumain::TYPE_PLANETE, Planete::GetTypeMondeAsStr(MondeAgricole), Comparateur::c_Egal)});
    return cond;
}

Condition* Planete::AjouterModifProbaSiMondeFeodal(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(GenVieHumain::TYPE_PLANETE, Planete::GetTypeMondeAsStr(MondeFeodal), Comparateur::c_Egal)});
    return cond;
}

Condition* Planete::AjouterModifProbaSiMondeChevalier(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(GenVieHumain::TYPE_PLANETE, Planete::GetTypeMondeAsStr(MondeChevalier), Comparateur::c_Egal)});
    return cond;
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
        effetNaissancePlanete->AjouterChangeurDeCarac(GenVieHumain::TYPE_PLANETE, planete->GetTypeMondeAsStr());
        effetNaissancePlanete->m_GoToEffetId = evtIdGoToApresEffet;
        NoeudProbable* noeud = new NoeudProbable(
                    effetNaissancePlanete,
                    new Condition(planete->m_Population));

        effetsPlanetes.push_back(noeud);

        planete = new Planete();
    }

    return effetsPlanetes;
}
