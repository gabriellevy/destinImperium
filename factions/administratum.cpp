#include "administratum.h"
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
#include "../destinLib/execeffet.h"
#include "texte/jourapresjour.h"
#include "humain.h"
#include "../destinLib/aleatoire.h"

// ids :
QString Administratum::ID_AFFECTATION_DIVISION = "Affectation Division";

// sous-divisions
QString Administratum::C_DIVISION = "Division Administratum";
QString Administratum::C_BUREAU_MUNITORUM = "Bureau du Munitorum";
// valeurs de C_DIVISION
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

// grades
QString Administratum::C_RANG = "Rang administratum";
QString Administratum::GRADE_SCRIBE = "Scribe";
QString Administratum::GRADE_ORDINATE = "Ordinate";
QString Administratum::GRADE_PREFET = "Préfet";
QString Administratum::GRADE_MAITRE = "Maître";

void Administratum::AffecterBureauMunitorum()
{
    int index = Aleatoire::GetAl()->EntierInferieurA(DivisionAdministratum::BUREAU_MUNITORUM.length());
    Humain* humain = Humain::GetHumainJoue();
    humain->SetValeurACaracId(Administratum::C_BUREAU_MUNITORUM,
                              DivisionAdministratum::BUREAU_MUNITORUM[index].first);
    QString texte = DivisionAdministratum::BUREAU_MUNITORUM[index].second;
    QString imgPath = "";
    ExecEffet* execEffet = ExecHistoire::GetExecEffetActuel();

    execEffet->GetEffet()->m_Texte = texte;
    if ( imgPath != "" )
        execEffet->ChargerImage(imgPath);
}

Administratum::Administratum(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = Administratum::ID_AFFECTATION_DIVISION;
        m_ConditionSelecteurProba = new Condition(0, p_Pure);
        Administratum::AjouterModifProbaSiADivision(m_ConditionSelecteurProba, -1);
        Administratum::AjouterModifProbaSiAdepteAdministratum(m_ConditionSelecteurProba, 0.1);
        m_ModificateursCaracs[Administratum::C_RANG] = Administratum::GRADE_SCRIBE;

    }break;
    case 1 : {
        m_Nom = Administratum::GRADE_ORDINATE;
        m_ConditionSelecteurProba = new Condition(0, p_Relative);
        m_ModificateursCaracs[Administratum::C_RANG] = Administratum::GRADE_ORDINATE;
        m_Image = ":/images/metier/Metallic_Scribe.jpg";
        m_Description = "Vous avez l'insigne honneur de devenir Ordinate mécaniquement augmenté.";
        Administratum::AjouterModifProbaSiScribeAdministratum40Ans(m_ConditionSelecteurProba, 0.15);

    }break;
    case 2 : {
        m_Nom = Administratum::GRADE_PREFET;
        m_ConditionSelecteurProba = new Condition(0, p_Relative);
        m_ModificateursCaracs[Administratum::C_RANG] = Administratum::GRADE_PREFET;
        m_Image = ":/images/metier/Prefet.jpg";
        m_Description = "Vous avez l'insigne honneur de devenir Préfet de l'Administratum.";
        Administratum::AjouterModifProbaSiOrdinateAdministratum50Ans(m_ConditionSelecteurProba, 0.05);

    }break;
    case 3 : {
        m_Nom = Administratum::GRADE_MAITRE;
        m_ConditionSelecteurProba = new Condition(0, p_Relative);
        m_ModificateursCaracs[Administratum::C_RANG] = Administratum::GRADE_MAITRE;
        m_Image = ":/images/metier/Maitre.jpg";
        m_Description = "Vous avez l'insigne honneur de devenir Maître de votre division.";
        Administratum::AjouterModifProbaSiScribeAdministratum40Ans(m_ConditionSelecteurProba, 0.01);

    }break;
    case 4 : {
        m_Nom = "Approvisionnement régiment";
        m_ConditionSelecteurProba = new Condition(0, p_Relative);
        m_ModificateursCaracs[Administratum::C_RANG] = Administratum::GRADE_MAITRE;
        m_Image = ":/images/metier/Maitre.jpg";
        m_Description = "Vous avez l'insigne honneur de devenir Maître de votre division.";
        Administratum::AjouterModifProbaSiScribeAdministratum40Ans(m_ConditionSelecteurProba, 0.01);

    }break;
    case 5 : {
        m_Nom = "Affectation à un bureau du departmento Munitorum";
        m_ConditionSelecteurProba = new Condition(0.1, p_Relative);
        m_Description = "???? munitorum ????";
        m_Conditions.push_back(new Condition(Administratum::C_BUREAU_MUNITORUM, "", Comparateur::c_Egal));
        m_Conditions.push_back(new Condition(Administratum::C_DIVISION, Administratum::DEPARTMENTO_MUNITORUM, Comparateur::c_Egal));
        m_CallbackDisplay = [] {
            Administratum::AffecterBureauMunitorum();
        };
    }break;
    }
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
         new Condition(Metier::C_METIER, Metier::ADEPTE_ADMINISTRATUM, Comparateur::c_Egal)
        });
    return cond;
}

Condition* Administratum::AjouterModifProbaSiScribeAdministratum40Ans(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(GenVieHumain::AGE, "400", Comparateur::c_Superieur),
         new Condition(Metier::C_METIER, Metier::ADEPTE_ADMINISTRATUM, Comparateur::c_Egal),
         new Condition(Administratum::C_RANG, Administratum::GRADE_SCRIBE, Comparateur::c_Egal)
        });
    return cond;
}

