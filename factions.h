#ifndef FACTIONS_H
#define FACTIONS_H

#include <QString>

enum e_Factions {
    // Imperium
    AdeptusMechanicus,
    Imperium
};

class Factions
{
    e_Factions m_FactionE;
public:
    Factions(e_Factions faction);

    QString m_Nom;
};

#endif // FACTIONS_H
