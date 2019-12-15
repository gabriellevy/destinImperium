#include "planet.h"
//#include "../destinLib/noeudnarratif.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/gestionnairecarac.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "humain.h"
#include "../socio_eco/classesociale.h"

int Planete::COMPTEUR = 0;
QMap<QString, Planete*> Planete::PLANETES;

// caracs :
QString Planete::C_PLANETE = "Planète";
QString Planete::C_TYPE_PLANETE = "Type de planète";
// valeurs de caracs :
QString Planete::PLANETE_DIVERS = "Divers";
QString Planete::PLANETE_AGRICOLE = "Monde agricole";
QString Planete::PLANETE_FORGE = "Monde forge";
QString Planete::PLANETE_FERAL = "Monde féral";
QString Planete::PLANETE_CHEVALIER = "Monde chevalier";
QString Planete::PLANETE_FEODAL = "Monde féodal";
QString Planete::PLANETE_CIVILISE = "Monde civilisé";
QString Planete::PLANETE_RUCHE = "Monde ruche";
QString Planete::PLANETE_MINIERE = "Monde minier";
// valeurs de carac C_PLANETE
QString Planete::TERRE = "Terre";

Planete::Planete()
{
    switch (Planete::COMPTEUR) {
    case 0 : {
        m_Nom = Planete::TERRE;
        m_Population = 300;// sans doute plus...
        m_TypePlanete = Planete::PLANETE_RUCHE;
        m_Faction = new Factions(Imperium);
        m_Image = ":/images/planetes/Terra_And_Luna.jpg";
        m_Climat = Tempere;
        m_TitheGrade = new TitheGrade(AptusNon);
    }break;
    case 1 : {
        m_Nom = "Accatran";
        m_Population = 10;
        m_TypePlanete = Planete::PLANETE_FORGE;
        m_Faction = new Factions(AdeptusMechanicus);
        m_Image = ":/images/planetes/Accatran.jpg";
        m_Climat = AtmosphereQuasiMorte;
        m_TitheGrade = new TitheGrade(AptusNon, IV_Secundi);
    }break;
    case 2 : {
        m_Nom = "Acreage";
        m_Population = 1;
        m_TypePlanete = Planete::PLANETE_FEODAL;
        m_Faction = new Factions(Imperium);
        m_Image = ":/images/planetes/Acreage.gif";
        m_Climat = Tempere;
    }break;
    case 3 : {
        m_Nom = "Adrastapol";
        m_Population = 10;
        m_TypePlanete = Planete::PLANETE_CHEVALIER;
        m_Faction = new Factions(Imperium);
        m_Climat = Tempere;
    }break;
    case 4 : {
        m_Nom = "Aerius";
        m_Population = 10;
        m_TypePlanete = Planete::PLANETE_RUCHE;
        m_Faction = new Factions(Imperium);
        m_Climat = Tempere;
    }break;
    case 5 : {
        m_Nom = "Aexe Cardinal";
        m_Population = 10;
        m_TypePlanete = Planete::PLANETE_AGRICOLE;
        m_Faction = new Factions(Imperium);
        m_Climat = Tempere;
    }break;
    case 6 : {
        m_Nom = "Agripinaa";
        m_Population = 1;
        m_TypePlanete = Planete::PLANETE_FORGE;
        m_Faction = new Factions(AdeptusMechanicus);
        m_Image = ":/images/planetes/Agripinaa.jpg";
        m_Climat = Froid;
        m_TitheGrade = new TitheGrade(Exactis, I_Extremis);
    }break;
    case 7 : {
        m_Nom = "Alaric Prime";
        m_Population = 1;
        m_TypePlanete = Planete::PLANETE_CHEVALIER;
        m_Faction = new Factions(Imperium);
        m_Image = ":/images/planetes/Agripinaa.jpg";
        m_Climat = Tempere;
    }break;
    case 8 : {
        m_Nom = "Amontep II";
        m_Population = 20;
        m_TypePlanete = Planete::PLANETE_FORGE;
        m_Faction = new Factions(AdeptusMechanicus);
        m_Climat = Aride;
        m_Xenos = {ex_MondeTombe};
    }break;
    case 9 : {
        m_Nom = "Anark Zeta";
        m_Population = 1;
        m_TypePlanete = Planete::PLANETE_FERAL;
        m_TitheGrade = new TitheGrade(Solutio, IV_Tertius);
        m_Faction = new Factions(Imperium);
        m_Climat = Froid;
        m_Xenos = {ex_Ogryn};
    }break;
    case 10 : {
        m_Nom = "Antax";
        m_Population = 10;
        m_TypePlanete = Planete::PLANETE_FORGE;
        m_Faction = new Factions(Imperium);
        m_Climat = Tempere;
    }break;
    case 11 : {
        m_Nom = "Kronite";
        m_Population = 1;
        m_TypePlanete = Planete::PLANETE_FEODAL;
        m_Faction = new Factions(Imperium);
        m_Climat = Tempere;
    }break;
    case 12 : {
        m_Nom = "Ogris Major";
        m_Population = 1;
        m_TypePlanete = Planete::PLANETE_FEODAL;
        m_Faction = new Factions(Imperium);
        m_Climat = Tempere;
    }break;
    case 13 : {
        m_Nom = "Birmingham";
        m_Population = 1;
        m_TypePlanete = Planete::PLANETE_FERAL;
        m_TitheGrade = new TitheGrade(Solutio, IV_Tertius);
        m_Faction = new Factions(Imperium);
        m_Climat = Tempere;
    }break;
    case 14 : {
        m_Nom = "Kaledon";
        m_Population = 1;
        m_TypePlanete = Planete::PLANETE_FERAL;
        m_TitheGrade = new TitheGrade(Solutio, IV_Tertius);
        m_Faction = new Factions(Imperium);
        m_Climat = Tempere;
    }break;
    case 15 : {
        m_Nom = "Attila";
        m_Population = 1;
        m_TypePlanete = Planete::PLANETE_FERAL;
        m_TitheGrade = new TitheGrade(Solutio, IV_Tertius);
        m_Faction = new Factions(Imperium);
        m_Climat = Tempere;
    }break;
    case 16 : {
        m_Nom = "Dreer";
        m_Population = 1;
        m_TypePlanete = Planete::PLANETE_FERAL;
        m_TitheGrade = new TitheGrade(Solutio, IV_Tertius);
        m_Faction = new Factions(Imperium);
        m_Climat = Tempere;
    }break;
    case 17 : {
        m_Nom = "Anuaris";
        m_Population = 10;
        m_TypePlanete = Planete::PLANETE_FORGE;
        m_Faction = new Factions(AdeptusMechanicus);
        m_Climat = Tempere;
    }break;
    case 18 : {
        m_Nom = "Ardium";
        m_Population = 100;
        m_TypePlanete = Planete::PLANETE_RUCHE;
        m_Faction = new Factions(Ultramarines);
        m_Climat = Tempere;
    }break;
    case 19 : {
        m_Nom = "Calth";
        m_Population = 100;
        m_TypePlanete = Planete::PLANETE_CIVILISE;
        m_Faction = new Factions(Ultramarines);
        m_Image = ":/images/planetes/Calth_1.png";
        m_Climat = Climat::AtmosphereQuasiMorte;
        m_Xenos = {ex_SuivivantsTyranides};
    }break;
    case 20 : {
        m_Nom = "Necromunda";
        m_Population = 150;
        m_TypePlanete = Planete::PLANETE_RUCHE;
        m_Faction = new Factions(Imperium);
        m_Image = ":/images/planetes/Necromunda.jpg";
        m_Climat = Climat::AtmosphereQuasiMorte;
        m_PresenceNotableImperium = {ep_RecrutementSpaceMarine};
    }break;
    case 21 : {
        m_Nom = "Mars";
        m_Population = 20;
        m_TypePlanete = Planete::PLANETE_FORGE;
        m_Faction = new Factions(AdeptusMechanicus);
        m_Image = ":/images/planetes/Mars_Red_Planet2.jpg";
        m_Climat = Climat::Aride;
        m_PresenceNotableImperium = {ep_HautAutelTechnologie};
    }break;
    case 22 : {
        m_Nom = "Macragge";
        m_Population = 0.4;
        m_TypePlanete = Planete::PLANETE_CIVILISE;
        m_Faction = new Factions(Ultramarines);
        m_Image = ":/images/planetes/Mars_Red_Planet2.jpg";
        m_Climat = Climat::Tempere;
        m_PresenceNotableImperium = {ep_MondeMereSpaceMarine, ep_DefenseOrbitalesHautes};
        m_TitheGrade = new TitheGrade(AptusNon);
    }break;
    case 23 : {
        m_Nom = "Gantz";
        m_Population = 10;
        m_TypePlanete = Planete::PLANETE_FORGE;
        m_Faction = new Factions(AdeptusMechanicus);
        m_Image = ":/images/planetes/Gantz.png";
        m_Climat = Climat::Tempere;
    }break;
    case 24 : {
        m_Nom = "Konor";
        m_Population = 10;
        m_TypePlanete = Planete::PLANETE_FORGE;
        m_Faction = new Factions(Ultramarines);
        m_Image = ":/images/planetes/Konor.png";
        m_Climat = Climat::Tempere;
    }break;
    case 25 : {
        m_Nom = "Armageddon";
        m_Population = 100;
        m_TypePlanete = Planete::PLANETE_RUCHE;
        m_Faction = new Factions(Imperium);
        m_Image = ":/images/planetes/Armageddon.jpg";
        m_Climat = Climat::AtmosphereQuasiMorte;
        m_TitheGrade = new TitheGrade(Exactis, IV_Extremis);
        this->m_Xenos = {Xenos::ex_OrksSauvagesSurvivants};
    }break;
    case 26 : {
        m_Nom = "Betalis III";
        m_Population = 1;
        m_TypePlanete = Planete::PLANETE_MINIERE;
        m_Faction = new Factions(Imperium);
        m_Image = ":/images/planetes/BetalisIII.jpg";
        m_Climat = Climat::Froid;
        this->m_Xenos = {Xenos::ex_OrksSauvagesSurvivants};
    }break;
    }

    Planete::COMPTEUR++;
}

