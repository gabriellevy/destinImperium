#include "humain.h"
#include "imperium.h"
#include "genviehumain.h"

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
    QString planeteStr = DPerso::GetValeurCarac(GenVieHumain::PLANETE);
    return Planete::PLANETES[planeteStr];
}

int Humain::GetAge()
{
    return DPerso::GetValeurCaracAsInt(GenVieHumain::AGE);
}
