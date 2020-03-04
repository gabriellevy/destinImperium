#ifndef IMPERIUM_H
#define IMPERIUM_H

#include "../destinLib/abs/univers.h"

class Imperium : public Univers
{
    Q_OBJECT

public:
    explicit Imperium(ModeAffichage modeAffichage = ModeAffichage::ema_Jeu,
             QWidget *parent = nullptr);

    // noms d'aventures
    static QString VIE_HUMAIN;
};

#endif // IMPERIUM_H
