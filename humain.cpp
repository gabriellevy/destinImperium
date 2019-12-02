#include "humain.h"
#include "imperium.h"
#include "genviehumain.h"
#include "actions/combat.h"
#include "jourapresjour.h"

Humain* Humain::ME = nullptr;

Humain::Humain(QString nom):DPerso(nom, nom, nom, "")
{
    Humain::ME = this;
}

Humain* Humain::GetHumainJoue()
{
    if ( Humain::ME == nullptr )
        Humain::ME = new Humain("inconnu ??");
    return ME;
}

Planete* Humain::GetPlanete()
{
    QString planeteStr = DPerso::GetValeurCarac(Planete::C_PLANETE);
    return Planete::PLANETES[planeteStr];
}

int Humain::GetAge()
{
    return DPerso::GetValeurCaracAsInt(GenVieHumain::AGE);
}

QString Humain::GetValeurCarac(QString id)
{
    return DPerso::GetValeurCarac(id);
}

int Humain::GetValeurCaracAsInt(QString id)
{
    // cas particuliers où on ne rend aps directement la valeur associée :
    if ( id == Combat::C_FORCE_COMBAT) {
        int val = 1; //humain de base

        // ici on pourra ajouter ou retirer des points selon les caracs du perso (space marine = +2 par exemple
        // cf échelle des Combat.h

        return val;
    }

    return DPerso::GetValeurCaracAsInt(id);
}

void Humain::ExecutionPostChangeCarac()
{
    JourApresJour::RafraichirPhrases();
}

