#ifndef MONDEFORGE_H
#define MONDEFORGE_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

/**
 * @brief événements liés aux mondes forges
 */
class MondeForge : public GenerateurNoeudsProbables
{
public:
    MondeForge(int indexEvt);

    static void RafraichirPhrases(); // phrases d'ambiance
};

#endif // MONDEFORGE_H
