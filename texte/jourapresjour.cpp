#include "jourapresjour.h"
#include "../destinLib/aleatoire.h"
#include "humain.h"
#include "types_planete/planet.h"
#include "types_planete/mondeforge.h"
#include "socio_eco/classesociale.h"
#include "metier.h"
#include "genviehumain.h"
#include "factions/inquisition.h"
#include "factions/ministorum.h"
#include "warp/sectechaos.h"

QVector<Phrase> JourApresJour::PHRASES = {};

JourApresJour::JourApresJour(){}

void JourApresJour::RafraichirPhrasesSelonPlanete(QString typePlanete, QString classeSociale, QString /*metier*/)
{

    if ( typePlanete == Planete::PLANETE_RUCHE) {
        if ( classeSociale == ClasseSociale::MISERABLES ) {
            JourApresJour::PHRASES.push_back(
                        Phrase("Encore une bonne bouillie de déchets organiques recyclés comme repas", ""));
            JourApresJour::PHRASES.push_back(
                        Phrase("La fatigue et la déprime est telle après cette journée épuisante que vous vous laissez aller à boire de l'immonde Torboyo. "
                               "Eespérons que vous ne serez pas aveugle demain.",
                               ""));

        } else
        {
            // les non misérables :
            JourApresJour::PHRASES.push_back(
                        Phrase("Plaisir rare dans votre vie harassante : vous partagez une bonne bouteille de Whiskar avec vos amis. "
                               "Le serpent mort qui s'y trouve prouve que c'est de la qualité",
                               ""));

        }
        if ( classeSociale == ClasseSociale::PAUVRES) {
            JourApresJour::PHRASES.push_back(
                        Phrase("Encore une bonne bouillie de déchets organiques recyclés comme repas", ""));
            JourApresJour::PHRASES.push_back(
                        Phrase("La fatigue et la déprime est telle après cette journée épuisante que vous vous laissez aller à boire de l'immonde Torboyo. "
                               "Eespérons que vous ne serez pas aveugle demain.",
                               ""));

        } else if ( classeSociale == ClasseSociale::CLASSE_MOYENNE ) {
            JourApresJour::PHRASES.push_back(
                        Phrase("Encore une bonne bouillie de déchets organiques recyclés comme repas"));

        } else if ( classeSociale == ClasseSociale::INFLUENTS ) {

        } else if ( classeSociale == ClasseSociale::MAITRES ) {
            JourApresJour::PHRASES.push_back(
                        Phrase(
                            "Encore une délicieuse journée sur le satelitte privé de divertissement de votre famille, à chevaucher les nuages boréals multicolores.",
                            ":/images/socio_eco/FemmeNobleApparat.jpg"));
            JourApresJour::PHRASES.push_back(
                        Phrase(
                            "Vous avez goûté un vin délicieux. Si délicieux que vous avez décidé de réduire le village qui le produit en esclavage.",
                            ":/images/socio_eco/GrosNoble.png"));
        }
    }
    else if ( typePlanete == Planete::PLANETE_FEODAL)
    {
        JourApresJour::PHRASES.push_back(
                    Phrase("Vous avez goûté un vin délicieux. Si délicieux que vous avez décidé de réduire le village qui le produit en esclavage."));
    }
    else if ( typePlanete == Planete::PLANETE_AGRICOLE)
    {
    }
    else if ( typePlanete == Planete::PLANETE_FORGE)
    {
        if ( classeSociale == ClasseSociale::MISERABLES ) {
            JourApresJour::PHRASES.push_back(
                        Phrase("Encore une bonne bouillie de déchets organiques recyclés comme repas", ""));

        } else if ( classeSociale == ClasseSociale::PAUVRES) {
            JourApresJour::PHRASES.push_back(
                        Phrase("Encore une bonne bouillie de déchets organiques recyclés comme repas", ""));

        }
        MondeForge::RafraichirPhrases();
    }
    else if ( typePlanete == Planete::PLANETE_FERAL)
    {

    }
    else if ( typePlanete == Planete::PLANETE_CHEVALIER)
    {

    }
    else if ( typePlanete == Planete::PLANETE_CIVILISE)
    {

    }
}

