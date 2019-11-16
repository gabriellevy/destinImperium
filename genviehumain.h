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

    const static int CHRONO = 5000; // nombre de ms entre chaque effet

    // caracs :
    static QString PLANETE;
    static QString AGE;
protected:
    // génère toutes les caracs qui peuvent être visualisées par le joueur (d'autres caracs peuvent être générées et invisibles n'importe quand dans l'aventure)
    virtual void GenererCaracs();
    virtual void GenererPersos();
    void GenererDataUnivers();

private:
    // génération des événement et effets de base
    void GenererEvtsAccueil();
    void GenererEvtsDeBase(QVector<NoeudProbable*> &noeuds);
    void GenererPrincipalSelectionneurDEffet();

    Effet* TransformerEffetEnEffetMoisDeVie(Effet* effet); //  cet effet représente à lui seul un mois complet de vie, il veiilit de le personnage
};

#endif // GENVIEHUMAIN_H
