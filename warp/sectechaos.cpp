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
#include "texte/jourapresjour.h"
#include "socio_eco/economieevt.h"

QString SecteChaos::C_SECTE_CHAOS = "Appartient à secte du chaos";
QString SecteChaos::C_MUTATIONS = "Mutations";
QString SecteChaos::C_INFLUENCE_CHAOS = "Influence du chaos";
QString SecteChaos::C_DETECTION_SECTE = "Détection de la secte";
QString SecteChaos::C_PUISSANCE_SECTE = "Puissance de la secte";
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
        m_ConditionSelecteurProba = new Condition(0.05 + tmpTestVal, p_Relative);
        m_Description = "Tenté par les dieux noirs, vous rejoignez une secte du chaos.";
        m_Image = ":/images/chaos/Chaos_Cultists2.jpg";
        m_Conditions.push_back(SecteChaos::AjouterConditionSiInfluenceChaosSuperieurA(5));
        m_ModificateursCaracs[SecteChaos::C_SECTE_CHAOS] = "1";
        m_Conditions.push_back(SecteChaos::AjouterConditionSiPasSecte());
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
        m_ModificateursCaracs[Metier::C_METIER] = Metier::INEMPLOYABLE;

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
                "Un de vos amis vous confie aller souvent à des réunions secrètes mystiques.",
                "Une légère mutation apparaît sur votre corps. La marque du chaos."
            };
            int num = Aleatoire::GetAl()->EntierInferieurA(textes.length());
            ExecHistoire::GetEffetActuel()->m_Texte = textes[num];
        };

    }break;
    case 3 : {
        m_Nom = "Détection de la secte";
        m_ConditionSelecteurProba = new Condition(0.01 + tmpTestVal, p_Relative);
        SecteChaos::AjouterModificateurProbaSiPuissanceSecteSuperieurA(m_ConditionSelecteurProba, 5, 0.02);
        m_Description = "La puissance de votre secte et son influence attirent l'attention des autorités.";
        m_IncrementeursCaracs[SecteChaos::C_DETECTION_SECTE] = 1;
        m_Conditions.push_back(SecteChaos::AjouterConditionSiSecte());

    }break;
    case 4 : {
        m_Nom = "Gain de puissance de la secte";
        m_ConditionSelecteurProba = new Condition(0.01 + tmpTestVal, p_Relative);
        m_Description = "La puissance de votre secte grandit.";
        m_IncrementeursCaracs[SecteChaos::C_PUISSANCE_SECTE] = 1;
        m_Conditions.push_back(SecteChaos::AjouterConditionSiSecte());

    }break;
    case 5 : {
        m_Nom = "Révélation de la secte";
        m_ConditionSelecteurProba = new Condition(0.001 + tmpTestVal, p_Relative);
        SecteChaos::AjouterModificateurProbaSiDetectionSecteSuperieurA(m_ConditionSelecteurProba, 5, 0.02);
        m_Description = "Les autorités ont découvert votre secte et tentent de la détruire. Il va falloir se défendre ! ==> pas fait !";
        m_Conditions.push_back(SecteChaos::AjouterConditionSiSecte());

    }break;
    case 6 : {
        m_Nom = "Travaille mal à cause de la secte";
        m_ConditionSelecteurProba = new Condition(0.01 + tmpTestVal, p_Relative);
        m_Description = "Votre obsession pour les deux noirs affectent votre vie. Votre efficacité au travail diminue fortement.";
        m_Conditions.push_back(SecteChaos::AjouterConditionSiSecte());
        m_Conditions.push_back(Metier::AjouterConditionSiAMetier());
        m_IncrementeursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = -2;
    }break;
    case 7 : {
        m_Nom = "Possession démoniaque";
        m_ConditionSelecteurProba = new Condition(0.01 + tmpTestVal, p_Relative);
        m_Description = "Votre dévotion  au chaos est devenue si forte qu'un démon tente de prendre possession de votre corps pour envahir le plan matériel."
                "===> pas fait";
        m_Conditions.push_back(SecteChaos::AjouterConditionSiInfluenceChaosSuperieurA(20));
    }break;
    case 8 : {
        m_Nom = "Enfant du chaos";
        m_ConditionSelecteurProba = new Condition(0.01 + tmpTestVal, p_Relative);
        m_Description = "Les énergies du chaos ont tellement pris d'emprise sur votre corps que vous mutez en un horrible enfant du chaos décérébré.";
        m_Image = ":/images/chaos/enfant_du_chaos.jpg";
        m_ModificateursCaracs[PbSante::C_SANTE] = PbSante::MORT;
        m_Conditions.push_back(SecteChaos::AjouterConditionSiMutationsSuperieurA(15));
    }break;
    case 9 : {
        m_Nom = "Mutation du chaos";
        m_ConditionSelecteurProba = new Condition(0.001 + tmpTestVal, p_Relative);
        m_ConditionSelecteurProba = SecteChaos::AjouterModificateurProbaSiInfluenceChaosSuperieurA(m_ConditionSelecteurProba, 3, 0.01);
        m_ConditionSelecteurProba = SecteChaos::AjouterModificateurProbaSiInfluenceChaosSuperieurA(m_ConditionSelecteurProba, 8, 0.01);
        m_Description = "Mutation à mettre à jour.";
        m_Image = ":/images/chaos/enfant_du_chaos.jpg";
        m_IncrementeursCaracs[SecteChaos::C_MUTATIONS] = 1;
        m_CallbackDisplay = []{
            QVector<QString> textes = {
                "Un tentacule vous a poussé sur le corps.",
                "Votre peau devient écailleuse en plusieurs points."
            };
            int num = Aleatoire::GetAl()->EntierInferieurA(textes.length());
            ExecHistoire::GetEffetActuel()->m_Texte = textes[num];

        };
    }break;

    }
}

