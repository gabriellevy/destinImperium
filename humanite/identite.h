#ifndef IDENTITE_H
#define IDENTITE_H

#include <QString>
#include <QVector>

/**
 * @brief ce qui concerne les bases de l'identité du personnage à la naissance
 */
class Identite
{
public:
    static QVector<QString> PRENOMS;
    static QVector<QString> PRENOMS_FEMININS;
    static QVector<QString> NOMS;

    static QString CreerPatronyme(bool male = true);
};

#endif // IDENTITE_H
