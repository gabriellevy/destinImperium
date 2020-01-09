#include "pbsante.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "types_planete/planet.h"
#include "warp/sectechaos.h"
#include "socio_eco/classesociale.h"
#include "techno/bionique.h"

QString PbSante::PESTE = "Peste";
QString PbSante::C_SANTE = "Sante";
QString PbSante::C_CONSTITUTION = "Constitution";
// valeurs de C_CONSTITUTION normal = ""
QString PbSante::RESISTANT = "Résistant";
QString PbSante::FRELE = "Frêle";
QString PbSante::MORT = "Mort";
QString PbSante::FOLIE = "Folie";

PbSante::PbSante(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "mort de vieillesse";
        m_ConditionSelecteurProba = new Condition(0.0, p_Pure);
        m_Description = "Vous êtes mort de vieillesse.";
        // déclenchable quand on vieillit (et de plus en plus probable au fur et à mesure)
        m_ConditionSelecteurProba->AjouterModifProba(0.0001,
            {new Condition(GenVieHumain::AGE, "480", Comparateur::c_Superieur)}); // 40 ans
        m_ConditionSelecteurProba->AjouterModifProba(0.0005,
            {new Condition(GenVieHumain::AGE, "600", Comparateur::c_Superieur)}); // 50 ans
        m_ConditionSelecteurProba->AjouterModifProba(0.001,
            {new Condition(GenVieHumain::AGE, "720", Comparateur::c_Superieur)}); // 60 ans
        m_ConditionSelecteurProba->AjouterModifProba(0.005,
            {new Condition(GenVieHumain::AGE, "840", Comparateur::c_Superieur)}); // 70 ans
        m_ConditionSelecteurProba->AjouterModifProba(0.01,
            {new Condition(GenVieHumain::AGE, "1020", Comparateur::c_Superieur)}); // 85 ans
        m_ConditionSelecteurProba->AjouterModifProba(0.05,
            {new Condition(GenVieHumain::AGE, "1200", Comparateur::c_Superieur)}); // 100 ans
        m_ConditionSelecteurProba->AjouterModifProba(0.1,
            {new Condition(GenVieHumain::AGE, "2400", Comparateur::c_Superieur)}); // 200 ans

        // espérance de vie différente selon la classe sociale... :
        m_ConditionSelecteurProba->AjouterModifProba(-0.001,
            {new Condition(ClasseSociale::C_CLASSE_SOCIALE, ClasseSociale::PAUVRES, Comparateur::c_Egal)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {new Condition(ClasseSociale::C_CLASSE_SOCIALE, ClasseSociale::INFLUENTS, Comparateur::c_Egal)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.01,
            {new Condition(ClasseSociale::C_CLASSE_SOCIALE, ClasseSociale::MAITRES, Comparateur::c_Egal)});
        // différence selon constitution
        m_ConditionSelecteurProba->AjouterModifProba(0.0001,
            {new Condition(PbSante::C_CONSTITUTION, PbSante::FRELE, Comparateur::c_Egal)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.005,
            {new Condition(PbSante::C_CONSTITUTION, PbSante::RESISTANT, Comparateur::c_Egal)});
        // différence selon le nombre d'implants de longévité :
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(0)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(1)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(2)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(3)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(4)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(5)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(6)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(7)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(8)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(9)});

        m_ModificateursCaracs[PbSante::C_SANTE] = PbSante::MORT;
        m_Conditions.push_back(PbSante::AjouterConditionSiVivant());

    }break;
    case 1 : {
        m_Nom = "attraper la peste noire";
        m_ConditionSelecteurProba = new Condition(0.001, p_Relative);
        m_Description = "Vous avez contracté la peste noire.";
        Planete::AjouterModifProbaSiMondeFeodal(m_ConditionSelecteurProba, 0.01);
        m_ModificateursCaracs[PbSante::PESTE] = "1";

    }break;
    case 2 : {
        m_Nom = "mort de la lèpre de Nurgle";
        m_ConditionSelecteurProba = new Condition(0.01, p_Relative);
        m_Description = "Vous mourez des suites de la lèpre de Nurgle.";
        m_ModificateursCaracs[PbSante::C_SANTE] = PbSante::MORT;
        m_Conditions.push_back(SecteChaos::AjouterConditionSiLepreDeNurgle());

    }break;
    case 3 : {
        m_Nom = "mort de la peste";
        m_ConditionSelecteurProba = new Condition(0.01, p_Relative);
        m_Description = "Vous mourez des suites de la peste.";
        m_ModificateursCaracs[PbSante::C_SANTE] = PbSante::MORT;
        m_Conditions.push_back(new Condition(PbSante::PESTE, "1", Comparateur::c_Egal));

    }break;
    }
}

Condition* PbSante::AjouterConditionSiAgeSuperieurA(int ageAnnees)
{
    Condition* cond = new Condition(GenVieHumain::AGE, QString::number(ageAnnees*12), Comparateur::c_Superieur);
    return cond;
}

Condition* PbSante::AjouterConditionSiVivant()
{
    return new Condition(PbSante::C_SANTE, PbSante::MORT, Comparateur::c_Different);
}

Condition* PbSante::AjouterModifProbaSiMort(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(PbSante::C_SANTE, PbSante::MORT, Comparateur::c_Egal)});
    return cond;
}
