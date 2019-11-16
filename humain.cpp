#include "humain.h"
#include "imperium.h"
#include "genviehumain.h"

Humain::Humain():DPerso("Reynault", "Reynault", "Reynault", "")
{}

Planete* Humain::GetPlanete()
{
    QString planeteStr = DPerso::GetValeurCarac(GenVieHumain::PLANETE);
    return Planete::PLANETES[planeteStr];
}
