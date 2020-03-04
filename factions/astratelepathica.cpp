#include "astratelepathica.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "../types_planete/planet.h"
#include "warp/voyage.h"
#include "metier.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/exec/execeffet.h"
#include "socio_eco/economieevt.h"
#include "humain.h"
#include "texte/jourapresjour.h"
#include "humanite/pbsante.h"
#include "warp/psyker.h"

QString AstraTelepathica::C_LIEN_DES_AMES = "Lien des âmes";
QString AstraTelepathica::C_NIVEAU_APPRENTISSAGE = "Niveau apprentissage";

AstraTelepathica::AstraTelepathica(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = AstraTelepathica::C_LIEN_DES_AMES;
        m_ConditionSelecteurProba = make_shared<Condition>(0.3, p_Relative);
        m_Description = "à remplacer";
        m_Image = ":/images/warp/LienDesAmes.jpg";
        m_Conditions.push_back(AstraTelepathica::AjouterConditionSiScholasticaPsykana());
        m_Conditions.push_back(AstraTelepathica::AjouterConditionSiApprentissageSuperieurA(6));
        m_Conditions.push_back(make_shared<Condition>(AstraTelepathica::C_LIEN_DES_AMES, "", Comparateur::c_Egal));
        m_ModificateursCaracs[AstraTelepathica::C_LIEN_DES_AMES] = "1";
        m_CallbackDisplay = []{
            Humain* humain = Humain::GetHumainJoue();
            QString txt = "Vous subissez la terrible cérémonie du lien des âmes. "
                          "L'empereur vous transmet une infome partie de son inébranlable volonté pour vous donner la force de résister aux tentations démoniques.";
            // risques d'échecs ou de contrecoups
            int val = Aleatoire::GetAl()->EntierInferieurA(10);

            if ( val == 0) {
                // mort
                txt += "\n\nLe choc est trop fort. Vous mourrez le corps tordu de spasmes incontrollables.";
                humain->SetValeurACaracId(PbSante::C_SANTE, PbSante::MORT);
            } else if (val == 1) {
                // folie
                txt += "\n\nLe choc est trop fort. Votre esprit vacille dans la folie pour toujours.";
                humain->SetValeurACaracId(PbSante::C_SANTE, PbSante::FOLIE);
            } else if ( val < 4) {
                // perte de tous les sens
                txt += "\n\nLe choc est tel que vos nerfs sont brulés en de multiples points. "
                        "Vous pedez la quasi totalité de vos sens mais vos capacités psychiques vous permettront heureusement de surmonter ce handicap jusqu'à un certain point. "
                        "Le rituel est réussi, c'est tout ce qui compte.";
            } else if ( val < 8 ) {
                // aveugle (ok)
                txt += "\n\nLe choc est tel que vos nerfs sont brulés et que vous devenez aveugle. "
                        "C'est un lourd prix à payer mais vos ses psychiques vous permettront heureusement de surmonter ce handicap jusqu'à un certain point. "
                        "Le rituel est réussi, c'est tout ce qui compte.";
            } else {
                // réussite complète
                txt += "\n\nVotre volonté surhumaine fait des miracles. Le rituel est une réussite complète.";
            }

            ExecHistoire::GetExecEffetActuel()->GetEffet()->m_Texte = txt;
        };

    }break;
    case 1 : {
        m_Nom = "Apprentissage_AstraTelepathica";
        m_ConditionSelecteurProba = make_shared<Condition>(0.4, p_Relative);
        m_Description = "Vous faites de grands progrès dans l'utilisation de vos pouvoirs. ";
        m_Image = ":/images/warp/Primaris_Psyker2.jpg";
        m_Conditions.push_back(AstraTelepathica::AjouterConditionSiScholasticaPsykana());
        m_IncrementeursCaracs[AstraTelepathica::C_NIVEAU_APPRENTISSAGE] = 1;
    }break;
    case 2 : {
        m_Nom = "Diplome_AstraTelepathica";
        m_ConditionSelecteurProba = make_shared<Condition>(0.4, p_Relative);
        m_Description = "à remplacer ";
        m_Image = ":/images/warp/Primaris_Psyker2.jpg";
        m_Conditions.push_back(AstraTelepathica::AjouterConditionSiScholasticaPsykana());
        m_Conditions.push_back(AstraTelepathica::AjouterConditionSiApprentissageSuperieurA(9));
        m_ModificateursCaracs[Psyker::C_PSYKER] = Psyker::PSYKER_CONFIRME;
        m_CallbackDisplay = [] {
            AstraTelepathica::AffecterMetierPsyker();
        };
    }break;
    case 3 : {
        m_Nom = "Les fous sont sacrifiés";
        m_ConditionSelecteurProba = make_shared<Condition>(1.0, p_Relative);
        m_Description = "Votre esprit brisé n'est plus utilisable par l'Imperium. Vous êtes sacrifié à l'empereur. ";
        m_Conditions.push_back(Psyker::AjouterConditionSiPsyker());
        m_Conditions.push_back(make_shared<Condition>(PbSante::C_SANTE, PbSante::FOLIE, Comparateur::c_Egal));
        m_ModificateursCaracs[Psyker::C_RAPPORT_AU_GVT] = Psyker::SACRIFIABLE;
    }break;
    }

}

// version ultra simple à améliorer => potentiel :
// très jeune peut devenir archiviste
// inquisiteur
// chevalier gris...
void AstraTelepathica::AffecterMetierPsyker()
{
    Humain* humain = Humain::GetHumainJoue();
    ExecEffet* exec_effet = ExecHistoire::GetExecEffetActuel();
    QString texte = "Vous êtes arrivé au bout de la formation. Vous êtes maintenant un psyker reconnu et accept par l'Imperium. Un carrière glorieuse vous attend. ";
    QString metier = "";
    int val = Aleatoire::GetAl()->EntierInferieurA(2);
    if ( val == 0)
    {
        metier = Metier::ASTROPATHE;
        exec_effet->ChargerImage(":/images/metier/Astropathe.jpg");
        texte += "\n\nVous êtes affecté à la division des astropathes, chargés des communications psychiques interstellaires instantanées. "
                "Un travail extrêmement précieux pour l'Imperium mais épuisant pour l'esprit et le corps.";
        humain->SetValeurACaracId(PbSante::C_CONSTITUTION, PbSante::FRELE);
    }
    else if ( val == 1)
    {
        metier = Metier::PSYKER_PRIMARIS;
        texte += "\n\nVous êtes maintenant un psyker Primaris au service de la garde impériale.";
        exec_effet->ChargerImage(":/images/metier/Primaris_Psyker.jpg");
    }
    humain->SetValeurACaracId(Metier::C_METIER, metier);
    exec_effet->GetEffet()->m_Texte= texte;
}

shared_ptr<Condition> AstraTelepathica:: AjouterConditionSiScholasticaPsykana()
{    return make_shared<Condition>(Metier::C_METIER, Metier::SCHOLIA_PSYKANA, Comparateur::c_Egal);}

shared_ptr<Condition> AstraTelepathica::AjouterConditionSiApprentissageSuperieurA(int val)
{    return make_shared<Condition>(AstraTelepathica::C_NIVEAU_APPRENTISSAGE, QString::number(val), Comparateur::c_Superieur);}

void AstraTelepathica::RafraichirPhrasesScholasticaPsykana(QString /*typePlanete*/, QString /*classeSociale*/)
{
    Humain* hum = Humain::GetHumainJoue();
    if ( hum->GetValeurCarac(Psyker::C_PSYKER) == Psyker::POTENTIEL_PSY)
    {

    }
}
