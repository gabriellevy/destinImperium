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
#include "humanite/pbsante.h"
#include "socio_eco/crime.h"

// caracs :
QString Psyker::C_PSYKER = "Psyker";
//valeurs de C_PSYKER
QString Psyker::POTENTIEL_PSY = "Potentiel psy";
QString Psyker::SANS_AME = "Sans âme";

Psyker::Psyker(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmp_Modificateur = 0.0; //pour les tests (doit être à 0 en prod)
    switch (indexEvt) {
    case 0 : {
        m_Nom = Psyker::POTENTIEL_PSY + " élimination";
        m_ConditionSelecteurProba = new Condition(0.005 + tmp_Modificateur, p_Relative);
        m_Description = "Vous êtes identifié par l'Ordo Hereticus comme un dangereux psyker et êtes emprisonné.";
        m_Image = ":/images/inquisition/Inquisitor_Ordo_Hereticus.png";
        m_Conditions.push_back(
                    new Condition(Psyker::C_PSYKER,
                                  Psyker::POTENTIEL_PSY,
                                  Comparateur::c_Egal));
        m_ModificateursCaracs[GenVieHumain::C_LIBERTE] = Crime::CAPTURE_ORDO_HERETICUS;

    }break;
    }
}


Condition* Psyker::AjouterConditionSiPsyker()
{
    return new Condition(Psyker::C_PSYKER, "", Comparateur::c_Different);
}


Condition* Psyker::AjouterConditionSiNonPsyker()
{
    return new Condition(Psyker::C_PSYKER, "", Comparateur::c_Egal);
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
