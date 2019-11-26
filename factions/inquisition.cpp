#include "inquisition.h"
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


int Inquisition::COMPTEUR = 0;

QString Inquisition::C_ORDO = "Ordo";

QString Inquisition::ORDO_XENOS = "Ordo Xenos";
QString Inquisition::ORDO_MALLEUS = "Ordo Malleus";
QString Inquisition::ORDO_HERETICUS = "Ordo Hereticos";

// ids :
QString Inquisition::ID_AFFECTATION_DIVISION = "Affectation Ordo";

Inquisition::Inquisition()
{
    switch (Inquisition::COMPTEUR) {
    case 0 : {
        m_Nom = Inquisition::ID_AFFECTATION_DIVISION;
        m_Condition = new Condition(0, p_Pure);
        Inquisition::AjouterModifProbaSiAOrdo(m_Condition, -1);
        Inquisition::AjouterModifProbaSiInquisiteur(m_Condition, 0.1);
        //m_ModificateursCaracs[Inquisition::RANG] = Administratum::GRADE_SCRIBE;

    }break;
    }

    Inquisition::COMPTEUR++;

}

Condition* Inquisition::AjouterModifProbaSiAOrdo(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {         new Condition(Inquisition::C_ORDO, "", Comparateur::c_Different)        });
    return cond;
}

Condition* Inquisition::AjouterModifProbaSiInquisiteur(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {
         new Condition(GenVieHumain::METIER, Metier::GetMetierAsStr(Inquisiteur), Comparateur::c_Egal)
        });
    return cond;
}

Effet* Inquisition::GenererEffet(GenEvt* genEvt)
{
    Effet* effet = nullptr;
    if ( m_Nom == Inquisition::ID_AFFECTATION_DIVISION) {
        // sélectionneur d'effets
        QVector<NoeudProbable*> noeudsAffectation;
        Ordo::GenererNoeudsAffectation(genEvt, noeudsAffectation);
        effet = genEvt->AjouterEffetSelecteurDEvt(noeudsAffectation, Inquisition::ID_AFFECTATION_DIVISION, "", GenVieHumain::EVT_SELECTEUR);
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


void Inquisition::GenererNoeudsInquisition(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    Inquisition* evt = new Inquisition();
    while ( evt->m_Nom != "") {

        Effet* effet = evt->GenererEffet(genEvt);

        Condition* cond = evt->m_Condition;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new Inquisition();
    }
}

QVector<Ordo*> Ordo::ORDOS = {};
void Ordo::GenererOrdos()
{
    if ( Ordo::ORDOS.length() > 0)
        return;

    Ordo* div = new Ordo();
    while ( div->m_Nom != "") {
        Ordo::ORDOS.push_back(div);
        div = new Ordo();
    }
}
int Ordo::COMPTEUR = 0;

Ordo::Ordo()
{
    switch (Ordo::COMPTEUR) {
    case 0 : {
        m_Nom = Inquisition::ORDO_XENOS;
        m_Condition = new Condition(0.4, p_Relative);
        m_Image = ":/images/metier/inquisiteur_ordo_xenos.jpg";
        m_Description = "Vous avez été assigné à l'Ordo Xenos, "
                "les exterminateurs d'extra-terrestres.";
    }break;
    case 1 : {
        m_Nom = Inquisition::ORDO_MALLEUS;
        m_Condition = new Condition(0.4, p_Relative);
        m_Image = ":/images/metier/inquisiteur_ordo_malleus.png";
        m_Description = "Vous avez été assigné à l'Ordo Malleus. "
                "Vous êtes un chasseur de démons.";
    }break;
    case 2 : {
        m_Nom = Inquisition::ORDO_HERETICUS;
        m_Condition = new Condition(0.4, p_Relative);
        m_Image = ":/images/metier/inquisiteur_ordo_hereticus.jpg";
        m_Description = "Vous avez été assigné à l'Ordo Hereticus. "
                "Vous êtes chargé d'éliminer les psykers, les traîtres et les hérétiques.";
    }break;
    }
    m_ModificateursCaracs[Inquisition::C_ORDO] = m_Nom;

    Ordo::COMPTEUR++;
}

void Ordo::GenererNoeudsAffectation(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    for (int i = 0; i < Ordo::ORDOS.length() ; ++i) {
        Ordo* div = ORDOS[i];
        Effet* effet = genEvt->AjouterEffetNarration(
            div->m_Description,
            div->m_Image,
            "affectation_division_administratum_" + div->m_Nom, GenVieHumain::EVT_SELECTEUR);
        effet->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
        effet = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet);
        effet->AjouterChangeurDeCarac(Inquisition::C_ORDO, div->m_Nom);

        Condition* cond = div->m_Condition;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

    }
}

