#ifndef SECTECHAOS_H
#define SECTECHAOS_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

/**
 * @brief événements de sectes du chaos
 */
class SecteChaos : public GenerateurNoeudsProbables
{
public:
    SecteChaos(int indexEvt);

    static QPair<QString, QString>  DeterminerDieuVenere();

    static Condition* AjouterConditionSiLepreDeNurgle();
    static Condition* AjouterConditionSiSecte();
    static Condition* AjouterConditionSiPasSecte();
    static Condition* AjouterConditionSiInfluenceChaosSuperieurA(int nivInfluence);
    static Condition* AjouterModificateurProbaSiInfluenceChaosSuperieurA(Condition* condProba, int nivInfluence, double modifProba);
    static Condition* AjouterModificateurProbaSiPuissanceSecteSuperieurA(Condition* condProba, int nivInfluence, double modifProba);
    static Condition* AjouterModificateurProbaSiDetectionSecteSuperieurA(Condition* condProba, int nivInfluence, double modifProba);
    static Condition* AjouterConditionSiMutationsSuperieurA(int nivMutation);

    static void RafraichirPhrases(); // phrases d'ambiance

    // caracs :
    // int augmentant quand le chaos gagne de l'influence sur vous.
    // Il augmente les risques de rejoindre une secte, d'être possédé, d'être jugé hérétique...
    static QString C_INFLUENCE_CHAOS;
    static QString C_MUTATIONS; // int allant de 1 (très légère miutation à peine visible à 20 (enfant du chaos)
    static QString C_PUISSANCE_SECTE;
    // int augmentant quand les autorités détectent la secte => plus de 5 devient dangereux
    static QString C_DETECTION_SECTE;
    static QString C_SECTE_CHAOS; // "1" = on en fait partie
    static QString C_DIEU; // dieu vénéré
    // valeurs caracs
    static QString KHORNE;
    static QString TZEENTCH;
    static QString SLAANESH;
    static QString NURGLE;
    // valeurs de PbSante::SANTE liées à Nurgle
    static QString LEPRE_DE_NURGLE;


};

#endif // SECTECHAOS_H