void JourApresJour::RafraichirPhrasesSelonMetier(QString typePlanete, QString /*classeSociale*/, QString metier)
{
    if ( metier == Metier::ARBITES) {
        JourApresJour::PHRASES.push_back(
            Phrase(
                "Encore une patrouille tranquille autour de la fortresse de circonscription.",
                ":/images/metier/Arbite_aboard_vessel.jpg"
                ));
        JourApresJour::PHRASES.push_back(
            Phrase(
                "Rien de particulier. Juste quelques coups de matraque énergétique pour calmer les délinquants des environs.",
                ":/images/metier/Female_Arbiter_2.jpg"
                ));
    } else if ( metier == Metier::OUVRIER)
    {
        if ( typePlanete == Planete::PLANETE_RUCHE) {
            JourApresJour::PHRASES.push_back(
                Phrase(
                    "Encore une dure journée de travail à l'usine de la ruche.",
                    ":/images/socio_eco/UsineRuche.jpg"
                    ));
            JourApresJour::PHRASES.push_back(
                Phrase(
                    "Vous allez au travail dans le labyrinthe chaothique de la ruche.",
                    ":/images/ruche/usine.PNG"
                    ));
        }
    } else if (metier == Metier::PAYSAN)
    {
        JourApresJour::PHRASES.push_back(Phrase("Encore une journée de récolte de blé."));
        JourApresJour::PHRASES.push_back(Phrase("Encore une journée de récolte de riz."));
        JourApresJour::PHRASES.push_back(Phrase("Encore une journée de récolte de céréales."));
        JourApresJour::PHRASES.push_back(Phrase("Encore une journée de récolte de légumes."));
        JourApresJour::PHRASES.push_back(Phrase("Vous avez essentiellement abattu des têtes de bétail ces jours-ci."));
        JourApresJour::PHRASES.push_back(Phrase("Les Grox se tiennent à carreau et se nourrissent normalement."));
        JourApresJour::PHRASES.push_back(Phrase("La ponte d'oeufs géants a été bonne."));
        JourApresJour::PHRASES.push_back(Phrase("Vous avez récolté des champignons géants comestibles."));
        JourApresJour::PHRASES.push_back(Phrase("Vous avez chargé des milliers de tonnes d'eau potable pour les mondes ruches."));
        JourApresJour::PHRASES.push_back(Phrase("La pêche devrait suffire à remplir vos quotas du mois."));
        JourApresJour::PHRASES.push_back(Phrase("La récolte d'algues nutritive est satisfaisante."));
    } else if ( metier == Metier::INQUISITEUR)
    {
        QString ordo = Humain::GetHumainJoue()->GetValeurCarac(Inquisition::C_ORDO);
        if ( ordo == Inquisition::ORDO_XENOS) {
            JourApresJour::PHRASES.push_back(
                  Phrase(
                     "Vous avez capturé un recelleur d'artefacts xenos prohibés puis l'avez exécuté.",
                     ":/images/inquisition/élimination_contrebandier.jpg"));
        } else if ( ordo == Inquisition::ORDO_SICARIUS) {
            JourApresJour::PHRASES.push_back(
                  Phrase(
                     "Vous autorisez une mission d'assassinat sur un immonde traître en la faisant passer pour un ordre des hauts seigneurs de Terra."
                     "\nBien qu'en théorie illégal cela est toléré quand le temps presse autant.",
                     ":/images/metier/inquisiteur_ordo_sicarius.jpg"));
        }
    } else if (metier == Metier::TECHNOPRETRE)
    {
        JourApresJour::PHRASES.push_back(
              Phrase("Par vos rituels précis et vos discussions mystiques avec l'esprit de la machine, vous parvenez à réparer un char de combat.",
                 ":/images/metier/Technopretre.jpg"));
        JourApresJour::PHRASES.push_back(
              Phrase("Vous travaillez sur un aliage amélioré. Pourvu que le conseil approuve vos recherches.",
                 ":/images/mechanicus/Adeptus_Mechanicus_Tech-priest.jpg"));
        JourApresJour::PHRASES.push_back(
              Phrase("On vous amène un tank à réparer qui démarre mal. Probablement que l'équipage ne chante pas correctement les hymnes de démarrage.",
                 ":/images/mechanicus/MagosExplorator.jpg"));
    }
}

void JourApresJour::RafraichirPhrases()
{
    Humain* humain = Humain::GetHumainJoue();
    // extraire les critères qui influent sur les textes/événements possibles :
    QString typePlanete = Humain::GetHumainJoue()->GetValeurCarac(Planete::C_TYPE_PLANETE);
    QString classeSociale = Humain::GetHumainJoue()->GetValeurCarac(ClasseSociale::C_CLASSE_SOCIALE);
    QString metier = Humain::GetHumainJoue()->GetValeurCarac(Metier::C_METIER);
    QString liberte = Humain::GetHumainJoue()->GetValeurCarac(GenVieHumain::C_LIBERTE);

    if ( humain->GetValeurCarac(SecteChaos::C_SECTE_CHAOS) == "1")
        SecteChaos::RafraichirPhrases();

    RafraichirPhrasesSelonPlanete(typePlanete, classeSociale, metier);
    MinistorumEvts::RafraichirPhrasesDeLaFoi(typePlanete, classeSociale, metier); // ce qui a rapport à l'Adeptus Administratum et à la foi en l'empereur
    if ( liberte == "" ) // pas d'actions de métier si on est enfermé
        RafraichirPhrasesSelonMetier(typePlanete, classeSociale, metier);

    if ( PHRASES.length() == 0 )
        JourApresJour::PHRASES.push_back(
                    Phrase("Il ne se passe rien."));
}

Phrase JourApresJour::ExtrairePhrase()
{
    return JourApresJour::PHRASES[Aleatoire::GetAl()->EntierInferieurA(PHRASES.length())];
}