Condition* Administratum::AjouterModifProbaSiOrdinateAdministratum50Ans(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(GenVieHumain::AGE, "520", Comparateur::c_Superieur),
         new Condition(Metier::C_METIER, Metier::ADEPTE_ADMINISTRATUM, Comparateur::c_Egal),
         new Condition(Administratum::C_RANG, Administratum::GRADE_ORDINATE, Comparateur::c_Egal)
        });
    return cond;
}

Condition* Administratum::AjouterModifProbaSiPrefetAdministratum60Ans(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {new Condition(GenVieHumain::AGE, "640", Comparateur::c_Superieur),
         new Condition(Metier::C_METIER, Metier::ADEPTE_ADMINISTRATUM, Comparateur::c_Egal),
         new Condition(Administratum::C_RANG, Administratum::GRADE_PREFET, Comparateur::c_Egal)
        });
    return cond;
}

void Administratum::RafraichirPhrases()
{
    Humain* humain = Humain::GetHumainJoue();
    QString division = humain->GetValeurCarac(Administratum::C_DIVISION);

    if ( division == Administratum::DEPARTMENTO_MUNITORUM)
    {
        JourApresJour::PHRASES.push_back(
            Phrase("Vous réquisitionnez le tribut habituel."));
        JourApresJour::PHRASES.push_back(
            Phrase("Vous recevez une demande d'assistance militaire mais elle est mal formulée. Demande rejetée."));
        JourApresJour::PHRASES.push_back(
            Phrase("Vous mettez à jour les demandes de ravitaillement du secteur. Plusieurs sont encore d'actualité."));
        JourApresJour::PHRASES.push_back(
            Phrase("Un vaisseau de renforts a été perdu dans le warp. Vous en réquisitionnez un nouveau."));
        JourApresJour::PHRASES.push_back(
            Phrase("Les troupes du secteur sont en déficit d'alcool et risquent de se mutiner. Vous vous êtes chargé d'accélérer la réquisition de liqueurs locales."));
        JourApresJour::PHRASES.push_back(
            Phrase("Les fournitures médicales sont en tel déficit que les hommes meurent des suites dinfections bénignes. Il faut réquisitionner des stocks supplémentaires."));
        JourApresJour::PHRASES.push_back(
            Phrase("Tout se passe bien, les campagnes suivent leur cours."));
    }
    JourApresJour::PHRASES.push_back(
        Phrase("Le serviteur Calligraphus de la division de la division est en panne. Vous avez des dizaines de documents à copier."));

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
        effet = GenerateurNoeudsProbables::GenererEffet(genEvt);
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

QString Administratum::OFFICIO_TACTICA = "Officio Tactica";
QString Administratum::BUREAU_COMMISSAIRE = "Bureau du commissaire de bord";
QString Administratum::BUREAU_ENREGISTREMENT = "Bureau d'enregistrement";
QString Administratum::SCHOLA_PROGENIUM = "Schola Progenium";
QString Administratum::CORPS_EVALUATION = "Corps d'évaluation";
QString Administratum::COMMISSARIAT = "Commissariat";
QString Administratum::CORPS_INGENIEUR = "Corps des ingénieurs";
QString Administratum::CORPS_EXECUTION = "Corps d'exécution";
QString Administratum::CORPS_SAPEURS = "Corps des sapeurs";
QString Administratum::CORPS_PIONNIERS = "Corps des pionniers";
QString Administratum::CORPS_SIEGE = "Corps des auxiliaires de siège";

QVector<QPair<QString, QString>> DivisionAdministratum::BUREAU_MUNITORUM = {
    QPair<QString, QString>(Administratum::OFFICIO_TACTICA,
        "Vous faites maintenant partie de l'Officio Tactica, chargé de la logistique des zones de guerre."),
    QPair<QString, QString>(Administratum::BUREAU_COMMISSAIRE,
        "Vous êtes maintenant chargé de tenir les comptes et les enregistrements de l'astra militarum."),
    QPair<QString, QString>(Administratum::BUREAU_ENREGISTREMENT,
        "Vous êtes maintenant membre du bureau d'enregistrement administratif de toutes les actions de l'astra militarum."),
    QPair<QString, QString>(Administratum::SCHOLA_PROGENIUM,
        "Vous êtes chargé de gérer la Scholia Progenium, l'école des orphelins de guerre de l'Imperium."),
    QPair<QString, QString>(Administratum::CORPS_EVALUATION,
        "Vous êtes chargé d'évaluer les agents de l'administratum et leur incorruptibilité."),
    QPair<QString, QString>(Administratum::COMMISSARIAT,
        "Vous êtes chargé du recrutement et de la gestion des commissaires."),
    QPair<QString, QString>(Administratum::CORPS_INGENIEUR,
        "Vous faites partie du corps des ingénieur. Vous devez entretenir et préparer les machines avant qu'elles soient utilisées au front."),
    QPair<QString, QString>(Administratum::CORPS_EXECUTION,
        "Vous êtes chargé de la surveillance des troupes, en particulier de la lutte contre la corruption."),
    QPair<QString, QString>(Administratum::CORPS_SAPEURS,
        "Vous gérez la construction des bases arrières, stations spatiales, aéroports, et toutes les autres installations complexes nécessaires pour mener la guerre."),
    QPair<QString, QString>(Administratum::CORPS_PIONNIERS,
        "Vous faites partie du corps des pionniers. Votre travail est de préparer les planètes à l'arrivée de l'astra militarum."),
    QPair<QString, QString>(Administratum::CORPS_SIEGE,
        "Vous êtes recruté par le corps de siège. Vous devez construire les machines et fortifications qui permettront de prendre des installations ou au contraire de les défendre.")
};

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
