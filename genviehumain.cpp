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

QString GenVieHumain::PLANETE = "Planète";
QString GenVieHumain::TYPE_PLANETE = "Type de planète";
QString GenVieHumain::AGE = "Age";
QString GenVieHumain::METIER = "Métier";

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
    Carac* caracPlanete = new Carac(GenVieHumain::PLANETE, GenVieHumain::PLANETE,"",
                                    "", GenVieHumain::PLANETE, MODE_AFFICHAGE::ma_Texte, nullptr);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(caracPlanete);

    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(
                new Carac(GenVieHumain::METIER, GenVieHumain::METIER,"",
                   "", GenVieHumain::METIER, MODE_AFFICHAGE::ma_Texte, nullptr));
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(GenVieHumain::AGE, 180); // début à 15 ans (180)
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(
                new Carac(Administratum::C_DIVISION, Administratum::C_DIVISION,"",
                   "", Administratum::C_DIVISION, MODE_AFFICHAGE::ma_Texte, nullptr));
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(
                new Carac(Administratum::RANG, Administratum::RANG,"",
                   "", Administratum::RANG, MODE_AFFICHAGE::ma_Texte, nullptr));
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(
                new Carac(Inquisition::C_ORDO, Inquisition::C_ORDO,"",
                   "", Inquisition::C_ORDO, MODE_AFFICHAGE::ma_Texte, nullptr));

    // temp test :
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(
                new Carac(Voyage::REAFFECTATION_PLANETE, Voyage::REAFFECTATION_PLANETE,"",
                   "", Voyage::REAFFECTATION_PLANETE, MODE_AFFICHAGE::ma_Texte, nullptr));
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(
                new Carac(Voyage::DESTINATION_PLANETE, Voyage::DESTINATION_PLANETE,"",
                   "", Voyage::DESTINATION_PLANETE, MODE_AFFICHAGE::ma_Texte, nullptr));
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(
                new Carac(Voyage::VOYAGE_WARP, Voyage::VOYAGE_WARP,"",
                   "", Voyage::VOYAGE_WARP, MODE_AFFICHAGE::ma_Texte, nullptr));
}

void GenVieHumain::GenererEvtsAccueil()
{
    this->AjouterEvt("Debut", "Génération du perso par les choix");
    Effet* effet1 = AjouterEffetNarration("", "");
    effet1->m_GoToEffetId = "effetSelectionPlanete";

    QVector<NoeudProbable*> noeudsDestination = Planete::ConstruireToutePlanetes(m_GenerateurEvt, "finNaissance"); // doit se faire ici car contient la génération d'effets associés
    Effet* effetSelectionPlanete = m_GenerateurEvt->AjouterEffetSelecteurDEvt(noeudsDestination, "effetSelectionPlanete");
    effetSelectionPlanete->m_MsChrono = 1;

    AjouterEffetGoToEvt("PrincipalSelecteur", "finNaissance");
}

void GenVieHumain::GenererEvtsDeBase(QVector<NoeudProbable*> &noeuds)
{
    Evt* evtRien = AjouterEvt("evtRien");
    Effet* effetRien = AjouterEffetNarration("Il ne se passe rien.");
    effetRien = TransformerEffetEnEffetMoisDeVie(effetRien);
    NoeudProbable* noeudEvtRien = new NoeudProbable(
                evtRien,
                new Condition(1, p_Relative));
    noeuds.push_back(noeudEvtRien);

    Evt* evtRien2 = AjouterEvt("evtRien2");
    Effet* effetRien2 = AjouterEffetNarration("Encore un mois tranquille.");
    effetRien2 = TransformerEffetEnEffetMoisDeVie(effetRien2);
    noeuds.push_back( new NoeudProbable(
                           evtRien2,
                           new Condition(1, p_Relative)));

    Metier::GenererNoeudsSelectionMetier(m_GenerateurEvt, noeuds);
    PbSante::GenererNoeudsSelectionPbSante(m_GenerateurEvt, noeuds);
    Voyage::GenererNoeudsVoyage(m_GenerateurEvt, noeuds);
    Administratum::GenererNoeudsAdministratum(m_GenerateurEvt, noeuds);
    Inquisition::GenererNoeudsInquisition(m_GenerateurEvt, noeuds);

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
