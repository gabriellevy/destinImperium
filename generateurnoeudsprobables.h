#ifndef GENERATEURNOEUDSPROBABLES_H
#define GENERATEURNOEUDSPROBABLES_H

#include "../destinLib/selectionneurdenoeud.h"
#include <QString>
#include <QMap>

class GenEvt;
class Effet;
class Condition;


class GenerateurNoeudsProbables
{
public:
    GenerateurNoeudsProbables(int indexEvt);
    virtual ~GenerateurNoeudsProbables(){}

    QString m_Nom = "";
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant le métier
    Condition* m_ConditionSelecteurProba = nullptr; // proba d'exécution de cet événement
    QList<Condition*> m_Conditions; // éventuelle limitation bloquant ou activant l'exécution de cet événement
    QMap<QString, QString> m_ModificateursCaracs;
    QMap<QString, int> m_IncrementeursCaracs;

    std::function<void()> m_CallbackDisplay = nullptr;

    virtual Effet* GenererEffet(GenEvt* genEvt);

};

#endif // GENERATEURNOEUDSPROBABLES_H
