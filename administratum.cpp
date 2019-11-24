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
#include "../destinLib/effet.h"

int Administratum::COMPTEUR = 0;

// ids :
QString Administratum::ID_AFFECTATION_DIVISION = "Affectation Division";

// sous-divisions
QString Administratum::C_DIVISION = "Division Administratum";
QString Administratum::DEPARTMENTO_MUNITORUM = "Departmento Munitorum";
QString Administratum::DEPARTMENTO_EXACTA = "Departmento Exacta";
QString Administratum::ESTATE_IMPERIUM = "Estate Imperium";
QString Administratum::REVISION_HISTORIQUE = "Unité de révision historique";
QString Administratum::OFFICIO_MEDICAE = "Officio Medicae";
QString Administratum::LOGIS_STRATEGOS = "Logis Strategos";
QString Administratum::FLOTTE_IMPERIALE_DE_GUERRE = "Flotte impériale de guerre";
QString Administratum::FLOTTE_MARCHANDE = "Flotte marchande";
QString Administratum::FLOTTE_CIVILE = "Flotte civile";
QString Administratum::OFFICIO_ASSASSINORUM = "Officio Assassinorum";
QString Administratum::OFFICIO_SABATORUM = "Officio Sabatorum";
QString Administratum::OFFICIO_AGRICULTAE = "Officio Agricultae";
QString Administratum::ORDO_TEMPESTUS = "Ordo Tempestus";
QVector<QString> Administratum::DIVISIONS = {
    Administratum::DEPARTMENTO_MUNITORUM, Administratum::DEPARTMENTO_EXACTA
};

// grades
QString Administratum::RANG = "Rang administratum";
QString Administratum::GRADE_SCRIBE = "Scribe";
QString Administratum::GRADE_ORDINATE = "Ordinate";
QString Administratum::GRADE_PREFET = "Préfet";
QString Administratum::GRADE_MAITRE = "Maître";

Administratum::Administratum()
{
    switch (Administratum::COMPTEUR) {
    case 0 : {
        m_Nom = Administratum::ID_AFFECTATION_DIVISION;
        m_Condition = new Condition(0, p_Pure);
        Administratum::AjouterModifProbaSiADivision(m_Condition, -1);
        Administratum::AjouterModifProbaSiAdepteAdministratum(m_Condition, 0.1);
        m_ModificateursCaracs[Administratum::RANG] = Administratum::GRADE_SCRIBE;

    }break;
    case 1 : {
        m_Nom = Administratum::GRADE_ORDINATE;
        m_Condition = new Condition(0, p_Relative);
        m_ModificateursCaracs[Administratum::RANG] = Administratum::GRADE_ORDINATE;
        m_Image = ":/images/metier/Metallic_Scribe.jpg";
        m_Description = "Vous avez l'insigne honneur de devenir Ordinate mécaniquement augmenté.";
        Administratum::AjouterModifProbaSiScribeAdministratum40Ans(m_Condition, 0.15);

    }break;
    case 2 : {
        m_Nom = Administratum::GRADE_PREFET;
        m_Condition = new Condition(0, p_Relative);
        m_ModificateursCaracs[Administratum::RANG] = Administratum::GRADE_PREFET;
        m_Image = ":/images/metier/Prefet.jpg";
        m_Description = "Vous avez l'insigne honneur de devenir Préfet de l'Administratum.";
        Administratum::AjouterModifProbaSiOrdinateAdministratum50Ans(m_Condition, 0.05);

    }break;
    case 3 : {
        m_Nom = Administratum::GRADE_MAITRE;
        m_Condition = new Condition(0, p_Relative);
        m_ModificateursCaracs[Administratum::RANG] = Administratum::GRADE_MAITRE;
        m_Image = ":/images/metier/Maitre.jpg";
        m_Description = "Vous avez l'insigne honneur de devenir Maître de votre division.";
        Administratum::AjouterModifProbaSiScribeAdministratum40Ans(m_Condition, 0.01);

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

Condition* Administratum::AjouterModifProbaSiScribeAdministratum40Ans(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(GenVieHumain::AGE, "400", Comparateur::c_Superieur),
         new Condition(GenVieHumain::METIER, Metier::GetMetierAsStr(AdepteAdministratum), Comparateur::c_Egal),
         new Condition(Administratum::RANG, Administratum::GRADE_SCRIBE, Comparateur::c_Egal)
        });
    return cond;
}

Condition* Administratum::AjouterModifProbaSiOrdinateAdministratum50Ans(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(GenVieHumain::AGE, "520", Comparateur::c_Superieur),
         new Condition(GenVieHumain::METIER, Metier::GetMetierAsStr(AdepteAdministratum), Comparateur::c_Egal),
         new Condition(Administratum::RANG, Administratum::GRADE_ORDINATE, Comparateur::c_Egal)
        });
    return cond;
}

