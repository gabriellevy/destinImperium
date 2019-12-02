#ifndef JOURAPRESJOUR_H
#define JOURAPRESJOUR_H

#include <QString>
#include <QVector>

/**
 * @brief Génération des textes à afficher quand il n'arrive rien au joueur, et ce en fonction de son état actuel
 * (socio économique, métier, planète...)
 */
class JourApresJour
{
    static QVector<QString> PHRASES;
public:
    static void RafraichirPhrases();

    static QString ExtrairePhrase();

};

#endif // JOURAPRESJOUR_H
