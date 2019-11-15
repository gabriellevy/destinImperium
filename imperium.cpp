#include "imperium.h"
#include "ui_univers.h"
#include "genviehumain.h"

QString Imperium::VIE_HUMAIN = "Vie d'un humain";

Imperium::Imperium(ModeAffichage modeAffichage,
                   QWidget *parent)
    : Univers(parent, modeAffichage)
{
    this->AppliquerTheme(QColor(240, 214, 113));

    m_GensHistoire[Imperium::VIE_HUMAIN] = new GenVieHumain();
}
