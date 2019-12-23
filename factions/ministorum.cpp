#include "ministorum.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "../types_planete/planet.h"
#include "warp/voyage.h"
#include "metier.h"
#include "../destinLib/effet.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/execeffet.h"
#include "socio_eco/economieevt.h"
#include "humain.h"
#include "texte/jourapresjour.h"

// caracs
QString MinistorumEvts::C_FONCTION = "Poste Ministorum";
// valeurs de C_POSTE
QString MinistorumEvts::CONFESSEUR = "Confesseur";
QString MinistorumEvts::CONFESSEUR_ACOLYTE = "Confesseur";

MinistorumEvts::MinistorumEvts(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "Sélection de poste au Ministorum";
        m_ConditionSelecteurProba = new Condition(1.0, p_Relative);
        m_Description = "??? Ministorum";

        // si Ministorum et pas encore affecté :
        m_Conditions.push_back( MinistorumEvts::AjouterConditionSiMinistorum());
        m_Conditions.push_back(new Condition(MinistorumEvts::C_FONCTION,
                                             "", Comparateur::c_Egal));

        m_CallbackDisplay = [] {
            Humain* humain = Humain::GetHumainJoue();
            AdepteMinistorum* adepteMinistorum = new AdepteMinistorum();
            humain->SetValeurACaracId(MinistorumEvts::C_FONCTION, adepteMinistorum->m_Fonction);

            QString texte = "L'Adeptus Ministorum vous a affecté votre tâche sacrée. Vous êtes maintenant " +
                    adepteMinistorum->m_Fonction + ". " +
                    adepteMinistorum->m_Description;

            ExecHistoire::GetExecEffetActuel()->GetEffet()->m_Texte = texte;
            if ( adepteMinistorum->m_Image != "") {
                ExecHistoire::GetEffetActuel()->m_ImgPath = adepteMinistorum->m_Image;
                if ( ExecHistoire::GetExecEffetActuel() != nullptr) {
                    ExecHistoire::GetExecEffetActuel()->ChargerImage(adepteMinistorum->m_Image);
                }
            }
        };

    }break;
    case 1 : {
        m_Nom = "Confesseur affecté à la suite d'un inquisiteur";
        m_ConditionSelecteurProba = new Condition(0.02, p_Relative);
        m_Description = "Votre mérite dans la traque des hérétiques est arrivée aux oreilles de personnes de valeur."
                " Vous êtes recruté par la sainte Inquisition pour devenir l'acolyte gardien de al foi de sa suite.";

        // si Ministorum et pas encore affecté :
        m_Conditions.push_back( MinistorumEvts::AjouterConditionSiMinistorum());
        m_Conditions.push_back( EconomieEvt::AjouterConditionSiNiveauEconomiqueSuperieurA(8));
        m_Conditions.push_back(new Condition(MinistorumEvts::C_FONCTION,
                                             MinistorumEvts::CONFESSEUR, Comparateur::c_Egal));

        // remise à 0 du niveau de réputation lors d'un changement de métier
        m_ModificateursCaracs[MinistorumEvts::C_FONCTION] = MinistorumEvts::CONFESSEUR_ACOLYTE;
        m_ModificateursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = "0";

    }break;
    }
}


void MinistorumEvts::RafraichirPhrasesDeLaFoi(QString /*typePlanete*/, QString /*classeSociale*/, QString metier)
{
    Humain* humain = Humain::GetHumainJoue();
    QString fonction = humain->GetValeurCarac(MinistorumEvts::C_FONCTION);
    if ( metier == Metier::ADEPTUS_MINISTORUM)
    {
        if ( fonction == MinistorumEvts::CONFESSEUR)
        {
            JourApresJour::PHRASES.push_back(Phrase(
                "Un peuvre diable mutant s'est confessé à vous. Nul doute que l'empereur l'accueillera en sa sainte présence après son immolation.",
                ":/images/metier/Confesseur.jpg"));
        }
    }
}

Condition* MinistorumEvts::AjouterConditionSiMinistorum()
{
    return new Condition(Metier::C_METIER, Metier::ADEPTUS_MINISTORUM, Comparateur::c_Egal);
}

void AdepteMinistorum::DeterminerAffectation()
{
    DeterminerAffectationFonction();
    DeterminerImage();
}

void AdepteMinistorum::DeterminerAffectationFonction()
{
    // fait à la va vite mais à terme devra dépendre de paramètres comme la classe sociale
    // (un confesseur ne peut pas venir de la classe pauvre ou misérable sans mérite particulier)
    m_Fonction = MinistorumEvts::CONFESSEUR;
    m_Description = "Vous êtes un individu passionné dont les harangues peuvent pousser un peuple à la révolte contre un seigneur "
            "hérétique, ou persuader une armée de déposer les armes pour implorer la pitié de l'Empereur "
            "(qui est rapide et sanglante).";
}

void AdepteMinistorum::DeterminerImage()
{
    if ( m_Fonction == MinistorumEvts::CONFESSEUR)
    {
        m_Image = ":/images/metier/Confesseur.jpg";
    }
}
