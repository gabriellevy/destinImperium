#include "factions.h"

Factions::Factions(e_Factions faction):m_FactionE(faction)
{
    switch (m_FactionE) {
    case AdeptusMechanicus : {
        m_Nom = "l'Adeptus Mechnicus";
    } break;

    }
}
