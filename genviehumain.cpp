#include "genviehumain.h"
#include "imperium.h"
#include "../destinLib/gestionnairecarac.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/perso.h"
#include "../destinLib/execeffet.h"
#include "../destinLib/lancerde.h"
#include "../destinLib/setcarac.h"
#include "../destinLib/choix.h"
#include "planet.h"
#include "humain.h"

QString GenVieHumain::PLANETE = "Planète";
QString GenVieHumain::AGE = "Age";

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

    return m_HistoireGeneree;
}

void GenVieHumain::GenererDataUnivers()
{
}

void GenVieHumain::GenererPersos()
{
    Humain* perso = new Humain();
    perso->InitialiserPerso();
    IPerso::AjouterPersoJouable(perso);
}

void GenVieHumain::GenererCaracs()
{
    Carac* caracPlanete = new Carac(GenVieHumain::PLANETE, GenVieHumain::PLANETE,"",
                                    "", GenVieHumain::PLANETE, MODE_AFFICHAGE::ma_Texte, nullptr);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(caracPlanete);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(GenVieHumain::AGE, 0);
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
                new Condition(1));
    noeuds.push_back(noeudEvtRien);

    Evt* evtRien2 = AjouterEvt("evtRien2");
    Effet* effetRien2 = AjouterEffetNarration("Encore un mois tranquille.");
    effetRien2 = TransformerEffetEnEffetMoisDeVie(effetRien2);
    noeuds.push_back(  new NoeudProbable(
                           evtRien2,
                           new Condition(1)));
}

Effet* GenVieHumain::TransformerEffetEnEffetMoisDeVie(Effet* effet)
{
    effet->m_MsChrono = GenVieHumain::CHRONO;
    effet->m_GoToEvtId = "PrincipalSelecteur";
    effet->AjouterAjouteurACarac(GenVieHumain::AGE, 1);
    return effet;
}

void GenVieHumain::GenererPrincipalSelectionneurDEffet()
{
    // ce vector doit contenir tous les noeuds de base déclenchant des effets et événements à partir du cours normal de la vie
    // en dehors de lui les sélections de noeuds ne sont qu'à la création du personnage et quand un événement particulier est en cours d'exécution
    // à sa fin on doit avoir un goto qui ramène à cet événement/effet "sélecteur"
    QVector<NoeudProbable*> tousLesNoeudsDeBase;
    GenererEvtsDeBase(tousLesNoeudsDeBase);

    this->AjouterEvt("PrincipalSelecteur", "Principal sélecteur");
    Effet* effetSelecteur = m_GenerateurEvt->AjouterEffetSelecteurDEvt(tousLesNoeudsDeBase, "effetSelecteur");
    effetSelecteur->m_MsChrono = 1; // passé automatiquement
}
