#include "planet.h"
//#include "../destinLib/noeudnarratif.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"

int Planete::COMPTEUR = 0;
QList<Planete*> Planete::PLANETES = {};

Planete::Planete()
{
    m_Nom = "";
    m_Population = -1;

    switch (Planete::COMPTEUR) {
    case 0 : {
        m_Nom = "Terre";
        m_Population = 100000000;
    }break;
    case 1 : {
        m_Nom = "Youpi";
        m_Population = 5;
    }break;
    }

    Planete::COMPTEUR++;
}
QVector<NoeudProbable*> Planete::ConstruireToutePlanetes(GenEvt* genEvt)
{
    QVector<NoeudProbable*> effetPlanetes;
    Planete* planete = new Planete();
    while ( planete->m_Population > 0) {
        Planete::PLANETES.push_back(planete);

        NoeudProbable* noeud = new NoeudProbable(
                    genEvt->AjouterEffetNarration(
                        "Vous êtes nés sur " + planete->m_Nom, "",
                        "planete_" + planete->m_Nom),
                    new Condition(planete->m_Population));

        effetPlanetes.push_back(noeud);

        planete = new Planete();
    }

    return effetPlanetes;
}
