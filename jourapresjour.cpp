#include "jourapresjour.h"
#include "../destinLib/aleatoire.h"
#include "humain.h"
#include "types_planete/planet.h"
#include "socio_eco/classesociale.h"

QVector<Phrase> JourApresJour::PHRASES = {};

void JourApresJour::RafraichirPhrases()
{
    // extraire les critères qui influent sur les textes/événements possibles :
    QString typePlanete = Humain::GetHumainJoue()->GetValeurCarac(Planete::C_TYPE_PLANETE);
    QString classeSociale = Humain::GetHumainJoue()->GetValeurCarac(ClasseSociale::C_CLASSE_SOCIALE);

    if ( typePlanete == Planete::PLANETE_RUCHE) {
        if ( classeSociale == ClasseSociale::MISERABLES ) {
            JourApresJour::PHRASES.push_back(
                        Phrase("Encore une bonne bouillie de déchets organiques recyclés comme repas", ""));

        } else if ( classeSociale == ClasseSociale::PAUVRES) {
            JourApresJour::PHRASES.push_back(
                        Phrase("Encore une bonne bouillie de déchets organiques recyclés comme repas", ""));

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


    if ( PHRASES.length() == 0 )
        JourApresJour::PHRASES.push_back(
                    Phrase("Il ne se passe rien."));
}

Phrase JourApresJour::ExtrairePhrase()
{
    return JourApresJour::PHRASES[Aleatoire::GetAl()->EntierInferieurA(PHRASES.length())];
}
