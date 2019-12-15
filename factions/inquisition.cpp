#include "inquisition.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "../types_planete/planet.h"
#include "warp/voyage.h"
#include "metier.h"
#include "../destinLib/effet.h"
#include "socio_eco/crime.h"
#include "humanite/pbsante.h"
#include "warp/psyker.h"

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

Inquisition::Inquisition(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmp_Modificateur = 0.0;
    switch (indexEvt) {
    case 0 : {
        m_Nom = Inquisition::ID_AFFECTATION_ORDO;
        m_ConditionSelecteurProba = new Condition(0, p_Pure);
        //m_ModificateursCaracs[Inquisition::RANG] = Administratum::GRADE_SCRIBE;

        m_Conditions = {
            new Condition(Metier::C_METIER, Metier::INQUISITEUR, Comparateur::c_Egal),
            new Condition(Inquisition::C_ORDO, "", Comparateur::c_Egal)
        };

    }break;
    case 1 : {
        m_Nom = "Exécuté par l'ordo Hereticus";
        m_ConditionSelecteurProba = new Condition(0.05 + tmp_Modificateur, p_Relative);
        m_Description = "L'Ordo Hereticus vous juge trop instable pour être gardé en vie mais vous accordent néanmoins un grand honneur. "
                "Vous êtes convoyé par les vaisseaux noirs de l'inquisition jusqu'au Trône d'Or de l'Empereur et lui êtes sacrifié pour nourrir son esprit en perpétuelle souffrance.";
        m_Image = ":/images/warp/god-emperor.jpg";
        m_Conditions.push_back(
                    new Condition(GenVieHumain::C_LIBERTE,
                                  Crime::CAPTURE_ORDO_HERETICUS,
                                  Comparateur::c_Egal));
        m_Conditions.push_back(Psyker::AjouterConditionSiPsyker());
        m_ModificateursCaracs[PbSante::C_SANTE] = PbSante::MORT;

    }break;
    case 2 : {
        m_Nom = "Renvoyé à la justice par l'ordo Hereticus";
        m_ConditionSelecteurProba = new Condition(0.05 + tmp_Modificateur, p_Relative);
        m_Description = "L'Ordo Hereticus vous juge non coupable d'hérésie mais pas innocent pour autant. "
                "Vous êtes déféré à la justice planétaire traditionelle";
        m_Image = ":/images/inquisition/OrdoHereticus_Inquisitor.jpg";
        m_Conditions.push_back(
                    new Condition(GenVieHumain::C_LIBERTE,
                                  Crime::CAPTURE_ORDO_HERETICUS,
                                  Comparateur::c_Egal));
        m_Conditions.push_back(Psyker::AjouterConditionSiNonPsyker());
        m_ModificateursCaracs[GenVieHumain::C_LIBERTE] = Crime::CAPTURE_POLICE;

    }break;
    }

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
        m_ConditionSelecteurProba = new Condition(0.4, p_Relative);
        m_Image = ":/images/metier/inquisiteur_ordo_xenos.jpg";
        m_Description = "Vous avez été assigné à l'Ordo Xenos, "
                "les exterminateurs d'extra-terrestres.";
    }break;
    case 1 : {
        m_Nom = Inquisition::ORDO_MALLEUS;
        m_ConditionSelecteurProba = new Condition(0.4, p_Relative);
        m_Image = ":/images/metier/inquisiteur_ordo_malleus.png";
        m_Description = "Vous avez été assigné à l'Ordo Malleus. "
                "Vous êtes un chasseur de démons.";
    }break;
    case 2 : {
        m_Nom = Inquisition::ORDO_HERETICUS;
        m_ConditionSelecteurProba = new Condition(0.4, p_Relative);
        m_Image = ":/images/metier/inquisiteur_ordo_hereticus.jpg";
        m_Description = "Vous avez été assigné à l'Ordo Hereticus. "
                "Vous êtes chargé d'éliminer les psykers, les traîtres et les hérétiques.";
    }break;
    case 3 : {
        m_Nom = Inquisition::ORDO_MACHINUM;
        m_ConditionSelecteurProba = new Condition(0.05, p_Relative);
        m_Description = "Vous avez été assigné à l'Ordo Machinum. "
                "Vous êtes chargé de surveiller l'Adeptus Mechanicus et leurs découvertes d'archéotechnologie.";
    }break;
    case 4 : {
        m_Nom = Inquisition::ORDO_MILITUM;
        m_ConditionSelecteurProba = new Condition(0.05, p_Relative);
        m_Description = "Vous avez été assigné à l'Ordo Militum. "
                "Vous êtes chargé de surveiller les branches armées de l'Imperium.";
    }break;
    case 5 : {
        m_Nom = Inquisition::ORDO_OBSULETUS;
        m_ConditionSelecteurProba = new Condition(0.05, p_Relative);
        m_Description = "Vous avez été assigné à l'Ordo Obsuletus. "
                "Vous êtes chargé de repérer et analyser les phénomènes inexpliqués, pour déterminer si il s'agit de miracles de l'empereur ou des pièges des xenos ou du chaos.";
    }break;
    case 6 : {
        m_Nom = Inquisition::ORDO_ORIGINATUS;
        m_ConditionSelecteurProba = new Condition(0.01, p_Relative);
        m_Description = "Vous avez été assigné à l'Ordo Originatus. "
                "Vous devez enquêter sur l'histoire et la corriger en triant le mythe de la réalité.";
    }break;
    case 7 : {
        m_Nom = Inquisition::ORDO_REDACTUS;
        m_ConditionSelecteurProba = new Condition(0.01, p_Relative);
        m_Description = "Vous avez été assigné à l'Ordo Redactus. "
                "Vous devez obscurcir et mythifier l'histoire pour confondre les ennemis de l'imperium et les empêcher de s'en servir pour vous combattre.";
    }break;
    case 8 : {
        m_Nom = Inquisition::ORDO_SCRIPTORUM;
        m_ConditionSelecteurProba = new Condition(0.01, p_Relative);
        m_Description = "Vous avez été assigné à l'Ordo Scriptorum. "
                "Vous devez surveiller et corriger les enregistrements et communiqués de l'Adeptus Ministorum.";
    }break;
    case 9 : {
        m_Nom = Inquisition::ORDO_SEPULTURUM;
        m_ConditionSelecteurProba = new Condition(0.01, p_Relative);
        m_Description = "Vous avez été assigné à l'Ordo Sepulturum, "
                "la branche chargée de gérer les diverses menaces zombies.";
    }break;
    case 10 : {
        m_Nom = Inquisition::ORDO_SICARIUS;
        m_ConditionSelecteurProba = new Condition(0.01, p_Relative);
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
        effet->m_Conditions = ordo->m_Conditions;
        effet->AjouterChangeurDeCarac(Inquisition::C_ORDO, ordo->m_Nom);

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    ordo->m_ConditionSelecteurProba);

        noeuds.push_back(noeud);

    }
}

