#include "factions.h"

Factions::Factions(e_Factions faction):m_FactionE(faction)
{
    switch (m_FactionE) {
    case ef_AdeptusMechanicus : {
        m_Nom = "l'Adeptus Mechnicus";
    } break;
    case ef_Imperium : {
        m_Nom = "l'Imperium de l'homme";
    } break;
    case ef_Ultramarines : {
        m_Nom = "les Ultramarines";
    } break;
    case ef_BloodAngels : {
        m_Nom = "les Blood Angels";
    } break;

    }
}
