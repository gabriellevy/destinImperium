#ifndef TITHEGRADE_H
#define TITHEGRADE_H

#include <QString>

enum e_TitheGrade {
    AptusNon
};

enum e_ProductionGrade { //  niveau de production indutrielle du monde
    I_Maximus,
    I_Extremis,
    I_Prima,
    I_Secundi,
    I_Tertius,
    II_Maximus,
    II_Extremis,
    II_Prima,
    II_Secundi,
    II_Tertius,
    III_Maximus,
    III_Extremis,
    III_Prima,
    III_Secundi,
    III_Tertius,
    IV_Maximus,
    IV_Extremis,
    IV_Prima,
    IV_Secundi,
    IV_Tertius,
    Inconnu,
    epg_Aucun
};

/**
 * @brief classement des planètes par l'adeptus Administratum
 */
class TitheGrade
{
    e_TitheGrade m_TitheGrade;
    e_ProductionGrade m_ProductionGrade;
public:
    TitheGrade(e_TitheGrade TitheGrade, e_ProductionGrade ProductionGrade = Inconnu);

    QString GetIntitule();
};

#endif // TITHEGRADE_H
