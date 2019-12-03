#include "genviehumain.h"
#include "imperium.h"
#include "../destinLib/gestionnairecarac.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/perso.h"
#include "../destinLib/execeffet.h"
#include "../destinLib/lancerde.h"
#include "../destinLib/setcarac.h"
#include "../destinLib/choix.h"
#include "types_planete/planet.h"
#include "humain.h"
#include "metier.h"
#include "pbsante.h"
#include "identite.h"
#include "voyage.h"
#include "factions/administratum.h"
#include "factions/inquisition.h"
#include "factions/spacemarine.h"
#include "types_planete/monderuche.h"
#include "socio_eco/classesociale.h"
#include "actions/combat.h"
#include "naissance.h"
#include "chaos/sectechaos.h"
#include "jourapresjour.h"
#include "factions/arbites.h"

QString GenVieHumain::AGE = "Age";
QString GenVieHumain::C_LIBERTE = "Liberté";

GenVieHumain::GenVieHumain():GenHistoire ("Vive l'Imperium") {}

GenVieHumain* GenVieHumain::GetGenVieHumain()
{
    return static_cast<GenVieHumain*>(ME);
}

Hist* GenVieHumain::GenererHistoire()
{
    GenererDataUnivers();

    GenererPersos();

    //GenererFonctionsCallback();

    GenererEvtsAccueil();

    GenererCaracs();

    GenererPrincipalSelectionneurDEffet();

    m_HistoireGeneree->m_ModeDeroulement = ModeDeroulement::Automatique;
    m_HistoireGeneree->m_MsDureeDefilement = GenVieHumain::CHRONO;

    return m_HistoireGeneree;
}

void GenVieHumain::GenererDataUnivers()
{
    Planete::ConstruireToutePlanetes();
    DivisionAdministratum::GenererDivisions();
    Ordo::GenererOrdos();
    SpaceMarine::GenererChapitres();
}

void GenVieHumain::GenererPersos()
{
    QString nom = Identite::CreerPatronyme();
    Humain* perso = new Humain(nom);
    perso->InitialiserPerso();
    IPerso::AjouterPersoJouable(perso);
}

void GenVieHumain::GenererCaracs()
{
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Planete::C_PLANETE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Metier::C_METIER);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(GenVieHumain::AGE, 180); // début à 15 ans (180)
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Administratum::C_DIVISION);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Administratum::RANG);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Inquisition::C_ORDO);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(ClasseSociale::C_CLASSE_SOCIALE);

    // temp test :
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Voyage::REAFFECTATION_PLANETE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Voyage::DESTINATION_PLANETE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Voyage::VOYAGE_WARP);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Combat::C_FORCE_COMBAT);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(SecteChaos::C_SECTE_CHAOS);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(SecteChaos::C_DIEU);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(GenVieHumain::C_LIBERTE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Planete::C_TYPE_PLANETE);
}

void GenVieHumain::GenererEvtsAccueil()
{
    this->AjouterEvt("Debut", "Génération du perso par les choix");
    Effet* effet1 = AjouterEffetNarration("", "");
    Naissance::GenererEffetNaissance(effet1);

    AjouterEffetGoToEvt("PrincipalSelecteur", "finNaissance");
}

void GenVieHumain::GenererEvtsDeBase(QVector<NoeudProbable*> &noeuds)
{
    Evt* evtRien = AjouterEvt("evtRien");
    Effet* effetRien = AjouterEffetNarration("Il ne se passe rien. => à régénérer");
    effetRien = TransformerEffetEnEffetMoisDeVie(effetRien);
    effetRien->m_CallbackDisplay = [] {
        Phrase phrase = JourApresJour::ExtrairePhrase();
        ExecHistoire::GetEffetActuel()->m_Texte = phrase.m_Texte;
        ExecHistoire::GetEffetActuel()->m_ImgPath = phrase.m_CheminImg;
        ExecHistoire::GetExecEffetActuel()->ChargerImage(phrase.m_CheminImg);
    };
    NoeudProbable* noeudEvtRien = new NoeudProbable(
                evtRien,
                new Condition(1, p_Relative));
    noeuds.push_back(noeudEvtRien);

    Metier::GenererNoeudsSelectionMetier(m_GenerateurEvt, noeuds);
    PbSante::GenererNoeudsSelectionPbSante(m_GenerateurEvt, noeuds);
    Voyage::GenererNoeudsVoyage(m_GenerateurEvt, noeuds);
    Administratum::GenererNoeudsAdministratum(m_GenerateurEvt, noeuds);
    Inquisition::GenererNoeudsInquisition(m_GenerateurEvt, noeuds);
    MondeRuche::GenererNoeudsMondeRuche(m_GenerateurEvt, noeuds);
    ClasseSociale::GenererNoeudsClasseSociale(m_GenerateurEvt, noeuds);
    SecteChaos::GenererNoeudsSecteChaos(m_GenerateurEvt, noeuds);
    Arbites::GenererNoeudsArbites(m_GenerateurEvt, noeuds);

    Evt* evtFinVie = AjouterEvt("evtFinVie");
    Effet* effetFinVie = AjouterEffetNarration("Cette vie est terminée...");
    effetFinVie->m_ChangeurModeDeroulement = ModeDeroulement::Fini;
    Condition* condMort = new Condition(0, p_Pure);
    PbSante::AjouterModifProbaSiMort(condMort, 1.0);
    noeuds.push_back( new NoeudProbable(
                           evtFinVie,
                           condMort));
}

Effet* GenVieHumain::TransformerEffetEnEffetMoisDeVie(Effet* effet)
{
    // ne se déclenche que si le personnage est encore en vie :
    effet->AjouterCondition(PbSante::SANTE, Comparateur::c_Different, PbSante::MORT);
    effet->m_MsChrono = GenVieHumain::CHRONO;
    effet->m_GoToEvtId = "PrincipalSelecteur";
    effet->AjouterAjouteurACarac(GenVieHumain::AGE, 1);
    return effet;
}

QString GenVieHumain::EFFET_SELECTEUR_ID = "effetSelecteur";
QString GenVieHumain::EVT_SELECTEUR_ID = "PrincipalSelecteur";
Evt* GenVieHumain::EVT_SELECTEUR = nullptr;

void GenVieHumain::GenererPrincipalSelectionneurDEffet()
{
    GenVieHumain::EVT_SELECTEUR = this->AjouterEvt(GenVieHumain::EVT_SELECTEUR_ID, "Principal sélecteur");
    /*Effet* effetDebut = */AjouterEffetGoToEffet(GenVieHumain::EFFET_SELECTEUR_ID);
    // ce vector doit contenir tous les noeuds de base déclenchant des effets et événements à partir du cours normal de la vie
    // en dehors de lui les sélections de noeuds ne sont qu'à la création du personnage et quand un événement particulier est en cours d'exécution
    // à sa fin on doit avoir un goto qui ramène à cet événement/effet "sélecteur"
    QVector<NoeudProbable*> tousLesNoeudsDeBase;
    GenererEvtsDeBase(tousLesNoeudsDeBase);

    Effet* effetSelecteur = m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                tousLesNoeudsDeBase, GenVieHumain::EFFET_SELECTEUR_ID, "", GenVieHumain::EVT_SELECTEUR);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement
}
