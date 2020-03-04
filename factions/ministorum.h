#ifndef MINISTORUM_H
#define MINISTORUM_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

class AdepteMinistorum {
public:
    AdepteMinistorum() {
        DeterminerAffectation();
    }
    QString m_Fonction = "";
    QString m_Description = "";
    QString m_Image = "";

    void DeterminerAffectation();
    void DeterminerAffectationFonction();
    void DeterminerImage();
};

class MinistorumEvts : public GenerateurNoeudsProbables
{
public:
    MinistorumEvts(int indexEvt);

    static std::shared_ptr<Condition> AjouterConditionSiMinistorum();
    static std::shared_ptr<Condition> AjouterConditionSiCroyant();
    static std::shared_ptr<Condition> AjouterConditionSiCroyantEnEmpereur();
    static std::shared_ptr<Condition> AjouterConditionSiNiveauFoiSuperieurA(int niv);

    static void RafraichirPhrasesDeLaFoi(QString typePlanete, QString classeSociale, QString metier);

    // caracs
    static QString C_FONCTION;
    // valeur int approximant la foi du personnage dans sa religion (-10 = au bord de l'hérésie, +10 = fanatique)
    static QString C_FOI;
    static QString C_RELIGION; //"" = empereur
    // valeurs de C_POSTE
    static QString CONFESSEUR; // haut placé mais relativement mobile et indépendant
    static QString CONFESSEUR_ACOLYTE; // confesseur affecté à un inquisiteur
    static QString FRATERIS_MILITIA;
    // valeurs de C_RELIGION
    static QString ATHEE;

};

#endif // MINISTORUM_H
