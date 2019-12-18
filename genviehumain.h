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
    static QString AGE;
    static QString C_LIBERTE; // par défaut le perso est libre. Si il est enfermé ou très restraint, le préciser dasn cette carac

    // evts important :
    static QString EFFET_SELECTEUR_ID;
    static QString EVT_SELECTEUR_ID;
    static Evt* EVT_SELECTEUR;
    static Effet* TransformerEffetEnEffetMoisDeVie(Effet* effet);
protected:
    // génère toutes les caracs qui peuvent être visualisées par le joueur (d'autres caracs peuvent être générées et invisibles n'importe quand dans l'aventure)
    virtual void GenererCaracs();
    virtual void GenererPersos();
    void GenererDataUnivers();
    /**
     * T doit hériter de GenerateurNoeudsProbables
     */
    template<class T >static void GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);

private:
    // génération des événement et effets de base
    void GenererEvtsAccueil();
    void GenererEvtsDeBase(QVector<NoeudProbable*> &noeuds);
    void GenererPrincipalSelectionneurDEffet();
 //  cet effet représente à lui seul un mois complet de vie, il veiilit de le personnage
};

#endif // GENVIEHUMAIN_H
