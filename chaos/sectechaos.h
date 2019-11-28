#ifndef SECTECHAOS_H
#define SECTECHAOS_H

#include <QString>
#include <QMap>
#include "../types_planete/planet.h"

class NoeudProbable;
class GenEvt;
class Effet;
class Condition;

/**
 * @brief événements de sectes du chaos
 */
class SecteChaos
{
    static int COMPTEUR;
public:
    SecteChaos();

    QString m_Nom = "";
    QString m_Description = "";
    QString m_Image = ""; // chemin vers une éventuelle image représentant l'événement
    Condition* m_Condition = nullptr;
    QMap<QString, QString> m_ModificateursCaracs;
    std::function<void()> m_CallbackDisplay = nullptr;

    Effet* GenererEffet(GenEvt* genEvt);

    static void GenererNoeudsSecteChaos(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

    // caracs :
    static QString C_SECTE_CHAOS;
    static QString C_DIEU; // dieu vénéré
    // valeurs caracs
    static QString KHORNE;
    static QString TZEENTCH;
    static QString SLAANESH;
    static QString NURGLE;

};

#endif // SECTECHAOS_H
