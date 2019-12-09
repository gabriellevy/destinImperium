#include "maison.h"
#include <QList>
#include <QString>
#include "../destinLib/aleatoire.h"
#include "socio_eco/classesociale.h"

// valeurs statiques
// caracs :
QString Maison::C_MAISON = "Maison";
// maisons "pauvres" et "moyennes"
QString Maison::VANSAAR = "Van Saar";
QString Maison::ORLOCK = "Orlock";
QString Maison::GOLIATH = "Goliath";
QString Maison::ESHER = "Esher";
QString Maison::DELAQUE = "Delaque";
QString Maison::CAWDOR = "Cawdor";

// maisons influentes et maîtres

Maison::Maison(QString id):m_Id(id)
{}

QString Maison::AssignerMaison(QString classeSociale, QString typeMonde)
{
    QList<QString> maisons = {};

    if ( typeMonde == Planete::PLANETE_RUCHE) {
        if ( classeSociale == ClasseSociale::PAUVRES ||
             classeSociale == ClasseSociale::CLASSE_MOYENNE)
        {
            maisons.push_back(Maison::VANSAAR);
            maisons.push_back(Maison::ORLOCK);
            maisons.push_back(Maison::GOLIATH);
            maisons.push_back(Maison::ESHER);
            maisons.push_back(Maison::DELAQUE);
            maisons.push_back(Maison::CAWDOR);
        }

    }
    if ( maisons.length() == 0 )
         maisons.push_back("");

    return maisons[Aleatoire::GetAl()->EntierInferieurA(maisons.length())];
}

QString Maison::GetImageAleatoire()
{
    QList<QString> imgs = {};
    if (m_Id == Maison::VANSAAR) {
        imgs.push_back(":/images/crime/VanSaar.PNG");
    }
    else if (m_Id == Maison::ORLOCK) {
        imgs.push_back(":/images/crime/Orlock.PNG");
    }
    else if (m_Id == Maison::GOLIATH) {
        imgs.push_back(":/images/crime/Goliath.PNG");
        imgs.push_back(":/images/crime/Goliath2.PNG");
    }
    else if (m_Id == Maison::ESHER) {
        imgs.push_back(":/images/crime/Esher.PNG");
    }
    else if (m_Id == Maison::DELAQUE) {
        imgs.push_back(":/images/crime/Delaque.PNG");
    }
    else if (m_Id == Maison::CAWDOR) {
        imgs.push_back(":/images/crime/Cawdor.PNG");
    }

    if ( imgs.length() == 0 )
         imgs.push_back(":/images/crime/gang.PNG");

    return imgs[Aleatoire::GetAl()->EntierInferieurA(imgs.length())];
}