Condition* Administratum::AjouterModifProbaSiPrefetAdministratum60Ans(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(GenVieHumain::AGE, "640", Comparateur::c_Superieur),
         new Condition(GenVieHumain::METIER, Metier::GetMetierAsStr(AdepteAdministratum), Comparateur::c_Egal),
         new Condition(Administratum::RANG, Administratum::GRADE_PREFET, Comparateur::c_Egal)
        });
    return cond;
}

Effet* Administratum::GenererEffet(GenEvt* genEvt)
{
    Effet* effet = nullptr;
    if ( m_Nom == Administratum::ID_AFFECTATION_DIVISION) {
        // sélectionneur d'effets
        QVector<NoeudProbable*> noeudsAffectation;
        DivisionAdministratum::GenererNoeudsAffectation(genEvt, noeudsAffectation);
        effet = genEvt->AjouterEffetSelecteurDEvt(noeudsAffectation, Administratum::ID_AFFECTATION_DIVISION, "", GenVieHumain::EVT_SELECTEUR);
    } else {
        // système de création d'effets de base :
        effet = genEvt->AjouterEffetNarration(
            m_Description,
            m_Image,
            "avt_administratum_" + m_Nom, GenVieHumain::EVT_SELECTEUR);
        effet->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
        effet = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet);
    }

    // modificateurs de carac :
    QMapIterator<QString, QString> it(m_ModificateursCaracs);
    while ( it.hasNext()) {
        it.next();
        effet->AjouterChangeurDeCarac(it.key(), it.value());
    }

    return effet;
}

void Administratum::GenererNoeudsAdministratum(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    Administratum* evt = new Administratum();
    while ( evt->m_Nom != "") {

        Effet* effet = evt->GenererEffet(genEvt);

        Condition* cond = evt->m_Condition;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new Administratum();
    }
}
QVector<DivisionAdministratum*> DivisionAdministratum::DIVISIONS = {};
void DivisionAdministratum::GenererDivisions()
{
    if ( DivisionAdministratum::DIVISIONS.length() > 0)
        return;

    DivisionAdministratum* div = new DivisionAdministratum();
    while ( div->m_Nom != "") {
        DivisionAdministratum::DIVISIONS.push_back(div);
        div = new DivisionAdministratum();
    }
}
int DivisionAdministratum::COMPTEUR = 0;

