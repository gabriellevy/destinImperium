#include "sectechaos.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "../types_planete/planet.h"
#include "voyage.h"
#include "metier.h"
#include "../destinLib/effet.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/execeffet.h"
#include "humain.h"
#include "psyker.h"
#include "humanite/pbsante.h"

QString SecteChaos::C_SECTE_CHAOS = "Appartient à secte du chaos";
QString SecteChaos::C_INFLUENCE_CHAOS = "Influence du chaos";
QString SecteChaos::C_DIEU = "Dieu du chaos vénéré";

QString SecteChaos::KHORNE = "Khorne";
QString SecteChaos::TZEENTCH = "Tzeentch";
QString SecteChaos::SLAANESH = "Slaanesh";
QString SecteChaos::NURGLE = "Nurgle";

QString SecteChaos::LEPRE_DE_NURGLE = "Lèpre de Nurgle";

SecteChaos::SecteChaos(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmpTestVal = 0.0;
    switch (indexEvt) {
    case 0 : {
        m_Nom = "Entrée dans secte du chaos";
        m_ConditionSelecteurProba = new Condition(0.05, p_Relative);
        m_Description = "Tenté par les dieux noirs, vous rejoignez une secte du chaos.";
        m_Conditions.push_back(SecteChaos::AjouterConditionSiInfluenceChaosSuperieurA(5));
        m_ModificateursCaracs[SecteChaos::C_SECTE_CHAOS] = "1";
        m_CallbackDisplay = [] {
            QPair<QString, QString> dieu = SecteChaos::DeterminerDieuVenere();
            ExecHistoire::GetExecEffetActuel()->ChargerImage(dieu.second);
            Humain::GetHumainJoue()->SetValeurACaracId(SecteChaos::C_DIEU, dieu.first);
        };

    }break;
    case 1 : {
        m_Nom = "Attrape la lèpre de Nurgle";
        m_ConditionSelecteurProba = new Condition(0.0001, p_Relative);
        m_Description = "Vous attrapez une horrible maladie semblable à la lèpre. "
                "Vous êtes rapidement forcé à vous isoler et perdez votre travail et ebaucoup de vos relations.";
        m_ModificateursCaracs[PbSante::C_SANTE] = SecteChaos::LEPRE_DE_NURGLE;
        m_ModificateursCaracs[SecteChaos::C_DIEU] = SecteChaos::NURGLE;
        m_IncrementeursCaracs[SecteChaos::C_INFLUENCE_CHAOS] = 3;
        m_ModificateursCaracs[Metier::C_METIER] = "";

    }break;
    case 2 : {
        m_Nom = "Influence du chaos";
        m_ConditionSelecteurProba = new Condition(0.005 + tmpTestVal, p_Relative);
        Psyker::AjouterModifProbaSiPsyker(m_ConditionSelecteurProba, 0.01);
        SecteChaos::AjouterModificateurProbaSiInfluenceChaosSuperieurA(m_ConditionSelecteurProba, 1, 0.02);
        m_Description = "remplacé à l'exécution";
        m_IncrementeursCaracs[SecteChaos::C_INFLUENCE_CHAOS] = 1;
        m_CallbackDisplay = [] {
            QVector<QString> textes = {
                "Vous avez des hallucinations étranges et terrifiantes. Des créatures spectrales grimaçantes.",
                "Un de vos amis vous confie aller souvent à des réunions sacrètes mystiques."
            };
            ExecHistoire::GetEffetActuel()->m_Texte = textes[Aleatoire::GetAl()->EntierInferieurA(textes.length())];
        };

    }break;
    }
}

Condition* SecteChaos::AjouterModificateurProbaSiInfluenceChaosSuperieurA(Condition* condProba, int nivInfluence, double modifProba)
{
    condProba->AjouterModifProba(modifProba,
        {         new Condition(SecteChaos::C_INFLUENCE_CHAOS, QString::number(nivInfluence), Comparateur::c_Superieur)        });
    return condProba;
}

Condition* SecteChaos::AjouterConditionSiInfluenceChaosSuperieurA(int nivInfluence)
{
    return new Condition(SecteChaos::C_INFLUENCE_CHAOS, QString::number(nivInfluence), Comparateur::c_Superieur);
}

Condition* SecteChaos::AjouterConditionSiLepreDeNurgle()
{
    return new Condition(PbSante::C_SANTE, SecteChaos::LEPRE_DE_NURGLE, Comparateur::c_Egal);
}

QPair<QString, QString> SecteChaos::DeterminerDieuVenere()
{
    QPair<QString, QString> dieu;
    Humain* humain = Humain::GetHumainJoue();
    double probaKhorne = 0.25;
    if ( humain->GetValeurCarac(Planete::C_TYPE_PLANETE) == Planete::PLANETE_FERAL )
        probaKhorne += 0.8;
    double probaTzeentch = 0.15; // moins courant que Khorne sauf chez les psykers (et les éduqués ??)
    if ( humain->GetValeurCarac(Psyker::C_PSYKER) != "" )
        probaTzeentch += 0.8;
    double probaSlaanesh = 0.25;
    double probaNurgle = 0.2;

    double probaTotale = probaKhorne + probaTzeentch + probaSlaanesh + probaNurgle;
    double val = Aleatoire::GetAl()->Entre0Et1() * probaTotale;
    if ( val < probaKhorne) {
        dieu.first = SecteChaos::KHORNE;
        dieu.second = ":/images/organisations/Khorne.png";
    } if ( val < probaKhorne + probaTzeentch) {
        dieu.first = SecteChaos::TZEENTCH;
        dieu.second = ":/images/organisations/Tzeentch.png";
    } if ( val < probaKhorne + probaTzeentch + probaSlaanesh) {
        dieu.first = SecteChaos::SLAANESH;
        dieu.second = ":/images/organisations/Slaanesh.png";
    } if ( val < probaKhorne + probaTzeentch + probaSlaanesh + probaNurgle) {
        dieu.first = SecteChaos::NURGLE;
        dieu.second = ":/images/organisations/Nurgle.png";
    }

    return dieu;
}
