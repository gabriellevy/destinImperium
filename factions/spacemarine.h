#ifndef SPACEMARINE_H
#define SPACEMARINE_H
#include <QString>
#include <QList>
#include <QVector>
#include "../types_planete/planet.h"

class SpaceMarine
{

    static int COMPTEUR;

public:

    SpaceMarine();

    static QVector<SpaceMarine*> CHAPITRES;
    static void GenererChapitres();

    QString m_Nom;
    QVector<QString> m_PlanetesRecrutement;

    // chapitres :
    static QString IMPERIAL_FIST;
};

#endif // SPACEMARINE_H
