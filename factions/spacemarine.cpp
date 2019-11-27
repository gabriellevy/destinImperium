#include "spacemarine.h"

int SpaceMarine::COMPTEUR = 0;
QString SpaceMarine::IMPERIAL_FIST = "Imperial Fist";

SpaceMarine::SpaceMarine()
{
    switch (SpaceMarine::COMPTEUR) {
    case 0 : {
        m_Nom = SpaceMarine::IMPERIAL_FIST;
        m_PlanetesRecrutement = {"Necromunda"};
    }break;
    }

    SpaceMarine::COMPTEUR++;
}

QVector<SpaceMarine*> SpaceMarine::CHAPITRES = {};
void SpaceMarine::GenererChapitres()
{
    if ( SpaceMarine::CHAPITRES.length() > 0)
        return;

    SpaceMarine* div = new SpaceMarine();
    while ( div->m_Nom != "") {
        SpaceMarine::CHAPITRES.push_back(div);
        div = new SpaceMarine();
    }
}


