#include "jourapresjour.h"
#include "../destinLib/aleatoire.h"
#include "humain.h"
#include "types_planete/planet.h"

QVector<QString> JourApresJour::PHRASES = {};

void JourApresJour::RafraichirPhrases()
{
    // extraire les critères qui influent sur les textes/événements possibles :
    QString typePlanete = Humain::GetHumainJoue()->GetValeurCarac(Planete::C_TYPE_PLANETE);

    if ( typePlanete == Planete::PLANETE_RUCHE) {
        JourApresJour::PHRASES.push_back("Encore une bonne bouillie de déchets organiques recyclés comme repas");
    }


    if ( PHRASES.length() == 0 )
        JourApresJour::PHRASES.push_back("Il ne se passe rien.");
}

QString JourApresJour::ExtrairePhrase()
{
    return JourApresJour::PHRASES[Aleatoire::GetAl()->EntierInferieurA(PHRASES.length())];
}
