#include "genviehumain.h"
#include "generateurnoeudsprobables.h"
#include "imperium.h"
#include "../destinLib/gestionnairecarac.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/perso.h"
#include "../destinLib/exec/execeffet.h"
#include "../destinLib/abs/lancerde.h"
#include "../destinLib/abs/setcarac.h"
#include "../destinLib/abs/choix.h"
#include "types_planete/planet.h"
#include "humain.h"
#include "metier.h"
#include "humanite/pbsante.h"
#include "humanite/identite.h"
#include "warp/voyage.h"
#include "factions/administratum.h"
#include "factions/inquisition.h"
#include "factions/spacemarine.h"
#include "types_planete/monderuche.h"
#include "types_planete/mondeforge.h"
#include "socio_eco/classesociale.h"
#include "socio_eco/crime.h"
#include "socio_eco/maison.h"
#include "socio_eco/economieevt.h"
#include "actions/combat.h"
#include "humanite/naissance.h"
#include "warp/sectechaos.h"
#include "warp/psyker.h"
#include "texte/jourapresjour.h"
#include "factions/arbites.h"
#include "factions/assassinorum.h"
#include "factions/ministorum.h"
#include "factions/astramilitarum.h"
#include "factions/marineimperiale.h"
#include "factions/adeptusmechanicus.h"
#include "factions/astratelepathica.h"
#include "factions/astronomica.h"
#include "techno/bionique.h"
#include "age.h"

QString GenVieHumain::AGE = "Age";
QString GenVieHumain::C_LIBERTE = "Liberté";

GenVieHumain::GenVieHumain():GenHistoire ("Vive l'Imperium") {}

GenVieHumain* GenVieHumain::GetGenVieHumain()
{
    return static_cast<GenVieHumain*>(ME);
}

shared_ptr<Hist> GenVieHumain::GenererHistoire()
{
    GenHistoire::GenererHistoire();
    GenererDataUnivers();
    GenererPersos();
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
    shared_ptr<Humain> perso = make_shared<Humain>(nom);
    perso->InitialiserPerso();
    IPerso::AjouterPersoJouable(perso);
}

