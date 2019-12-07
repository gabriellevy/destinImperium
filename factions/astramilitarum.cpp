#include "astramilitarum.h"
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
#include "humain.h"
#include "../destinLib/execeffet.h"

int AstraMilitarum::COMPTEUR = 0;

// caracs
QString AstraMilitarum::C_FONCTION_ASTRA_MILITARUM = "Fonction dans l'astra Militarum";
QString AstraMilitarum::C_REGIMENT_ASTRA_MILITARUM = "Régiment Astra Militarum";
// valeurs FONCTION_ASTRA_MILITARUM :
QString AstraMilitarum::FANTASSIN = "Fantassin";
// valeurs REGIMENT_ASTRA_MILITARUM :
QString AstraMilitarum::CADIAN = "Troupes de choc de Cadian";
QString AstraMilitarum::LEGIONS_D_ACIER = "Légons d'acier d'Armageddon";

AstraMilitarum::AstraMilitarum()
{
    switch (AstraMilitarum::COMPTEUR) {
    case 0 : {
        m_Nom = "youpi Ministorum";
        m_ConditionSelecteurProba = new Condition(1.0, p_Relative);
        m_Description = "???";
        //m_ModificateursCaracs[SecteChaos::C_SECTE_CHAOS] = "1";
        m_CallbackDisplay = [] {
            SoldatImperial* soldat = new SoldatImperial();

            Humain::GetHumainJoue()->SetValeurACaracId(AstraMilitarum::C_REGIMENT_ASTRA_MILITARUM, soldat->m_Regiment);
            Humain::GetHumainJoue()->SetValeurACaracId(AstraMilitarum::C_FONCTION_ASTRA_MILITARUM, soldat->m_Fonction);

            QString texte = "Vous êtes affecté au régiment " + soldat->m_Regiment + " comme " + soldat->m_Fonction + ".";

            ExecHistoire::GetExecEffetActuel()->GetEffet()->m_Texte = texte;
            if ( soldat->m_Image != "") {
                ExecHistoire::GetEffetActuel()->m_ImgPath = soldat->m_Image;
                //qDebug() << "this->m_Image : " << this->m_Image << endl;
                if ( ExecHistoire::GetExecEffetActuel() != nullptr) {
                    ExecHistoire::GetExecEffetActuel()->ChargerImage(soldat->m_Image);
                }
            }
        };

        // si garde impérial et pas encore affecté :
        m_Conditions = AstraMilitarum::AjouterConditionSiAstraMilitarum(m_Conditions);
        m_Conditions.push_back(new Condition(AstraMilitarum::C_FONCTION_ASTRA_MILITARUM,
                                             "", Comparateur::c_Egal));

    }break;
    }

    AstraMilitarum::COMPTEUR++;
}

QList<Condition*> AstraMilitarum::AjouterConditionSiAstraMilitarum(QList<Condition*> conditions)
{
    conditions.push_back(new Condition(Metier::C_METIER,
                        Metier::GARDE_IMPERIAL, Comparateur::c_Egal));
    return conditions;
}

void SoldatImperial::DeterminerAffectation()
{
    m_Regiment = DeterminerAffectationRegiment();
    m_Fonction = DeterminerAffectationFonction();
    m_Image = DeterminerImage();
}

QString SoldatImperial::DeterminerImage()
{
    if ( m_Regiment == AstraMilitarum::CADIAN) {
        m_Image = ":/images/guerre/Cadian.jpg";
    }
    else if ( m_Regiment == AstraMilitarum::LEGIONS_D_ACIER)
    {
        m_Image = ":/images/guerre/Legion-D-Acier.jpg";
    }

    // défaut :
    m_Image = ":/images/guerre/Cadian.jpg";

    return m_Image;
}

QString SoldatImperial::DeterminerAffectationRegiment()
{
    Planete* planete = Humain::GetHumainJoue()->GetPlanete();

    if ( planete->m_TypePlanete == Planete::PLANETE_FORGE) {
        m_Regiment = AstraMilitarum::LEGIONS_D_ACIER;
    }

    // défaut :
    m_Regiment = AstraMilitarum::CADIAN;

    return m_Regiment;
}

QString SoldatImperial::DeterminerAffectationFonction()
{
    // défaut :
    m_Fonction = AstraMilitarum::FANTASSIN;

    return m_Fonction;
}

Effet* AstraMilitarum::GenererEffet(GenEvt* genEvt)
{
    Effet* effet = genEvt->AjouterEffetNarration(
            m_Description,
            m_Image,
            "evt_monde_ruche_" + m_Nom, GenVieHumain::EVT_SELECTEUR);

    effet->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
    effet = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet);
    effet->m_CallbackDisplay = m_CallbackDisplay;
    effet->m_Conditions = m_Conditions;

    // modificateurs de carac :
    QMapIterator<QString, QString> it(m_ModificateursCaracs);
    while ( it.hasNext()) {
        it.next();
        effet->AjouterChangeurDeCarac(it.key(), it.value());
    }

    return effet;
}

void AstraMilitarum::GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    AstraMilitarum* evt = new AstraMilitarum();
    while ( evt->m_Nom != "") {

        Effet* effet = evt->GenererEffet(genEvt);

        Condition* cond = evt->m_ConditionSelecteurProba;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new AstraMilitarum();
    }
}
