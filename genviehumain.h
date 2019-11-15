#ifndef GENVIEHUMAIN_H
#define GENVIEHUMAIN_H

#include "../destinLib/genhistoire.h"

class Imperium;

using namespace std;

class GenVieHumain : public GenHistoire
{
public:
    GenVieHumain();

    virtual Hist* GenererHistoire();

    static GenVieHumain* GetGenVieHumain();

    const static int CHRONO = 1000; // nombre de ms entre chaque effet
protected:
    // génère toutes les caracs qui peuvent être visualisées par le joueur (d'autres caracs peuvent être générées et invisibles n'importe quand dans l'aventure)
    virtual void GenererCaracs();
    virtual void GenererPersos();

private:
    // génération des événement et effets de base
    void GenererEvtsAccueil();

};

#endif // GENVIEHUMAIN_H
