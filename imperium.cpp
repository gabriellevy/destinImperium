#include "imperium.h"
#include "ui_univers.h"
#include "genviehumain.h"

QString Imperium::VIE_HUMAIN = "Vie d'un humain";

Imperium::Imperium(ModeAffichage modeAffichage,
                   QWidget *parent)
    : Univers(parent, modeAffichage)
{
    //this->AppliquerTheme(QColor(54, 46, 43));
    this->AppliquerTheme(QColor(100, 90, 80));

    m_GensHistoire[Imperium::VIE_HUMAIN] = new GenVieHumain();
}