void GenVieHumain::GenererCaracs()
{
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Planete::C_PLANETE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Metier::C_METIER);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(
                make_shared<Age>(180)); // début à 15 ans (180)
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Administratum::C_DIVISION);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Administratum::C_BUREAU_MUNITORUM );
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Administratum::C_RANG);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Inquisition::C_ORDO);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(ClasseSociale::C_CLASSE_SOCIALE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Maison::C_MAISON);

    // temp test :
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Voyage::C_REAFFECTATION_PLANETE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Voyage::C_DESTINATION_PLANETE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Voyage::C_DUREE_VOYAGE_WARP);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Combat::C_FORCE_COMBAT);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(SecteChaos::C_SECTE_CHAOS);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(SecteChaos::C_DIEU);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(GenVieHumain::C_LIBERTE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Planete::C_TYPE_PLANETE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Crime::C_CRIMINEL);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Psyker::C_PSYKER);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Planete::C_TYPE_PLANETE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(AstraMilitarum::C_FONCTION_ASTRA_MILITARUM);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(AstraMilitarum::C_REGIMENT_ASTRA_MILITARUM);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(MarineImperiale::C_FLOTTE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(MarineImperiale::C_FONCTION);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Crime::C_GANG);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(MondeRuche::C_ZONE_DHABITATION);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(EconomieEvt::C_NIVEAU_ECONOMIQUE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(PbSante::C_SANTE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(PbSante::C_CONSTITUTION);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(MinistorumEvts::C_FOI);
    // secte du chaos :
//    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(SecteChaos::C_INFLUENCE_CHAOS);
//    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(SecteChaos::C_PUISSANCE_SECTE);
//    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(SecteChaos::C_DETECTION_SECTE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(AdeptusMechanicus::C_DIVISION);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(MinistorumEvts::C_FONCTION);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Arbites::C_AFFECTATION);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Arbites::C_GRADE);
    shared_ptr<Carac> carac = GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(Crime::C_MOIS_PRISON);
    carac->m_ModeAffichage = MODE_AFFICHAGE::ma_NombreSupZero;
    shared_ptr<Carac> caracMoisVoyage = GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(Voyage::C_DUREE_VOYAGE_WARP);
    caracMoisVoyage->m_ModeAffichage = MODE_AFFICHAGE::ma_NombreSupZero;
    shared_ptr<Carac> caracMutations = GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(SecteChaos::C_MUTATIONS);
    caracMutations->m_ModeAffichage = MODE_AFFICHAGE::ma_NombreSupZero;
    shared_ptr<Carac> caracBionique = GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(Bionique::C_BIONIQUE_LONGEVITE);
    caracBionique->m_ModeAffichage = MODE_AFFICHAGE::ma_NombreSupZero;
}

void GenVieHumain::GenererEvtsAccueil()
{
    this->AjouterEvt("Debut", "Génération du perso par les choix");
    shared_ptr<Effet> effet1 = AjouterEffetNarration("", "");
    Naissance::GenererEffetNaissance(effet1);

    AjouterEffetGoToEvt(GenVieHumain::EVT_SELECTEUR_ID, "finNaissance");
}

void GenVieHumain::GenererEvtsDeBase(QVector<shared_ptr<NoeudProbable>> &noeuds)
{
    shared_ptr<Evt> evtRien = AjouterEvt("evtRien");
    shared_ptr<Effet> effetRien = AjouterEffetNarration("Il ne se passe rien. => à régénérer");
    effetRien = TransformerEffetEnEffetMoisDeVie(effetRien);
    effetRien->m_CallbackDisplay = [] {
        Phrase phrase = JourApresJour::ExtrairePhrase();
        ExecHistoire::GetEffetActuel()->m_Texte = phrase.m_Texte;
        ExecHistoire::GetEffetActuel()->m_ImgPath = phrase.m_CheminImg;
        ExecHistoire::GetExecEffetActuel()->ChargerImage(phrase.m_CheminImg);
    };
    shared_ptr<NoeudProbable> noeudEvtRien = make_shared<NoeudProbable>(
                evtRien,
                make_shared<Condition>(1, p_Relative));
    noeuds.push_back(noeudEvtRien);

    GenererNoeuds<Metier>(m_GenerateurEvt, noeuds);
    GenererNoeuds<PbSante>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Voyage>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Administratum>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Inquisition>(m_GenerateurEvt, noeuds);
    GenererNoeuds<MondeRuche>(m_GenerateurEvt, noeuds);
    GenererNoeuds<ClasseSociale>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Crime>(m_GenerateurEvt, noeuds);
    GenererNoeuds<SecteChaos>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Psyker>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Arbites>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Assassinorum>(m_GenerateurEvt, noeuds);
    GenererNoeuds<MinistorumEvts>(m_GenerateurEvt, noeuds);
    GenererNoeuds<AstraMilitarum>(m_GenerateurEvt, noeuds);
    GenererNoeuds<MarineImperiale>(m_GenerateurEvt, noeuds);
    GenererNoeuds<EconomieEvt>(m_GenerateurEvt, noeuds);
    GenererNoeuds<AdeptusMechanicus>(m_GenerateurEvt, noeuds);
    GenererNoeuds<MondeForge>(m_GenerateurEvt, noeuds);
    GenererNoeuds<AstraTelepathica>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Astronomica>(m_GenerateurEvt, noeuds);
}

template<class T>
void GenVieHumain::GenererNoeuds(shared_ptr<GenEvt> genEvt, QVector<shared_ptr<NoeudProbable>> &noeuds)
{
    int indexEvt = 0;
    GenerateurNoeudsProbables* evt = new T(indexEvt++);
    while ( evt->m_Nom != "") {

        shared_ptr<Effet> effet = evt->GenererEffet(genEvt);

        shared_ptr<Condition> cond = evt->m_ConditionSelecteurProba;

        shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new T(indexEvt++);
    }
}

shared_ptr<Effet> GenVieHumain::TransformerEffetEnEffetMoisDeVie(shared_ptr<Effet> effet)
{
    // ne se déclenche que si le personnage est encore en vie :
    effet->AjouterCondition(PbSante::C_SANTE, Comparateur::c_Different, PbSante::MORT);
    effet->m_MsChrono = GenVieHumain::CHRONO;
    effet->m_GoToEvtId = "PrincipalSelecteur";
    effet->AjouterAjouteurACarac(GenVieHumain::AGE, 1);
    effet->AjouterAjouteurACarac(Crime::C_MOIS_PRISON, -1);
    effet->AjouterAjouteurACarac(Voyage::C_DUREE_VOYAGE_WARP, -1);
    return effet;
}

QString GenVieHumain::EFFET_SELECTEUR_ID = "effetSelecteur";
QString GenVieHumain::EVT_SELECTEUR_ID = "PrincipalSelecteur";
shared_ptr<Evt> GenVieHumain::EVT_SELECTEUR = nullptr;

void GenVieHumain::GenererPrincipalSelectionneurDEffet()
{
    GenVieHumain::EVT_SELECTEUR = this->AjouterEvt(GenVieHumain::EVT_SELECTEUR_ID, "Principal sélecteur");
    /*Effet* effetDebut = */AjouterEffetGoToEffet(GenVieHumain::EFFET_SELECTEUR_ID, "effet_go_to_" + GenVieHumain::EFFET_SELECTEUR_ID);
    // ce vector doit contenir tous les noeuds de base déclenchant des effets et événements à partir du cours normal de la vie
    // en dehors de lui les sélections de noeuds ne sont qu'à la création du personnage et quand un événement particulier est en cours d'exécution
    // à sa fin on doit avoir un goto qui ramène à cet événement/effet "sélecteur"
    QVector<shared_ptr<NoeudProbable>> tousLesNoeudsDeBase;
    GenererEvtsDeBase(tousLesNoeudsDeBase);

    /*Effet* effetDebutBoucle = m_GenerateurEvt->AjouterEffetVide(GenVieHumain::EVT_SELECTEUR, GenVieHumain::EFFET_SELECTEUR_ID);
    effetDebutBoucle->m_Texte = "blablablabla";*/

    shared_ptr<Effet> effetTestMort = m_GenerateurEvt->AjouterEffetVide(GenVieHumain::EVT_SELECTEUR, GenVieHumain::EFFET_SELECTEUR_ID);
    effetTestMort->m_GoToEffetId = "effetFinVie";
    effetTestMort->AjouterCondition(PbSante::C_SANTE, Comparateur::c_Egal, PbSante::MORT);

    /*Effet* effetDebutBoucle2 = m_GenerateurEvt->AjouterEffetVide(GenVieHumain::EVT_SELECTEUR, GenVieHumain::EFFET_SELECTEUR_ID + "hbjk");
    effetDebutBoucle2->m_Texte = "blablablabla2";*/

    shared_ptr<Effet> effetSelecteur = m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                tousLesNoeudsDeBase, GenVieHumain::EFFET_SELECTEUR_ID + "_selecteur", "", GenVieHumain::EVT_SELECTEUR);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    shared_ptr<Effet> effetFinVie = AjouterEffetNarration("Cette vie est terminée...", "", "effetFinVie", GenVieHumain::EVT_SELECTEUR);
    effetFinVie->m_ChangeurPhaseDeroulement = PhaseDeroulement::epd_Fini;
}
