#ifndef MONDERUCHE_H
#define MONDERUCHE_H

#include <QString>
#include <QMap>

class NoeudProbable;
class GenEvt;
class Effet;
class Condition;

/**
 * @brief événements liés aux mondes ruches
 */
class MondeRuche
{
    static int COMPTEUR;
public:
    MondeRuche();

    QString m_Nom = "";
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant l'événement
    Condition* m_ConditionSelecteurProba = nullptr; // proba d'exécution de cet événement
    QList<Condition*> m_Conditions; // éventuelle limitation bloquant ou activant l'exécution de cet événement
    QMap<QString, QString> m_ModificateursCaracs;
    std::function<void()> m_CallbackDisplay = nullptr;

    Effet* GenererEffet(GenEvt* genEvt);

    static void GenererNoeudsMondeRuche(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);



};

#endif // MONDERUCHE_H
