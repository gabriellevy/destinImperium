#include "psyker.h"
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
#include "humanite/pbsante.h"
#include "socio_eco/crime.h"
#include "humain.h"
#include "../destinLib/execeffet.h"
#include "warp/sectechaos.h"
#include "texte/jourapresjour.h"


// caracs :
QString Psyker::C_PSYKER = "Psyker";
QString Psyker::C_RAPPORT_AU_GVT = "Rapport au gouvernement";
QString Psyker::C_NIVEAU_PSYKER = "Niveau de psyker";
//valeurs de C_PSYKER
QString Psyker::POTENTIEL_PSY = "Potentiel psy";
QString Psyker::PSYKER_CONFIRME = "Psyker confirmé";
QString Psyker::SANS_AME = "Sans âme";
//valeurs de C_RAPPORT_AU_GVT
QString Psyker::IDENTIFIE = "Identifié";
QString Psyker::CHARGE_DANS_VAISSEAU_NOIR = "Chargé dans un vaisseau noir";
QString Psyker::DIGNE_DE_SERVIR = "Digne de servir";
QString Psyker::SACRIFIABLE = "Sacrifiable";// valeurs de C_NIVEAU_PSYKER :
QString Psyker::OMICRON = "Omicron";
QString Psyker::XI = "Xi";
QString Psyker::NU = "Nu";
QString Psyker::MU = "Mu";
QString Psyker::LAMBDA = "Lambda";
QString Psyker::KAPPA = "Kappa";
QString Psyker::IOTA = "Iota";
QString Psyker::THETA = "Theta";
QString Psyker::ETA = "Eta";
QString Psyker::ALPHA_PLUS = "Alpha Plus";

Psyker::Psyker(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmp_Modificateur = 0.0; //pour les tests (doit être à 0 en prod)
    switch (indexEvt) {
    case 0 : {
        m_Nom = Psyker::POTENTIEL_PSY + " élimination";
        m_ConditionSelecteurProba = new Condition(0.002 - tmp_Modificateur, p_Relative);
        m_Description = "Vous êtes identifié par l'Ordo Hereticus comme un dangereux psyker et êtes emprisonné.";
        m_Image = ":/images/inquisition/Inquisitor_Ordo_Hereticus.png";
        m_Conditions.push_back(Psyker::AjouterConditionSiPsyker());
        m_ModificateursCaracs[GenVieHumain::C_LIBERTE] = Crime::CAPTURE_ORDO_HERETICUS;
    }break;
    case 1 : {
        m_Nom = Psyker::IDENTIFIE;
        m_ConditionSelecteurProba = new Condition(0.03 + tmp_Modificateur, p_Relative);
        m_Description = "Identifié comme psyker par les agents du gouverneur vous êtes enregistré et répertorié. "
                "Vous êtes néanmoins remis en liberté ensuite.";
        m_Conditions.push_back(Psyker::AjouterConditionSiPsyker());
        m_Conditions.push_back(Psyker::AjouterConditionSiPsykerPasIdentifie());
        m_ModificateursCaracs[Psyker::C_RAPPORT_AU_GVT] = Psyker::IDENTIFIE;
    }break;
    case 2 : {
        m_Nom = Psyker::CHARGE_DANS_VAISSEAU_NOIR;
        m_ConditionSelecteurProba = new Condition(0.02 + tmp_Modificateur, p_Relative);
        m_Description = "Un vaisseau noir de l'inquisition a aterri sur la planète. Sa mission est de capturer tous les psykers de la planète pour les emmener sur Terre."
                "Les forces du gouvernement qui vous avaient fiché vous livrent à lui sans la moindre hésitation.";
        m_Image = ":/images/vaisseaux/InquisitorialBlackShip.png";
        m_Conditions.push_back(Psyker::AjouterConditionSiPsyker());
        m_Conditions.push_back(new Condition(Psyker::C_RAPPORT_AU_GVT, Psyker::IDENTIFIE, Comparateur::c_Egal));
        m_ModificateursCaracs[Psyker::C_RAPPORT_AU_GVT] = Psyker::CHARGE_DANS_VAISSEAU_NOIR;
        m_ModificateursCaracs[Voyage::C_DESTINATION_PLANETE] = Planete::TERRE;
        m_ModificateursCaracs[GenVieHumain::C_LIBERTE] = Psyker::CHARGE_DANS_VAISSEAU_NOIR;
        m_ModificateursCaracs[Metier::C_METIER] = "";
    }break;
    case 3 : {
        m_Nom = "Traitement des psykers sur les vaisseaux noirs à Terra";
        m_ConditionSelecteurProba = new Condition(0.2 + tmp_Modificateur, p_Relative);
        m_Description = "à mettre à jour";
        m_Image = ":/images/vaisseaux/InquisitorialBlackShip.png";
        m_Conditions.push_back(Psyker::AjouterConditionSiPsyker());
        m_Conditions.push_back(new Condition(Psyker::C_RAPPORT_AU_GVT, Psyker::CHARGE_DANS_VAISSEAU_NOIR, Comparateur::c_Egal));
        m_Conditions.push_back(new Condition(Planete::C_PLANETE, Planete::TERRE, Comparateur::c_Egal));
        m_CallbackDisplay = [] {
            ExecEffet* effetActuel = Univers::ME->GetExecHistoire()->GetExecEffetActuel();
            Humain* humain = Humain::GetHumainJoue();
            QString texte = "à remplacer 2";
            int influenceChaos = humain->GetValeurCaracAsInt(SecteChaos::C_INFLUENCE_CHAOS);
            QString criminel = humain->GetValeurCarac(Crime::C_CRIMINEL);
            int age = humain->GetValeurCaracAsInt(GenVieHumain::AGE);

            double probaSacrifice = 0.1;
            if ( criminel != "")
                probaSacrifice += 0.3;
            if ( age > 30*12)
                probaSacrifice += 0.2;

            if ( Aleatoire::GetAl()->Entre0Et1() < probaSacrifice || influenceChaos > 0) {
                texte = "Vous n'êtes pas jugé digne de rejoindre la Scholia Psykana. Néanmoins un grand honneur vous attend."
                        "Vous allez être intégré à l'adeptus astronomica pour soutenir l'empereur et l'aider dans sa mission sacrée de mener "
                        "l'imperium et de garder allumée la balise galactique de l'astronomicon.";

                effetActuel->ChargerImage( ":/images/organisations/Adeptus_Astronomica_Icon_update.jpg");
                IPerso::GetPersoCourant()->SetValeurACaracId(Metier::C_METIER, Metier::ASTRONOMICA);
                IPerso::GetPersoCourant()->SetValeurACaracId(Psyker::C_RAPPORT_AU_GVT, Psyker::SACRIFIABLE);
                IPerso::GetPersoCourant()->SetValeurACaracId(GenVieHumain::C_LIBERTE, "");
            } else {
                texte = "Vous êtes jugé digne de rejoindre la Scholista Psykana pour devenir un psyker qui pourra servir l'Imperium.";

                effetActuel->ChargerImage( ":/images/metier/Primaris_Psyker.jpg");
                IPerso::GetPersoCourant()->SetValeurACaracId(Metier::C_METIER, Metier::SCHOLIA_PSYKANA);
                IPerso::GetPersoCourant()->SetValeurACaracId(Psyker::C_RAPPORT_AU_GVT, Psyker::DIGNE_DE_SERVIR);
                IPerso::GetPersoCourant()->SetValeurACaracId(GenVieHumain::C_LIBERTE, "");
            }
            effetActuel->GetEffet()->m_Texte = texte;

        };
    }break;
    }
}


