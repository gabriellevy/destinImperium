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

// sous-divisions
QString Administratum::C_DIVISION = "Division Administratum";
QString Administratum::DEPARTMENTO_MUNITORUM = "Departmento Munitorum";
QString Administratum::DEPARTMENTO_EXACTA = "Departmento Exacta";
QString Administratum::ESTATE_IMPERIUM = "Estate Imperium";
QString Administratum::REVISION_HISTORIQUE = "Unité de révision historique";
QString Administratum::OFFICIO_MEDICAE = "Officio Medicae";
QString Administratum::LOGIS_STRATEGOS = "Logis Strategos";
QVector<QString> Administratum::DIVISIONS = {
    Administratum::DEPARTMENTO_MUNITORUM, Administratum::DEPARTMENTO_EXACTA
};

Administratum::Administratum()
{
    switch (Administratum::COMPTEUR) {
    case 0 : {
        m_Nom = "Passer au rang de scribe";
        m_Condition = new Condition(0);
        m_ModificateursCaracs[Administratum::RANG] = "Scribe augmenté";
        m_Image = ":/images/metier/Metallic_Scribe.jpg";
        m_Description = "Vous avez l'insigne honneur de devenir scribe vétéran mécaniqueemnt augmenté.";
        Administratum::AjouterModifProbaSiAdepteAdministratum40Ans(m_Condition, 0.15);

    }break;
    case 1 : {
        m_Nom = "Affectation Division";
        m_Condition = new Condition(0);
        m_ModificateursCaracs[Administratum::C_DIVISION] = Administratum::DEPARTMENTO_MUNITORUM;
        m_Image = ":/images/metier/Munitorum_Scribe.jpg";
        m_Description = "Vous avez été assigné à la division du departmento munitorum, la branche logistique au service de la garde impériale.";
        Administratum::AjouterModifProbaSiADivision(m_Condition, -1);
        Administratum::AjouterModifProbaSiAdepteAdministratum(m_Condition, 1);
    }break;
    case 2 : {
        m_Nom = "Affectation Division Departmento Exacta";
        m_Condition = new Condition(0);
        m_ModificateursCaracs[Administratum::C_DIVISION] = Administratum::DEPARTMENTO_EXACTA;
        m_Description = "Vous avez été assigné à la division du departmento Exacta. Vous êtes chargé de la collecte du considérable tribut Exacta prélevé sur la plupart des mondes de l'Imperium.";
        Administratum::AjouterModifProbaSiADivision(m_Condition, -1);
        Administratum::AjouterModifProbaSiAdepteAdministratum(m_Condition, 1);
    }break;
    case 3 : {
        m_Nom = "Affectation Division Estate Imperium";
        m_Condition = new Condition(0);
        m_ModificateursCaracs[Administratum::C_DIVISION] = Administratum::ESTATE_IMPERIUM;
        m_Description = "Vous avez été assigné à la division de l'Estate Imperium."
                " Vous êtes chargé de tenir à jour les comptes et registres.";
        Administratum::AjouterModifProbaSiADivision(m_Condition, -1);
        Administratum::AjouterModifProbaSiAdepteAdministratum(m_Condition, 1);
    }break;
    case 4 : {
        m_Nom = "Affectation Division Unité de révision historique";
        m_Condition = new Condition(0);
        m_ModificateursCaracs[Administratum::C_DIVISION] = Administratum::REVISION_HISTORIQUE;
        m_Description = "Vous avez été assigné à l'unité de révision historique en tant qu'Historitor."
                " Vous êtes chargé de contrôler les registres historiques et de les éditer, voire de les purger de tous les éléments non approuvés par hauts seigneurs de Terre.";
        Administratum::AjouterModifProbaSiADivision(m_Condition, -1);
        Administratum::AjouterModifProbaSiAdepteAdministratum(m_Condition, 1);
    }break;
    case 5 : {
        m_Nom = "Affectation Division Officio Medicae";
        m_Condition = new Condition(0);
        m_ModificateursCaracs[Administratum::C_DIVISION] = Administratum::OFFICIO_MEDICAE;
        m_Description = "Vous avez été assigné à l'Officio Medicae, en charge de la santé public.";
        Administratum::AjouterModifProbaSiADivision(m_Condition, -1);
        Administratum::AjouterModifProbaSiAdepteAdministratum(m_Condition, 1);
    }break;
    case 6 : {
        m_Nom = "Affectation Division Logis Strategos";
        m_Condition = new Condition(0);
        m_ModificateursCaracs[Administratum::C_DIVISION] = Administratum::LOGIS_STRATEGOS;
        m_Description = "Vous avez été assigné à la Logis Strategos, en charge de l'a santé public'analyse de données d'espionnage et de la détection de menaces.";
        Administratum::AjouterModifProbaSiADivision(m_Condition, -1);
        Administratum::AjouterModifProbaSiAdepteAdministratum(m_Condition, 1);
    }break;
    }

    Administratum::COMPTEUR++;
}

Condition* Administratum::AjouterModifProbaSiADivision(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {         new Condition(Administratum::C_DIVISION, "", Comparateur::c_Different)        });
    return cond;
}

Condition* Administratum::AjouterModifProbaSiAdepteAdministratum(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {
         new Condition(GenVieHumain::METIER, Metier::GetMetierAsStr(AdepteAdministratum), Comparateur::c_Egal)
        });
    return cond;
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