Planete* Planete::GetPlaneteAleatoire(bool usePopulationCommePoids, bool ignorePlaneteActuelle, QString typePlanete)
{
    Planete* planeteCourante = nullptr;
    if ( ignorePlaneteActuelle)
        planeteCourante = Humain::GetHumainJoue()->GetPlanete();

    double poidsTotal = 0;
    QMap<QString, Planete*>::iterator i = Planete::PLANETES.begin();
    while (i != Planete::PLANETES.end()) {
        if ( planeteCourante != i.value() &&
             (typePlanete == "" || typePlanete == i.value()->m_TypePlanete)) {
            if ( usePopulationCommePoids)
                poidsTotal += i.value()->m_Population;
            else poidsTotal += 1;
        }
        ++i;
    }

    double val = Aleatoire::GetAl()->EntierInferieurA(qAbs(poidsTotal));
    double poidsCourant = 0;
    i = Planete::PLANETES.begin();
    while ( i != Planete::PLANETES.end()) {
        if ( planeteCourante != i.value()) {
            if ( usePopulationCommePoids)
                poidsCourant += i.value()->m_Population;
            else {
                poidsCourant += 1;
            }
            if ( poidsCourant >= val)
                break;
        }
        ++i;
    }
    return i.value();
}

Condition* Planete::AjouterModifProbaSiMondeAgricole(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_AGRICOLE, Comparateur::c_Egal)});
    return cond;
}