Condition* Psyker::AjouterConditionSiPsyker()
{
    return new Condition(Psyker::C_PSYKER, "", Comparateur::c_Different);
}

Condition* Psyker::AjouterConditionSiPsykerPasIdentifie()
{
    return new Condition(Psyker::C_RAPPORT_AU_GVT, "", Comparateur::c_Egal);
}


Condition* Psyker::AjouterConditionSiNonPsyker()
{
    return new Condition(Psyker::C_PSYKER, "", Comparateur::c_Egal);
}

Condition* Psyker::AjouterModifProbaSiPsyker(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {         new Condition(Psyker::C_PSYKER, "", Comparateur::c_Different)        });
    return cond;
}

Condition* Psyker::AjouterModifProbaSiNonPsyker(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {         new Condition(Psyker::C_PSYKER, "", Comparateur::c_Egal)        });
    return cond;
}

QString Psyker::GetNiveauPsykerNaissance()
{
    double proba = Aleatoire::GetAl()->Entre0Et1();

    if ( proba < 0.0001) {
        return Psyker::SANS_AME;

    } else if ( proba < 0.05) {
        return Psyker::POTENTIEL_PSY;
    }

    // non psyker :
    return "";
}
void Psyker::RafraichirPhrasesPsyker()
{
    Humain* hum = Humain::GetHumainJoue();
    if ( hum->GetValeurCarac(Psyker::C_PSYKER) == Psyker::POTENTIEL_PSY)
    {
        // psyker non maîtrisés :
        JourApresJour::PHRASES.push_back(Phrase(
            "Les statues se mettent à pleurer du sangsur la grande place. Est-ce un miracle de l'empereur ?"));
        JourApresJour::PHRASES.push_back(Phrase(
            "Le sol se couvre de glace sur votre passage. Ce semble être de la sorcellerie. Vient-elle de vous ?"));
        JourApresJour::PHRASES.push_back(Phrase(
            "Vous entedez des murmures fantomatiques. Est-ce que vous devenez fou ?"));
    }
}
