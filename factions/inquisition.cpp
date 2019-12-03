#include "inquisition.h"
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


int Inquisition::COMPTEUR = 0;

QString Inquisition::C_ORDO = "Ordo";

QString Inquisition::ORDO_XENOS = "Ordo Xenos";
QString Inquisition::ORDO_MALLEUS = "Ordo Malleus";
QString Inquisition::ORDO_HERETICUS = "Ordo Hereticos";
QString Inquisition::ORDO_MACHINUM = "Ordo Machinum";
QString Inquisition::ORDO_MILITUM = "Ordo Militum";
QString Inquisition::ORDO_OBSULETUS = "Ordo Obsuletus";
QString Inquisition::ORDO_ORIGINATUS = "Ordo Originatus";
QString Inquisition::ORDO_REDACTUS = "Ordo Redactus";
QString Inquisition::ORDO_SCRIPTORUM = "Ordo Scriptarum";
QString Inquisition::ORDO_SEPULTURUM = "Ordo Sepulturum";
QString Inquisition::ORDO_SICARIUS = "Ordo Sicarius";

// ids :
QString Inquisition::ID_AFFECTATION_ORDO = "Affectation Ordo";

Inquisition::Inquisition()
{
    switch (Inquisition::COMPTEUR) {
    case 0 : {
        m_Nom = Inquisition::ID_AFFECTATION_ORDO;
        m_ConditionSelecteurProba = new Condition(0, p_Pure);
        Inquisition::AjouterModifProbaSiAOrdo(m_ConditionSelecteurProba, -1);
        Inquisition::AjouterModifProbaSiInquisiteur(m_ConditionSelecteurProba, 0.1);
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
         new Condition(Metier::C_METIER, Metier::INQUISITEUR, Comparateur::c_Egal)
        });
    return cond;
}

Effet* Inquisition::GenererEffet(GenEvt* genEvt)
{
    Effet* effet = nullptr;
    if ( m_Nom == Inquisition::ID_AFFECTATION_ORDO) {
        // sélectionneur d'effets
        QVector<NoeudProbable*> noeudsAffectation;
        Ordo::GenererNoeudsAffectation(genEvt, noeudsAffectation);
        effet = genEvt->AjouterEffetSelecteurDEvt(
                    noeudsAffectation,
                    Inquisition::ID_AFFECTATION_ORDO,
                    "",
                    GenVieHumain::EVT_SELECTEUR);
    } else {
        // système de création d'effets de base :
        effet = genEvt->AjouterEffetNarration(
            m_Description,
            m_Image,
            "evt_inquisition_" + m_Nom, GenVieHumain::EVT_SELECTEUR);
        effet->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
        effet = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet);
    }
    effet->m_Conditions = m_Conditions;

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

        Condition* cond = evt->m_ConditionSelecteurProba;

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
    case 3 : {
        m_Nom = Inquisition::ORDO_MACHINUM;
        m_Condition = new Condition(0.05, p_Relative);
        m_Description = "Vous avez été assigné à l'Ordo Machinum. "
                "Vous êtes chargé de surveiller l'Adeptus Mechanicus et leurs découvertes d'archéotechnologie.";
    }break;
    case 4 : {
        m_Nom = Inquisition::ORDO_MILITUM;
        m_Condition = new Condition(0.05, p_Relative);
        m_Description = "Vous avez été assigné à l'Ordo Militum. "
                "Vous êtes chargé de surveiller les branches armées de l'Imperium.";
    }break;
    case 5 : {
        m_Nom = Inquisition::ORDO_OBSULETUS;
        m_Condition = new Condition(0.05, p_Relative);
        m_Description = "Vous avez été assigné à l'Ordo Obsuletus. "
                "Vous êtes chargé de repérer et analyser les phénomènes inexpliqués, pour déterminer si il s'agit de miracles de l'empereur ou des pièges des xenos ou du chaos.";
    }break;
    case 6 : {
        m_Nom = Inquisition::ORDO_ORIGINATUS;
        m_Condition = new Condition(0.01, p_Relative);
        m_Description = "Vous avez été assigné à l'Ordo Originatus. "
                "Vous devez enquêter sur l'histoire et la corriger en triant le mythe de la réalité.";
    }break;
    case 7 : {
        m_Nom = Inquisition::ORDO_REDACTUS;
        m_Condition = new Condition(0.01, p_Relative);
        m_Description = "Vous avez été assigné à l'Ordo Redactus. "
                "Vous devez obscurcir et mythifier l'histoire pour confondre les ennemis de l'imperium et les empêcher de s'en servir pour vous combattre.";
    }break;
    case 8 : {
        m_Nom = Inquisition::ORDO_SCRIPTORUM;
        m_Condition = new Condition(0.01, p_Relative);
        m_Description = "Vous avez été assigné à l'Ordo Scriptorum. "
                "Vous devez surveiller et corriger les enregistrements et communiqués de l'Adeptus Ministorum.";
    }break;
    case 9 : {
        m_Nom = Inquisition::ORDO_SEPULTURUM;
        m_Condition = new Condition(0.01, p_Relative);
        m_Description = "Vous avez été assigné à l'Ordo Sepulturum, "
                "la branche chargée de gérer les diverses menaces zombies.";
    }break;
    case 10 : {
        m_Nom = Inquisition::ORDO_SICARIUS;
        m_Condition = new Condition(0.01, p_Relative);
        m_Image = ":/images/metier/inquisiteur_ordo_sicarius.jpg";
        m_Description = "Vous avez été assigné à l'Ordo Sicarius, "
                "la branche chargée de surveiller les activités de l'iOfficio Assassinorum.";
    }break;
    }
    m_ModificateursCaracs[Inquisition::C_ORDO] = m_Nom;

    Ordo::COMPTEUR++;
}

void Ordo::GenererNoeudsAffectation(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    for (int i = 0; i < Ordo::ORDOS.length() ; ++i) {
        Ordo* ordo = ORDOS[i];
        Effet* effet = genEvt->AjouterEffetNarration(
            ordo->m_Description,
            ordo->m_Image,
            "affectation_ordo_inquisition_" + ordo->m_Nom, GenVieHumain::EVT_SELECTEUR);
        effet->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
        effet = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet);
        effet->AjouterChangeurDeCarac(Inquisition::C_ORDO, ordo->m_Nom);

        Condition* cond = ordo->m_Condition;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

    }
}

