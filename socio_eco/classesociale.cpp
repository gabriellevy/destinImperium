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

QString ClasseSociale::ID_CLASSE_SOCIALE = "Classe sociale";


e_ClasseSociale ClasseSociale::GetClasseSocialeAleatoire(QString typeMonde)
{
    double proba = Aleatoire::GetAl()->Entre0Et1();
    if (typeMonde == Planete::PLANETE_RUCHE) {
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
    } else {
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


QString ClasseSociale::MISERABLES = "Misérable";
QString ClasseSociale::PAUVRES = "Pauvre";
QString ClasseSociale::CLASSE_MOYENNE = "Classe moyenne";
QString ClasseSociale::INFLUENTS = "Classe dominante";
QString ClasseSociale::MAITRES = "Classe dirigeante";

QString ClasseSociale::GetClasseSocialeAsStr(e_ClasseSociale classeSociale, QString typeMonde)
{
    switch (classeSociale) {
    case Miserable :
        return ClasseSociale::MISERABLES;
    case Pauvre :
        return ClasseSociale::PAUVRES;
    case ClasseMoyenne :
        return ClasseSociale::CLASSE_MOYENNE;
    case Influents :
        return ClasseSociale::INFLUENTS;
    case Maitres :
        return ClasseSociale::MAITRES;
    }
}
