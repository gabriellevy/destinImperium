#include "pbsante.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "planet.h"

int PbSante::COMPTEUR = 0;
QString PbSante::PESTE = "Peste";
QString PbSante::SANTE = "Sante";
QString PbSante::MORT = "Mort";

PbSante::PbSante()
{
    switch (PbSante::COMPTEUR) {
    case 0 : {
        m_IdPbSante = MortVieillesse;
        m_Condition = new Condition(0.0);
        m_Intitule = "Vous êtes mort de vieillesse.";
        // déclenchable quand on vieillit (et de plus en plus probable au fur et à mesure)
        m_Condition->AjouterModifProba(0.02,
            {new Condition(GenVieHumain::AGE, "600", Comparateur::c_Superieur)});
        m_Condition->AjouterModifProba(0.1,
            {new Condition(GenVieHumain::AGE, "720", Comparateur::c_Superieur)});
        m_Condition->AjouterModifProba(1,
            {new Condition(GenVieHumain::AGE, "840", Comparateur::c_Superieur)});
        m_Condition->AjouterModifProba(2,
            {new Condition(GenVieHumain::AGE, "1020", Comparateur::c_Superieur)});
        m_Condition->AjouterModifProba(5,
            {new Condition(GenVieHumain::AGE, "1200", Comparateur::c_Superieur)});
        m_Condition->AjouterModifProba(0.5,
            {new Condition(PbSante::PESTE, "1", Comparateur::c_Egal)});
        m_ModificateursCaracs[PbSante::SANTE] = PbSante::MORT;

    }break;
    case 1 : {
        m_IdPbSante = PesteNoire;
        m_Condition = new Condition(0.0);
        m_Intitule = "Vous avez contracté la peste noire.";
        Planete::AjouterModifProbaSiMondeFeodal(m_Condition, 0.1);
        m_ModificateursCaracs[PbSante::PESTE] = "1";

    }break;
    }

    PbSante::COMPTEUR++;
}

void PbSante::GenererNoeudsSelectionPbSante(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    PbSante* pbSante = new PbSante();
    while ( pbSante->m_Intitule != "") {
        Effet* effetAffectation = genEvt->AjouterEffetNarration(
                    pbSante->m_Intitule,
                    pbSante->m_Image,
                    "pb_santé_" + pbSante->m_Intitule,
                    GenVieHumain::EVT_SELECTEUR);

        effetAffectation->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
        effetAffectation = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effetAffectation);

        // modificateurs de carac :
        QMapIterator<QString, QString> it(pbSante->m_ModificateursCaracs);
        while ( it.hasNext()) {
            it.next();
            effetAffectation->AjouterChangeurDeCarac(it.key(), it.value());
        }

        Condition* cond = pbSante->m_Condition;

        NoeudProbable* noeud = new NoeudProbable(
                    effetAffectation,
                    cond);

        noeuds.push_back(noeud);

        pbSante = new PbSante();
    }
}
