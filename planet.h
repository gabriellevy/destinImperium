#ifndef PLANET_H
#define PLANET_H

#include <QString>
#include <QList>
#include <QVector>

class NoeudProbable;
class GenEvt;

class Planete
{
    static int COMPTEUR;

public:
    Planete();

    QString m_Nom;
    double m_Population;// en millions

    static QList<Planete*> PLANETES;
    static QVector<NoeudProbable*> ConstruireToutePlanetes(GenEvt* genEvt);
};

#endif // PLANET_H
