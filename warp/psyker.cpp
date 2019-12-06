#include "psyker.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "../types_planete/planet.h"
#include "voyage.h"
#include "metier.h"
#include "../destinLib/effet.h"
#include "../destinLib/aleatoire.h"
#include "pbsante.h"
#include "socio_eco/crime.h"

int Psyker::COMPTEUR = 0;

// caracs :
QString Psyker::C_PSYKER = "Psyker";
//valeurs de C_PSYKER
QString Psyker::POTENTIEL_PSY = "Potentiel psy";
QString Psyker::SANS_AME = "Sans âme";

Psyker::Psyker()
{
    double tmp_Modificateur = 0.0; //pour les tests (doit être à 0 en prod)
    switch (Psyker::COMPTEUR) {
    case 0 : {
        m_Nom = Psyker::POTENTIEL_PSY + " élimination";
        m_ConditionSelecteurProba = new Condition(0.005 + tmp_Modificateur, p_Relative);
        m_Description = "Vous êtes identifié par les autorités locales comme un dangereux psyker et êtes emprisonné.";
        m_Image = ":/images/metier/Primaris_Psyker.jpg";
        m_Conditions.push_back(
                    new Condition(Psyker::C_PSYKER,
                                  Psyker::POTENTIEL_PSY,
                                  Comparateur::c_Egal));
        m_ModificateursCaracs[GenVieHumain::C_LIBERTE] = Crime::CAPTURE_POLICE;

    }break;
    }

    Psyker::COMPTEUR++;

}

Effet* Psyker::GenererEffet(GenEvt* genEvt)
{
    Effet* effet = nullptr;
    // système de création d'effets de base :
    effet = genEvt->AjouterEffetNarration(
        m_Description,
        m_Image,
        "evt_monde_ruche_" + m_Nom, GenVieHumain::EVT_SELECTEUR);
    effet->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
    effet = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet);

    effet->m_Conditions = m_Conditions;

    // modificateurs de carac :
    QMapIterator<QString, QString> it(m_ModificateursCaracs);
    while ( it.hasNext()) {
        it.next();
        effet->AjouterChangeurDeCarac(it.key(), it.value());
    }

    return effet;
}


void Psyker::GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    Psyker* evt = new Psyker();
    while ( evt->m_Nom != "") {

        Effet* effet = evt->GenererEffet(genEvt);

        Condition* cond = evt->m_ConditionSelecteurProba;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new Psyker();
    }
}

QString Psyker::GetNiveauPsykerNaissance()
{
    double proba = Aleatoire::GetAl()->Entre0Et1();

    if ( proba < 0.0001) {
        return Psyker::SANS_AME;

    } else if ( proba < 0.05) {
        return Psyker::POTENTIEL_PSY;
    }

    // non psyker :
    return "";
}