DivisionAdministratum::DivisionAdministratum()
{
    switch (DivisionAdministratum::COMPTEUR) {
    case 0 : {
        m_Nom = Administratum::DEPARTMENTO_MUNITORUM;
        m_Condition = new Condition(0.5, p_Relative);
        m_Image = ":/images/metier/Munitorum_Scribe.jpg";
        m_Description = "Vous avez été assigné à la division du departmento munitorum, la branche logistique au service de la garde impériale.";
    }break;
    case 1 : {
        m_Nom = Administratum::DEPARTMENTO_EXACTA;
        m_Condition = new Condition(0.3, p_Relative);
        m_Image = ":/images/metier/DepartmentoExacta.jpg";
        m_Description = "Vous avez été assigné à la division du departmento Exacta. Vous êtes chargé de la collecte du considérable tribut Exacta prélevé sur la plupart des mondes de l'Imperium.";
    }break;
    case 2 : {
        m_Nom = Administratum::OFFICIO_SABATORUM;
        m_Condition = new Condition(0.01, p_Relative);
        m_Image = ":/images/organisations/Officio_Assassinorum_symbol_2.png";
        m_Description = "Vous avez été assigné à la gestion logistique de l'Officio Sabatorum, un bureau de sabotage ultra secret.";
    }break;
    case 3 : {
        m_Nom = Administratum::ESTATE_IMPERIUM;
        m_Condition = new Condition(0.3, p_Relative);
        m_Description = "Vous avez été assigné à la division de l'Estate Imperium."
                " Vous êtes chargé de tenir à jour les comptes et registres.";
    }break;
    case 4 : {
        m_Nom = Administratum::REVISION_HISTORIQUE;
        m_Condition = new Condition(0.1, p_Relative);
        m_Description = "Vous avez été assigné à l'unité de révision historique en tant qu'Historitor."
                " Vous êtes chargé de contrôler les registres historiques et de les éditer, voire de les purger de tous les éléments non approuvés par hauts seigneurs de Terre.";
    }break;
    case 5 : {
        m_Nom = Administratum::OFFICIO_MEDICAE;
        m_Condition = new Condition(0.2, p_Relative);
        m_Description = "Vous avez été assigné à l'Officio Medicae, en charge de la santé public.";
    }break;
    case 6 : {
        m_Nom = Administratum::LOGIS_STRATEGOS;
        m_Condition = new Condition(0.2, p_Relative);
        m_Description = "Vous avez été assigné à la Logis Strategos, en charge de l'analyse de données d'espionnage et de la détection de menaces.";
    }break;
    case 7 : {
        m_Nom = Administratum::FLOTTE_IMPERIALE_DE_GUERRE;
        m_Condition = new Condition(0.3, p_Relative);
        m_Image = ":/images/organisations/FlotteImperialeDeGuerre.jpg";
        m_Description = "Vous avez été assigné à la gestion logistique de la flotte de guerre impériale.";
    }break;
    case 8 : {
        m_Nom = Administratum::FLOTTE_MARCHANDE;
        m_Condition = new Condition(0.3, p_Relative);
        m_Image = ":/images/vaisseaux/VagabondTrader.jpg";
        m_Description = "Vous avez été assigné à la gestion logistique de la flotte marchande impériale.";
    }break;
    case 9 : {
        m_Nom = Administratum::FLOTTE_CIVILE;
        m_Condition = new Condition(0.3, p_Relative);
        m_Image = ":/images/vaisseaux/VagabondTrader.jpg";
        m_Description = "Vous avez été assigné à la gestion logistique de la flotte civile impériale.";
    }break;
    case 10 : {
        m_Nom = Administratum::OFFICIO_ASSASSINORUM;
        m_Condition = new Condition(0.1, p_Relative);
        m_Image = ":/images/organisations/Officio_Assassinorum_symbol_2.png";
        m_Description = "Vous avez été assigné à la gestion logistique de l'Officio Assassinorum, le bureau des assassins impériaux.";
    }break;
    case 11 : {
        m_Nom = Administratum::OFFICIO_AGRICULTAE;
        m_Condition = new Condition(0.3, p_Relative);
        m_Description = "Vous avez été assigné à la gestion de l'Officio Agricultae, l'organisation de contrôle des mondes agricoles de l'imperium.";
    }break;
    case 12 : {
        m_Nom = Administratum::ORDO_TEMPESTUS;
        m_Condition = new Condition(0.1, p_Relative);
        m_Description = "Vous avez été assigné à la gestion de l'Ordo Tempestus, une branche militaire d'élite de l'Imperium.";
    }break;
    }
    m_ModificateursCaracs[Administratum::C_DIVISION] = m_Nom;

    DivisionAdministratum::COMPTEUR++;
}

void DivisionAdministratum::GenererNoeudsAffectation(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    for (int i = 0; i < DivisionAdministratum::DIVISIONS.length() ; ++i) {
        DivisionAdministratum* div = DIVISIONS[i];
        Effet* effet = genEvt->AjouterEffetNarration(
            div->m_Description,
            div->m_Image,
            "affectation_division_administratum_" + div->m_Nom, GenVieHumain::EVT_SELECTEUR);
        effet->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
        effet = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet);
        effet->AjouterChangeurDeCarac(Administratum::C_DIVISION, div->m_Nom);

        Condition* cond = div->m_Condition;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

    }
}