Condition* Planete::AjouterModifProbaSiMondeFeodal(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_FEODAL, Comparateur::c_Egal)});
    return cond;
}

Condition* Planete::AjouterModifProbaSiMondeForge(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_FORGE, Comparateur::c_Egal)});
    return cond;
}

Condition* Planete::AjouterModifProbaSiMondeMinier(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_MINIERE, Comparateur::c_Egal)});
    return cond;
}

Condition* Planete::AjouterModifProbaSiMondeRuche(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_RUCHE, Comparateur::c_Egal)});
    return cond;
}

Condition* Planete::AjouterModifProbaSiMondeFeral(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_FERAL, Comparateur::c_Egal)});
    return cond;
}

Condition* Planete::AjouterModifProbaSiMondeChevalier(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_CHEVALIER, Comparateur::c_Egal)});
    return cond;
}

Condition* Planete::AjouterConditionSiMondeFeral()
{    return new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_FERAL, Comparateur::c_Egal);}

Condition* Planete::AjouterConditionSiMondeAgricole()
{    return new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_AGRICOLE, Comparateur::c_Egal);}

Condition* Planete::AjouterConditionSiMondeFeodal()
{    return new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_FEODAL, Comparateur::c_Egal);}

Condition* Planete::AjouterConditionSiMondeChevalier()
{    return new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_CHEVALIER, Comparateur::c_Egal);}

Condition* Planete::AjouterConditionSiMondeForge()
{    return new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_FORGE, Comparateur::c_Egal);}

Condition* Planete::AjouterConditionSiMondeRuche()
{    return new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_RUCHE, Comparateur::c_Egal);}

Condition* Planete::AjouterConditionSiPasMondeFeral()
{    return new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_FERAL, Comparateur::c_Different);}

Condition* Planete::AjouterConditionSiPasMondeAgricole()
{    return new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_AGRICOLE, Comparateur::c_Different);}

Condition* Planete::AjouterConditionSiPasMondeFeodal()
{    return new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_FEODAL, Comparateur::c_Different);}

Condition* Planete::AjouterConditionSiPasMondeChevalier()
{    return new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_CHEVALIER, Comparateur::c_Different);}

Condition* Planete::AjouterConditionSiPasMondeForge()
{    return new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_FORGE, Comparateur::c_Different);}

Condition* Planete::AjouterConditionSiPasMondeRuche()
{    return new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_RUCHE, Comparateur::c_Different);}

QVector<NoeudProbable*> Planete::ConstruireToutePlanetes()
{
    QVector<NoeudProbable*> effetsPlanetes;
    Planete* planete = new Planete();
    while ( planete->m_Population > 0) {
        Planete::PLANETES[planete->m_Nom] = planete;

        planete = new Planete();
    }

    return effetsPlanetes;
}