void SecteChaos::RafraichirPhrases()
{
    JourApresJour::PHRASES.push_back(Phrase("Vous recevez des tatouages de la confrérie du chaos."));
    JourApresJour::PHRASES.push_back(Phrase("Les puissances de la ruine vous promettent gloire et pouvoir pour votre obéissance.",
                                            ":/images/chaos/ff086889e09fac6503c6559082ffa50a.jpg"));
    Humain* humain = Humain::GetHumainJoue();
    QString dieu_venere = humain->GetValeurCarac(SecteChaos::C_DIEU);
    if ( dieu_venere == SecteChaos::KHORNE)
    {
        JourApresJour::PHRASES.push_back(
                    Phrase("C'est le jour de la ronde du massacre, le sang va couler à flot.",
                          ":/images/chaos/Sanguinary_Cultist.png"));
    }
}

Condition* SecteChaos::AjouterModificateurProbaSiPuissanceSecteSuperieurA(Condition* condProba, int nivInfluence, double modifProba)
{
    condProba->AjouterModifProba(modifProba,
        {         new Condition(SecteChaos::C_PUISSANCE_SECTE, QString::number(nivInfluence), Comparateur::c_Superieur)        });
    return condProba;
}

Condition* SecteChaos::AjouterModificateurProbaSiInfluenceChaosSuperieurA(Condition* condProba, int nivInfluence, double modifProba)
{
    condProba->AjouterModifProba(modifProba,
        {         new Condition(SecteChaos::C_INFLUENCE_CHAOS, QString::number(nivInfluence), Comparateur::c_Superieur)        });
    return condProba;
}

Condition* SecteChaos::AjouterModificateurProbaSiDetectionSecteSuperieurA(Condition* condProba, int nivInfluence, double modifProba)
{
    condProba->AjouterModifProba(modifProba,
        {         new Condition(SecteChaos::C_DETECTION_SECTE, QString::number(nivInfluence), Comparateur::c_Superieur)        });
    return condProba;
}

Condition* SecteChaos::AjouterConditionSiInfluenceChaosSuperieurA(int nivInfluence)
{
    return new Condition(SecteChaos::C_INFLUENCE_CHAOS, QString::number(nivInfluence), Comparateur::c_Superieur);
}

Condition* SecteChaos::AjouterConditionSiMutationsSuperieurA(int nivMutation)
{
    return new Condition(SecteChaos::C_MUTATIONS, QString::number(nivMutation), Comparateur::c_Superieur);
}

Condition* SecteChaos::AjouterConditionSiLepreDeNurgle()
{    return new Condition(PbSante::C_SANTE, SecteChaos::LEPRE_DE_NURGLE, Comparateur::c_Egal);}
Condition* SecteChaos::AjouterConditionSiSecte()
{    return new Condition(SecteChaos::C_SECTE_CHAOS, "1", Comparateur::c_Egal);}
Condition* SecteChaos::AjouterConditionSiPasSecte()
{    return new Condition(SecteChaos::C_SECTE_CHAOS, "1", Comparateur::c_Different);}

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
    } else if ( val < probaKhorne + probaTzeentch) {
        dieu.first = SecteChaos::TZEENTCH;
        dieu.second = ":/images/organisations/Tzeentch.png";
    } else if ( val < probaKhorne + probaTzeentch + probaSlaanesh) {
        dieu.first = SecteChaos::SLAANESH;
        dieu.second = ":/images/organisations/Slaanesh.png";
    } else if ( val < probaKhorne + probaTzeentch + probaSlaanesh + probaNurgle) {
        dieu.first = SecteChaos::NURGLE;
        dieu.second = ":/images/organisations/Nurgle.png";
    }

    return dieu;
}
