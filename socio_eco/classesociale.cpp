#include "classesociale.h"
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

int ClasseSociale::COMPTEUR = 0;

ClasseSociale::ClasseSociale()
{
    switch (ClasseSociale::COMPTEUR) {
    case 0 : {
        m_Nom = "test temp";
        m_Condition = new Condition(0, p_Pure);
        m_Description = "blablabla ClasseSociale";
        //Inquisition::AjouterModifProbaSiInquisiteur(m_Condition, 0.1);
        //m_ModificateursCaracs[Inquisition::RANG] = Administratum::GRADE_SCRIBE;

    }break;
    }

    ClasseSociale::COMPTEUR++;

}


Effet* ClasseSociale::GenererEffet(GenEvt* genEvt)
{
    Effet* effet = nullptr;
    /*if ( m_Nom == Inquisition::ID_AFFECTATION_ORDO) {
        // sélectionneur d'effets
        QVector<NoeudProbable*> noeudsAffectation;
        Ordo::GenererNoeudsAffectation(genEvt, noeudsAffectation);
        effet = genEvt->AjouterEffetSelecteurDEvt(
                    noeudsAffectation,
                    Inquisition::ID_AFFECTATION_ORDO,
                    "",
                    GenVieHumain::EVT_SELECTEUR);
    } else*/ {
        // système de création d'effets de base :
        effet = genEvt->AjouterEffetNarration(
            m_Description,
            m_Image,
            "evt_monde_ruche_" + m_Nom, GenVieHumain::EVT_SELECTEUR);
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


void ClasseSociale::GenererNoeudsClasseSociale(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    ClasseSociale* evt = new ClasseSociale();
    while ( evt->m_Nom != "") {

        Effet* effet = evt->GenererEffet(genEvt);

        Condition* cond = evt->m_Condition;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new ClasseSociale();
    }
}

QString ClasseSociale::CLASSE_SOCIALE = "Classe sociale";


e_ClasseSociale ClasseSociale::GetClasseSocialeAleatoire(TypePlanete typeMonde)
{
    double proba = Aleatoire::GetAl()->Entre0Et1();
    switch (typeMonde) {
    case TypePlanete::MondeRuche :
        if ( proba < 0.01)
            return Miserable;
        else if (proba < 0.7)
            return Pauvre;
        else if ( proba < 0.98)
            return ClasseMoyenne;
        else if ( proba < 0.999)
            return Influents;
        else {
            return Maitres;
        }
    default :
        if ( proba < 0.01)
            return Miserable;
        else if (proba < 0.7)
            return Pauvre;
        else if ( proba < 0.98)
            return ClasseMoyenne;
        else if ( proba < 0.999)
            return Influents;
        else {
            return Maitres;
        }

    }
}

QString ClasseSociale::GetClasseSocialeAsStr(e_ClasseSociale classeSociale, TypePlanete typeMonde)
{
    switch (classeSociale) {
    case Miserable :
        switch (typeMonde) {
        case TypePlanete::MondeRuche : return "Très pauvre habitant du sous-monde"; // ou nomade des cendres ?
        default : return "Misérable";
        }
    case Pauvre :
        switch (typeMonde) {
        case TypePlanete::MondeRuche : return "Ouvrier pauvre"; // ou Ganger
        default : return "Pauvre";
        }
    case ClasseMoyenne :
        switch (typeMonde) {
        case TypePlanete::MondeRuche : return "Classe moyenne";
        default : return "Classe moyenne";
        }
    case Influents :
        switch (typeMonde) {
        case TypePlanete::MondeRuche : return "Riche";
        default : return "Classe dominante";
        }
    case Maitres :
        switch (typeMonde) {
        case TypePlanete::MondeRuche : return "Noble";
        default : return "Classe dirigeante";
        }
    }
}
