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

QString SecteChaos::C_SECTE_CHAOS = "Appartient à secte du chaos";
QString SecteChaos::C_DIEU = "Dieu du chaos vénéré";

QString SecteChaos::KHORNE = "Khorne";
QString SecteChaos::TZEENTCH = "Tzeentch";
QString SecteChaos::SLAANESH = "Slaanesh";
QString SecteChaos::NURGLE = "Nurgle";

SecteChaos::SecteChaos(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "Entrée dans secte du chaos";
        m_ConditionSelecteurProba = new Condition(0.001, p_Relative);
        m_Description = "Tenté par les dieux noirs, vous rejoignez une secte du chaos.";
        //Inquisition::AjouterModifProbaSiInquisiteur(m_Condition, 0.1);
        m_ModificateursCaracs[SecteChaos::C_SECTE_CHAOS] = "1";
        m_CallbackDisplay = [this] {
            QPair<QString, QString> dieu = SecteChaos::DeterminerDieuVenere();
            ExecHistoire::GetExecEffetActuel()->ChargerImage(dieu.second);
            Humain::GetHumainJoue()->SetValeurACaracId(SecteChaos::C_DIEU, dieu.first);
        };

    }break;
    }
}


QPair<QString, QString> SecteChaos::DeterminerDieuVenere()
{
    QPair<QString, QString> dieu;
    Humain* humain = Humain::GetHumainJoue();
    double probaKhorne = 0.25;
    if ( humain->GetValeurCarac(Planete::C_TYPE_PLANETE) == Planete::PLANETE_FERAL )
        probaKhorne += 0.8;
    double probaTzeentch = 0.25;
    double probaSlaanesh = 0.25;
    double probaNurgle = 0.25;

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
