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
#include "humain.h"

int SecteChaos::COMPTEUR = 0;

QString SecteChaos::C_SECTE_CHAOS = "Appartient à secte du chaos";
QString SecteChaos::C_DIEU = "Dieu du chaos vénéré";

QString SecteChaos::KHORNE = "Khorne";
QString SecteChaos::TZEENTCH = "Tzeentch";
QString SecteChaos::SLAANESH = "Slaanesh";
QString SecteChaos::NURGLE = "Nurgle";

SecteChaos::SecteChaos()
{
    switch (SecteChaos::COMPTEUR) {
    case 0 : {
        m_Nom = "Entrée dans secte du chaos";
        m_ConditionSelecteurProba = new Condition(0.001, p_Relative);
        m_Description = "Tenté par les dieux noirs, vous rejoignez une secte du chaos.";
        //Inquisition::AjouterModifProbaSiInquisiteur(m_Condition, 0.1);
        m_ModificateursCaracs[SecteChaos::C_SECTE_CHAOS] = "1";
        // techniquement on pourra faire une fonction spéciale qui affecte un dieu selon le perso en question mais en attendant :
        m_CallbackDisplay = [this] {
            int val = Aleatoire::GetAl()->EntierInferieurA(4);
            QString dieu = "";
            switch(val) {
            case 0 :
                dieu = SecteChaos::KHORNE;
                m_Image = ":/images/organisations/Khorne.png";
                break;
            case 1 :
                dieu = SecteChaos::TZEENTCH;
                m_Image = ":/images/organisations/Tzeentch.png";
                break;
            case 2 :
                dieu = SecteChaos::SLAANESH;
                m_Image = ":/images/organisations/Slaanesh.png";
                break;
            case 3 :
                dieu = SecteChaos::NURGLE;
                m_Image = ":/images/organisations/Nurgle.png";
                break;
            }
            Humain::GetHumainJoue()->SetValeurACaracId(SecteChaos::C_DIEU, dieu);
        };

    }break;
    }

    SecteChaos::COMPTEUR++;


}


Effet* SecteChaos::GenererEffet(GenEvt* genEvt)
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


void SecteChaos::GenererNoeudsSecteChaos(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    SecteChaos* evt = new SecteChaos();
    while ( evt->m_Nom != "") {

        Effet* effet = evt->GenererEffet(genEvt);

        Condition* cond = evt->m_ConditionSelecteurProba;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new SecteChaos();
    }
}


