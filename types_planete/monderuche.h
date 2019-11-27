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
    Condition* m_Condition = nullptr;
    QMap<QString, QString> m_ModificateursCaracs;

    Effet* GenererEffet(GenEvt* genEvt);

    static void GenererNoeudsMondeRuche(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);



};

#endif // MONDERUCHE_H
