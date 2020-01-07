#ifndef CLASSESOCIALE_H
#define CLASSESOCIALE_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

/**
 * @brief événements liés à la classe sociale des personnages
 */
class ClasseSociale : public GenerateurNoeudsProbables
{
public:
    ClasseSociale(int indexEvt);

    static Condition* AjouterConditionSiCetteClasseSociale(QString classeSociale);

    static QString GetClasseSocialeAleatoire(QString typeMonde);

    // caracs :
    static QString C_CLASSE_SOCIALE; // noté de 0(misérable) à 4 (seigneurs de planètes)
    // valeurs de caracs :
    static QString MISERABLES; // dépourvus de logement et de métier, mendiants...
    static QString PAUVRES; // travaillerrs non qualifiés
    static QString CLASSE_MOYENNE;// travailleurs qualifiés
    static QString INFLUENTS; // commerçants, financiers, trafiqueurs d'inflence
    static QString MAITRES; // gouverneurs impériaux, maîtres de la ruche, planète etc..

};

#endif // CLASSESOCIALE_H
