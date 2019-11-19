#include "administratum.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "planet.h"
#include "voyage.h"
#include "metier.h"

QString Administratum::RANG = "Rang administratum";
int Administratum::COMPTEUR = 0;

Administratum::Administratum()
{
    switch (Administratum::COMPTEUR) {
    case 0 : {
        m_Nom = "Passer au rang de scribe";
        m_Condition = new Condition(0);
        m_ModificateursCaracs[Administratum::RANG] = "Scribe augmenté";
        m_Image = ":/images/metier/Metallic_Scribe.jpg";
        Administratum::AjouterModifProbaSiAdepteAdministratum40Ans(m_Condition, 0.15);

    }break;
    }

    Administratum::COMPTEUR++;
}

Condition* Administratum::AjouterModifProbaSiAdepteAdministratum40Ans(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(GenVieHumain::AGE, "400", Comparateur::c_Superieur),
         new Condition(GenVieHumain::METIER, Metier::GetMetierAsStr(AdepteAdministratum), Comparateur::c_Egal)
        });
    return cond;
}


void Administratum::GenererNoeudsAdministratum(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    Administratum* evt = new Administratum();
    while ( evt->m_Nom != "") {

        Effet* effetAffectation = genEvt->AjouterEffetNarration(
                    evt->m_Description,
                    evt->m_Image,
                    "avt_administratum_" + evt->m_Nom, GenVieHumain::EVT_SELECTEUR);
        effetAffectation->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
        effetAffectation = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effetAffectation);

        // modificateurs de carac :
        QMapIterator<QString, QString> it(evt->m_ModificateursCaracs);
        while ( it.hasNext()) {
            it.next();
            effetAffectation->AjouterChangeurDeCarac(it.key(), it.value());
        }

        Condition* cond = evt->m_Condition;

        NoeudProbable* noeud = new NoeudProbable(
                    effetAffectation,
                    cond);

        noeuds.push_back(noeud);

        evt = new Administratum();
    }
}
