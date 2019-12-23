#ifndef ASTRATELEPATHICA_H
#define ASTRATELEPATHICA_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;


class AstraTelepathica : public GenerateurNoeudsProbables
{
public:
    AstraTelepathica(int indexEvt);

    static Condition* AjouterConditionSiScholasticaPsykana();
    static Condition* AjouterConditionSiApprentissageSuperieurA(int val);

    static void AffecterMetierPsyker();

    static void RafraichirPhrasesScholasticaPsykana(QString typePlanete, QString classeSociale);

    // caracs
    static QString C_LIEN_DES_AMES; // 1 = rituel terminé
    static QString C_NIVEAU_APPRENTISSAGE; // int : 10 = formation réussie
};

#endif // ASTRATELEPATHICA_H
