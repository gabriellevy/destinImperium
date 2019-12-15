#include "marineimperiale.h"
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

// caracs
QString MarineImperiale::C_FLOTTE = "Flotte";
QString MarineImperiale::C_FONCTION = "Fonction";
// valeurs C_FONCTION :
QString MarineImperiale::OPERATEUR = "Opérateur de vaisseau";
// valeurs de C_FLOTTE
QString MarineImperiale::AGRIPINAA = "Agripinaa";
QString MarineImperiale::ARMAGEDDON = "Armageddon";
QString MarineImperiale::BAKKA     = "Bakka";
QString MarineImperiale::CADIA     = "Cadia";
QString MarineImperiale::CALIXIS   = "Calixis";
QString MarineImperiale::CORONA    = "Corona";
QString MarineImperiale::CORRIBRA  = "Corribra";
QString MarineImperiale::GOTHIC    = "Gothic";
QString MarineImperiale::KORONUS   = "Koronus";
QString MarineImperiale::ORPHEUS   = "Orpheus";
QString MarineImperiale::SCARUS    = "Scarus";
QString MarineImperiale::SOLAR     = "Solar";

QList<QString> MarineImperiale::FLOTTES     = {
    MarineImperiale::AGRIPINAA,
    MarineImperiale::ARMAGEDDON,
    MarineImperiale::BAKKA,
    MarineImperiale::CADIA,
    MarineImperiale::CALIXIS,
    MarineImperiale::CORONA,
    MarineImperiale::CORRIBRA,
    MarineImperiale::GOTHIC,
    MarineImperiale::KORONUS,
    MarineImperiale::ORPHEUS,
    MarineImperiale::SCARUS,
    MarineImperiale::SOLAR
    };


QString MarineImperiale::GetFlotteAlmatoire()
{
    return MarineImperiale::FLOTTES[Aleatoire::GetAl()->EntierInferieurA(MarineImperiale::FLOTTES.length())];
}

MarineImperiale::MarineImperiale(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = MarineImperiale::C_FONCTION;
        m_ConditionSelecteurProba = new Condition(1.0, p_Relative);
        m_Description = "???";
        //m_ModificateursCaracs[SecteChaos::C_SECTE_CHAOS] = "1";
        m_CallbackDisplay = [] {
            MarinImperial* soldat = new MarinImperial();

            Humain::GetHumainJoue()->SetValeurACaracId(MarineImperiale::C_FLOTTE, soldat->m_Flotte);
            Humain::GetHumainJoue()->SetValeurACaracId(MarineImperiale::C_FONCTION, soldat->m_Fonction);

            QString texte = "Vous êtes affecté à la flotte " + soldat->m_Flotte + " comme " + soldat->m_Fonction + ".";

            ExecHistoire::GetExecEffetActuel()->GetEffet()->m_Texte = texte;
            if ( soldat->m_Image != "") {
                ExecHistoire::GetEffetActuel()->m_ImgPath = soldat->m_Image;
                //qDebug() << "this->m_Image : " << this->m_Image << endl;
                if ( ExecHistoire::GetExecEffetActuel() != nullptr) {
                    ExecHistoire::GetExecEffetActuel()->ChargerImage(soldat->m_Image);
                }
            }
        };

        // si marin impérial et pas encore affecté :
        m_Conditions = MarineImperiale::AjouterConditionSiMarineImperiale(m_Conditions);
        m_Conditions.push_back(new Condition(MarineImperiale::C_FONCTION,
                                             "", Comparateur::c_Egal));

    }break;
    }
}

QList<Condition*> MarineImperiale::AjouterConditionSiMarineImperiale(QList<Condition*> conditions)
{
    conditions.push_back(new Condition(Metier::C_METIER,
                        Metier::MARIN_IMPERIAL, Comparateur::c_Egal));
    return conditions;
}

void MarinImperial::DeterminerAffectation()
{
    m_Flotte = DeterminerAffectationFlotte();
    m_Fonction = DeterminerAffectationFonction();
    m_Image = DeterminerImage();
}

QString MarinImperial::DeterminerImage()
{
    if ( m_Flotte == MarineImperiale::AGRIPINAA) {
        m_Image = ":/images/vaisseaux/Agripinaa.jpg";
    }
    else if ( m_Flotte == MarineImperiale::ARMAGEDDON) {
        m_Image = ":/images/vaisseaux/Armageddon.jpg";
    }
    else if ( m_Flotte == MarineImperiale::BAKKA) {
        m_Image = ":/images/vaisseaux/Bakka.jpg";
    }
    else if ( m_Flotte == MarineImperiale::CADIA) {
        m_Image = ":/images/vaisseaux/Cadia.jpg";
    }
    else if ( m_Flotte == MarineImperiale::CALIXIS) {
        m_Image = ":/images/vaisseaux/Calixis.jpg";
    }
    else if ( m_Flotte == MarineImperiale::CORONA) {
        m_Image = ":/images/vaisseaux/Corona.jpg";
    }
    else if ( m_Flotte == MarineImperiale::CORRIBRA) {
        m_Image = ":/images/vaisseaux/Corribra.jpg";
    }
    else if ( m_Flotte == MarineImperiale::GOTHIC) {
        m_Image = ":/images/vaisseaux/Gothic.jpg";
    }
    else if ( m_Flotte == MarineImperiale::KORONUS) {
        m_Image = ":/images/vaisseaux/Koronus.jpg";
    }
    else if ( m_Flotte == MarineImperiale::ORPHEUS) {
        m_Image = ":/images/vaisseaux/Orpheus.jpg";
    }
    else if ( m_Flotte == MarineImperiale::SCARUS) {
        m_Image = ":/images/vaisseaux/Scarus.jpg";
    }
    else if ( m_Flotte == MarineImperiale::SOLAR) {
        m_Image = ":/images/vaisseaux/Solar.jpg";
    }

    // défaut :
    m_Image = ":/images/vaisseaux/Solar.jpg";

    return m_Image;
}

QString MarinImperial::DeterminerAffectationFlotte()
{
    return MarineImperiale::GetFlotteAlmatoire();
}

QString MarinImperial::DeterminerAffectationFonction()
{
    // défaut :
    m_Fonction = MarineImperiale::OPERATEUR;

    return m_Fonction;
}
