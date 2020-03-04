#include "generateurnoeudsprobables.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "imperium.h"
#include "genviehumain.h"
#include "types_planete/planet.h"
#include "warp/voyage.h"
#include "metier.h"

GenerateurNoeudsProbables::GenerateurNoeudsProbables(int indexEvt){}


shared_ptr<Effet> GenerateurNoeudsProbables::GenererEffet(shared_ptr<GenEvt> genEvt)
{
    shared_ptr<Effet> effet = nullptr;

    // système de création d'effets de base :
    effet = genEvt->AjouterEffetNarration(
        m_Description,
        m_Image,
        "evt_monde_ruche_" + m_Nom, GenVieHumain::EVT_SELECTEUR);
    effet->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
    effet = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet);
    effet->m_Conditions = m_Conditions;
    effet->m_CallbackDisplay = m_CallbackDisplay;

    // modificateurs de carac :
    QMapIterator<QString, QString> it(m_ModificateursCaracs);
    while ( it.hasNext()) {
        it.next();
        effet->AjouterChangeurDeCarac(it.key(), it.value());
    }
    QMapIterator<QString, int> itInc(m_IncrementeursCaracs);
    while ( itInc.hasNext()) {
        itInc.next();
        effet->AjouterAjouteurACarac(itInc.key(), itInc.value());
    }

    return effet;
}

